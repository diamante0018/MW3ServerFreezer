#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include <utils/hook.hpp>

#include "console.hpp"

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

void bd_log_message_stub(const game::bdLogMessageType /*type*/,
                         const char* const /*base_channel*/,
                         const char* const /*channel*/,
                         const char* const /*file*/,
                         const char* const /*function*/,
                         const unsigned int /*line*/, const char* format, ...) {
  char buf[4096] = {0};
  va_list ap;
  va_start(ap, format);
  vsnprintf_s(buf, _TRUNCATE, format, ap);
  va_end(ap);

  console::info("{}", buf);
}
} // namespace

class component final : public component_interface {
  void post_unpack() override {
    utils::hook(0x4E470D, get_com_max_fps, HOOK_JUMP).install()->quick();
    utils::hook::nop(0x4E4712, 4);

    utils::hook(0x6EA960, HOOK_CAST(bd_log_message_stub), HOOK_JUMP)
        .install() // hook*
        ->quick();

    // Another meme
    static const auto* my_cg_fov = game::Dvar_RegisterFloat(
        "my_cg_fov", 100.0f, 65.0f, 160.0f, game::DVAR_INIT, "");
    utils::hook::set<const game::dvar_t**>(0x54BAF8, &my_cg_fov);
    utils::hook::set<const game::dvar_t**>(0x54BC35, &my_cg_fov);
    utils::hook::set<const game::dvar_t**>(0x5711C4, &my_cg_fov);
  }
};
} // namespace patches

REGISTER_COMPONENT(patches::component)
