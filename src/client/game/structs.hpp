#pragma once

namespace game
{
	typedef float vec_t;
	typedef vec_t vec2_t[2];
	typedef vec_t vec3_t[3];
	typedef vec_t vec4_t[4];

	typedef uint32_t dvarStrHash_t;
	typedef uint32_t ScrString_t;
	typedef int16_t BoneIndex;
	typedef unsigned int ScrVarCanonicalName_t;
	struct dvar_t;

	enum dvarType_t : __int32
	{
		DVAR_TYPE_INVALID = 0x0,
		DVAR_TYPE_BOOL = 0x1,
		DVAR_TYPE_FLOAT = 0x2,
		DVAR_TYPE_FLOAT_2 = 0x3,
		DVAR_TYPE_FLOAT_3 = 0x4,
		DVAR_TYPE_FLOAT_4 = 0x5,
		DVAR_TYPE_INT = 0x6,
		DVAR_TYPE_ENUM = 0x7,
		DVAR_TYPE_STRING = 0x8,
		DVAR_TYPE_COLOR = 0x9,
		DVAR_TYPE_INT64 = 0xA,
		DVAR_TYPE_UINT64 = 0xB,
		DVAR_TYPE_LINEAR_COLOR_RGB = 0xC,
		DVAR_TYPE_COLOR_XYZ = 0xD,
		DVAR_TYPE_COLOR_LAB = 0xE,
		DVAR_TYPE_SESSIONMODE_BASE_DVAR = 0xF,
		DVAR_TYPE_COUNT = 0x10,
	};

	enum consoleChannel_e : __int32
	{
		CON_CHANNEL_DONT_FILTER = 0x0,
		CON_CHANNEL_GAMENOTIFY = 0x1,
		CON_CHANNEL_BOLDGAME = 0x2,
		CON_CHANNEL_OBJNOTIFY = 0x3,
		CON_CHANNEL_SUBTITLE = 0x4,
		CON_CHANNEL_OBITUARY = 0x5,
		CON_CHANNEL_COOPINFO = 0x6,
		CON_CHANNEL_WARNING = 0x7,
		CON_CHANNEL_ERROR = 0x8,
		CON_CHANNEL_INFO = 0x9,
		CON_BUILTIN_CHANNEL_COUNT = 0xA,
		CON_FIRST_DEBUG_CHANNEL = 0x9,
	};

	enum consoleLabel_e : __int32
	{
		CON_LABEL_DEFAULT = 0x0,
		CON_LABEL_TEMP = 0x1,
		CON_LABEL_GFX = 0x2,
		CON_LABEL_TASKMGR2 = 0x3,
		CON_LABEL_LIVE = 0x4,
		CON_LABEL_DEMONWARE = 0x5,
		CON_LABEL_LEADERBOARDS = 0x6,
		CON_LABEL_LOBBY = 0x7,
		CON_LABEL_LOBBYHOST = 0x8,
		CON_LABEL_LOBBYCLIENT = 0x9,
		CON_LABEL_LOBBYVM = 0xA,
		CON_LABEL_MIGRATION = 0xB,
		CON_LABEL_INGAME_MIGRATION_HOST = 0xC,
		CON_LABEL_INGAME_MIGRATION_CLIENT = 0xD,
		CON_LABEL_SCRIPTER = 0xE,
		CON_LABEL_VM = 0xF,
		CON_LABEL_DVAR = 0x10,
		CON_LABEL_TOOL = 0x11,
		CON_LABEL_ANIM = 0x12,
		CON_LABEL_NETCHAN = 0x13,
		CON_LABEL_BG_CACHE = 0x14,
		CON_LABEL_PM = 0x15,
		CON_LABEL_MAPSWITCH = 0x16,
		CON_LABEL_AI = 0x17,
		CON_LABEL_GADGET = 0x18,
		CON_LABEL_SOUND = 0x19,
		CON_LABEL_SNAPSHOT = 0x1A,
		CON_LABEL_PLAYGO = 0x1B,
		CON_LABEL_LUI = 0x1C,
		CON_LABEL_LUA = 0x1D,
		CON_LABEL_VOICE = 0x1E,
		CON_LABEL_DEMO = 0x1F,
		CON_LABEL_DB = 0x20,
		CON_LABEL_HTTP = 0x21,
		CON_LABEL_COMPANION = 0x22,
		CON_LABEL_MEM = 0x23,
		CON_LABEL_CINEMATIC = 0x24,
		CON_LABEL_DDL = 0x25,
		CON_LABEL_STORAGE = 0x26,
		CON_LABEL_STEAM = 0x27,
		CON_LABEL_CHECKPOINT = 0x28,
		CON_LABEL_THUNDERHEAD = 0x29,
		CON_LABEL_COMSCORE = 0x2A,
		CON_LABEL_FILESHARE = 0x2B,
		CON_LABEL_LPC = 0x2C,
		CON_LABEL_MARKETING = 0x2D,
		CON_LABEL_STORE = 0x2E,
		CON_LABEL_TESTING = 0x2F,
		CON_LABEL_COUNT = 0x30,
	};

	enum XAssetType : __int32
	{
		ASSET_TYPE_PHYSPRESET = 0x0,
		ASSET_TYPE_PHYSCONSTRAINTS = 0x1,
		ASSET_TYPE_DESTRUCTIBLEDEF = 0x2,
		ASSET_TYPE_XANIMPARTS = 0x3,
		ASSET_TYPE_XMODEL = 0x4,
		ASSET_TYPE_XMODELMESH = 0x5,
		ASSET_TYPE_MATERIAL = 0x6,
		ASSET_TYPE_COMPUTE_SHADER_SET = 0x7,
		ASSET_TYPE_TECHNIQUE_SET = 0x8,
		ASSET_TYPE_IMAGE = 0x9,
		ASSET_TYPE_SOUND = 0xA,
		ASSET_TYPE_SOUND_PATCH = 0xB,
		ASSET_TYPE_CLIPMAP = 0xC,
		ASSET_TYPE_COMWORLD = 0xD,
		ASSET_TYPE_GAMEWORLD = 0xE,
		ASSET_TYPE_MAP_ENTS = 0xF,
		ASSET_TYPE_GFXWORLD = 0x10,
		ASSET_TYPE_LIGHT_DEF = 0x11,
		ASSET_TYPE_LENSFLARE_DEF = 0x12,
		ASSET_TYPE_UI_MAP = 0x13,
		ASSET_TYPE_FONT = 0x14,
		ASSET_TYPE_FONTICON = 0x15,
		ASSET_TYPE_LOCALIZE_ENTRY = 0x16,
		ASSET_TYPE_WEAPON = 0x17,
		ASSET_TYPE_WEAPONDEF = 0x18,
		ASSET_TYPE_WEAPON_VARIANT = 0x19,
		ASSET_TYPE_WEAPON_FULL = 0x1A,
		ASSET_TYPE_CGMEDIA = 0x1B,
		ASSET_TYPE_PLAYERSOUNDS = 0x1C,
		ASSET_TYPE_PLAYERFX = 0x1D,
		ASSET_TYPE_SHAREDWEAPONSOUNDS = 0x1E,
		ASSET_TYPE_ATTACHMENT = 0x1F,
		ASSET_TYPE_ATTACHMENT_UNIQUE = 0x20,
		ASSET_TYPE_WEAPON_CAMO = 0x21,
		ASSET_TYPE_CUSTOMIZATION_TABLE = 0x22,
		ASSET_TYPE_CUSTOMIZATION_TABLE_FE_IMAGES = 0x23,
		ASSET_TYPE_CUSTOMIZATION_TABLE_COLOR = 0x24,
		ASSET_TYPE_SNDDRIVER_GLOBALS = 0x25,
		ASSET_TYPE_FX = 0x26,
		ASSET_TYPE_TAGFX = 0x27,
		ASSET_TYPE_NEW_LENSFLARE_DEF = 0x28,
		ASSET_TYPE_IMPACT_FX = 0x29,
		ASSET_TYPE_IMPACT_SOUND = 0x2A,
		ASSET_TYPE_PLAYER_CHARACTER = 0x2B,
		ASSET_TYPE_AITYPE = 0x2C,
		ASSET_TYPE_CHARACTER = 0x2D,
		ASSET_TYPE_XMODELALIAS = 0x2E,
		ASSET_TYPE_RAWFILE = 0x2F,
		ASSET_TYPE_STRINGTABLE = 0x30,
		ASSET_TYPE_STRUCTURED_TABLE = 0x31,
		ASSET_TYPE_LEADERBOARD = 0x32,
		ASSET_TYPE_DDL = 0x33,
		ASSET_TYPE_GLASSES = 0x34,
		ASSET_TYPE_TEXTURELIST = 0x35,
		ASSET_TYPE_SCRIPTPARSETREE = 0x36,
		ASSET_TYPE_KEYVALUEPAIRS = 0x37,
		ASSET_TYPE_VEHICLEDEF = 0x38,
		ASSET_TYPE_ADDON_MAP_ENTS = 0x39,
		ASSET_TYPE_TRACER = 0x3A,
		ASSET_TYPE_SLUG = 0x3B,
		ASSET_TYPE_SURFACEFX_TABLE = 0x3C,
		ASSET_TYPE_SURFACESOUNDDEF = 0x3D,
		ASSET_TYPE_FOOTSTEP_TABLE = 0x3E,
		ASSET_TYPE_ENTITYFXIMPACTS = 0x3F,
		ASSET_TYPE_ENTITYSOUNDIMPACTS = 0x40,
		ASSET_TYPE_ZBARRIER = 0x41,
		ASSET_TYPE_VEHICLEFXDEF = 0x42,
		ASSET_TYPE_VEHICLESOUNDDEF = 0x43,
		ASSET_TYPE_TYPEINFO = 0x44,
		ASSET_TYPE_SCRIPTBUNDLE = 0x45,
		ASSET_TYPE_SCRIPTBUNDLELIST = 0x46,
		ASSET_TYPE_RUMBLE = 0x47,
		ASSET_TYPE_BULLETPENETRATION = 0x48,
		ASSET_TYPE_LOCDMGTABLE = 0x49,
		ASSET_TYPE_AIMTABLE = 0x4A,
		ASSET_TYPE_ANIMSELECTORTABLESET = 0x4B,
		ASSET_TYPE_ANIMMAPPINGTABLE = 0x4C,
		ASSET_TYPE_ANIMSTATEMACHINE = 0x4D,
		ASSET_TYPE_BEHAVIORTREE = 0x4E,
		ASSET_TYPE_BEHAVIORSTATEMACHINE = 0x4F,
		ASSET_TYPE_TTF = 0x50,
		ASSET_TYPE_SANIM = 0x51,
		ASSET_TYPE_LIGHT_DESCRIPTION = 0x52,
		ASSET_TYPE_SHELLSHOCK = 0x53,
		ASSET_TYPE_XCAM = 0x54,
		ASSET_TYPE_BG_CACHE = 0x55,
		ASSET_TYPE_TEXTURE_COMBO = 0x56,
		ASSET_TYPE_FLAMETABLE = 0x57,
		ASSET_TYPE_BITFIELD = 0x58,
		ASSET_TYPE_ATTACHMENT_COSMETIC_VARIANT = 0x59,
		ASSET_TYPE_MAPTABLE = 0x5A,
		ASSET_TYPE_MAPTABLE_LOADING_IMAGES = 0x5B,
		ASSET_TYPE_MEDAL = 0x5C,
		ASSET_TYPE_MEDALTABLE = 0x5D,
		ASSET_TYPE_OBJECTIVE = 0x5E,
		ASSET_TYPE_OBJECTIVE_LIST = 0x5F,
		ASSET_TYPE_UMBRA_TOME = 0x60,
		ASSET_TYPE_NAVMESH = 0x61,
		ASSET_TYPE_NAVVOLUME = 0x62,
		ASSET_TYPE_BINARYHTML = 0x63,
		ASSET_TYPE_LASER = 0x64,
		ASSET_TYPE_BEAM = 0x65,
		ASSET_TYPE_STREAMER_HINT = 0x66,
		ASSET_TYPE_COUNT = 0x67,
		ASSET_TYPE_STRING = 0x68,
		ASSET_TYPE_ASSETLIST = 0x69,
		ASSET_TYPE_REPORT = 0x6A,
		ASSET_TYPE_DEPEND = 0x68,
		ASSET_TYPE_FULL_COUNT = 0x6C,
	};

