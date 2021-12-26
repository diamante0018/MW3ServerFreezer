#pragma once

#pragma warning(push)
#pragma warning(disable: 4324)

namespace game
{
	typedef float vec_t;
	typedef vec_t vec2_t[2];
	typedef vec_t vec3_t[3];
	typedef vec_t vec4_t[4];

	struct cmd_function_t
	{
		cmd_function_t* next;
		const char* name;
		const char* autoCompleteDir;
		const char* autoCompleteExt;
		void(__cdecl* function)();
		int flags;
	};

	struct CmdArgs
	{
		int nesting;
		int localClientNum[8];
		int controllerIndex[8];
		int argc[8];
		const char** argv[8];
	};

	typedef enum
	{
		K_NONE = 0x0,
		K_FIRSTGAMEPADBUTTON_RANGE_1 = 0x1, // First Gamepad 1
		K_BUTTON_A = 0x1,
		K_BUTTON_B = 0x2,
		K_BUTTON_X = 0x3,
		K_BUTTON_Y = 0x4,
		K_BUTTON_LSHLDR = 0x5,
		K_BUTTON_RSHLDR = 0x6,
		K_LASTGAMEPADBUTTON_RANGE_1 = 0x6, // Last Gamepad 1
		K_TAB = 0x9,
		K_ENTER = 0xD,
		K_FIRSTGAMEPADBUTTON_RANGE_2 = 0xE, // First Gamepad 2
		K_BUTTON_START = 0xE,
		K_BUTTON_BACK = 0xF,
		K_BUTTON_LSTICK = 0x10,
		K_BUTTON_RSTICK = 0x11,
		K_BUTTON_LTRIG = 0x12,
		K_BUTTON_RTRIG = 0x13,
		K_FIRSTDPAD = 0x14, // First Dpad
		K_DPAD_UP = 0x14,
		K_DPAD_DOWN = 0x15,
		K_DPAD_LEFT = 0x16,
		K_DPAD_RIGHT = 0x17,
		K_LASTDPAD = 0x17, // Last Dpad
		K_DPAD_LEFTRIGHT = 0x18,
		K_DPAD_UPDOWN = 0x19,
		K_LASTGAMEPADBUTTON_RANGE_2 = 0x19, // Last Gamepad 2
		K_ESCAPE = 0x1B,
		K_FIRSTGAMEPADBUTTON_RANGE_3 = 0x1C, // First Gamepad 3
		K_FIRSTAPAD = 0x1C, // First APad
		K_APAD_UP = 0x1C,
		K_APAD_DOWN = 0x1D,
		K_APAD_LEFT = 0x1E,
		K_APAD_RIGHT = 0x1F,
		K_LASTAPAD = 0x1F, // Last APad
		K_LASTGAMEPADBUTTON_RANGE_3 = 0x1F, // Last Gamepad 3
		K_SPACE = 0x20,
		K_BACKSPACE = 0x7F,
		K_ASCII_FIRST = 0x80,
		K_ASCII_181 = 0x80,
		K_ASCII_191 = 0x81,
		K_ASCII_223 = 0x82,
		K_ASCII_224 = 0x83,
		K_ASCII_225 = 0x84,
		K_ASCII_228 = 0x85,
		K_ASCII_229 = 0x86,
		K_ASCII_230 = 0x87,
		K_ASCII_231 = 0x88,
		K_ASCII_232 = 0x89,
		K_ASCII_233 = 0x8A,
		K_ASCII_236 = 0x8B,
		K_ASCII_241 = 0x8C,
		K_ASCII_242 = 0x8D,
		K_ASCII_243 = 0x8E,
		K_ASCII_246 = 0x8F,
		K_ASCII_248 = 0x90,
		K_ASCII_249 = 0x91,
		K_ASCII_250 = 0x92,
		K_ASCII_252 = 0x93,
		K_END_ASCII_CHARS = 0x94,
		K_COMMAND = 0x96,
		K_CAPSLOCK = 0x97,
		K_POWER = 0x98,
		K_PAUSE = 0x99,
		K_UPARROW = 0x9A,
		K_DOWNARROW = 0x9B,
		K_LEFTARROW = 0x9C,
		K_RIGHTARROW = 0x9D,
		K_ALT = 0x9E,
		K_CTRL = 0x9F,
		K_SHIFT = 0xA0,
		K_INS = 0xA1,
		K_DEL = 0xA2,
		K_PGDN = 0xA3,
		K_PGUP = 0xA4,
		K_HOME = 0xA5,
		K_END = 0xA6,
		K_F1 = 0xA7,
		K_F2 = 0xA8,
		K_F3 = 0xA9,
		K_F4 = 0xAA,
		K_F5 = 0xAB,
		K_F6 = 0xAC,
		K_F7 = 0xAD,
		K_F8 = 0xAE,
		K_F9 = 0xAF,
		K_F10 = 0xB0,
		K_F11 = 0xB1,
		K_F12 = 0xB2,
		K_F13 = 0xB3,
		K_F14 = 0xB4,
		K_F15 = 0xB5,
		K_KP_HOME = 0xB6,
		K_KP_UPARROW = 0xB7,
		K_KP_PGUP = 0xB8,
		K_KP_LEFTARROW = 0xB9,
		K_KP_5 = 0xBA,
		K_KP_RIGHTARROW = 0xBB,
		K_KP_END = 0xBC,
		K_KP_DOWNARROW = 0xBD,
		K_KP_PGDN = 0xBE,
		K_KP_ENTER = 0xBF,
		K_KP_INS = 0xC0,
		K_KP_DEL = 0xC1,
		K_KP_SLASH = 0xC2,
		K_KP_MINUS = 0xC3,
		K_KP_PLUS = 0xC4,
		K_KP_NUMLOCK = 0xC5,
		K_KP_STAR = 0xC6,
		K_KP_EQUALS = 0xC7,
		K_MOUSE1 = 0xC8,
		K_MOUSE2 = 0xC9,
		K_MOUSE3 = 0xCA,
		K_MOUSE4 = 0xCB,
		K_MOUSE5 = 0xCC,
		K_MWHEELDOWN = 0xCD,
		K_MWHEELUP = 0xCE,
		K_AUX1 = 0xCF,
		K_AUX2 = 0xD0,
		K_AUX3 = 0xD1,
		K_AUX4 = 0xD2,
		K_AUX5 = 0xD3,
		K_AUX6 = 0xD4,
		K_AUX7 = 0xD5,
		K_AUX8 = 0xD6,
		K_AUX9 = 0xD7,
		K_AUX10 = 0xD8,
		K_AUX11 = 0xD9,
		K_AUX12 = 0xDA,
		K_AUX13 = 0xDB,
		K_AUX14 = 0xDC,
		K_AUX15 = 0xDD,
		K_AUX16 = 0xDE,
		K_LAST_KEY = 0xDF
	} keyNum_t;

