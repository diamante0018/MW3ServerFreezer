#pragma once

namespace key_catcher
{
	using callback = std::function<void(game::LocalClientNum_t& localClient)>;

	void on_key_press(const std::string& command, const callback& callback);
}
