#pragma once

#define WEAK __declspec(selectany)

namespace game {
// Functions
WEAK symbol<void()> Sys_ShowConsole{0x515CD0};
WEAK symbol<void(HINSTANCE__*)> Sys_CreateConsole{0x51B770};
WEAK symbol<void(const char* fmt, ...)> Sys_Error{0x434000};
WEAK symbol<void(const char* text)> Conbuf_AppendText{0x4F7300};
WEAK symbol<void(errorParm_t, const char* fmt, ...)> Com_Error{0x4A6660};
WEAK symbol<const char*(int index)> ConcatArgs{0x539060};
WEAK symbol<void(LocalClientNum_t, const char* text)> Cbuf_AddText{0x4C1030};
WEAK symbol<void(LocalClientNum_t, const char* text)> Cbuf_InsertText{0x429920};
WEAK symbol<void(const char* cmdName, void(), cmd_function_t* cmd)>
    Cmd_AddCommandInternal{0x537E70};
WEAK symbol<void(LocalClientNum_t, int, const char* text)>
    Cmd_ExecuteSingleCommand{0x4EB8F0};
WEAK symbol<void(const char* cmdName)> Cmd_RemoveCommand{0x4EAF30};
WEAK symbol<const char*(int index)> Cmd_Argv{0x5580E0};

WEAK symbol<dvar_t*(const char*)> Dvar_FindVar{0x4EBB50};
WEAK symbol<dvar_t*(const char* dvarName, int value, int min, int max,
                    unsigned __int16 flags, const char* desc)>
    Dvar_RegisterInt{0x50C760};
WEAK symbol<dvar_t*(const char* dvarName, bool value, unsigned __int16 flags,
                    const char* description)>
    Dvar_RegisterBool{0x4A3300};
WEAK symbol<dvar_t*(const char* dvarName, const char* value,
                    unsigned __int16 flags, const char* description)>
    Dvar_RegisterString{0x4157E0};
WEAK symbol<dvar_t*(const char* dvarName, float value, float min, float max,
                    unsigned __int16 flags, const char* description)>
    Dvar_RegisterFloat{0x4A5CF0};
WEAK symbol<void(dvar_t* var, bool value)> Dvar_SetBool{0x46DD70};
WEAK symbol<void(const char* dvarName, bool value)> Dvar_SetBoolByName{
    0x48C7D0};
WEAK symbol<const char*(int, int)> Dvar_InfoString{0x4028C0};
WEAK symbol<void(const dvar_t* dvar, const char* value)> Dvar_SetString{
    0x465240};

WEAK symbol<int(const char* cmd)> Key_GetBindingForCmd{0x47D300};
WEAK symbol<int(const char* keyAsText)> Key_StringToKeynum{
    0x50A710}; // Virtual-Key Code
WEAK symbol<void(LocalClientNum_t, int, int)> Key_SetBinding{0x50B770};

WEAK symbol<void(int arg, char* buffer, int bufferLength)> SV_Cmd_ArgvBuffer{
    0x4F6B00};

WEAK symbol<bool(netsrc_t, netadr_s dest, const char* message)>
    NET_OutOfBandPrint{0x496230};
WEAK symbol<bool(netsrc_t, netadr_s dest, unsigned char* data, int size)>
    NET_OutOfBandData{0x4639C0};
WEAK symbol<void(netadr_s*, sockaddr*)> NetadrToSockadr{0x48B460};
WEAK symbol<int(const char* serverName, netadr_s serverRemote)> NET_StringToAdr{
    0x4E09A0};
WEAK symbol<SOCKET> query_socket{0x5A861EC};
WEAK symbol<void()> Com_Quit_f{0x556060};

WEAK symbol<void(const msg_t*, unsigned char*, int)> MSG_Init{0x40E030};
WEAK symbol<void(const msg_t*, const char*)> MSG_WriteString{0x42A560};
WEAK symbol<void(const msg_t*, unsigned __int64)> MSG_WriteInt64{0x4906B0};
WEAK symbol<void(const msg_t*, int)> MSG_WriteShort{0x4ACD80};
WEAK symbol<void(const msg_t*, const void*, int)> MSG_WriteData{0x4F8C20};
WEAK symbol<void(int, const char*)> CL_AddReliableCommand{0x4EE3A0};

WEAK symbol<int(const char* from, char* to, int size)> MSG_ReadBitsCompress{
    0x4C62F0};

WEAK symbol<unsigned __int64()> LiveSteam_GetUid{0x4A4050};
WEAK symbol<int(unsigned __int64, const void*, unsigned int)>
    LiveSteam_Client_ConnectToSteamServer{0x4D6980};

WEAK symbol<XAssetHeader(int type, const char* name, int allowCreateDefault)>
    DB_FindXAssetHeader{0x4B25C0};

WEAK symbol<void(const char* text, int maxChars, Font_s* font, float x, float y,
                 float xScale, float yScale, float rotation, const float* color,
                 int style)>
    R_AddCmdDrawText{0x42C970};

// Variables
WEAK symbol<CmdArgs> cmd_args{0x1C96850};
WEAK symbol<PlayerKeyState> playerKeys{0xB3A38C};
WEAK symbol<clientConnection_t> localClientConnection{0xB3D360};
WEAK symbol<HWND> g_wv_hWnd{0x5A86AF0};
WEAK symbol<HWND> s_wcd_hWnd{0x5A86330};
WEAK symbol<int> serverId{0xFF5058};
WEAK symbol<connstate_t> connectionState{0x1060214};
WEAK symbol<ScreenPlacement> scrPlaceFullUnsafe{0x1337FC0};
WEAK symbol<bool> isCheatOverride{0x8B4444};
} // namespace game
