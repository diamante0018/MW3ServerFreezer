#include <std_include.hpp>
#include "../loader/component_loader.hpp"

#include <utils/hook.hpp>
#include <utils/string.hpp>

#include "key_catcher.hpp"
#include "command.hpp"
#include "console.hpp"

namespace cheats {
game::dvar_t* cl_EnableCheats;

void __declspec(naked) draw_red_box_stub() {
  __asm {
    push eax
    mov eax, cl_EnableCheats
    cmp byte ptr [eax + 0xC], 1
    pop eax

    je draw

    test byte ptr ds:0x8FF110, 0x10

    push 0x430568
    retn

  draw:
    push 0x43056A
    retn
  }
}

void __declspec(naked) blind_eye_check_stub() {
  __asm {
    push eax
    mov eax, cl_EnableCheats
    cmp byte ptr [eax + 0xC], 1
    pop eax

    je draw

    test byte ptr [esi], 0x20
    jnz skip_because_blindeye

    jmp draw

  skip_because_blindeye:
    push 0x5AA5A2
    retn

  draw:
    push 0x5AA529
    retn
  }
}

class component final : public component_interface {
public:
  void post_unpack() override {
    cl_EnableCheats = game::Dvar_RegisterBool(
        "cl_EnableCheats", false, game::DVAR_NONE, "Enable FoF wallhack");

    utils::hook(0x430561, draw_red_box_stub, HOOK_JUMP).install()->quick();
    utils::hook::nop(0x430566, 2);

    utils::hook(0x5AA524, blind_eye_check_stub, HOOK_JUMP).install()->quick();

    add_cheat_commands();
  }

private:
  static void add_cheat_commands() {
    key_catcher::on_key_press(
        "Z", []([[maybe_unused]] const game::LocalClientNum_t& local_client) {
          game::Dvar_SetBool(cl_EnableCheats, true);
          console::info("Enabled cl_EnableCheats");
        });

    key_catcher::on_key_press(
        "X", []([[maybe_unused]] const game::LocalClientNum_t& local_client) {
          game::Dvar_SetBool(cl_EnableCheats, false);
          console::info("Disabled cl_EnableCheats");
        });

    key_catcher::on_key_press(
        "Y", []([[maybe_unused]] const game::LocalClientNum_t& local_client) {
          const auto* cmd =
              utils::string::va("cmd mr %i 2 allies", *game::serverId);
          command::execute(cmd, true);
          console::info("Executed: {}", cmd);
        });

    key_catcher::on_key_press(
        "8", []([[maybe_unused]] const game::LocalClientNum_t& local_client) {
          const auto* cmd =
              utils::string::va("cmd mr %i -1 endround", *game::serverId);
          command::execute(cmd, true);
          console::info("Executed: {}", cmd);
        });
  }
};
} // namespace cheats

REGISTER_COMPONENT(cheats::component)
