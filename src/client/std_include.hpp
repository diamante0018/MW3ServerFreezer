#pragma once

#define DLL_EXPORT extern "C" __declspec(dllexport)

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#include <DbgHelp.h>

#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstring>
#include <format>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <source_location>
#include <string>
#include <string_view>

#pragma comment(lib, "ntdll.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "dbghelp.lib")

using namespace std::literals;

#include <proto/rcon.pb.h>

// clang-format off
#include "game/structs.hpp"
#include "game/game.hpp"
// clang-format on
