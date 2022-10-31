#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include <utils/hook.hpp>

#include "key_catcher.hpp"

namespace key_catcher {
namespace {
std::unordered_map<std::string, key_catcher::callback>& get_key_callbacks() {
  static std::unordered_map<std::string, key_catcher::callback> key_callbacks{};
  return key_callbacks;
}

void handle_key_event(game::LocalClientNum_t local_client, int key_id) {
  const auto result = VkKeyScanA(static_cast<CHAR>(key_id));
  const auto vk_key = LOBYTE(result);
  const auto& callbacks = get_key_callbacks();

  for (auto const& [key, value] : callbacks) {
    const auto game_vk_key = game::Key_StringToKeynum(key.data());
    if (static_cast<BYTE>(game_vk_key) == vk_key) {
      value(local_client);
      return;
    }
  }
}
} // namespace

void on_key_press(const std::string& command, const callback& callback) {
  get_key_callbacks()[command] = callback;
}

void cl_key_event_stub(game::LocalClientNum_t local_client, int key_id,
                       int a3) {
  handle_key_event(local_client, key_id);

  utils::hook::invoke<void>(0x4CD840, local_client, key_id, a3);
}

class component final : public component_interface {
public:
  void post_unpack() override {
    utils::hook(0x53CC70, cl_key_event_stub, HOOK_CALL).install()->quick();
  }
};
} // namespace key_catcher

REGISTER_COMPONENT(key_catcher::component)
