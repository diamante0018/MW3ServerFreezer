#pragma once

namespace network {
void send(const game::netadr_s& address, const std::string& command,
          const std::string& data = {}, char separator = ' ');
void send_data(const game::netadr_s& address, const std::string& data);

using callback = std::function<void(const game::netadr_s&, const std::string&)>;
void on_packet(const std::string& command, const callback& callback);

const char* net_adr_to_string(const game::netadr_s& a);
} // namespace network
