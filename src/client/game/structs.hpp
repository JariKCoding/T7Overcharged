#pragma once

namespace game
{
	typedef float vec_t;
	typedef vec_t vec2_t[2];
	typedef vec_t vec3_t[3];
	typedef vec_t vec4_t[4];

	typedef uint32_t dvarStrHash_t;
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

	enum consoleLabel_e : __int32
	{
		CON_LABEL_DEFAULT_0 = 0x0,
		CON_LABEL_TEMP_0 = 0x1,
		CON_LABEL_GFX_0 = 0x2,
		CON_LABEL_TASKMGR2_0 = 0x3,
		CON_LABEL_LIVE_0 = 0x4,
		CON_LABEL_DEMONWARE_0 = 0x5,
		CON_LABEL_LEADERBOARDS_0 = 0x6,
		CON_LABEL_LOBBY_0 = 0x7,
		CON_LABEL_LOBBYHOST_0 = 0x8,
		CON_LABEL_LOBBYCLIENT_0 = 0x9,
		CON_LABEL_LOBBYVM_0 = 0xA,
		CON_LABEL_MIGRATION_0 = 0xB,
		CON_LABEL_INGAME_MIGRATION_HOST_0 = 0xC,
		CON_LABEL_INGAME_MIGRATION_CLIENT_0 = 0xD,
		CON_LABEL_SCRIPTER_0 = 0xE,
		CON_LABEL_VM_0 = 0xF,
		CON_LABEL_DVAR_0 = 0x10,
		CON_LABEL_TOOL_0 = 0x11,
		CON_LABEL_ANIM_0 = 0x12,
		CON_LABEL_NETCHAN_0 = 0x13,
		CON_LABEL_BG_CACHE_0 = 0x14,
		CON_LABEL_PM_0 = 0x15,
		CON_LABEL_MAPSWITCH_0 = 0x16,
		CON_LABEL_AI_0 = 0x17,
		CON_LABEL_GADGET_0 = 0x18,
		CON_LABEL_SOUND_0 = 0x19,
		CON_LABEL_SNAPSHOT_0 = 0x1A,
		CON_LABEL_PLAYGO_0 = 0x1B,
		CON_LABEL_LUI_0 = 0x1C,
		CON_LABEL_LUA_0 = 0x1D,
		CON_LABEL_VOICE_0 = 0x1E,
		CON_LABEL_DEMO_0 = 0x1F,
		CON_LABEL_DB_0 = 0x20,
		CON_LABEL_HTTP_0 = 0x21,
		CON_LABEL_COMPANION_0 = 0x22,
		CON_LABEL_MEM_0 = 0x23,
		CON_LABEL_CINEMATIC_0 = 0x24,
		CON_LABEL_DDL_0 = 0x25,
		CON_LABEL_STORAGE_0 = 0x26,
		CON_LABEL_STEAM_0 = 0x27,
		CON_LABEL_CHECKPOINT_0 = 0x28,
		CON_LABEL_THUNDERHEAD_0 = 0x29,
		CON_LABEL_COMSCORE_0 = 0x2A,
		CON_LABEL_FILESHARE_0 = 0x2B,
		CON_LABEL_LPC_0 = 0x2C,
		CON_LABEL_MARKETING_0 = 0x2D,
		CON_LABEL_STORE_0 = 0x2E,
		CON_LABEL_TESTING_0 = 0x2F,
		CON_LABEL_COUNT_0 = 0x30,
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

	struct dvar_t
	{
		dvarStrHash_t name;
		const char* debugName;
		const char* description;
		unsigned int flags;
		dvarType_t type;
		bool modified;
		DvarValue current;
		DvarValue latched;
		DvarValue reset;
		DvarLimits domain;
		dvar_t* hashNext;
	};
}