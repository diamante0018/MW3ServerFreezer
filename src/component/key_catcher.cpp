#include <stdinc.hpp>

#include <loader/component_loader.hpp>
#include <utils/hook.hpp>

#include "key_catcher.hpp"

namespace key_catcher
{
	utils::hook::detour cl_key_event_hook;

	namespace
	{
		std::unordered_map<std::string, callback>& get_key_callbacks()
		{
			static std::unordered_map<std::string, callback> key_callbacks{};
			return key_callbacks;
		}

		void handle_key_event(game::LocalClientNum_t localClient, int keyID)
		{
			auto result = VkKeyScanA(static_cast<CHAR>(keyID));
			auto VkKey = LOBYTE(result);
			auto& callbacks = get_key_callbacks();

			for (auto const& i : callbacks)
			{
				auto gameVkKey = game::Key_StringToKeynum(i.first.data());
				if (static_cast<BYTE>(gameVkKey) == VkKey)
				{
					i.second(localClient);
					return;
				}
			}
		}
	}

	void on_key_press(const std::string& command, const callback& callback)
	{
		get_key_callbacks()[command] = callback;
	}

	void cl_key_event_stub(game::LocalClientNum_t localClient, int keyID, int a3)
	{
		handle_key_event(localClient, keyID);

		cl_key_event_hook.invoke<void>(localClient, keyID, a3);
	}

	class component final : public component_interface
	{
	public:
		void post_unpack() override
		{
			cl_key_event_hook.create(0x4CD840, &cl_key_event_stub);
		}

		void pre_destroy() override
		{
			cl_key_event_hook.clear();
		}
	};
}

REGISTER_COMPONENT(key_catcher::component)
