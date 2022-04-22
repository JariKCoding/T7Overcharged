#pragma once

#define WEAK __declspec(selectany)

namespace game
{
#define REBASE(address) (uintptr_t)((address - 0x140000000) + game::base)
#define OFFSET(address) (uintptr_t)((address - 0x140000000) + (uintptr_t)GetModuleHandle(NULL))

	/* BG */
	WEAK symbol<int(void* ps, void* weapon/*const playerState_t* ps, const Weapon weapon*/)> BG_GetAmmoInClip{ OFFSET(0x1426E7310) };
	WEAK symbol<int(void* ps, void* weapon/*const playerState_t* ps, const Weapon weapon*/)> BG_GetTotalAmmoReserve{ OFFSET(0x1426E7AB0) };
	WEAK symbol<bool(void* weapon/*const Weapon weapon*/)> BG_IsLeftHandWeapon{ OFFSET(0x1426F4A90) };

	/* BUILT-IN */
	WEAK symbol<const char* (const char* s0, const char* substr)> I_stristr{ OFFSET(0x1422EA2B0) };
	WEAK symbol<__int64(int* a1, __int64 a2, __int64 a3)> PLmemset{ OFFSET(0x142C3EA20) };
	WEAK symbol<int(char* string, unsigned int count, const char* format, char* ap)> vsnprintf{ OFFSET(0x142C3DB30) };

	/* CG */
	WEAK symbol<void(void* obj, const game::XAnimNotifyInfo* notifyInfo, void* info, const unsigned int notifyFilter, bool shutdown, bool skipNonImportantNotifies)> CG_ProcessClientNote{ OFFSET(0x140255C70) };

	/* CMD */
	// Variables
	WEAK symbol<game::cmd_function_t*> cmd_functions{ OFFSET(0x15689FF58) };

	/* COM */
	WEAK symbol<char(const char* file, int line, lua::ErrorCode code, const char* fmt, ...)> Com_Error_{ OFFSET(0x1420F8BD0) };
	WEAK symbol<const char* (const char* name)> Com_GameInfo_GetGameTypeRefCaps{ OFFSET(0x1420F4090) };
	WEAK symbol<const char* (const char* name)> Com_GameInfo_GetGameTypeRef{ OFFSET(0x1420F4010) };
	WEAK symbol<const char* (const char* name)> Com_GameInfo_GetMapRef{ OFFSET(0x1420F4280) };
	WEAK symbol<bool()> Com_IsRunningUILevel{ OFFSET(0x142148DB0) };
	WEAK symbol<bool(consoleChannel_e channel, consoleLabel_e label, const char* fmt, ...)> Com_Printf{ OFFSET(0x1421499C0) };
	WEAK symbol<bool(consoleChannel_e channel, consoleLabel_e label, const char* msg, int error)> Com_PrintMessage{ OFFSET(0x142149660) };
	WEAK symbol<bool(eGameModes mode)> Com_SessionMode_IsGameMode{ OFFSET(0x1420F7D90) };
	WEAK symbol<bool(eModes mode)> Com_SessionMode_IsMode{ OFFSET(0x1420F7DD0) };
	WEAK symbol<int(char* dest, size_t size, const char* fmt, ...)> Com_sprintf{ OFFSET(0x142C3D620) };

	/* CSC/GSC */
	WEAK symbol<ScrString_t(const char* s)> GScr_AllocString{ OFFSET(0x141A83520) };

	/* DB */
	WEAK symbol<int(XAssetType type)> DB_GetXAssetTypeSize{ OFFSET(0x1413E9DD0) };
	// Variables
	static XAssetPool* DB_XAssetPool = reinterpret_cast<XAssetPool*>(OFFSET(0x1494093F0));
	static bool s_luaInFrontend = ((bool)OFFSET(0x143415BD8));
	static lua::lua_State* UI_luaVM = ((lua::lua_State*)((*(INT64*)OFFSET(0x159C78D88))));

	/* DObj */
	WEAK symbol<int(void*/*const DObj*/ obj, ScrString_t name, BoneIndex* index, int modelNum)> DObjGetBoneIndex{ OFFSET(0x14233DF70) };
	WEAK symbol<LocalClientNum_t(void*/*const DObj*/ obj)> DObjGetLocalClientIndex{ OFFSET(0x142337A30) };
	WEAK symbol<int(void*/*const DObj*/ obj, int* partBits, uint16_t boneIndex, const vec3_t* trans, const vec3_t* angles)> DObjSetLocalTag{ OFFSET(0x14233EDE0) };

	/* DVAR */
	WEAK symbol<game::dvarStrHash_t(const char* str)> Dvar_GenerateHash{ OFFSET(0x14133DBF0) };
	WEAK symbol<bool(const dvar_t* dvar)> Dvar_GetBool{ OFFSET(0x1422BD930) };
	WEAK symbol<const char* (const dvar_t* dvar)> Dvar_GetString{ OFFSET(0x1422BFFF0) };
	WEAK symbol<void(const char* dvarName, const char* string, bool createIfMissing)> Dvar_SetFromStringByName{ OFFSET(0x1422C7F60) };
	// Variables
	WEAK symbol<char> s_dvarPool{ OFFSET(0x157AC8220) };
	WEAK symbol<int> g_dvarCount{ OFFSET(0x157AC81CC) };

	/* LOBBYSESSION */
	WEAK symbol<int(INT64 lobbySession, LobbyClientType clientType)> LobbySession_GetClientCount{ OFFSET(0x141ED8B30) };

	/* LUA / UI */
	WEAK symbol<const char* (const char* name)> UI_SafeTranslateString{ OFFSET(0x14228F7B0) };
	WEAK symbol<game::LUIElement* (const char* rootName, lua::lua_State* luaVM)> UI_GetRootElement{ OFFSET(0x1427056C0) };
	WEAK symbol<void(LUIScopedEvent* event, lua::lua_State* luaVM, const char* rootName, const char* eventName)> GetLUIScopedEvent{ OFFSET(0x1426FF350) };
	WEAK symbol<void(LUIScopedEvent* event)> ExecuteLUIScopedEvent{ OFFSET(0x1426FF580) };

	/* MATERIAL */
	WEAK symbol<INT64(const char* name, int imageTrack, bool errorIfMissing, int waitTime)> Material_RegisterHandle{ OFFSET(0x141CD4B90) };

	/* SYS */
	WEAK symbol<int()> Sys_IsDatabaseReady2{ OFFSET(0x142184490) };
	WEAK symbol<void()> Sys_ShowConsole{ OFFSET(0x142333F80) };
}
