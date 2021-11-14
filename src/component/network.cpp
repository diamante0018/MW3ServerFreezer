#include <stdinc.hpp>

#include <loader/component_loader.hpp>
#include <utils/hook.hpp>
#include <utils/string.hpp>

#include "network.hpp"
#include "command.hpp"

namespace network
{
	namespace
	{
		std::unordered_map<std::string, callback>& get_callbacks()
		{
			static std::unordered_map<std::string, callback> network_callbacks{};
			return network_callbacks;
		}

		bool handle_command(game::netadr_s* address, const char* command, game::msg_t* message)
		{
			const auto cmd_string = utils::string::to_lower(command);
			auto& callbacks = get_callbacks();
			const auto handler = callbacks.find(cmd_string);

			if (handler == callbacks.end())
			{
				return false;
			}

			const auto offset = cmd_string.size() + 5;
			const std::string_view data(message->data + offset, message->cursize - offset);

			handler->second(*address, data);
			return true;
		}
	}

	int packet_interception_handler(game::netadr_s* from, const char* command, game::msg_t* message)
	{
		if (!handle_command(from, command, message))
		{
			return reinterpret_cast<int (*)(game::netadr_s*, const char*, game::msg_t*)>(0x525730)(from, command, message);
		}

		return TRUE;
	}

	void on_packet(const std::string& command, const callback& callback)
	{
		get_callbacks()[utils::string::to_lower(command)] = callback;
	}

	class component final : public component_interface
	{
	public:
		void post_unpack() override
		{
			add_network_commands();

			utils::hook::call(0x5B27E1, packet_interception_handler);
		}

	private:
		static void add_network_commands()
		{
			on_packet("naughty_reply", [](const game::netadr_s&, const std::string_view&)
			{
				command::execute("quit_meme");
			});
		}
	};
}

REGISTER_COMPONENT(network::component)
