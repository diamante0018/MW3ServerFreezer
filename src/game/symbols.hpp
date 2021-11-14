#pragma once

#define WEAK __declspec(selectany)

namespace game
{
	// Functions
	WEAK symbol<const char*(int index)> ConcatArgs{0x539060};
	WEAK symbol<void(LocalClientNum_t, const char* text)> Cbuf_AddText{0x4C1030};
	WEAK symbol<void(LocalClientNum_t, const char* text)> Cbuf_InsertText{0x429920};
	WEAK symbol<void(const char* cmdName, void(), cmd_function_t* cmd)> Cmd_AddCommandInternal{0x537E70};
	WEAK symbol<void(LocalClientNum_t, int, const char* text)> Cmd_ExecuteSingleCommand{0x4EB8F0};
	WEAK symbol<void(const char* cmdName)> Cmd_RemoveCommand{0x4EAF30};
	WEAK symbol<const char*(int index)> Cmd_Argv{0x5580E0};

	WEAK symbol<dvar_t*(const char*)> Dvar_FindVar{0x4EBB50};
	WEAK symbol<dvar_t*(const char* dvarName, int value, int min, int max, unsigned __int16 flags, const char* desc)>
		Dvar_RegisterInt{0x50C760};
	WEAK symbol<dvar_t*(const char* dvarName, bool value, unsigned __int16 flags, const char* description)>
		Dvar_RegisterBool{0x4A3300};
	WEAK symbol<dvar_t*(const char* dvarName, const char* value, unsigned __int16 flags, const char* description)>
		Dvar_RegisterString{0x4157E0};
	WEAK symbol<dvar_t*(const char* dvarName, float value, float min, float max, unsigned __int16 flags, const char* description)>
		Dvar_RegisterFloat{0x4A5CF0};

	WEAK symbol<int(const char* cmd)> Key_GetBindingForCmd{0x47D300};
	WEAK symbol<int(const char* keyAsText)> Key_StringToKeynum{0x50A710}; // Virtual-Key Code
	WEAK symbol<void(LocalClientNum_t, int, int)> Key_SetBinding{0x50B770};

	WEAK symbol<void(int arg, char* buffer, int bufferLength)> SV_Cmd_ArgvBuffer{0x4F6B00};

	WEAK symbol<bool(netsrc_t, game::netadr_s dest, const char* message)> NET_OutOfBandPrint{0x496230};
	WEAK symbol<void()> Com_Quit_f{0x556060};

	// Variables
	WEAK symbol<CmdArgs> cmd_args{0x1C96850};
	WEAK symbol<PlayerKeyState> playerKeys{0xB3A38C};
}