	struct kbutton_t
	{
		int down[2];
		unsigned int downtime;
		unsigned int msec;
		bool active;
		bool wasPressed;
	};

	static_assert(sizeof(kbutton_t) == 20);

	typedef enum
	{
		NS_CLIENT1 = 0,
		NS_CLIENT2 = 1,
		NS_CLIENT3 = 2,
		NS_CLIENT4 = 3,
		NS_MAXCLIENTS = 4,
		NS_SERVER = 4,
		NS_PACKET = 5,
		NS_INVALID_NETSRC = 6
	} netsrc_t;

	enum netadrtype_t
	{
		NA_BOT = 0x0,
		NA_BAD = 0x1,
		NA_LOOPBACK = 0x2,
		NA_BROADCAST = 0x3,
		NA_IP = 0x4
	};

	struct netadr_s
	{
		netadrtype_t type;
		unsigned char ip[4];
		unsigned __int16 port;
		unsigned char ipx[10];
		unsigned int addrHandleIndex;
	};

	static_assert(sizeof(netadr_s) == 24);

	typedef enum
	{
		BD_ECC_KEY_UNINITIALIZED = 0x0,
		BD_ECC_KEY_INITIALIZED = 0x1
	} bdECCKeyStatus;

	typedef enum
	{
		BD_DTLS_INIT = 0x1,
		BD_DTLS_INIT_ACK = 0x2,
		BD_DTLS_COOKIE_ECHO = 0x3,
		BD_DTLS_COOKIE_ACK = 0x4,
		BD_DTLS_ERROR = 0x5,
		BD_DTLS_DATA = 0x6
	} bdDTLSPacketTypes;

