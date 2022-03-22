#include <stdinc.hpp>

#include <loader/component_loader.hpp>
#include <utils/hook.hpp>
#include <utils/string.hpp>

#include "key_catcher.hpp"
#include "command.hpp"

namespace cheats
{
  game::dvar_t* cl_EnableCheats;

  __declspec(naked) void draw_red_box_stub()
  {
    __asm {
			push eax
			mov eax, cl_EnableCheats
			cmp byte ptr [eax + 12], 1
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

  __declspec(naked) void blind_eye_check_stub()
  {
    __asm {
			push eax
			mov eax, cl_EnableCheats
			cmp byte ptr [eax + 12], 1
			pop eax

			je draw

			test byte ptr [esi], 0x20
			jnz skip_because_blindeye

			jmp draw

		skip_because_blindeye:
			push 0x5AA5A2
			retn

		draw:
			push 0x05AA529
			retn
    }
  }

  class component final : public component_interface
  {
   public:
    void post_unpack() override
    {
      cl_EnableCheats = game::Dvar_RegisterBool(
          "cl_EnableCheats", false, game::DVAR_NONE, "Enable FoF wallhack");

      utils::hook::jump(0x430561, draw_red_box_stub);
      utils::hook::nop(0x430566, 2);

      utils::hook::jump(0x5AA524, blind_eye_check_stub);

      add_cheat_commands();
    }

   private:
    static void add_cheat_commands()
    {
      key_catcher::on_key_press(
          "Z",
          []([[maybe_unused]] const game::LocalClientNum_t& local_client)
          {
            game::Dvar_SetBool(cl_EnableCheats, true);
          });

      key_catcher::on_key_press(
          "X",
          []([[maybe_unused]] const game::LocalClientNum_t& local_client)
          {
            game::Dvar_SetBool(cl_EnableCheats, false);
          });

      key_catcher::on_key_press(
          "Y",
          []([[maybe_unused]] const game::LocalClientNum_t& local_client)
          {
            command::execute(
                utils::string::va("cmd mr %i 2 allies", *game::serverId), true);
          });

      key_catcher::on_key_press(
          "8",
          []([[maybe_unused]] const game::LocalClientNum_t& local_client)
          {
            command::execute(
                utils::string::va("cmd mr %i -1 endround", *game::serverId),
                true);
          });
    }
  };
} // namespace cheats

REGISTER_COMPONENT(cheats::component)
