#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include <utils/cryptography.hpp>

#include "network/network.hpp"

#include "crypto_key.hpp"
#include "key_catcher.hpp"

namespace rcon {
namespace {
utils::cryptography::ecc::key key;
std::string commands;
} // namespace

class component final : public component_interface {
public:
  void post_unpack() override {
    key = crypto_key::get();
    add_key_hooks();
    add_commands();
  }

private:
  static void add_key_hooks() {
    // Why commands don't work? I don't know!
    key_catcher::on_key_press(
        "7", []([[maybe_unused]] const game::LocalClientNum_t& local_client) {
          commands = "quit";
          network::send(game::localClientConnection->serverAddress,
                        "rcon_request");
        });
  }

  static void add_commands() {
    network::on_packet("rcon_authorization", [](const game::netadr_s& adr,
                                                const std::string& data) {
      const auto signed_msg = utils::cryptography::ecc::sign_message(key, data);

      proto::rcon::command info;
      info.set_commands(commands);
      info.set_signature(signed_msg);

      network::send(adr, "rcon_execute", info.SerializeAsString());
    });
  }
};
} // namespace rcon

REGISTER_COMPONENT(rcon::component)