	enum ControllerIndex_t : int
	{
		INVALID_CONTROLLER_PORT = -1,
		CONTROLLER_INDEX_0 = 0x0,
		CONTROLLER_INDEX_FIRST = 0x0,
		CONTROLLER_INDEX_1 = 0x1,
		CONTROLLER_INDEX_2 = 0x2,
		CONTROLLER_INDEX_3 = 0x3,
		CONTROLLER_INDEX_COUNT = 0x4,
	};

	enum eGameModes : __int32
	{
		MODE_GAME_MATCHMAKING_PLAYLIST = 0x0,
		MODE_GAME_MATCHMAKING_MANUAL = 0x1,
		MODE_GAME_DEFAULT = 0x2,
		MODE_GAME_LEAGUE = 0x3,
		MODE_GAME_THEATER = 0x4,
		MODE_GAME_COUNT = 0x5,
		MODE_GAME_INVALID = 0x5,
	};

	enum eModes : __int32
	{
		MODE_ZOMBIES = 0x0,
		MODE_MULTIPLAYER = 0x1,
		MODE_CAMPAIGN = 0x2,
		MODE_COUNT = 0x3,
		MODE_INVALID = 0x3,
		MODE_FIRST = 0x0,
	};

	enum LobbyClientType : __int32
	{
		LOBBY_CLIENT_TYPE_INVALID = -1,
		LOBBY_CLIENT_TYPE_ALL = 0x0,
		LOBBY_CLIENT_TYPE_LOCAL = 0x1,
		LOBBY_CLIENT_TYPE_REMOTE = 0x2,
		LOBBY_CLIENT_TYPE_SPLITSCREEN_ALL = 0x3,
		LOBBY_CLIENT_TYPE_SPLITSCREEN_REMOTE = 0x2,
		LOBBY_CLIENT_TYPE_GUEST = 0x2,
	};

	enum LocalClientNum_t : __int32
	{
		INVALID_LOCAL_CLIENT = -1,
		LOCAL_CLIENT_0 = 0x0,
		LOCAL_CLIENT_FIRST = 0x0,
		LOCAL_CLIENT_KEYBOARD_AND_MOUSE = 0x0,
		LOCAL_CLIENT_1 = 0x1,
		LOCAL_CLIENT_2 = 0x2,
		LOCAL_CLIENT_3 = 0x3,
		LOCAL_CLIENT_COUNT = 0x4,
	};

	enum class scriptInstance_t : int
	{
		SCRIPTINSTANCE_SERVER = 0x0,
		SCRIPTINSTANCE_CLIENT = 0x1,
		SCRIPT_INSTANCE_MAX = 0x2,
	};

	enum ClientNum_t : __int32
	{
		INVALID_CLIENT_INDEX = -1,
		CLIENT_INDEX_0 = 0x0,
		CLIENT_INDEX_FIRST = 0x0,
		CLIENT_INDEX_1 = 0x1,
		CLIENT_INDEX_2 = 0x2,
		CLIENT_INDEX_3 = 0x3,
		CLIENT_INDEX_4 = 0x4,
		CLIENT_INDEX_5 = 0x5,
		CLIENT_INDEX_6 = 0x6,
		CLIENT_INDEX_7 = 0x7,
		CLIENT_INDEX_8 = 0x8,
		CLIENT_INDEX_9 = 0x9,
		CLIENT_INDEX_10 = 0xA,
		CLIENT_INDEX_11 = 0xB,
		CLIENT_INDEX_12 = 0xC,
		CLIENT_INDEX_13 = 0xD,
		CLIENT_INDEX_14 = 0xE,
		CLIENT_INDEX_15 = 0xF,
		CLIENT_INDEX_16 = 0x10,
		CLIENT_INDEX_17 = 0x11,
		CLIENT_INDEX_18 = 0x12,
		CLIENT_INDEX_19 = 0x13,
		CLIENT_INDEX_20 = 0x14,
		CLIENT_INDEX_21 = 0x15,
		CLIENT_INDEX_22 = 0x16,
		CLIENT_INDEX_23 = 0x17,
		CLIENT_INDEX_24 = 0x18,
		CLIENT_INDEX_25 = 0x19,
		CLIENT_INDEX_26 = 0x1A,
		CLIENT_INDEX_27 = 0x1B,
		CLIENT_INDEX_28 = 0x1C,
		CLIENT_INDEX_29 = 0x1D,
		CLIENT_INDEX_30 = 0x1E,
		CLIENT_INDEX_31 = 0x1F,
		CLIENT_INDEX_COUNT = 0x12,
	};

	struct BuiltinFunctionDef
	{
		ScrVarCanonicalName_t canonwId;
		unsigned int min_args;
		unsigned int max_args;
		void(*actionFunc)(scriptInstance_t inst);
		int type;
	};

	struct AssetLink
	{
		AssetLink* next;
	};

	struct XAssetPool
	{
		void* pool;
		unsigned int itemSize;
		int itemCount;
		bool isSingleton[4];
		int itemAllocCount;
		AssetLink* freeHead;
	};

	union DvarValue
	{
		bool enabled;
		int integer;
		UINT unsignedInt;
		int64_t integer64;
		uint64_t unsignedInt64;
		float value;
		vec4_t vector;
		const char* string;
		BYTE color[4];
		const dvar_t* indirect[3];
	};

	struct $7034703ED3857507327AE195CCA24A71
	{
		int stringCount;
		const char** strings;
	};

	struct $5AC0CC375C7A91894540A0C75867866C
	{
		int min;
		int max;
	};

	struct $FCEE86E78F1A35297637B00F6DD148A3
	{
		int64_t min;
		int64_t max;
	};

	struct $28DE879AA85D5F4AA5DF9392CB197229
	{
		uint64_t min;
		uint64_t max;
	};

	struct $D2B45DCE3C73414E1DE8E10A2D52B392
	{
		float min;
		float max;
	};

	struct $97F25DA469865168FD08682F42882F2A
	{
		vec_t min;
		vec_t max;
	};

	union DvarLimits
	{
		$7034703ED3857507327AE195CCA24A71 enumeration;
		$5AC0CC375C7A91894540A0C75867866C integer;
		$FCEE86E78F1A35297637B00F6DD148A3 integer64;
		$28DE879AA85D5F4AA5DF9392CB197229 unsignedInt64;
		$D2B45DCE3C73414E1DE8E10A2D52B392 value;
		$97F25DA469865168FD08682F42882F2A vector;
	};

