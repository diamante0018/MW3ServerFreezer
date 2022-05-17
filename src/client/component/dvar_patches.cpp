#include <std_include.hpp>
#include "../loader/component_loader.hpp"

#include <utils/hook.hpp>

#include "console.hpp"

namespace dvar_patches {
void dvar_set_from_string_by_name_stub(const char* dvar_name,
                                       const char* string) {
  console::print("Server tried setting {} with value {}", dvar_name, string);
}

class component final : public component_interface {
public:
  void post_unpack() override {
    utils::hook(0x59C0EF, dvar_set_from_string_by_name_stub, HOOK_CALL)
        .install()
        ->quick();
  }
};
} // namespace dvar_patches

REGISTER_COMPONENT(dvar_patches::component)