	typedef enum
	{
		BD_DTLS_CLOSED = 0x0,
		BD_DTLS_COOKIE_WAIT = 0x1,
		BD_DTLS_COOKIE_ECHOED = 0x2,
		BD_DTLS_ESTABLISHED = 0x3
	} bdDTLSStatus;

	typedef enum
	{
		BD_DTLS_ERROR_BAD_SECID = 0x0,
		BD_DTLS_INVALID_STATE = 0x1
	} bdDTLSErrorType;

	typedef enum
	{
		BD_NAT_OPEN = 0x1,
		BD_NAT_MODERATE = 0x2,
		BD_NAT_STRICT = 0x3
	} bdNATType;

	typedef enum
	{
		BD_SOCKET_IDLE = 0x0,
		BD_SOCKET_PENDING = 0x1,
		BD_SOCKET_CONNECTED = 0x2,
		BD_SOCKET_LOST = 0x3
	} bdDTLSAssociationStatus;

	typedef enum
	{
		ERR_FATAL = 0x0,
		ERR_DROP = 0x1,
		ERR_SERVERDISCONNECT = 0x2,
		ERR_DISCONNECT = 0x3,
		ERR_SCRIPT = 0x4,
		ERR_SCRIPT_DROP = 0x5,
		ERR_LOCALIZATION = 0x6,
		ERR_MAPLOADERRORSUMMARY = 0x7
	} errorParm_t;

	enum class LocalClientNum_t
	{
		LOCAL_CLIENT_0 = 0,
		LOCAL_CLIENT_1 = 1,
		LOCAL_CLIENT_2 = 2,
		LOCAL_CLIENT_3 = 3,
		LOCAL_CLIENT_LAST = 3,
		LOCAL_CLIENT_COUNT = 4
	};

