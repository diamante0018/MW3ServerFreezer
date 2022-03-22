#include <stdinc.hpp>
#include <loader/component_loader.hpp>

#include <utils/hook.hpp>

namespace remove_hooks
{
  class component final : public component_interface
  {
   public:
    void post_unpack() override
    {
      remove_tekno_hooks();
    }

   private:
    static void remove_tekno_hooks()
    {
      utils::hook::set<BYTE>(0x4E3D42, 0xE8);
      utils::hook::set<BYTE>(0x4E3D43, 0xA9);
      utils::hook::set<BYTE>(0x4E3D44, 0x25);
      utils::hook::set<BYTE>(0x4E3D45, 0xFE);
      utils::hook::set<BYTE>(0x4E3D46, 0xFF);

      utils::hook::set<BYTE>(0x6EA960, 0x55);
      utils::hook::set<BYTE>(0x6EA961, 0x8B);
      utils::hook::set<BYTE>(0x6EA962, 0xEC);
      utils::hook::set<BYTE>(0x6EA963, 0x81);
      utils::hook::set<BYTE>(0x6EA964, 0xEC);
    }
  };
} // namespace remove_hooks

REGISTER_COMPONENT(remove_hooks::component)