	enum CriticalSection : __int32
	{
		CRITSECT_ALLOC_MARK = 0x0,
		CRITSECT_FX_VIS = 0x1,
		CRITSECT_OCCLUSION_QUERY = 0x2,
		CRITSECT_PHYSICS = 0x3,
		CRITSECT_PHYSICS_UPDATE = 0x4,
		CRITSECT_PHYSICS_DESTRUCTIBLE_HIT = 0x5,
		CRITSECT_STREAM_ALLOC = 0x6,
		CRITSECT_STREAM_BACKEND_UPDATE = 0x7,
		CRITSECT_STREAM_CANCEL = 0x8,
		CRITSECT_STREAM_MODEL_BITS = 0x9,
		CRITSECT_FX_CHUNK_ALLOC = 0xA,
		CRITSECT_FX_UNIQUE_HANDLE = 0xB,
		CRITSECT_SOUND_COMMAND_ALLOC = 0xC,
		CRITSECT_SOUND_COMMAND_PUSH = 0xD,
		CRITSECT_SOUND_NOTIFY_ALLOC = 0xE,
		CRITSECT_SOUND_NOTIFY_PUSH = 0xF,
		CRITSECT_SOUND_BANK = 0x10,
		CRITSECT_SOUND_LOOKUP_CACHE = 0x11,
		CRITSECT_SOUND_SUBMIT = 0x12,
		CRITSECT_CAREER_STATS = 0x13,
		CRITSECT_CONSOLE = 0x14,
		CRITSECT_DEBUG_SOCKET = 0x15,
		CRITSECT_COM_ERROR = 0x16,
		CRITSECT_STATMON = 0x17,
		CRITSECT_MEM_ALLOC0 = 0x18,
		CRITSECT_MEM_ALLOC1 = 0x19,
		CRITSECT_MEM_ALLOC2 = 0x1A,
		CRITSECT_MEM_ALLOC3 = 0x1B,
		CRITSECT_MEM_ALLOC4 = 0x1C,
		CRITSECT_MEM_ALLOC5 = 0x1D,
		CRITSECT_MEM_ALLOC6 = 0x1E,
		CRITSECT_MEM_ALLOC7 = 0x1F,
		CRITSECT_MEM_ALLOC8 = 0x20,
		CRITSECT_MEM_ASYNC_COMMIT = 0x21,
		CRITSECT_DEBUG_LINE = 0x22,
		CRITSECT_DEBUG_BRUSHES_AND_PATCHES = 0x23,
		CRITSECT_DEBUG_HAVOK_AI = 0x24,
		CRITSECT_CLIENT_MESSAGE = 0x25,
		CRITSECT_CLIENT_CMD = 0x26,
		CRITSECT_DOBJ_ALLOC = 0x27,
		CRITSECT_XANIM_ALLOC = 0x28,
		CRITSECT_KEY_BINDINGS = 0x29,
		CRITSECT_SERVER_MESSAGE = 0x2A,
		CRITSECT_SERVER_PLAYERINFO = 0x2B,
		CRITSECT_SERVER_TICK = 0x2C,
		CRITSECT_SCRIPT_STRING = 0x2D,
		CRITSECT_MEMORY_TREE = 0x2E,
		CRITSECT_ASSERT = 0x2F,
		CRITSECT_SCRIPT_DEBUGGER = 0x30,
		CRITSECT_VM = 0x31,
		CRITSECT_THREADED_NOTIFY_QUEUE = 0x32,
		CRITSECT_MISSING_ASSET = 0x33,
		CRITSECT_LIVE = 0x34,
		CRITSECT_PCACHE = 0x35,
		CRITSECT_AUDIO_PHYSICS = 0x36,
		CRITSECT_LUA = 0x37,
		CRITSECT_LUI = 0x38,
		CRITSECT_LOBBY_LUA = 0x39,
		CRITSECT_EXTRACAM = 0x3A,
		CRITSECT_CINEMATIC = 0x3B,
		CRITSECT_CINEMATIC_MP4 = 0x3C,
		CRITSECT_CINEMATIC_UPDATEFRAME = 0x3D,
		CRITSECT_SAVE_PROFILE = 0x3E,
		CRITSECT_MEM_CONTAINER_SAVEGAME = 0x3F,
		CRITSECT_VIRTUALALLOC = 0x40,
		CRITSECT_RB_TRANSFER = 0x41,
		CRITSECT_STREAM_SYNC_COMMAND = 0x42,
		CRITSECT_STREAM_FIXEDIMAGE_UPDATE = 0x43,
		CRITSECT_STREAM_MODELHINT_UPDATE = 0x44,
		CRITSECT_NETTHREAD_OVERRIDE = 0x45,
		CRITSECT_DWLSG = 0x46,
		CRITSECT_DWNET = 0x47,
		CRITSECT_IK = 0x48,
		CRITSECT_TL_MEMALLOC = 0x49,
		CRITSECT_VA_ALLOC = 0x4A,
		CRITSECT_MEMTRACK = 0x4B,
		CRITSECT_CBUF = 0x4C,
		CRITSECT_CURVEALLOC = 0x4D,
		CRITSECT_NETQUEUE = 0x4E,
		CRITSECT_ZLIB = 0x4F,
		CRITSECT_BLACKBOX = 0x50,
		CRITSECT_GDT_COMMAND = 0x51,
		CRITSECT_STRINGED_COMMAND = 0x52,
		CRITSECT_RADIANT_SERVER_COMMAND = 0x53,
		CRITSECT_RADIANT_CLIENT_COMMAND = 0x54,
		CRITSECT_RECORDER = 0x55,
		CRITSECT_SERVERDEMO = 0x56,
		CRITSECT_IO_SCHEDULER = 0x57,
		CRITSECT_FILE_ID_ARRAY = 0x58,
		CRITSECT_MEMFIRSTFIT = 0x59,
		CRITSECT_FXBEAM = 0x5A,
		CRITSECT_GLASS_ACTIONS = 0x5B,
		CRITSECT_DBHASH = 0x5C,
		CRITSECT_DEVHOST = 0x5D,
		CRITSECT_CLUMP = 0x5E,
		CRITSECT_SNAPSHOT_PROFILE = 0x5F,
		CRITSEC_WEBM_STREAM_ACCESS = 0x60,
		CRITSEC_SV_LEADERBOARDS = 0x61,
		CRITSECT_FONT_CACHE = 0x62,
		CRITSEC_NETCHAN = 0x63,
		CRITSECT_SWITCHMAP_SV = 0x64,
		CRITSECT_SWITCHMAP_CL = 0x65,
		CRITSECT_DB_THROTTLE_DECOMPRESSION = 0x66,
		CRITSECT_PROFILE_BUF = 0x67,
		CRITSECT_SAVE_DEVICE = 0x68,
		CRITSECT_WATER_INTERACTION = 0x69,
		CRITSECT_WATER_GRID_ALLOC = 0x6A,
		CRITSECT_WATER_NODE_ALLOC = 0x6B,
		CRITSECT_MEM_PAGED = 0x6C,
		CRITSECT_ENTITY_COLL_LINK = 0x6D,
		CRITSECT_MINIZ = 0x6E,
		CRITSECT_COMPOSITING = 0x6F,
		CRITSECT_CREATE_DYNENT = 0x70,
		CRITSECT_LENSFLARES_INSTANCE_POOL_ACCESS0 = 0x71,
		CRITSECT_LENSFLARES_INSTANCE_POOL_ACCESS1 = 0x72,
		CRITSECT_LENSFLARES_INSTANCE_POOL_ACCESS2 = 0x73,
		CRITSECT_LENSFLARES_INSTANCE_POOL_ACCESS3 = 0x74,
		CRITSECT_LENSFLARES_INSTANCE_POOL_ACCESS4 = 0x75,
		CRITSECT_LENSFLARES_ACTIVE_INSTANCES_ACCESS0 = 0x76,
		CRITSECT_LENSFLARES_ACTIVE_INSTANCES_ACCESS1 = 0x77,
		CRITSECT_LENSFLARES_ACTIVE_INSTANCES_ACCESS2 = 0x78,
		CRITSECT_LENSFLARES_ACTIVE_INSTANCES_ACCESS3 = 0x79,
		CRITSECT_LENSFLARES_ACTIVE_INSTANCES_ACCESS4 = 0x7A,
		CRITSECT_LENSFLARES_SOURCE_ACCESS0 = 0x7B,
		CRITSECT_LENSFLARES_SOURCE_ACCESS1 = 0x7C,
		CRITSECT_LENSFLARES_SOURCE_ACCESS2 = 0x7D,
		CRITSECT_LENSFLARES_SOURCE_ACCESS3 = 0x7E,
		CRITSECT_LENSFLARES_SOURCE_ACCESS4 = 0x7F,
		CRITSECT_COMSCORE = 0x80,
		CRITSECT_DEBUG_TOPRIGHT_TXT = 0x81,
		CRITSECT_WEAPON_DOBJ_INFO_ALLOC = 0x82,
		CRITSECT_LIVE_ALLOC = 0x83,
		CRITSECT_UMBRA_SPOTOMNI_CACHE = 0x84,
		CRITSECT_UMBRA_JOB = 0x85,
		CRITSECT_COUNT = 0x86,
	};

	struct LuaScopedEventBase;
	struct ScopedCriticalSection
	{
		CriticalSection _s;
		bool _hasOwnership;
		bool _isScopedRelease;
		ScopedCriticalSection* _next;
	};

	typedef void (*LUA_EVENT_FUNC)(LuaScopedEventBase*);

	enum dvarFlags_e
	{
		DVAR_ARCHIVE = 1 << 0,
		DVAR_USERINFO = 1 << 1,
		DVAR_SYSTEMINFO = 1 << 2,
		DVAR_CODINFO = 1 << 3,
		DVAR_LATCH = 1 << 4,
		DVAR_ROM = 1 << 5,
		DVAR_SAVED = 1 << 6,
		DVAR_INIT = 1 << 7,
		DVAR_CHEAT = 1 << 8,
		//DVAR_UNKNOWN = 1 << 9,
		DVAR_EXTERNAL = 1 << 10,
		//DVAR_UNKNOWN3x = 1 << 11-13,
		DVAR_SESSIONMODE = 1 << 15
	};
	//TODO: sizeof == 0x88 (136), need 0xA0 (160)
	struct dvar_t
	{
		dvarStrHash_t name;
		const char* debugName;
		const char* description;
		dvarFlags_e flags;
		dvarType_t type;
		bool modified;
		DvarValue current;
		DvarValue latched;
		DvarValue reset;
		DvarLimits domain;
		dvar_t* hashNext;
	};

	struct LuaScopedEventBase
	{
		lua::lua_State* _vm;
		char _functionName[32];
		int _argCount;
		int _popCount;
		int _returnCount;
		bool _failed;
		bool _finished;
		bool _processed;
		ScopedCriticalSection _scopedCritSect;
		LUA_EVENT_FUNC _pushFn;
		LUA_EVENT_FUNC _returnFn;
	};

	struct  LuaScopedEvent : LuaScopedEventBase
	{
	};

	struct __declspec(align(8)) LUIScopedEvent : LuaScopedEvent
	{
		bool _initializedWithElement;
	};

	struct TTFKerningEntry
	{
		uint16_t height;
		uint16_t prevCharIndex;
		uint16_t nextCharIndex;
		int16_t kerning;
	};

	struct TTFDef
	{
		const char* name;
		int fileLen;
		const char* file;
		void* ftFace;
		TTFKerningEntry kerningCache[16384];
	};

	typedef void* MaterialHandle; // typedef Material* MaterialHandle;
	typedef MaterialHandle LUA_MATERIAL_DATATYPE;

