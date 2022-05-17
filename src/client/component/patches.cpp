#include <std_include.hpp>
#include "../loader/component_loader.hpp"

#include <utils/hook.hpp>

namespace patches {
namespace {
constexpr auto max_fps = 125; // Meme

void __declspec(naked) get_com_max_fps() {
  __asm {
    mov esi, max_fps

    push 0x4E4716
    retn
  }
}
} // namespace

class component final : public component_interface {
  void post_unpack() override {
    utils::hook(0x4E470D, get_com_max_fps, HOOK_JUMP).install()->quick();
    utils::hook::nop(0x4E4712, 4);
  }
};
} // namespace patches

REGISTER_COMPONENT(patches::component)
