#include <std_include.hpp>

namespace game {
ScreenPlacement* ScrPlace_GetUnsafeFullPlacement() {
  return scrPlaceFullUnsafe;
}

void __declspec(naked) Dvar_SetVariant(dvar_t* /*dvar*/, DvarValue /*value*/,
                                       DvarSetSource /*source*/) {
  static DWORD func = 0x649170;

  __asm {
    pushad

    mov eax, [esp + 0x20 + 0x4] // dvar
    push [esp + 0x20 + 0x18] // source
    push [esp + 0x20 + 0x18] // value
    push [esp + 0x20 + 0x18] // value
    push [esp + 0x20 + 0x18] // value
    push [esp + 0x20 + 0x18] // value
    call func
    add esp, 0x14

    popad
    ret
  }
}
} // namespace game
