#pragma once

#define DLL_EXPORT extern "C" __declspec(dllexport)

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#include <corecrt_io.h>
#include <fcntl.h>

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <mutex>
#include <string>
#include <string_view>
#include <source_location>
#include <queue>

#pragma comment(lib, "ntdll.lib")
#pragma comment(lib, "ws2_32.lib")

using namespace std::literals;

// clang-format off
#include "game/structs.hpp"
#include "game/game.hpp"
// clang-format on
