#include <std_include.hpp>
#include "../loader/component_loader.hpp"

#include <utils/thread.hpp>

namespace console {
namespace {
std::thread thread;

LRESULT __stdcall sys_start_console(HWND, UINT, WPARAM, LPARAM) {
  game::Sys_ShowConsole();
  return 0;
}

void console_unlock() {
  const auto callback = SetWindowLongA(
      *game::g_wv_hWnd, GWL_WNDPROC, reinterpret_cast<LONG>(sys_start_console));

  SendMessageA(*game::g_wv_hWnd, WM_QUIT, 0, 0);
  SetWindowLongA(*game::g_wv_hWnd, GWL_WNDPROC, callback);
}

void show_console() {
  if (*game::s_wcd_hWnd) {
    ShowWindow(*game::s_wcd_hWnd, SW_SHOW);
  }
}
} // namespace

class component final : public component_interface {
public:
  void post_unpack() override {
    thread = utils::thread::create_named_thread("Console Thread", []() {
      console_unlock();
      show_console();
    });
  }

  void pre_destroy() override {
    if (thread.joinable()) {
      thread.join();
    }
  }
};
} // namespace console

REGISTER_COMPONENT(console::component)
