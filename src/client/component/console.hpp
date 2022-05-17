#pragma once

namespace console {

#ifdef _DEBUG
void console_print(const std::source_location& location, std::string_view fmt,
                   std::format_args&& args);
#else
void console_print(std::string_view fmt, std::format_args&& args);
#endif

static inline void log(std::string_view fmt, std::format_args&& args) {
#ifdef _DEBUG
  console_print(std::source_location::current(), fmt, std::move(args));
#else
  console_print(fmt, std::move(args));
#endif
}

static inline void print(std::string_view fmt) {
  log(fmt, std::make_format_args(0));
}

template <typename... Args>
static inline void print(std::string_view fmt, Args&&... args) {
  log(fmt, std::make_format_args(args...));
}
} // namespace console
