#include <stdinc.hpp>

#include <loader/component_loader.hpp>

namespace console
{
  namespace
  {
    std::thread thread;
    std::thread::id async_thread_id;

    LRESULT __stdcall sys_start_console(HWND, UINT, WPARAM, LPARAM)
    {
      game::Sys_ShowConsole();
      return 0;
    }

    void console_unlock()
    {
      const auto callback =
          SetWindowLongA(*game::g_wv_hWnd,
                         GWL_WNDPROC,
                         reinterpret_cast<LONG>(sys_start_console));

      SendMessageA(*game::g_wv_hWnd, WM_QUIT, 0, 0);
      SetWindowLongA(*game::g_wv_hWnd, GWL_WNDPROC, callback);
    }

    void show_console()
    {
      if (*game::s_wcd_hWnd)
      {
        ShowWindow(*game::s_wcd_hWnd, SW_SHOW);
      }
    }
  } // namespace

  class component final : public component_interface
  {
   public:
    void post_unpack() override
    {
      thread = std::thread(
          []()
          {
            console_unlock();
            show_console();
          });

      async_thread_id = thread.get_id();
    }
  };
} // namespace console

REGISTER_COMPONENT(console::component)