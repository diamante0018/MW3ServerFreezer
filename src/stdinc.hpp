#pragma once

#define DLL_EXPORT extern "C" __declspec(dllexport)

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <WinSock2.h>

#include <vector>
#include <cassert>
#include <mutex>
#include <string>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_set>
#include <map>
#include <vector>

#pragma comment(lib, "ntdll.lib")

using namespace std::literals;

#include "game/structs.hpp"
#include "game/game.hpp"