	typedef enum
	{
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

	struct msg_t
	{
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

	struct netProfilePacket_t
	{
		int iTime;
		int iSize;
		int bFragment;
	};

	struct netProfileStream_t
	{
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

	struct netProfileInfo_t
	{
		netProfileStream_t send;
		netProfileStream_t recieve;
	};

	struct netchan_t
	{
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
	static_assert(sizeof(netProfileInfo_t) == 0x5E0);

	struct XZoneInfo
	{
		const char* name;
		int allocFlags;
		int freeFlags;
	};

	struct scr_entref_t
	{
		unsigned __int16 entnum;
		unsigned __int16 classnum;
	};

	typedef void(__cdecl* scr_call_t)(int entref);

	enum MeansOfDeath
	{
		MOD_UNKNOWN = 0,
		MOD_PISTOL_BULLET = 1,
		MOD_RIFLE_BULLET = 2,
		MOD_EXPLOSIVE_BULLET = 3,
		MOD_GRENADE = 4,
		MOD_GRENADE_SPLASH = 5,
		MOD_PROJECTILE = 6,
		MOD_PROJECTILE_SPLASH = 7,
		MOD_MELEE = 8,
		MOD_HEAD_SHOT = 9,
		MOD_CRUSH = 10,
		MOD_FALLING = 11,
		MOD_SUICIDE = 12,
		MOD_TRIGGER_HURT = 13,
		MOD_EXPLOSIVE = 14,
		MOD_IMPACT = 15,
		MOD_NUM = 16
	};

	enum scriptType_e
	{
		SCRIPT_NONE = 0,
		SCRIPT_OBJECT = 1,
		SCRIPT_STRING = 2,
		SCRIPT_ISTRING = 3,
		SCRIPT_VECTOR = 4,
		SCRIPT_FLOAT = 5,
		SCRIPT_INTEGER = 6,
		SCRIPT_END = 8,
		SCRIPT_FUNCTION = 9,
		SCRIPT_STRUCT = 19,
		SCRIPT_ARRAY = 22,
	};

	struct VariableStackBuffer
	{
		const char* pos;
		unsigned __int16 size;
		unsigned __int16 bufLen;
		unsigned __int16 localId;
		char time;
		char buf[1];
	};

	union VariableUnion
	{
		int intValue;
		float floatValue;
		unsigned int stringValue;
		const float* vectorValue;
		const char* codePosValue;
		unsigned int pointerValue;
		VariableStackBuffer* stackValue;
		unsigned int entityId;
		unsigned int uintValue;
	};

	struct VariableValue
	{
		VariableUnion u;
		scriptType_e type;
	};

	struct function_stack_t
	{
		const char* pos;
		unsigned int localId;
		unsigned int localVarCount;
		VariableValue* top;
		VariableValue* startTop;
	};

	struct function_frame_t
	{
		function_stack_t fs;
		int topType;
	};

	struct scrVmPub_t
	{
		unsigned int* localVars;
		VariableValue* maxstack;
		int function_count;
		function_frame_t* function_frame;
		VariableValue* top;
		/*bool debugCode;
		bool abort_on_error;
		bool terminal_error;
		bool block_execution;*/
		unsigned int inparamcount;
		unsigned int outparamcount;
		unsigned int breakpointOutparamcount;
		bool showError;
		function_frame_t function_frame_start[32];
		VariableValue stack[2048];
	};

	struct scr_classStruct_t
	{
		unsigned __int16 id;
		unsigned __int16 entArrayId;
		char charId;
		const char* name;
	};

	struct ObjectVariableChildren
	{
		unsigned __int16 firstChild;
		unsigned __int16 lastChild;
	};

	struct ObjectVariableValue_u_f
	{
		unsigned __int16 prev;
		unsigned __int16 next;
	};

	union ObjectVariableValue_u_o_u
	{
		unsigned __int16 size;
		unsigned __int16 entnum;
		unsigned __int16 nextEntId;
		unsigned __int16 self;
	};

	struct	ObjectVariableValue_u_o
	{
		unsigned __int16 refCount;
		ObjectVariableValue_u_o_u u;
	};

	union ObjectVariableValue_w
	{
		unsigned int type;
		unsigned int classnum;
		unsigned int notifyName;
		unsigned int waitTime;
		unsigned int parentLocalId;
	};

	struct ChildVariableValue_u_f
	{
		unsigned __int16 prev;
		unsigned __int16 next;
	};

	union ChildVariableValue_u
	{
		ChildVariableValue_u_f f;
		VariableUnion u;
	};

	struct ChildBucketMatchKeys_keys
	{
		unsigned __int16 name_hi;
		unsigned __int16 parentId;
	};

	union ChildBucketMatchKeys
	{
		ChildBucketMatchKeys_keys keys;
		unsigned int match;
	};

	struct	ChildVariableValue
	{
		ChildVariableValue_u u;
		unsigned __int16 next;
		char type;
		char name_lo;
		ChildBucketMatchKeys k;
		unsigned __int16 nextSibling;
		unsigned __int16 prevSibling;
	};

	union ObjectVariableValue_u
	{
		ObjectVariableValue_u_f f;
		ObjectVariableValue_u_o o;
	};

	struct ObjectVariableValue
	{
		ObjectVariableValue_u u;
		ObjectVariableValue_w w;
	};

	struct scrVarGlob_t
	{
		ObjectVariableValue objectVariableValue[36864];
		ObjectVariableChildren objectVariableChildren[36864];
		unsigned __int16 childVariableBucket[65536];
		ChildVariableValue childVariableValue[102400];
	};

	enum dvar_flags : std::uint16_t
	{
		DVAR_FLAG_NONE = 0,
		DVAR_FLAG_SAVED = 1,
		DVAR_FLAG_LATCHED = 2,
		DVAR_FLAG_CHEAT = 4,
		DVAR_FLAG_REPLICATED = 0x8,
		DVAR_FLAG_UNK1 = 0x40,
		DVAR_FLAG_UNK2 = 0x200,
		DVAR_FLAG_SYSTEM = 0x400,
		DVAR_FLAG_WRITE = 0x800,
		DVAR_FLAG_READONLY = 0x2000,
	};

	union DvarValue
	{
		bool enabled;
		int integer;
		unsigned int unsignedInt;
		float value;
		float vector[4];
		const char* string;
		char color[4];
	};

	struct enum_limit
	{
		int stringCount;
		const char** strings;
	};

	struct int_limit
	{
		int min;
		int max;
	};

	struct float_limit
	{
		float min;
		float max;
	};

	union DvarLimits
	{
		enum_limit enumeration;
		int_limit integer;
		float_limit value;
		float_limit vector;
	};

	struct dvar_t
	{
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

	struct usercmd_s
	{
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

	enum LocSelInputState
	{
		LOC_SEL_INPUT_NONE = 0,
		LOC_SEL_INPUT_CONFIRM = 1,
		LOC_SEL_INPUT_CANCEL = 2
	};

	struct field_t
	{
		int cursor;
		int scroll;
		int drawWidth;
		int widthInPixels;
		float charHeight;
		int fixedSize;
		char buffer[256];
	};

	struct KeyState
	{
		int down;
		int repeats;
		int binding;
		const char* bindingCheat;
	};

	static_assert(sizeof(field_t) == 280);

	struct PlayerKeyState
	{
		field_t chatField;
		int chat_team;
		int overstrikeMode;
		int anyKeyDown;
		KeyState keys[256];
		LocSelInputState locSelInputState;
	};

	static_assert(sizeof(PlayerKeyState) == 4392);

	enum EffectiveStance
	{
		PM_EFF_STANCE_DEFAULT = 0,
		PM_EFF_STANCE_PRONE = 1,
		PM_EFF_STANCE_DUCKED = 2,
		PM_EFF_STANCE_LASTSTANDCRAWL = 3,
		PM_EFF_STANCE_COUNT = 4
	};

	enum clientState_t : std::int32_t
	{
		CS_FREE = 0,
		CS_ZOMBIE = 1,
		CS_UNKNOWN = 2,
		CS_CONNECTED = 3,
		CS_PRIMED = 4,
		CS_ACTIVE = 5
	};

	struct MantleState
	{
		float yaw;
		int timer;
		int transIndex;
		int flags;
	};

	struct SprintState_s
	{
		int sprintButtonUpRequired; // 0x20C
		int sprintDelay; // 0x210
		int lastSprintStart;
		int lastSprintEnd; // 0x218
		int sprintStartMaxLength;
	};

	struct PlayerVehicleState
	{
		int entity;
		int flags;
		float origin[3];
		float angles[3];
		float velocity[3];
		float angVelocity[3];
		float tilt[2];
		float tiltVelocity[2];
	};

	struct PlayerActiveWeaponState
	{
		int weapAnim;
		int weaponTime;
		int weaponDelay;
		int weaponRestrictKickTime;
		int weaponState;
		int weaponHandFlags;
		int weaponShotCount;
	};

	struct PlayerEquippedWeaponState
	{
		bool usedBefore;
		bool dualWielding;
		bool inAltMode;
		bool needsRechamber[2];
		int zoomLevelIndex;
	};

	static_assert(sizeof(PlayerEquippedWeaponState) == 12);

	struct EntityEvent
	{
		int eventType;
		int eventParm;
	};

	struct playerEvents_t
	{
		int eventSequence;
		EntityEvent events[4];
		int oldEventSequence;
		int timeADSCameUp;
	};

	static_assert(sizeof(playerEvents_t) == 44);

	enum ViewLockTypes
	{
		PLAYERVIEWLOCK_NONE = 0,
		PLAYERVIEWLOCK_FULL = 1,
		PLAYERVIEWLOCK_WEAPONJITTER = 2,
		PLAYERVIEWLOCKCOUNT = 3
	};

	enum TraceHitType
	{
		TRACE_HITTYPE_NONE = 0,
		TRACE_HITTYPE_ENTITY = 1,
		TRACE_HITTYPE_DYNENT_MODEL = 2,
		TRACE_HITTYPE_DYNENT_BRUSH = 3,
		TRACE_HITTYPE_GLASS = 4
	};

#pragma pack(push, 1)
	struct playerState_s
	{
		int commandTime;
		int pm_type;
		int pm_time;
		int pm_flags;
		int otherFlags;
		int linkFlags;
		int bobCycle;
		float origin[3];
		float velocity[3];
		int grenadeTimeLeft;
		int throwbackGrenadeOwner;
		int throwbackGrenadeTimeLeft;
		unsigned int throwbackWeapon;
		int remoteEyesEnt;
		int remoteEyesTagname;
		int remoteControlEnt;
		int remoteTurretEnt;
		int foliageSoundTime;
		int gravity;
		int speed;
		float delta_angles[3];
		int groundEntityNum;
		float vLadderVec[3];
		int jumpTime;
		float jumpOriginZ;
		int legsTimer;
		int legsAnim;
		int torsoTimer;
		int torsoAnim;
		int legsAnimDuration;
		int torsoAnimDuration;
		int damageTimer;
		int damageDuration;
		int flinchYawAnim;
		int corpseIndex;
		PlayerVehicleState vehicleState;
		int movementDir;
		int eFlags;
		playerEvents_t pe;
		int unpredictableEventSequence;
		int unpredictableEventSequenceOld;
		int unpredictableEvents[4];
		char unpredictableEventParms[16];
		int clientNum;
		int viewmodelIndex;
		float viewangles[3];
		int viewHeightTarget;
		float viewHeightCurrent;
		int viewHeightLerpTime;
		int viewHeightLerpTarget;
		int viewHeightLerpDown;
		char viewAngleClampBase[8];
		char viewAngleClampRange[8];
		int damageEvent;
		int damageYaw;
		int damagePitch;
		int damageCount;
		int damageFlags;
		int stats[4];
		float proneDirection;
		float proneDirectionPitch;
		float proneTorsoPitch;
		ViewLockTypes viewlocked;
		int viewlocked_entNum;
		float linkAngles[3];
		float linkWeaponAngles[3];
		int linkWeaponEnt;
		int loopSound;
		int cursorHint;
		int cursorHintString;
		int cursorHintEntIndex;
		int cursorHintDualWield;
		int iCompassPlayerInfo;
		int radarEnabled;
		int radarBlocked;
		int radarMode;
		int radarStrength;
		int radarShowEnemyDirection;
		int locationSelectionInfo;
		SprintState_s sprintState;
		float holdBreathScale;
		int holdBreathTimer;
		float moveSpeedScaleMultiplier;
		MantleState mantleState;
		PlayerActiveWeaponState weapState[2];
		unsigned int weaponsEquipped[15];
		PlayerEquippedWeaponState weapEquippedData[15];
		char weapCommon[376];
		int meleeChargeDist;
		int meleeChargeTime;
		int meleeChargeEnt;
		int airburstMarkDistance;
		unsigned int perks[2];
		unsigned int perkSlots[9];
		char __pad0[11752];
	};

	struct pmove_t
	{
		playerState_s* ps;
		usercmd_s cmd;
		usercmd_s oldcmd;
		int tracemask;
		int numtouch;
		int touchents[32];
		char bounds[24];
		float speed;
		int proneChange;
		float maxSprintTimeMultiplier;
		bool mantleStarted;
		float mantleEndPos[3];
		int mantleDuration;
		int viewChangeTime;
		float viewChange;
		float fTorsoPitch;
		float fWaistPitch;
		int remoteTurretFireTime;
		int lastUpdateCMDServerTime;
		unsigned char handler;
	};
#pragma pack(pop)

	static_assert(sizeof(playerState_s) == 13056);

	struct gclient_s
	{
		playerState_s ps;
		char __pad0[716];
		int flags;
		int spectatorClient;
		int lastCmdTime;
//		int mpviewer; // Debug ?
		int buttons;
		int oldButtons;
		int latched_buttons;
		int buttonsSinceLastFrame;
		float oldOrigin[3];
		float fGunPitch;
		float fGunYaw;
		int damage_blood;
		int damage_stun;
		float damage_from[3];
		int damage_fromWorld;
		int accurateCount;
		int accuracy_shots;
		int accuracy_hits;
		int inactivityTime;
		int inactivityWarning;
		int lastVoiceTime;
		int switchTeamTime;
		float currentAimSpreadScale;
		float prevLinkedInvQuat[4];
		bool prevLinkAnglesSet;
		bool link_rotationMovesEyePos;
		bool link_doCollision;
		bool link_useTagAnglesForViewAngles;
		bool link_useBaseAnglesForViewClamp;
		float linkAnglesFrac;
		char link_viewClamp[64];
		char persistantPowerup[4];
		int portalID;
		int dropWeaponTime;
		int sniperRifleFiredTime;
		float sniperRifleMuzzleYaw;
		int PCSpecialPickedUpCount;
		int useHoldEntity;
		int useHoldTime;
		int useButtonDone;
		int iLastCompassPlayerInfoEnt;
		int compassPingTime;
		int damageTime;
		float v_dmg_roll;
		float v_dmg_pitch;
		float baseAngles[3];
		float baseOrigin[3];
		float swayViewAngles[3];
		float swayOffset[3];
		float swayAngles[3];
		float recoilAngles[3];
		float recoilSpeed[3];
		float fLastIdleFactor;
		int lastServerTime;
		int lastWeapon;
		bool lastWeaponAltStatus;
		bool previouslyFiring;
		bool previouslyFiringLeftHand;
		bool previouslyUsingNightVision;
		bool previouslySprinting;
		int visionDuration[6];
		char visionName[384];
		int lastStand;
		int lastStandTime;
		int hudElemLastAssignedSoundID;
		float lockedTargetOffset[3];
		unsigned __int16 attachShieldTagName;
		int hintForcedType;
		int hintForcedString;
	};

	struct clientConnection_t
	{
		int qport; // 0
		int clientNum; // 4
		int lastPacketSentTime; // 8
		int lastPacketTime; // 12
		netadr_s serverAddress; // 16
		int connectTime; // 40
		int connectPacketCount; // 44
		char serverMessage[256]; // 48
		int challenge; // 304
		int checksumFeed; // 308
		int reliableSequence; // 312
		int reliableAcknowledge; // 316
		char reliableCommands[128][1024]; // 320
		int serverMessageSequence; // 131392
		int serverCommandSequence; // 131396
		int lastExecutedServerCommand; // 131400
		char serverCommands[128][1024]; // 131404
		bool isServerRestarting; // 262476
		char clientDemo[16592]; // 262480
		netchan_t netchan; // 279072
		char netchanOutgoingBuffer[2048]; // 280656
		char netchanIncomingBuffer[65536]; // 282704
		netProfileInfo_t OOBProf; // 348240
		short statPacketsToSend; // 349744
		int statPacketSendTime[10]; // From here it might be wrong
		int currentGamestatePacket;
	};

	struct clientStatic_t
	{
	};
}

#pragma warning(pop)
