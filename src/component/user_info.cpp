#include <stdinc.hpp>

#include <loader/component_loader.hpp>
#include "utils/hook.hpp"
#include "utils/info_string.hpp"
#include "utils/string.hpp"

#include "scheduler.hpp"

namespace user_info
{
	namespace
	{
		int a1 = 0;
		void cl_check_user_info(int _a1, int force)
		{
			a1 = _a1;

			if (*game::connectionState <= game::connstate_t::CA_CHALLENGING)
				return;

			if (game::cl_paused->current.enabled && !force)
				return;

			const std::string infoString = game::Dvar_InfoString(_a1, 0x200);
			utils::info_string info(infoString);

			const auto colorCode = rand() % 10;

			char numbers[_MAX_U64TOSTR_BASE2_COUNT];
			char name[16];

			_itoa_s(rand() % 10000, numbers, sizeof(numbers), 10);
			_snprintf_s(name, sizeof(name), _TRUNCATE, "^%d%s", colorCode, numbers);

			info.set("name", name);

			info.set("ec_usingTag", "1");
			info.set("ec_TagText", utils::string::va("^%dGG", colorCode));

			char bigTitle[_MAX_U64TOSTR_BASE2_COUNT];
			_itoa_s(rand() % 512, bigTitle, sizeof(bigTitle), 10);

			info.set("ec_TitleBg", bigTitle);

			game::CL_AddReliableCommand(_a1, utils::string::va("userinfo \"%s\"", info.build().data()));
		}

		__declspec(naked) void cl_check_user_info_stub()
		{
			__asm
			{
				pushad

				push 0
				push esi
				call cl_check_user_info
				add esp, 8

				popad
				ret
			}
		}
	}

	class component final : public component_interface
	{
	public:
		void post_unpack() override
		{
			utils::hook::call(0x41CA53, cl_check_user_info_stub);

			scheduler::loop([]
			{
				cl_check_user_info(a1, TRUE);
			}, scheduler::pipeline::client, 4s);
		}
	};
}

REGISTER_COMPONENT(user_info::component)
