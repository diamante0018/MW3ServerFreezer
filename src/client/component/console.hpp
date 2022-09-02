#pragma once

#include <format>

namespace console {
HWND get_window();

void print(std::string_view fmt, std::format_args&& args,
           const std::source_location& loc);

template <typename... Args> class info {
public:
  info(std::string_view fmt, const Args&... args,
       const std::source_location& loc = std::source_location::current()) {
    print(fmt, std::make_format_args(args...), loc);
  }
};

template <typename... Args>
info(std::string_view fmt, const Args&... args) -> info<Args...>;
} // namespace console
