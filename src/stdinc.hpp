#pragma once

#define DLL_EXPORT extern "C" __declspec(dllexport)

#define WIN32_LEAN_AND_MEAN

#include <WinSock2.h>
#include <windows.h>

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <mutex>
#include <string>

#pragma comment(lib, "ntdll.lib")

using namespace std::literals;

// clang-format off
#include "game/structs.hpp"
#include "game/game.hpp"
// clang-format on
