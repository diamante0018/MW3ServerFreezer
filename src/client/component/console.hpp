#pragma once

namespace console {
HWND get_window();

#ifdef _DEBUG
void print(const std::source_location& location,

           std::string_view fmt, std::format_args&& args);
#else
void print(std::string_view fmt, std::format_args&& args);
#endif

static inline void console_log(std::string_view fmt, std::format_args&& args) {
#ifdef _DEBUG
  print(std::source_location::current(), fmt, std::move(args));
#else
  print(fmt, std::move(args));
#endif
}

template <typename... Args>
static inline void info(std::string_view fmt, Args&&... args) {
  console_log(fmt, std::make_format_args(args...));
}

static inline void info(std::string_view fmt) {
  console_log(fmt, std::make_format_args(0));
}
} // namespace console
