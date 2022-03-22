#pragma once

namespace network
{
  using callback =
      std::function<void(const game::netadr_s&, const std::string_view&)>;

  void on_packet(const std::string& command, const callback& callback);
} // namespace network