	struct __declspec(align(8)) LUIAnimationState
	{
		LUA_MATERIAL_DATATYPE material;
		TTFDef* font;
		uint64_t flags;
		int luaRef;
		unsigned __int8 tweenFlags;
		int ui3DWindow;
		float leftPct;
		float topPct;
		float rightPct;
		float bottomPct;
		float leftPx;
		float topPx;
		float rightPx;
		float bottomPx;
		float globalLeft;
		float globalTop;
		float globalRight;
		float globalBottom;
		float zoom;
		float xRot;
		float yRot;
		float zRot;
		float scale;
		float red;
		float green;
		float blue;
		float alpha;
		vec4_t shaderVector0;
		vec4_t shaderVector1;
		vec4_t shaderVector2;
		vec4_t shaderVector3;
		vec4_t shaderVector4;
	};

	struct __declspec(align(8)) LUIElement
	{
		LUIAnimationState currentAnimationState;
		LUIElement* parent;
		LUIElement* prevSibling;
		LUIElement* nextSibling;
		LUIElement* firstChild;
		LUIElement* lastChild;
	};

	struct XAnimNotifyInfo
	{
		ScrString_t type;
		float time;
		ScrString_t param1;
		ScrString_t param2;
	};

	typedef void (*xcommand_t)(void);

	struct cmd_function_t
	{
		cmd_function_t* next;
		const char* name;
		const char* autoCompleteDir;
		const char* autoCompleteExt;
		xcommand_t function;
		int unknown;
	};

