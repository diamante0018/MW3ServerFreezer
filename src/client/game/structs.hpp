#pragma once

#pragma warning(push)
#pragma warning(disable : 4324)

namespace game {
typedef float vec_t;
typedef vec_t vec2_t[2];
typedef vec_t vec3_t[3];
typedef vec_t vec4_t[4];

enum bdLogMessageType {
  BD_LOG_INFO,
  BD_LOG_WARNING,
  BD_LOG_ERROR,
};

struct cmd_function_t {
  cmd_function_t* next;
  const char* name;
  const char* autoCompleteDir;
  const char* autoCompleteExt;
  void(__cdecl* function)();
  int flags;
};

struct CmdArgs {
  int nesting;
  int localClientNum[8];
  int controllerIndex[8];
  int argc[8];
  const char** argv[8];
};

struct kbutton_t {
  int down[2];
  unsigned int downtime;
  unsigned int msec;
  bool active;
  bool wasPressed;
};

static_assert(sizeof(kbutton_t) == 20);

typedef enum {
  NS_CLIENT1 = 0,
  NS_CLIENT2 = 1,
  NS_CLIENT3 = 2,
  NS_CLIENT4 = 3,
  NS_MAXCLIENTS = 4,
  NS_SERVER = 4,
  NS_PACKET = 5,
  NS_INVALID_NETSRC = 6
} netsrc_t;

enum netadrtype_t {
  NA_BOT = 0x0,
  NA_BAD = 0x1,
  NA_LOOPBACK = 0x2,
  NA_BROADCAST = 0x3,
  NA_IP = 0x4
};

struct netadr_s {
  netadrtype_t type;
  unsigned char ip[4];
  unsigned __int16 port;
  unsigned char ipx[10];
  unsigned int addrHandleIndex;
};

static_assert(sizeof(netadr_s) == 0x18);

typedef enum {
  ERR_FATAL = 0x0,
  ERR_DROP = 0x1,
  ERR_SERVERDISCONNECT = 0x2,
  ERR_DISCONNECT = 0x3,
  ERR_SCRIPT = 0x4,
  ERR_SCRIPT_DROP = 0x5,
  ERR_LOCALIZATION = 0x6,
  ERR_MAPLOADERRORSUMMARY = 0x7
} errorParm_t;

enum class LocalClientNum_t {
  LOCAL_CLIENT_0 = 0,
  LOCAL_CLIENT_1 = 1,
  LOCAL_CLIENT_2 = 2,
  LOCAL_CLIENT_3 = 3,
  LOCAL_CLIENT_LAST = 3,
  LOCAL_CLIENT_COUNT = 4
};

typedef enum {
  CA_DISCONNECTED = 0,
  CA_CINEMATIC = 1,
  CA_LOGO = 2,
  CA_CONNECTING = 3,
  CA_CHALLENGING = 4,
  CA_CONNECTED = 5,
  CA_SENDINGSTATS = 6,
  CA_REQUESTING_MATCH_RULES = 7,
  CA_LOADING = 8,
  CA_PRIMED = 9,
  CA_ACTIVE = 10
} connstate_t;

struct msg_t {
  int overflowed;
  int readOnly;
  unsigned char* data;
  unsigned char* splitData;
  int maxsize;
  int cursize;
  int splitSize;
  int readcount;
  int bit;
  int lastEntityRef;
};

struct netProfilePacket_t {
  int iTime;
  int iSize;
  int bFragment;
};

struct netProfileStream_t {
  netProfilePacket_t packets[60];
  int iCurrPacket;
  int iBytesPerSeconds;
  int iLastBPSCalcTime;
  int iCountedPackets;
  int iCountedFragments;
  int iFragmentPercentage;
  int iLargestPacket;
  int iSmallestPacket;
};

struct netProfileInfo_t {
  netProfileStream_t send;
  netProfileStream_t recieve;
};

static_assert(sizeof(netProfileInfo_t) == 0x5E0);

struct netchan_t {
  int outgoingSequence;
  netsrc_t sock;
  int dropped;
  int incomingSequence;
  netadr_s remoteAddress;
  int qport;
  int fragmentSequence;
  int fragmentLength;
  unsigned char* fragmentBuffer;
  int fragmentBufferSize;
  int unsentFragments;
  int unsentFragmentStart;
  int unsentLength;
  unsigned char* unsentBuffer;
  int unsentBufferSize;
  netProfileInfo_t prof;
};

static_assert(sizeof(netchan_t) == 0x630);

enum dvar_flags : std::uint16_t {
  DVAR_NONE = 0,
  DVAR_ARCHIVE = 1 << 0,
  DVAR_LATCH = 1 << 1,
  DVAR_CHEAT = 1 << 2,
  DVAR_CODINFO = 1 << 3,
  DVAR_SCRIPTINFO = 1 << 4,
  DVAR_SERVERINFO = 1 << 10,
  DVAR_INIT = 1 << 11,
  DVAR_ROM = 1 << 13,
  DVAR_AUTOEXEC = 1 << 15,
};

enum dvar_type : std::int8_t {
  DVAR_TYPE_BOOL = 0x0,
  DVAR_TYPE_FLOAT = 0x1,
  DVAR_TYPE_FLOAT_2 = 0x2,
  DVAR_TYPE_FLOAT_3 = 0x3,
  DVAR_TYPE_FLOAT_4 = 0x4,
  DVAR_TYPE_INT = 0x5,
  DVAR_TYPE_ENUM = 0x6,
  DVAR_TYPE_STRING = 0x7,
  DVAR_TYPE_COLOR = 0x8,
  DVAR_TYPE_FLOAT_3_COLOR = 0x9,
};

enum class DvarSetSource {
  DVAR_SOURCE_INTERNAL,
  DVAR_SOURCE_EXTERNAL,
  DVAR_SOURCE_SCRIPT,
  DVAR_SOURCE_DEVGUI,
};

union DvarValue {
  bool enabled;
  int integer;
  unsigned int unsignedInt;
  float value;
  float vector[4];
  const char* string;
  char color[4];
};

static_assert(sizeof(DvarValue) == 0x10);

struct enum_limit {
  int stringCount;
  const char** strings;
};

struct int_limit {
  int min;
  int max;
};

struct float_limit {
  float min;
  float max;
};

union DvarLimits {
  enum_limit enumeration;
  int_limit integer;
  float_limit value;
  float_limit vector;
};

struct dvar_t {
  const char* name;
  unsigned int flags;
  char type;
  bool modified;
  DvarValue current;
  DvarValue latched;
  DvarValue reset;
  DvarLimits domain;
  bool(__cdecl* domainFunc)(dvar_t*, DvarValue);
  dvar_t* hashNext;
};

struct usercmd_s {
  int serverTime;
  int buttons;
  int angles[3];
  unsigned int weapon;
  unsigned int offHand;
  char forwardmove;
  char rightmove;
  unsigned __int16 airburstMarkDistance;
  unsigned __int16 meleeChargeEnt;
  unsigned char meleeChargeDist;
  char selectedLoc[2];
  char selectedLocAngle;
  char remoteControlAngles[2];
  int remoteControlMove;
};

enum LocSelInputState {
  LOC_SEL_INPUT_NONE = 0,
  LOC_SEL_INPUT_CONFIRM = 1,
  LOC_SEL_INPUT_CANCEL = 2
};

struct field_t {
  int cursor;
  int scroll;
  int drawWidth;
  int widthInPixels;
  float charHeight;
  int fixedSize;
  char buffer[256];
};

struct KeyState {
  int down;
  int repeats;
  int binding;
  const char* bindingCheat;
};

static_assert(sizeof(field_t) == 280);

struct PlayerKeyState {
  field_t chatField;
  int chat_team;
  int overstrikeMode;
  int anyKeyDown;
  KeyState keys[256];
  LocSelInputState locSelInputState;
};

static_assert(sizeof(PlayerKeyState) == 4392);

enum clientState_t {
  CS_FREE = 0,
  CS_ZOMBIE = 1,
  CS_RECONNECTING = 2,
  CS_CONNECTED = 3,
  CS_PRIMED = 4,
  CS_ACTIVE = 5
};

struct clientConnection_t {
  int qport;                         // 0
  int clientNum;                     // 4
  int lastPacketSentTime;            // 8
  int lastPacketTime;                // 12
  netadr_s serverAddress;            // 16
  int connectTime;                   // 40
  int connectPacketCount;            // 44
  char serverMessage[256];           // 48
  int challenge;                     // 304
  int checksumFeed;                  // 308
  int reliableSequence;              // 312
  int reliableAcknowledge;           // 316
  char reliableCommands[128][1024];  // 320
  int serverMessageSequence;         // 131392
  int serverCommandSequence;         // 131396
  int lastExecutedServerCommand;     // 131400
  char serverCommands[128][1024];    // 131404
  bool isServerRestarting;           // 262476
  char clientDemo[16592];            // 262480
  netchan_t netchan;                 // 279072
  char netchanOutgoingBuffer[2048];  // 280656
  char netchanIncomingBuffer[65536]; // 282704
  netProfileInfo_t OOBProf;          // 348240
  short statPacketsToSend;           // 349744
  int statPacketSendTime[10];        // From here it might be wrong
  int currentGamestatePacket;
};

struct clientStatic_t {};

struct ScreenPlacement {
  float scaleVirtualToReal[2];
  float scaleVirtualToFull[2];
  float scaleRealToVirtual[2];
  float realViewportPosition[2];
  float realViewportSize[2];
  float virtualViewableMin[2];
  float virtualViewableMax[2];
  float realViewableMin[2];
  float realViewableMax[2];
  float virtualAdjustableMin[2];
  float virtualAdjustableMax[2];
  float realAdjustableMin[2];
  float realAdjustableMax[2];
  float subScreenLeft;
};

static_assert(sizeof(ScreenPlacement) == 0x6C);

struct Font_s {
  const char* fontName;
  int pixelHeight;
  int glyphCount;
  void* material;
  void* glowMaterial;
  void* glyphs;
};

union XAssetHeader {
  Font_s* font;
};

} // namespace game

#pragma warning(pop)
