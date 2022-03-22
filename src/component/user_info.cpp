#include <stdinc.hpp>

#include <loader/component_loader.hpp>

#include <utils/hook.hpp>
#include <utils/info_string.hpp>
#include <utils/string.hpp>

#include "scheduler.hpp"

namespace user_info {
namespace {
int a1 = 0;
void cl_check_user_info(int _a1, const int force) {
  a1 = _a1;

  if (*game::connectionState <= game::connstate_t::CA_CHALLENGING)
    return;

  if (game::cl_paused->current.enabled && !force)
    return;

  const std::string info_string = game::Dvar_InfoString(_a1, 0x200);
  utils::info_string info(info_string);

  const auto color_code = std::rand() % 10;

  char name[16];

  const auto numbers = std::to_string(std::rand() % 10000);
  _snprintf_s(name, sizeof(name), _TRUNCATE, "^%d%s", color_code,
              numbers.data());

  info.set("name", name);

  info.set("ec_usingTag", "1");
  info.set("ec_TagText", utils::string::va("^%dGG", color_code));

  const auto big_title = std::to_string(std::rand() % 512);
  info.set("ec_TitleBg", big_title);

  game::CL_AddReliableCommand(
      _a1, utils::string::va("userinfo \"%s\"", info.build().data()));
}

__declspec(naked) void cl_check_user_info_stub() {
  __asm {
    pushad

    push 0
    push esi
    call cl_check_user_info
    add esp, 8

    popad
    ret
  }
}
} // namespace

class component final : public component_interface {
public:
  void post_unpack() override {
    utils::hook::call(0x41CA53, cl_check_user_info_stub);

    scheduler::loop([] { cl_check_user_info(a1, TRUE); },
                    scheduler::pipeline::client, 4s);
  }
};
} // namespace user_info

REGISTER_COMPONENT(user_info::component)
