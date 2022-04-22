#include <std_include.hpp>
#include "../loader/component_loader.hpp"

#include <utils/hook.hpp>

namespace dvar_patches {
void dvar_set_from_string_by_name_stub(const char* /*dvarName*/,
                                       const char* /*string*/) {}

class component final : public component_interface {
public:
  void post_unpack() override {
    utils::hook::call(0x59C0EF, dvar_set_from_string_by_name_stub);
  }
};
} // namespace dvar_patches

REGISTER_COMPONENT(dvar_patches::component)