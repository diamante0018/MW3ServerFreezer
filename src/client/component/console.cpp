#include <std_include.hpp>
#include "../loader/component_loader.hpp"

#include <utils/hook.hpp>
#include <utils/thread.hpp>
#include <utils/flags.hpp>
#include <utils/concurrency.hpp>

#include "console.hpp"
#include "command.hpp"

namespace console {
namespace {
using message_queue = std::queue<std::string>;
utils::concurrency::container<message_queue> messages;

void dispatch_message(const std::string& message) {
  messages.access([&message](message_queue& msgs) { msgs.emplace(message); });
}

void append_text(const char* text) { dispatch_message(text); }
} // namespace

class component final : public component_interface {
public:
  component() {
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    (void)_pipe(this->handles_, 1024, _O_TEXT);
    (void)_dup2(this->handles_[1], 1);
    (void)_dup2(this->handles_[1], 2);
  }

  void post_start() override {
    this->terminate_runner_ = false;

    this->console_runner_ = utils::thread::create_named_thread(
        "Console IO", [this] { this->runner(); });
  }

  void post_unpack() override {
    utils::hook(0x446930, append_text, HOOK_JUMP).install()->quick();

    this->initialize();
  }

  void pre_destroy() override {
    this->terminate_runner_ = true;

    printf("\r\n");
    _flushall();

    if (this->console_runner_.joinable()) {
      this->console_runner_.join();
    }

    if (this->console_thread_.joinable()) {
      this->console_thread_.join();
    }

    _close(this->handles_[0]);
    _close(this->handles_[1]);

    messages.access([&](message_queue& msgs) { msgs = {}; });
  }

private:
  volatile bool console_initialized_ = false;
  volatile bool terminate_runner_ = false;

  std::thread console_runner_;
  std::thread console_thread_;

  int handles_[2]{};

  void initialize() {
    this->console_thread_ =
        utils::thread::create_named_thread("Console", [this] {
          if (!utils::flags::has_flag("noconsole")) {
            game::Sys_ShowConsole();
          }

          messages.access(
              [&](message_queue&) { this->console_initialized_ = true; });

          MSG msg;
          while (!this->terminate_runner_) {
            if (PeekMessageA(&msg, nullptr, NULL, NULL, PM_REMOVE)) {
              if (msg.message == WM_QUIT) {
                command::execute("quit", false);
                break;
              }

              TranslateMessage(&msg);
              DispatchMessageA(&msg);
            } else {
              this->log_messages();
              std::this_thread::sleep_for(1ms);
            }
          }
        });
  }

  void log_messages() const {
    if (this->console_initialized_ && !messages.get_raw().empty()) {
      std::queue<std::string> message_queue_copy;

      {
        messages.access([&](message_queue& msgs) {
          message_queue_copy = std::move(msgs);
          msgs = {};
        });
      }

      while (!message_queue_copy.empty()) {
        log_message(message_queue_copy.front());
        message_queue_copy.pop();
      }
    }

    fflush(stdout);
    fflush(stderr);
  }

  static void log_message(const std::string& message) {
    OutputDebugStringA(message.data());
    game::Conbuf_AppendText(message.data());
  }

  void runner() const {
    char buffer[1024];

    while (!this->terminate_runner_ && this->handles_[0]) {
      const auto len = _read(this->handles_[0], buffer, sizeof(buffer));
      if (len > 0) {
        dispatch_message(std::string(buffer, len));
      } else {
        std::this_thread::sleep_for(1ms);
      }
    }

    std::this_thread::yield();
  }
};

HWND get_window() { return *reinterpret_cast<HWND*>(0x5A86330); }

void print(std::string_view fmt, std::format_args&& args,
           const std::source_location& loc) {
#ifdef _DEBUG
  const auto msg = std::vformat(fmt, args);
  const auto line = std::format("Debug:\n    {}\nFile:    {}\nLine:    {}\n",
                                msg, loc.file_name(), loc.line());
#else
  const auto line = std::vformat(fmt, args) + "\n";
#endif

  dispatch_message(line);
}
} // namespace console

REGISTER_COMPONENT(console::component)
