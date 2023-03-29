#include "std_include.hpp"
#include "loader/component_loader.hpp"

namespace {
LONG WINAPI exception_handler(PEXCEPTION_POINTERS exception_info) {
  if (exception_info->ExceptionRecord->ExceptionCode == 0x406D1388) {
    return EXCEPTION_CONTINUE_EXECUTION;
  }

  if (exception_info->ExceptionRecord->ExceptionCode < 0x80000000 ||
      exception_info->ExceptionRecord->ExceptionCode == 0xE06D7363) {
    return EXCEPTION_CONTINUE_SEARCH;
  }

  MINIDUMP_EXCEPTION_INFORMATION exception_information = {
      GetCurrentThreadId(), exception_info, FALSE};
  const auto type = MiniDumpIgnoreInaccessibleMemory //
                    | MiniDumpWithHandleData         //
                    | MiniDumpScanMemory             //
                    | MiniDumpWithProcessThreadData  //
                    | MiniDumpWithFullMemoryInfo     //
                    | MiniDumpWithThreadInfo;

  const auto file_name = std::format("minidumps\\mw3-server-freezer_{}.dmp",
                                     game::Sys_Milliseconds());
  const auto file_handle = CreateFileA(
      file_name.data(), GENERIC_WRITE | GENERIC_READ,
      FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, CREATE_ALWAYS,
      FILE_ATTRIBUTE_TEMPORARY | FILE_FLAG_DELETE_ON_CLOSE, nullptr);

  if (!MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),
                         file_handle, static_cast<MINIDUMP_TYPE>(type),
                         &exception_information, nullptr, nullptr)) {
    char buf[4096]{};
    sprintf_s(buf, "An exception 0x%08X occurred at location 0x%p\n",
              exception_info->ExceptionRecord->ExceptionCode,
              exception_info->ExceptionRecord->ExceptionAddress);
    MessageBoxA(nullptr, buf, "Fatal Error", MB_ICONERROR);
  }

  CloseHandle(file_handle);
  TerminateProcess(GetCurrentProcess(),
                   exception_info->ExceptionRecord->ExceptionCode);

  return EXCEPTION_CONTINUE_SEARCH;
}
} // namespace

BOOL APIENTRY DllMain(HMODULE /*hModule*/, DWORD ul_reason_for_call,
                      LPVOID /*lpReserved*/
) {
  if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
    AddVectoredExceptionHandler(0, exception_handler);
    SetProcessDEPPolicy(PROCESS_DEP_ENABLE);

    std::srand(std::uint32_t(time(nullptr)));

    component_loader::post_start();
    component_loader::post_unpack();
  }

  else if (ul_reason_for_call == DLL_PROCESS_DETACH) {
    component_loader::pre_destroy();
    google::protobuf::ShutdownProtobufLibrary();
  }

  return TRUE;
}
