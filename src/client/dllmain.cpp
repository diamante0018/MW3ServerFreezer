#include "std_include.hpp"
#include "loader/component_loader.hpp"

BOOL APIENTRY DllMain(HMODULE /*hModule*/, DWORD ul_reason_for_call,
                      LPVOID /*lpReserved*/
) {
  if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
    std::srand(uint32_t(time(nullptr)));
    component_loader::post_start();
    component_loader::post_unpack();
  }

  else if (ul_reason_for_call == DLL_PROCESS_DETACH) {
    component_loader::pre_destroy();
  }

  return TRUE;
}
