#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include <utils/hook.hpp>

#include "console.hpp"

namespace dvar_patches {
namespace {
void dvar_set_from_string_by_name_stub(const char* dvar_name,
                                       const char* string) {
  console::info("Server tried setting '{}' with value '{}'", dvar_name, string);
}

void dvar_override_cheat_protection_stub(bool /*cheat_override*/) {
  *game::isCheatOverride = true;
}
} // namespace

class component final : public component_interface {
public:
  void post_unpack() override {
    utils::hook(0x59C0EF, HOOK_CAST(dvar_set_from_string_by_name_stub),
                HOOK_CALL)
        .install() // hook*
        ->quick();

    *game::isCheatOverride = true;
    utils::hook(0x482CC0, HOOK_CAST(dvar_override_cheat_protection_stub),
                HOOK_JUMP)
        .install() // hook*
        ->quick();

    // Remove read/write protection
    utils::hook::nop(0x649227, 6);
  }
};
} // namespace dvar_patches

REGISTER_COMPONENT(dvar_patches::component)