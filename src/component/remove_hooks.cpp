#include <stdinc.hpp>

#include <loader/component_loader.hpp>
#include <utils/hook.hpp>

namespace remove_hooks
{
	class component final : public component_interface
	{
	public:
		void post_unpack() override
		{
			remove_tekno_hooks();
		}

	private:
		static void remove_tekno_hooks()
		{
			utils::hook::set<BYTE>(0x4E3D42, 0xE8);
			utils::hook::set<BYTE>(0x4E3D43, 0xA9);
			utils::hook::set<BYTE>(0x4E3D44, 0x25);
			utils::hook::set<BYTE>(0x4E3D45, 0xFE);
			utils::hook::set<BYTE>(0x4E3D46, 0xFF);
		}
	};
}

REGISTER_COMPONENT(remove_hooks::component)