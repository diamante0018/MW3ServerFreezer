#pragma once

namespace key_catcher {
using callback = std::function<void(game::LocalClientNum_t& local_client)>;

void on_key_press(const std::string& command, const callback& callback);
} // namespace key_catcher
