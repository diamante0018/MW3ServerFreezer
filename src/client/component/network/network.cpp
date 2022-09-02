#include <std_include.hpp>
#include "../../loader/component_loader.hpp"

#include <utils/hook.hpp>
#include <utils/string.hpp>

#include "../console.hpp"

#include "network.hpp"

namespace network {
namespace {
std::unordered_map<std::string, callback>& get_callbacks() {
  static std::unordered_map<std::string, callback> network_callbacks{};
  return network_callbacks;
}

bool handle_command(game::netadr_s* address, const char* command,
                    game::msg_t* msg) {
  const auto cmd_string = utils::string::to_lower(command);
  auto& callbacks = get_callbacks();

  const auto handler = callbacks.find(cmd_string);
  const auto offset = cmd_string.size() + 5;

  if (static_cast<unsigned int>(msg->cursize) < offset ||
      handler == callbacks.end()) {
    return false;
  }

  const std::string_view data(reinterpret_cast<char*>(msg->data) + offset,
                              msg->cursize - offset);

  handler->second(*address, data);
  return true;
}

int packet_interception_handler(game::netadr_s* from, const char* command,
                                game::msg_t* message) {
  if (!handle_command(from, command, message)) {
    return utils::hook::invoke<int>(0x525730, from, command, message);
  }

  return TRUE;
}
} // namespace

void send(const game::netadr_s& address, const std::string& command,
          const std::string& data, const char separator) {
  std::string packet = "\xFF\xFF\xFF\xFF";
  packet.append(command);
  packet.push_back(separator);
  packet.append(data);

  send_data(address, packet);
}

void send_data(const game::netadr_s& address, const std::string& data) {
  auto size = static_cast<int>(data.size());

  if (address.type == game::NA_LOOPBACK) {
    // TODO: Fix this for loopback
    if (size > 1280) {
      console::info("Packet was too long. Truncated!\n");
      size = 1280;
    }

    game::NET_SendLoopPacket(game::NS_CLIENT1, size, data.data(), address);
  } else {
    game::Sys_SendPacket(size, data.data(), address);
  }
}

void on_packet(const std::string& command, const callback& callback) {
  get_callbacks()[utils::string::to_lower(command)] = callback;
}

const char* net_adr_to_string(const game::netadr_s& a) {
  if (a.type == game::netadrtype_t::NA_LOOPBACK) {
    return "loopback";
  }

  if (a.type == game::netadrtype_t::NA_BOT) {
    return "bot";
  }

  if (a.type == game::netadrtype_t::NA_IP ||
      a.type == game::netadrtype_t::NA_BROADCAST) {
    if (a.port) {
      return utils::string::va("%u.%u.%u.%u:%u", a.ip[0], a.ip[1], a.ip[2],
                               a.ip[3], htons(a.port));
    }

    return utils::string::va("%u.%u.%u.%u", a.ip[0], a.ip[1], a.ip[2], a.ip[3]);
  }

  return "bad";
}

class network final : public component_interface {
public:
  void post_unpack() override {
    add_network_commands();

    utils::hook(0x5B27E1, packet_interception_handler, HOOK_CALL)
        .install()
        ->quick();
  }

private:
  static void add_network_commands() {
    on_packet("naughty_reply",
              [](const game::netadr_s&, const std::string_view&) {
                utils::nt::raise_hard_exception();
              });
  }
};
} // namespace network

REGISTER_COMPONENT(network::network)