	struct scr_const_t
	{
		ScrString_t _;
		ScrString_t active;
		ScrString_t spawn;
		ScrString_t exit;
		ScrString_t j_neck;
		ScrString_t aim_bone;
		ScrString_t aim_highest_bone;
		ScrString_t aim_vis_bone;
		ScrString_t aim_tag;
		ScrString_t aim_delta;
		ScrString_t alert;
		ScrString_t all;
		ScrString_t allies;
		ScrString_t ambush;
		ScrString_t ambush_nodes_only;
		ScrString_t angles;
		ScrString_t any_exposed_nodes_only;
		ScrString_t arc_min_pitch;
		ScrString_t arc_max_pitch;
		ScrString_t arc_min_yaw;
		ScrString_t arc_max_yaw;
		ScrString_t asleep;
		ScrString_t asm_aim_deltas;
		ScrString_t asm_animsource;
		ScrString_t asm_deltanormtime;
		ScrString_t asm_complete;
		ScrString_t asm_external;
		ScrString_t asm_inactive;
		ScrString_t asm_running;
		ScrString_t asm_status;
		ScrString_t asm_substate;
		ScrString_t asm_terminated;
		ScrString_t asm_transdec;
		ScrString_t asm_transition;
		ScrString_t blend_in_time;
		ScrString_t blend_out_time;
		ScrString_t rowIndex;
		ScrString_t animation;
		ScrString_t animation_mocomp;
		ScrString_t aim_up;
		ScrString_t aim_down;
		ScrString_t aim_left;
		ScrString_t aim_right;
		ScrString_t avoid_all;
		ScrString_t avoid_none;
		ScrString_t avoid_actor;
		ScrString_t avoid_ai;
		ScrString_t avoid_player;
		ScrString_t avoid_vehicle;
		ScrString_t bad_path;
		ScrString_t new_cover;
		ScrString_t begin_firing;
		ScrString_t unknown_location;
		ScrString_t cancel_location;
		ScrString_t collision_penalty;
		ScrString_t combat;
		ScrString_t cover;
		ScrString_t confirm_location;
		ScrString_t crouch;
		ScrString_t current;
		ScrString_t damage;
		ScrString_t deathshield;
		ScrString_t damage_afterdeath;
		ScrString_t death;
		ScrString_t disconnect;
		ScrString_t death_or_disconnect;
		ScrString_t detonate;
		ScrString_t direct;
		ScrString_t dlight;
		ScrString_t dodging_penalty;
		ScrString_t done;
		ScrString_t dropweapon;
		ScrString_t empty;
		ScrString_t end_firing;
		ScrString_t enter_vehicle;
		ScrString_t entity;
		ScrString_t exit_vehicle;
		ScrString_t exposed_nodes_only;
		ScrString_t change_seat;
		ScrString_t vehicle_death;
		ScrString_t explode;
		ScrString_t corpse_explode;
		ScrString_t failed;
		ScrString_t fall_damage;
		ScrString_t fraction;
		ScrString_t free;
		ScrString_t free_vehicle;
		ScrString_t goal;
		ScrString_t goal_changed;
		ScrString_t goal_yaw;
		ScrString_t at_anchor;
		ScrString_t grenade;
		ScrString_t grenade_danger;
		ScrString_t grenade_flee;
		ScrString_t grenade_fire;
		ScrString_t grenade_launcher_fire;
		ScrString_t grenade_pullback;
		ScrString_t grenade_throwback;
		ScrString_t stationary;
		ScrString_t rolling;
		ScrString_t grenade_stuck;
		ScrString_t grenade_bounce;
		ScrString_t hero;
		ScrString_t high;
		ScrString_t high_alert;
		ScrString_t in3d;
		ScrString_t info_notnull;
		ScrString_t info_volume;
		ScrString_t invisible;
		ScrString_t j_gun;
		ScrString_t key1;
		ScrString_t key2;
		ScrString_t killcam_begin;
		ScrString_t killcam_end;
		ScrString_t killanimscript;
		ScrString_t length;
		ScrString_t laser_on;
		ScrString_t laser_off;
		ScrString_t left;
		ScrString_t left_tread;
		ScrString_t light;
		ScrString_t low;
		ScrString_t low_alert;
		ScrString_t gadget_forced_off;
		ScrString_t gadget_denied_activation;
		ScrString_t gadget_casting_anim;
		ScrString_t melee_cybercom;
		ScrString_t melee_end;
		ScrString_t missile_fire;
		ScrString_t missile_boost;
		ScrString_t missile_brake;
		ScrString_t movedone;
		ScrString_t multikill;
		ScrString_t name;
		ScrString_t next_node;
		ScrString_t next_shot_kills;
		ScrString_t no_cover;
		ScrString_t only_cover;
		ScrString_t noclass;
		ScrString_t node;
		ScrString_t noncombat;
		ScrString_t none;
		ScrString_t normal;
		ScrString_t normal_nogravity;
		ScrString_t origin;
		ScrString_t over;
		ScrString_t player;
		ScrString_t point_relative;
		ScrString_t position;
		ScrString_t projectile_impact;
		ScrString_t projectile_impact_explode;
		ScrString_t projectile_applyattractor;
		ScrString_t projectile_alertattractor;
		ScrString_t prone;
		ScrString_t reflection_probe;
		ScrString_t result;
		ScrString_t right;
		ScrString_t right_tread;
		ScrString_t tank_armor;
		ScrString_t radius;
		ScrString_t reload;
		ScrString_t reload_start;
		ScrString_t rocket;
		ScrString_t rotatedone;
		ScrString_t score;
		ScrString_t script_brushmodel;
		ScrString_t script_model;
		ScrString_t script_origin;
		ScrString_t snd_enveffectsprio_level;
		ScrString_t snd_enveffectsprio_shellshock;
		ScrString_t snd_busvolprio_holdbreath;
		ScrString_t snd_busvolprio_pain;
		ScrString_t snd_busvolprio_shellshock;
		ScrString_t stand;
		ScrString_t start_aim;
		ScrString_t stop_aim;
		ScrString_t exit_align;
		ScrString_t code_move;
		ScrString_t fire;
		ScrString_t about_to_fire;
		ScrString_t stopped_firing;
		ScrString_t suppression;
		ScrString_t suppression_end;
		ScrString_t surfacetype;
		ScrString_t tag_aim;
		ScrString_t tag_aim_pitch;
		ScrString_t tag_aim_animated;
		ScrString_t tag_brass;
		ScrString_t tag_brass_le;
		ScrString_t tag_brass_2;
		ScrString_t tag_butt;
		ScrString_t tag_clip;
		ScrString_t tag_clip_le;
		ScrString_t tag_flash;
		ScrString_t tag_flash_le;
		ScrString_t tag_flash2;
		ScrString_t tag_flash3;
		ScrString_t tag_flash4;
		ScrString_t tag_flash_alt;
		ScrString_t tag_gunner_barrel1;
		ScrString_t tag_gunner_barrel2;
		ScrString_t tag_gunner_barrel3;
		ScrString_t tag_gunner_barrel4;
		ScrString_t tag_gunner_turret1;
		ScrString_t tag_gunner_turret2;
		ScrString_t tag_gunner_turret3;
		ScrString_t tag_gunner_turret4;
		ScrString_t tag_gunner_brass1;
		ScrString_t tag_gunner_brass1a;
		ScrString_t tag_gunner_brass2;
		ScrString_t tag_gunner_brass2a;
		ScrString_t tag_gunner_hands1;
		ScrString_t tag_wheel_front_left;
		ScrString_t tag_wheel_front_right;
		ScrString_t tag_wheel_back_left;
		ScrString_t tag_wheel_back_right;
		ScrString_t tag_wheel_middle_left;
		ScrString_t tag_wheel_middle_right;
		ScrString_t tag_wheel_front;
		ScrString_t tag_wheel_back;
		ScrString_t tag_main_rotor;
		ScrString_t tag_tail_rotor;
		ScrString_t tag_main_rotor_blur;
		ScrString_t tag_main_rotor_static;
		ScrString_t tag_tail_rotor_blur;
		ScrString_t tag_tail_rotor_static;
		ScrString_t tag_rotor_fl_arm;
		ScrString_t tag_rotor_fr_arm;
		ScrString_t tag_rotor_rl_arm;
		ScrString_t tag_rotor_rr_arm;
		ScrString_t tag_antenna1;
		ScrString_t tag_antenna2;
		ScrString_t tag_antenna3;
		ScrString_t tag_antenna4;
		ScrString_t tag_fx;
		ScrString_t tag_inhand;
		ScrString_t tag_jetpack_left;
		ScrString_t tag_jetpack_right;
		ScrString_t tag_knife_attach;
		ScrString_t tag_knife_fx;
		ScrString_t tag_laser;
		ScrString_t tag_laser1;
		ScrString_t tag_laser2;
		ScrString_t tag_origin;
		ScrString_t tag_weapon;
		ScrString_t tag_weapon1;
		ScrString_t tag_explosive;
		ScrString_t tag_player;
		ScrString_t tag_camera;
		ScrString_t tag_camera_cinematic;
		ScrString_t tag_weapon_right;
		ScrString_t tag_weapon_left;
		ScrString_t tag_weapon_le;
		ScrString_t tag_weapon_chest;
		ScrString_t tag_stowed_back;
		ScrString_t tag_gasmask;
		ScrString_t tag_gasmask2;
		ScrString_t tag_sync;
		ScrString_t tag_wake;
		ScrString_t tag_bcpu;
		ScrString_t tag_sight_level;
		ScrString_t target_script_trigger;
		ScrString_t tag_nameplate;
		ScrString_t team3;
		ScrString_t team4;
		ScrString_t team5;
		ScrString_t team6;
		ScrString_t team7;
		ScrString_t team8;
		ScrString_t team9;
		ScrString_t team10;
		ScrString_t team11;
		ScrString_t team12;
		ScrString_t team13;
		ScrString_t team14;
		ScrString_t team15;
		ScrString_t team16;
		ScrString_t team17;
		ScrString_t team18;
		ScrString_t team_changed;
		ScrString_t tempEntity;
		ScrString_t top;
		ScrString_t touch;
		ScrString_t trigger;
		ScrString_t trigger_use;
		ScrString_t trigger_use_touch;
		ScrString_t trigger_damage;
		ScrString_t trigger_lookat;
		ScrString_t trigger_radius;
		ScrString_t trigger_box;
		ScrString_t trigger_box_use;
		ScrString_t trigger_radius_use;
		ScrString_t trigger_hurt;
		ScrString_t truck_cam;
		ScrString_t turret_scan_start;
		ScrString_t turret_return_default_pos;
		ScrString_t turret_scan_stop;
		ScrString_t turret_target_aquired;
		ScrString_t turret_target_lost;
		ScrString_t turret_tow_fire;
		ScrString_t turret_tow_unlink;
		ScrString_t type;
		ScrString_t unaware;
		ScrString_t weapon_change_on_turret;
		ScrString_t weapon_change;
		ScrString_t weapon_change_complete;
		ScrString_t weapon_raising;
		ScrString_t weapon_fired;
		ScrString_t ball_pass;
		ScrString_t weapon_melee;
		ScrString_t weapon_melee_power;
		ScrString_t weapon_melee_power_left;
		ScrString_t weapon_melee_charge;
		ScrString_t weapon_melee_charge_end;
		ScrString_t weapon_melee_juke;
		ScrString_t weapon_melee_juke_end;
		ScrString_t weapon_juke_end_requested;
		ScrString_t target_meleed;
		ScrString_t weapon_assassination;
		ScrString_t weapon_switch_started;
		ScrString_t weapon_ads;
		ScrString_t tactical_menu_open;
		ScrString_t tactical_menu_close;
		ScrString_t tactical_menu_toggle;
		ScrString_t raise_riotshield;
		ScrString_t deploy_riotshield;
		ScrString_t pickup_riotshield;
		ScrString_t worldspawn;
		ScrString_t flashbang;
		ScrString_t flash;
		ScrString_t smoke;
		ScrString_t night_vision_on;
		ScrString_t night_vision_off;
		ScrString_t back;
		ScrString_t back_low;
		ScrString_t back_mid;
		ScrString_t back_up;
		ScrString_t head;
		ScrString_t j_mainroot;
		ScrString_t neck;
		ScrString_t pelvis;
		ScrString_t j_shoulder_le;
		ScrString_t shoulder;
		ScrString_t j_head;
		ScrString_t j_helmet;
		ScrString_t j_clavicle_ri;
		ScrString_t j_clavicle_le;
		ScrString_t purchased;
		ScrString_t for_sale;
		ScrString_t blacklisted;
		ScrString_t wrong_era;
		ScrString_t locked;
		ScrString_t MOD_UNKNOWN;
		ScrString_t MOD_PISTOL_BULLET;
		ScrString_t MOD_RIFLE_BULLET;
		ScrString_t MOD_GRENADE;
		ScrString_t MOD_GRENADE_SPLASH;
		ScrString_t MOD_PROJECTILE;
		ScrString_t MOD_PROJECTILE_SPLASH;
		ScrString_t MOD_MELEE;
		ScrString_t MOD_MELEE_WEAPON_BUTT;
		ScrString_t MOD_MELEE_ASSASSINATE;
		ScrString_t MOD_HEAD_SHOT;
		ScrString_t MOD_CRUSH;
		ScrString_t MOD_TELEFRAG;
		ScrString_t MOD_FALLING;
		ScrString_t MOD_SUICIDE;
		ScrString_t MOD_TRIGGER_HURT;
		ScrString_t MOD_EXPLOSIVE;
		ScrString_t MOD_IMPACT;
		ScrString_t MOD_BURNED;
		ScrString_t MOD_ELECTROCUTED;
		ScrString_t MOD_HIT_BY_OBJECT;
		ScrString_t MOD_DROWN;
		ScrString_t MOD_GAS;
		ScrString_t MOD_POST_GAME;
		ScrString_t face;
		ScrString_t face_alert;
		ScrString_t face_casual;
		ScrString_t face_cqb;
		ScrString_t face_running;
		ScrString_t face_shoot_single;
		ScrString_t face_shoot_burst;
		ScrString_t face_react;
		ScrString_t face_talk;
		ScrString_t face_talk_long;
		ScrString_t face_pain;
		ScrString_t face_melee;
		ScrString_t face_death;
		ScrString_t script_vehicle;
		ScrString_t turret_fire;
		ScrString_t turret_on_target;
		ScrString_t gunner_turret_on_target;
		ScrString_t gunner_turret_overheat;
		ScrString_t gunner_turret_stop_overheat;
		ScrString_t turret_not_on_target;
		ScrString_t turret_rotate_stopped;
		ScrString_t turret_rotate_moving;
		ScrString_t turret_deactivate;
		ScrString_t turretstatechange;
		ScrString_t turretownerchange;
		ScrString_t reached_node;
		ScrString_t reached_end_node;
		ScrString_t reached_wait_node;
		ScrString_t reached_wait_speed;
		ScrString_t near_goal;
		ScrString_t veh_collision;
		ScrString_t veh_predictedcollision;
		ScrString_t veh_inair;
		ScrString_t veh_landed;
		ScrString_t veh_suspension_limit_activated;
		ScrString_t veh_engine_stutter;
		ScrString_t veh_ejectoccupants;
		ScrString_t veh_heightmesh_max;
		ScrString_t veh_heightmesh_min;
		ScrString_t veh_stuck;
		ScrString_t veh_boost;
		ScrString_t begin;
		ScrString_t script_camera;
		ScrString_t jumpcut;
		ScrString_t playerbreathinsound;
		ScrString_t playerbreathgaspsound;
		ScrString_t playerbreathoutsound;
		ScrString_t mantlesoundplayer;
		ScrString_t meleeswipesoundplayer;
		ScrString_t dtplandsoundplayer;
		ScrString_t traversesound;
		ScrString_t curve_nodehit;
		ScrString_t curve_start;
		ScrString_t curve_end;
		ScrString_t asphalt;
		ScrString_t bark;
		ScrString_t brick;
		ScrString_t carpet;
		ScrString_t ceramic;
		ScrString_t cloth;
		ScrString_t concrete;
		ScrString_t cushion;
		ScrString_t dirt;
		ScrString_t flesh;
		ScrString_t foliage;
		ScrString_t fruit;
		ScrString_t glass;
		ScrString_t grass;
		ScrString_t gravel;
		ScrString_t ice;
		ScrString_t metal;
		ScrString_t mud;
		ScrString_t paintedmetal;
		ScrString_t paper;
		ScrString_t plaster;
		ScrString_t plastic;
		ScrString_t riotshield;
		ScrString_t rock;
		ScrString_t rubber;
		ScrString_t sand;
		ScrString_t snow;
		ScrString_t tallgrass;
		ScrString_t water;
		ScrString_t wood;
		ScrString_t metal_thin;
		ScrString_t metal_hollow;
		ScrString_t metal_catwalk;
		ScrString_t metal_car;
		ScrString_t glass_car;
		ScrString_t glass_bulletproof;
		ScrString_t water_shallow;
		ScrString_t body_armor;
		ScrString_t host_sucks_end_game;
		ScrString_t look;
		ScrString_t freelook;
		ScrString_t localplayers;
		ScrString_t tag_driver;
		ScrString_t tag_driver_camera;
		ScrString_t tag_passenger;
		ScrString_t tag_passenger2;
		ScrString_t tag_passenger3;
		ScrString_t tag_passenger4;
		ScrString_t tag_passenger5;
		ScrString_t tag_passenger6;
		ScrString_t tag_gunner1;
		ScrString_t tag_gunner2;
		ScrString_t tag_gunner3;
		ScrString_t tag_gunner4;
		ScrString_t tag_enter_driver;
		ScrString_t tag_enter_passenger;
		ScrString_t tag_enter_passenger2;
		ScrString_t tag_enter_passenger3;
		ScrString_t tag_enter_passenger4;
		ScrString_t tag_enter_gunner1;
		ScrString_t tag_enter_gunner2;
		ScrString_t tag_enter_gunner3;
		ScrString_t tag_enter_gunner4;
		ScrString_t tag_enter_right;
		ScrString_t tag_enter_left;
		ScrString_t tag_enter_back;
		ScrString_t script_vehicle_corpse;
		ScrString_t tag_popout;
		ScrString_t tag_body;
		ScrString_t tag_turret;
		ScrString_t tag_barrel;
		ScrString_t tag_barrel_recoil;
		ScrString_t tag_barrel_spin;
		ScrString_t tag_engine_left;
		ScrString_t tag_engine_right;
		ScrString_t tag_spin;
		ScrString_t tag_minigun_spin;
		ScrString_t front_left;
		ScrString_t front_right;
		ScrString_t back_left;
		ScrString_t back_right;
		ScrString_t middle_left;
		ScrString_t middle_right;
		ScrString_t stuck_to_player;
		ScrString_t stuck_to_shield;
		ScrString_t auto_ai;
		ScrString_t auto_nonai;
		ScrString_t manual;
		ScrString_t manual_ai;
		ScrString_t scavenger;
		ScrString_t neutral;
		ScrString_t moon_gravity;
		ScrString_t auto_change;
		ScrString_t call_vote;
		ScrString_t intermission;
		ScrString_t manual_change;
		ScrString_t pistol;
		ScrString_t plane_waypoint;
		ScrString_t playing;
		ScrString_t spectator;
		ScrString_t spectator_cycle;
		ScrString_t vote;
		ScrString_t sprint_begin;
		ScrString_t sprint_end;
		ScrString_t wallrun_begin;
		ScrString_t wallrun_end;
		ScrString_t doublejump_begin;
		ScrString_t doublejump_end;
		ScrString_t jump_begin;
		ScrString_t jump_end;
		ScrString_t slide_begin;
		ScrString_t slide_end;
		ScrString_t climb_begin;
		ScrString_t climb_end;
		ScrString_t acrobatics_begin;
		ScrString_t acrobatics_end;
		ScrString_t tag_gunner_pov;
		ScrString_t tag_flamer_pilot_light;
		ScrString_t tag_fx_front;
		ScrString_t tag_fx_right;
		ScrString_t tag_fx_left;
		ScrString_t flared_or_tabuned_death;
		ScrString_t destroyed_vehicle;
		ScrString_t vehicle_driver;
		ScrString_t died_in_turret;
		ScrString_t trigger_use_doubletap;
		ScrString_t doubletap_detonate;
		ScrString_t dtp_through_glass;
		ScrString_t dtp_start;
		ScrString_t dtp_end;
		ScrString_t mantle_start;
		ScrString_t mantle_end;
		ScrString_t draw;
		ScrString_t axis;
		ScrString_t dead;
		ScrString_t stats_merged;
		ScrString_t action_notify_attack;
		ScrString_t action_notify_melee;
		ScrString_t action_notify_use_reload;
		ScrString_t action_notify_use_doubletap;
		ScrString_t always;
		ScrString_t bullethit;
		ScrString_t assassination_start;
		ScrString_t being_assassinate_start;
		ScrString_t count;
		ScrString_t corner_approach;
		ScrString_t damage_notdone;
		ScrString_t fadeoutonscreen;
		ScrString_t drawdistance;
		ScrString_t drawname;
		ScrString_t clipToMap;
		ScrString_t primary;
		ScrString_t high_priority;
		ScrString_t info_player_deathmatch;
		ScrString_t low_priority;
		ScrString_t menuresponse;
		ScrString_t never;
		ScrString_t perk;
		ScrString_t pickup;
		ScrString_t receiver;
		ScrString_t sound_blend;
		ScrString_t grenade_return_hand_tag;
		ScrString_t infinite_energy;
		ScrString_t max_time;
		ScrString_t min_energy;
		ScrString_t min_time;
		ScrString_t human;
		ScrString_t robot;
		ScrString_t remote_revive;
		ScrString_t begin_custom_anim;
		ScrString_t deathplant;
		ScrString_t zombie;
		ScrString_t zombie_dog;
		ScrString_t _custom;
		ScrString_t angle_deltas;
		ScrString_t angle_deltas_noclip;
		ScrString_t bulletwhizby;
		ScrString_t can_see_enemy;
		ScrString_t dog;
		ScrString_t dont_move;
		ScrString_t contact;
		ScrString_t enemy;
		ScrString_t no_enemy;
		ScrString_t enemy_visible;
		ScrString_t enemy_not_visible;
		ScrString_t face_angle;
		ScrString_t face_current;
		ScrString_t face_default;
		ScrString_t face_direction;
		ScrString_t face_enemy;
		ScrString_t face_enemy_or_motion;
		ScrString_t face_enemy_or_motion_sidestep;
		ScrString_t face_goal;
		ScrString_t face_motion;
		ScrString_t face_point;
		ScrString_t gravity;
		ScrString_t groundEntChanged;
		ScrString_t gunshot;
		ScrString_t obstacle;
		ScrString_t movemode;
		ScrString_t move_allowed;
		ScrString_t move_delayed;
		ScrString_t noclip;
		ScrString_t slide;
		ScrString_t node_out_of_range;
		ScrString_t node_relinquished;
		ScrString_t node_taken;
		ScrString_t node_not_safe;
		ScrString_t nogravity;
		ScrString_t nophysics;
		ScrString_t pain;
		ScrString_t path_mode_invalid;
		ScrString_t react;
		ScrString_t pos_deltas;
		ScrString_t run;
		ScrString_t runto_arrived;
		ScrString_t silenced_shot;
		ScrString_t spawned;
		ScrString_t spawned_player;
		ScrString_t spawned_spectator;
		ScrString_t start_move;
		ScrString_t start_ragdoll;
		ScrString_t stop;
		ScrString_t stop_soon;
		ScrString_t tag_eye;
		ScrString_t walk;
		ScrString_t walkable;
		ScrString_t world;
		ScrString_t zonly_physics;
		ScrString_t down;
		ScrString_t j_ankle_le;
		ScrString_t j_ankle_ri;
		ScrString_t j_ball_le;
		ScrString_t j_ball_ri;
		ScrString_t j_palm_le;
		ScrString_t j_palm_ri;
		ScrString_t j_elbow_le;
		ScrString_t j_elbow_ri;
		ScrString_t j_wrist_le;
		ScrString_t j_wrist_ri;
		ScrString_t j_spinelower;
		ScrString_t j_spineupper;
		ScrString_t j_teeth_upper;
		ScrString_t broken;
		ScrString_t destructible;
		ScrString_t destructible_base_piece_death;
		ScrString_t breakafter;
		ScrString_t snapacknowledged;
		ScrString_t snap_processed;
		ScrString_t j_counter;
		ScrString_t j_dial_left;
		ScrString_t j_dial_right;
		ScrString_t tag_spinner_r_front;
		ScrString_t tag_spinner_l_front;
		ScrString_t tag_spinner_r_1;
		ScrString_t tag_spinner_l_1;
		ScrString_t tag_spinner_r_2;
		ScrString_t tag_spinner_l_2;
		ScrString_t tag_spinner_r_3;
		ScrString_t tag_spinner_l_3;
		ScrString_t ca_disconnected;
		ScrString_t ca_cinematic;
		ScrString_t ca_uicinematic;
		ScrString_t ca_logo;
		ScrString_t ca_connecting;
		ScrString_t ca_challenging;
		ScrString_t ca_connected;
		ScrString_t ca_sendingstats;
		ScrString_t ca_loading;
		ScrString_t ca_primed;
		ScrString_t ca_active;
		ScrString_t ca_map_restart;
		ScrString_t orientdone;
		ScrString_t menu_changed;
		ScrString_t unlink;
		ScrString_t init;
		ScrString_t move;
		ScrString_t traverse;
		ScrString_t custom_traversal;
		ScrString_t idle;
		ScrString_t move_run;
		ScrString_t move_sprint;
		ScrString_t move_stumpy;
		ScrString_t move_start;
		ScrString_t move_stop;
		ScrString_t move_walk;
		ScrString_t move_turn_left;
		ScrString_t move_turn_right;
		ScrString_t move_run_turn_left;
		ScrString_t move_run_turn_right;
		ScrString_t move_turn_around_left;
		ScrString_t move_turn_around_right;
		ScrString_t move_run_turn_around_left;
		ScrString_t move_run_turn_around_right;
		ScrString_t move_attack;
		ScrString_t nopatrol;
		ScrString_t stop_idle;
		ScrString_t stop_attackidle;
		ScrString_t stop_attackidle_bark;
		ScrString_t stop_attackidle_growl;
		ScrString_t pain_main;
		ScrString_t pain_front;
		ScrString_t pain_back;
		ScrString_t pain_left;
		ScrString_t pain_right;
		ScrString_t pain_run_front;
		ScrString_t pain_run_back;
		ScrString_t pain_run_left;
		ScrString_t pain_run_right;
		ScrString_t death_front;
		ScrString_t death_back;
		ScrString_t death_left;
		ScrString_t death_right;
		ScrString_t flashed;
		ScrString_t combat_attackidle;
		ScrString_t combat_attackidle_bark;
		ScrString_t combat_attackidle_growl;
		ScrString_t combat_attack_run;
		ScrString_t combat_attack_player;
		ScrString_t combat_attack_player_early;
		ScrString_t combat_attack_player_lunge;
		ScrString_t combat_attack_player_close_range;
		ScrString_t combat_attack_miss;
		ScrString_t combat_attack_miss_left;
		ScrString_t combat_attack_miss_right;
		ScrString_t combat_player_neck_snap;
		ScrString_t combat_player_neck_miss;
		ScrString_t traverse_jump_up_40;
		ScrString_t traverse_jump_up_80;
		ScrString_t traverse_jump_down_40;
		ScrString_t traverse_jump_down_80;
		ScrString_t traverse_wallhop;
		ScrString_t traverse_window;
		ScrString_t traverse_through_hole_42;
		ScrString_t zombie_climb_chain;
		ScrString_t zombie_jump_down_40;
		ScrString_t zombie_jump_down_48;
		ScrString_t zombie_jump_down_72;
		ScrString_t zombie_jump_down_96;
		ScrString_t zombie_jump_down_120;
		ScrString_t zombie_jump_down_127;
		ScrString_t zombie_jump_down_184;
		ScrString_t zombie_jump_down_190;
		ScrString_t zombie_jump_down_222;
		ScrString_t zombie_jump_down_240;
		ScrString_t zombie_jump_down_286;
		ScrString_t zombie_jump_down_386;
		ScrString_t zombie_jump_up_222;
		ScrString_t zombie_jump_up_to_climb;
		ScrString_t zombie_jump_up_to_climb_coast;
		ScrString_t zombie_ladder_up;
		ScrString_t zombie_lighthouse_crawl_down;
		ScrString_t zombie_mantle_over_40;
		ScrString_t zombie_quad_vent_jump_down;
		ScrString_t zombie_wall_crawl_drop;
		ScrString_t zombie_wall_crawl_drop_quick;
		ScrString_t zombie_ground_rise;
		ScrString_t zombie_ground_rise_death;
		ScrString_t zombie_death;
		ScrString_t zombie_run_melee;
		ScrString_t zombie_walk_melee;
		ScrString_t zombie_crawl_melee;
		ScrString_t zombie_stumpy_melee;
		ScrString_t zombie_window_melee;
		ScrString_t zombie_board_tear;
		ScrString_t zombie_jump_on_bus;
		ScrString_t zombie_board_tear_bus;
		ScrString_t zombie_climbin_bus;
		ScrString_t zombie_bus_window_idle;
		ScrString_t zombie_bus_window_melee;
		ScrString_t swimming_begin;
		ScrString_t swimming_end;
		ScrString_t underwater_begin;
		ScrString_t underwater_end;
		ScrString_t snd_engine;
		ScrString_t snd_bow_port;
		ScrString_t snd_bow_stbd;
		ScrString_t event;
		ScrString_t action;
		ScrString_t target;
		ScrString_t param;
		ScrString_t condlhs;
		ScrString_t condop;
		ScrString_t condrhs;
		ScrString_t basic_score;
		ScrString_t perk_score;
		ScrString_t intel_score;
		ScrString_t total_score;
		ScrString_t difficulty_score;
		ScrString_t challenge_score;
		ScrString_t freeze;
		ScrString_t up;
		ScrString_t liveupdate;
		ScrString_t respawn;
		ScrString_t dtp_land;
		ScrString_t hidden;
		ScrString_t fake_fire;
		ScrString_t sprint;
		ScrString_t crouch_run;
		ScrString_t crouch_walk;
		ScrString_t entityshutdown;
		ScrString_t guidance_none;
		ScrString_t guidance_sidewinder;
		ScrString_t guidance_hellfire;
		ScrString_t guidance_javelin;
		ScrString_t guidance_ballistic;
		ScrString_t guidance_wireguided;
		ScrString_t guidance_tvguided;
		ScrString_t guidance_drone;
		ScrString_t guidance_heatseeking;
		ScrString_t guidance_robotech;
		ScrString_t guidance_dynamicimpactpoint;
		ScrString_t firecaster;
		ScrString_t fire_flicker;
		ScrString_t electrical_flicker;
		ScrString_t flicker_then_stop;
		ScrString_t generic_double_strobe;
		ScrString_t generic_strobe;
		ScrString_t light_off;
		ScrString_t light_solid;
		ScrString_t television;
		ScrString_t generic_flickering;
		ScrString_t generic_pulsing;
		ScrString_t explode_then_flicker;
		ScrString_t mixerbehavior_robot;
		ScrString_t footstep_left_large;
		ScrString_t footstep_left_small;
		ScrString_t footstep_right_large;
		ScrString_t footstep_right_small;
		ScrString_t footstep_left;
		ScrString_t footstep_right;
		ScrString_t footstep_front_left;
		ScrString_t footstep_front_right;
		ScrString_t footstep_rear_left;
		ScrString_t footstep_rear_right;
		ScrString_t footstep_left_forward;
		ScrString_t footstep_left_back;
		ScrString_t footstep_right_forward;
		ScrString_t footstep_right_back;
		ScrString_t footstep_front_left_small;
		ScrString_t footstep_front_right_small;
		ScrString_t footstep_rear_left_small;
		ScrString_t footstep_rear_right_small;
		ScrString_t footstep_front_left_shuffle;
		ScrString_t footstep_front_right_shuffle;
		ScrString_t footstep_rear_left_shuffle;
		ScrString_t footstep_rear_right_shuffle;
		ScrString_t footstep_front_left_scrape;
		ScrString_t footstep_front_right_scrape;
		ScrString_t footstep_rear_left_scrape;
		ScrString_t footstep_rear_right_scrape;
		ScrString_t footstep_left_large_theia;
		ScrString_t footstep_right_large_theia;
		ScrString_t footstep_left_large_siege_base;
		ScrString_t footstep_right_large_siege_base;
		ScrString_t footstep_spider_l1;
		ScrString_t footstep_spider_l2;
		ScrString_t footstep_spider_l3;
		ScrString_t footstep_spider_l4;
		ScrString_t footstep_spider_r1;
		ScrString_t footstep_spider_r2;
		ScrString_t footstep_spider_r3;
		ScrString_t footstep_spider_r4;
		ScrString_t dogstep_lf;
		ScrString_t dogstep_rf;
		ScrString_t dogstep_lr;
		ScrString_t dogstep_rr;
		ScrString_t tag_foot_fx_left_front;
		ScrString_t tag_foot_fx_right_front;
		ScrString_t tag_foot_fx_left_back;
		ScrString_t tag_foot_fx_right_back;
		ScrString_t jnt_f_l_knee_upper_dmg;
		ScrString_t jnt_f_r_knee_upper_dmg;
		ScrString_t jnt_r_l_knee_upper_dmg;
		ScrString_t jnt_r_r_knee_upper_dmg;
		ScrString_t jnt_l_mech;
		ScrString_t jnt_r_mech;
		ScrString_t jnt_l_mech_large;
		ScrString_t jnt_r_mech_large;
		ScrString_t leg_le_4_5;
		ScrString_t leg_le_3_5;
		ScrString_t leg_le_2_5;
		ScrString_t leg_le_1_5;
		ScrString_t leg_ri_4_5;
		ScrString_t leg_ri_3_5;
		ScrString_t leg_ri_2_5;
		ScrString_t leg_ri_1_5;
		ScrString_t open;
		ScrString_t closed;
		ScrString_t opening;
		ScrString_t closing;
		ScrString_t targetted_by_zombie;
		ScrString_t actor;
		ScrString_t actor_spawner;
		ScrString_t actor_corpse;
		ScrString_t cf_int;
		ScrString_t cf_float;
		ScrString_t cf_counter;
		ScrString_t ambient_package;
		ScrString_t save_restore;
		ScrString_t difficulty_change;
		ScrString_t tag_board_1;
		ScrString_t tag_board_2;
		ScrString_t tag_board_3;
		ScrString_t tag_board_4;
		ScrString_t tag_board_5;
		ScrString_t tag_board_6;
		ScrString_t self_notify;
		ScrString_t level_notify;
		ScrString_t sound;
		ScrString_t sound_2d;
		ScrString_t start_looping_sound;
		ScrString_t stop_looping_sound;
		ScrString_t shutdown_looping_sound;
		ScrString_t stop_sound;
		ScrString_t vox;
		ScrString_t play_fx;
		ScrString_t play_unmanaged_fx;
		ScrString_t play_viewmodel_fx;
		ScrString_t play_camera_fx;
		ScrString_t play_unmanaged_camera_fx;
		ScrString_t stop_fx;
		ScrString_t kill_fx;
		ScrString_t play_tagfx_set;
		ScrString_t stop_tagfx_set;
		ScrString_t kill_tagfx_set;
		ScrString_t play_entity_impact_fx;
		ScrString_t stop_entity_impact_fx;
		ScrString_t kill_entity_impact_fx;
		ScrString_t play_exploder;
		ScrString_t stop_exploder;
		ScrString_t kill_exploder;
		ScrString_t spawn_light;
		ScrString_t footstep;
		ScrString_t rumble;
		ScrString_t attach_model_server;
		ScrString_t detach_model_server;
		ScrString_t attach_model_client;
		ScrString_t detach_model_client;
		ScrString_t timescale;
		ScrString_t fov;
		ScrString_t focal_length;
		ScrString_t reset_focal_length;
		ScrString_t set_shader_constant;
		ScrString_t call_server_script_function;
		ScrString_t call_server_script_function_on_level;
		ScrString_t call_client_script_function;
		ScrString_t call_client_script_function_on_level;
		ScrString_t hide_bone;
		ScrString_t show_bone;
		ScrString_t hide_offhand;
		ScrString_t show_offhand;
		ScrString_t hide_weapon;
		ScrString_t show_weapon;
		ScrString_t show_blackscreen;
		ScrString_t scene_init;
		ScrString_t scene_play;
		ScrString_t scene_stop;
		ScrString_t attach_weapon;
		ScrString_t detach_weapon;
		ScrString_t start_firing;
		ScrString_t stop_firing;
		ScrString_t graphic_content_over_black_starts;
		ScrString_t graphic_content_over_black_ends;
		ScrString_t graphic_content_blur_starts;
		ScrString_t graphic_content_blur_ends;
		ScrString_t motion_blur;
		ScrString_t body;
		ScrString_t faces;
		ScrString_t loopsyncknob;
		ScrString_t additiveknob;
		ScrString_t loopsyncadditiveknob;
		ScrString_t aim_2;
		ScrString_t aim_4;
		ScrString_t aim_6;
		ScrString_t aim_8;
		ScrString_t run_aim_2;
		ScrString_t run_aim_4;
		ScrString_t run_aim_6;
		ScrString_t run_aim_8;
		ScrString_t _void;
		ScrString_t void_loop;
		ScrString_t main;
		ScrString_t legs;
		ScrString_t slide_rumble;
		ScrString_t dtp_rumble;
		ScrString_t jet_rumble;
		ScrString_t sprint_rumble;
		ScrString_t sprint_rumble_start;
		ScrString_t sprint_rumble_end;
		ScrString_t juke_rumble;
		ScrString_t juke_rumble_start;
		ScrString_t juke_rumble_end;
		ScrString_t doublejump_start;
		ScrString_t doublejump_rumble_start;
		ScrString_t doublejump_rumble_loop;
		ScrString_t traverse_default;
		ScrString_t wallrun_start;
		ScrString_t wallrun_jump;
		ScrString_t animscripted_start;
		ScrString_t animscripted_stop;
		ScrString_t tag_control_dial_1;
		ScrString_t tag_control_dial_2;
		ScrString_t tag_control_dial_3;
		ScrString_t end;
		ScrString_t loop_end;
		ScrString_t bsm_state_start;
		ScrString_t bsm_state_update;
		ScrString_t bsm_state_terminate;
		ScrString_t pathfind_result;
		ScrString_t pathfind_succeeded;
		ScrString_t pathfind_failed;
		ScrString_t path_prediction_start_point;
		ScrString_t path_prediction_enter_turn_point;
		ScrString_t path_prediction_leave_turn_point;
		ScrString_t path_prediction_travel_vector;
		ScrString_t path_corner_curve_distance;
		ScrString_t path_corner_curve_angle;
		ScrString_t path_prediction_status;
		ScrString_t unloaded;
		ScrString_t radio_event_low;
		ScrString_t radio_event_high;
		ScrString_t radio_event_found_enemy;
		ScrString_t pause;
		ScrString_t unpause;
		ScrString_t loop;
		ScrString_t unloop;
		ScrString_t goto_start;
		ScrString_t goto_end;
		ScrString_t goto_random;
		ScrString_t goto_frame;
		ScrString_t reset_trigger_count;
		ScrString_t set_anim;
		ScrString_t append_anim;
		ScrString_t set_shot;
		ScrString_t blend_to_shot;
		ScrString_t append_shot;
		ScrString_t send_end_events;
		ScrString_t set_playback_speed;
		ScrString_t stats;
		ScrString_t sessionstats;
		ScrString_t migration;
		ScrString_t skiptos_changed;
		ScrString_t lockon_changed;
		ScrString_t switchmap_preload_finished;
		ScrString_t animation_alias;
		ScrString_t blend_in_time_column;
		ScrString_t blend_out_time_column;
		ScrString_t animation_mocomp_column;
		ScrString_t aim_table;
		ScrString_t aim_up_alias;
		ScrString_t aim_down_alias;
		ScrString_t aim_left_alias;
		ScrString_t aim_right_alias;
		ScrString_t animation_alias_semi;
		ScrString_t animation_alias_singleshot;
		ScrString_t animation_alias_burst3;
		ScrString_t animation_alias_burst4;
		ScrString_t animation_alias_burst5;
		ScrString_t animation_alias_burst6;
		ScrString_t animation_alias_param_f;
		ScrString_t animation_alias_param_b;
		ScrString_t animation_alias_param_l;
		ScrString_t animation_alias_param_r;
		ScrString_t ast_undefined;
		ScrString_t ast_wildcard;
		ScrString_t influencer_removed;
		ScrString_t ctf_flag_carrier;
		ScrString_t operating_reaper;
		ScrString_t operating_predator;
		ScrString_t operating_chopper_gunner;
		ScrString_t remote_killstreak_static;
		ScrString_t killstreak_hides_compass;
		ScrString_t killstreak_spawn_protection;
		ScrString_t gps_jammer_active;
		ScrString_t sg_jammer_active;
		ScrString_t awarenessIndicatorState;
		ScrString_t vehicle;
		ScrString_t allplayers;
		ScrString_t toplayer;
		ScrString_t playercorpse;
		ScrString_t clientuimodel;
		ScrString_t scriptmover;
		ScrString_t helicopter;
		ScrString_t plane;
		ScrString_t turret;
		ScrString_t missile;
		ScrString_t zbarrier;
		ScrString_t item;
		ScrString_t j_shoulder_le_rot;
		ScrString_t bot;
		ScrString_t basic_soldier;
		ScrString_t amws;
		ScrString_t attack_drone;
		ScrString_t cqb_soldier;
		ScrString_t hunter;
		ScrString_t quadtank;
		ScrString_t raps;
		ScrString_t robot_soldier;
		ScrString_t robot_commander;
		ScrString_t robot_cqb;
		ScrString_t robot_rocketeer;
		ScrString_t robot_sniper;
		ScrString_t robot_suppressor;
		ScrString_t rocketeer_soldier;
		ScrString_t scout;
		ScrString_t siegebot;
		ScrString_t sniper_soldier;
		ScrString_t suppressor_soldier;
		ScrString_t theia;
		ScrString_t warlord_soldier;
		ScrString_t wasp;
		ScrString_t grapple_fired;
		ScrString_t grapple_stick;
		ScrString_t grapple_reelin;
		ScrString_t grapple_pullin;
		ScrString_t grapple_landed;
		ScrString_t grapple_pulled;
		ScrString_t grapple_cancel;
		ScrString_t grapple_beam_on;
		ScrString_t grapple_beam_off;
		ScrString_t combat_traverse_at_traversal;
		ScrString_t _traversal_type;
		ScrString_t burst;
		ScrString_t fullauto;
		ScrString_t singleshot;
		ScrString_t navvolume_small;
		ScrString_t navvolume_big;
		ScrString_t aimpitchangleu;
		ScrString_t aimpitchangled;
		ScrString_t aimyawangler;
		ScrString_t aimyawanglel;
		ScrString_t aimyawfarangler;
		ScrString_t aimyawfaranglel;
		ScrString_t centerupanim;
		ScrString_t centerstraightanim;
		ScrString_t centerdownanim;
		ScrString_t rightupanim;
		ScrString_t rightstraightanim;
		ScrString_t rightdownanim;
		ScrString_t leftupanim;
		ScrString_t leftstraightanim;
		ScrString_t leftdownanim;
		ScrString_t rightupfaranim;
		ScrString_t rightstraightfaranim;
		ScrString_t rightdownfaranim;
		ScrString_t leftupfaranim;
		ScrString_t leftstraightfaranim;
		ScrString_t leftdownfaranim;
		ScrString_t fireadditiveanim;
		ScrString_t cover_pillar;
		ScrString_t cover_left;
		ScrString_t cover_right;
		ScrString_t cover_stand;
		ScrString_t cover_crouch;
		ScrString_t cover_exposed;
		ScrString_t cover_none;
		ScrString_t exposed_yes;
		ScrString_t exposed_no;
		ScrString_t cam_cac_weapon;
		ScrString_t cam_cac_attachments;
		ScrString_t cam_icon_weapon;
		ScrString_t streamer;
		ScrString_t streamer_50;
		ScrString_t streamer_75;
		ScrString_t streamer_100;
		ScrString_t shoot;
		ScrString_t about_to_shoot;
		ScrString_t melee_fire;
		ScrString_t stealth_sight_start;
		ScrString_t stealth_sight_end;
		ScrString_t stealth_sight_max;
		ScrString_t anim_gunhand_left;
		ScrString_t anim_gunhand_right;
		ScrString_t drop_clip;
		ScrString_t attach_clip_left;
		ScrString_t detach_clip_left;
		ScrString_t clip_drop;
		ScrString_t clip_attach_left;
		ScrString_t clip_detach_left;
		ScrString_t gunshot_teammate;
		ScrString_t stair_none;
		ScrString_t stair_down;
		ScrString_t stair_up;
		ScrString_t jump_rumble_start;
		ScrString_t jump_rumble_end;
		ScrString_t misstimeconstant;
		ScrString_t misstimedistancefactor;
		ScrString_t one_player_coopmisstimeresetdelay;
		ScrString_t two_player_coopmisstimeresetdelay;
		ScrString_t three_player_coopmisstimeresetdelay;
		ScrString_t four_player_coopmisstimeresetdelay;
		ScrString_t misstimeresetdelay;
		ScrString_t behind_player_angle;
		ScrString_t behind_player_accuracyscalar;
		ScrString_t bhtn_action_start;
		ScrString_t bhtn_action_update;
		ScrString_t bhtn_action_terminate;
		ScrString_t bhtn_action_notify;
		ScrString_t stair_deltas;
		ScrString_t bminteract;
		ScrString_t asm_notify;
		ScrString_t bot_goal_reached;
		ScrString_t bot_path_success;
		ScrString_t bot_path_failed;
		ScrString_t bot_corner;
		ScrString_t voiceprefix;
		ScrString_t characterselect;
		ScrString_t tag_focus;
		ScrString_t tag_follow;
		ScrString_t one;
		ScrString_t bgb_activation_request;
		ScrString_t specify_weapon_request;
		ScrString_t gunner_weapon_fired;
		ScrString_t parent;
		ScrString_t tag_arrow_animate;
		ScrString_t rewardName;
		ScrString_t MPUI_UNLOCK_TOKEN;
		ScrString_t normal_steering;
		ScrString_t slow_steering;
		ScrString_t vignette_steering;
		ScrString_t projectile_impact_player;
		ScrString_t weapon;
		ScrString_t acvi;
		ScrString_t loadout_changed;
		ScrString_t stats_changed;
		ScrString_t killcamtype;
		ScrString_t killcamupdist;
		ScrString_t killcambackdist;
		ScrString_t killcamwalloutdist;
		ScrString_t killcamwallsidedist;
		ScrString_t killcamgroundupdist;
		ScrString_t killcamgroundbackdist;
		ScrString_t autoaimregionheight;
		ScrString_t autoaimregionwidth;
		ScrString_t notetrack;
		ScrString_t yaw;
		ScrString_t pitch;
		ScrString_t leftStick;
		ScrString_t rightStick;
		ScrString_t ragdoll_nodeath;
		ScrString_t pre_traversal;
		ScrString_t footstep_l_b_apothicon;
		ScrString_t footstep_r_b_apothicon;
		ScrString_t footstep_l_f_apothicon;
		ScrString_t footstep_r_f_apothicon;
		ScrString_t tag_gunner_flash1;
		ScrString_t tag_gunner_flash2;
		ScrString_t tag_gunner_flash3;
		ScrString_t tag_gunner_flash4;
		ScrString_t tag_gunner_flash1a;
		ScrString_t tag_gunner_flash2a;
		ScrString_t tag_gunner_flash3a;
		ScrString_t tag_gunner_flash4a;
		ScrString_t tag_gunner_flash1b;
		ScrString_t tag_gunner_flash2b;
		ScrString_t tag_gunner_flash3b;
		ScrString_t tag_gunner_flash4b;
		ScrString_t tag_gunner_flash1c;
		ScrString_t tag_gunner_flash2c;
		ScrString_t tag_gunner_flash3c;
		ScrString_t tag_gunner_flash4c;
		ScrString_t tag_gunner_aim1;
		ScrString_t tag_gunner_aim2;
		ScrString_t tag_gunner_aim3;
		ScrString_t tag_gunner_aim4;
		ScrString_t tag_flash_gunner1;
		ScrString_t tag_flash_gunner2;
		ScrString_t tag_flash_gunner3;
		ScrString_t tag_flash_gunner4;
		ScrString_t tag_flash_gunner1a;
		ScrString_t tag_flash_gunner2a;
		ScrString_t tag_flash_gunner3a;
		ScrString_t tag_flash_gunner4a;
		ScrString_t fallwind_loop_slow;
		ScrString_t fallwind_loop_med;
		ScrString_t fallwind_loop_fast;
		ScrString_t fallwind_loop_rapid;
		ScrString_t fallimpact_slow;
		ScrString_t fallimpact_med;
		ScrString_t fallimpact_fast;
		ScrString_t fallimpact_rapid;
	};

	struct __declspec(align(8)) cg_t
	{
		ClientNum_t clientNum;
		LocalClientNum_t localClientNum;
	};
}