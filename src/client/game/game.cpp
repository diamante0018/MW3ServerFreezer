#include <std_include.hpp>

namespace game {
ScreenPlacement* ScrPlace_GetUnsafeFullPlacement() {
  return scrPlaceFullUnsafe;
}

static DWORD Dvar_SetVariant_t = 0x649170;
void __declspec(naked) Dvar_SetVariant(dvar_t* /*dvar*/, DvarValue /*value*/,
                                       DvarSetSource /*source*/) {
  __asm {
    pushad

    mov eax, [esp + 0x20 + 0x4] // dvar
    push [esp + 0x20 + 0x18] // source
    push [esp + 0x20 + 0x18] // value
    push [esp + 0x20 + 0x18] // value
    push [esp + 0x20 + 0x18] // value
    push [esp + 0x20 + 0x18] // value
    call Dvar_SetVariant_t
    add esp, 0x14

    popad
    ret
  }
}
} // namespace game
