#include <std_include.hpp>
#include "../loader/component_loader.hpp"

#include <utils/hook.hpp>

namespace remove_hooks {
namespace {
int msg_read_bits_compress_check_sv(const char* from, char* to, int size) {
  static char buffer[0x8000];

  if (size > 0x800) {
    return 0;
  }

  size = game::MSG_ReadBitsCompress(from, buffer, size);

  if (size > 0x800) {
    return 0;
  }

  std::memcpy(to, buffer, size);
  return size;
}

int msg_read_bits_compress_check_cl(const char* from, char* to, int size) {
  static char buffer[0x100000];

  if (size > 0x20000) {
    return 0;
  }

  size = game::MSG_ReadBitsCompress(from, buffer, size);

  if (size > 0x20000) {
    return 0;
  }

  std::memcpy(to, buffer, size);
  return size;
}
} // namespace

class component final : public component_interface {
public:
  void post_start() override { remove_tekno_hooks(); }

  void post_unpack() override {
    utils::hook(0x4E3D42, msg_read_bits_compress_check_sv, HOOK_CALL)
        .install()
        ->quick();
    utils::hook(0x4A9F56, msg_read_bits_compress_check_cl, HOOK_CALL)
        .install()
        ->quick();
  }

private:
  static void remove_tekno_hooks() {
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
