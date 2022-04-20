#pragma once

#define WEAK __declspec(selectany)

namespace game
{
	WEAK symbol<char(const char* file, int line, lua::ErrorCode code, const char* fmt, ...)> Com_Error_{ (uintptr_t)GetModuleHandle(NULL) + 0x20F8BD0 };
	WEAK symbol<bool()> Com_IsRunningUILevel{ (uintptr_t)GetModuleHandle(NULL) + 0x2148DB0 };
	WEAK symbol<bool(eGameModes mode)> Com_SessionMode_IsGameMode{ (uintptr_t)GetModuleHandle(NULL) + 0x20F7D90 };
	WEAK symbol<bool(eModes mode)> Com_SessionMode_IsMode{ (uintptr_t)GetModuleHandle(NULL) + 0x20F7DD0 };
	WEAK symbol<const char* (const char* name)> Com_GameInfo_GetGameTypeRefCaps{ (uintptr_t)GetModuleHandle(NULL) + 0x20F4090 };
	WEAK symbol<const char* (const char* name)> Com_GameInfo_GetGameTypeRef{ (uintptr_t)GetModuleHandle(NULL) + 0x20F4010 };
	WEAK symbol<const char* (const char* name)> Com_GameInfo_GetMapRef{ (uintptr_t)GetModuleHandle(NULL) + 0x20F4280 };

	WEAK symbol<const char* (const char* name)> UI_SafeTranslateString{ (uintptr_t)GetModuleHandle(NULL) + 0x228F7B0 };

	WEAK symbol<INT64 (const char* name, int imageTrack, bool errorIfMissing, int waitTime)> Material_RegisterHandle{ (uintptr_t)GetModuleHandle(NULL) + 0x1CD4B90 };

	WEAK symbol<int (INT64 lobbySession, LobbyClientType clientType)> LobbySession_GetClientCount{ (uintptr_t)GetModuleHandle(NULL) + 0x1ED8B30 };

	WEAK symbol<void (const char* dvarName, const char* string, bool createIfMissing)> Dvar_SetFromStringByName{ (uintptr_t)GetModuleHandle(NULL) + 0x22C7F60 };
	WEAK symbol<bool (const dvar_t* dvar)> Dvar_GetBool{ (uintptr_t)GetModuleHandle(NULL) + 0x22BD930 };
	WEAK symbol<const char* (const dvar_t* dvar)> Dvar_GetString{ (uintptr_t)GetModuleHandle(NULL) + 0x22BFFF0 };

	WEAK symbol<int(XAssetType type)> DB_GetXAssetTypeSize{ (uintptr_t)GetModuleHandle(NULL) + 0x13E9DD0 };
	static XAssetPool* DB_XAssetPool = reinterpret_cast<XAssetPool*>((uintptr_t)GetModuleHandle(NULL) + 0x94093F0);
	static lua::lua_State* UI_luaVM = ((lua::lua_State*)((*(INT64*)(((uintptr_t)GetModuleHandle(NULL) + 0x19C78D88)))));
	static bool s_luaInFrontend = ((bool)(((uintptr_t)GetModuleHandle(NULL) + 0x3415BD8)));


	WEAK symbol<bool(int channel, consoleLabel_e label, const char* fmt, ...)> Com_Printf{ (uintptr_t)GetModuleHandle(NULL) + 0x21499C0 };
	WEAK symbol<bool(int channel, consoleLabel_e label, const char* msg, int error)> Com_PrintMessage{ (uintptr_t)GetModuleHandle(NULL) + 0x2149660 };
	WEAK symbol<const char* (const char* s0, const char* substr)> I_stristr{ (uintptr_t)GetModuleHandle(NULL) + 0x22EA2B0 };
	WEAK symbol<__int64(int* a1, __int64 a2, __int64 a3)> PLmemset{ (uintptr_t)GetModuleHandle(NULL) + 0x2C3EA20 };
	WEAK symbol<int(char* dest, size_t size, const char* fmt, ...)> Com_sprintf{ (uintptr_t)GetModuleHandle(NULL) + 0x2C3D620 };

	WEAK symbol<game::dvarStrHash_t(const char* str)> Dvar_GenerateHash{ (uintptr_t)GetModuleHandle(NULL) + 0x133DBF0 };


	WEAK symbol<void()> Sys_ShowConsole{ (uintptr_t)GetModuleHandle(NULL) + 0x2333F80 };


	WEAK symbol<game::LUIElement* (const char* rootName, lua::lua_State* luaVM)> UI_GetRootElement{ (uintptr_t)GetModuleHandle(NULL) + 0x27056C0 };
	WEAK symbol<void(LUIScopedEvent* event, lua::lua_State* luaVM, const char* rootName, const char* eventName)> GetLUIScopedEvent{ (uintptr_t)GetModuleHandle(NULL) + 0x26FF350 };
	WEAK symbol<void(LUIScopedEvent* event)> ExecuteLUIScopedEvent{ (uintptr_t)GetModuleHandle(NULL) + 0x26FF580 };

	WEAK symbol<int ()> Sys_IsDatabaseReady2{ (uintptr_t)GetModuleHandle(NULL) + 0x2184490 };

	WEAK symbol<ScrString_t(const char* s)> GScr_AllocString{ (uintptr_t)GetModuleHandle(NULL) + 0x1A83520 };

	WEAK symbol<int(void* ps, void* weapon/*const playerState_t* ps, const Weapon weapon*/)> BG_GetAmmoInClip{(uintptr_t)GetModuleHandle(NULL) + 0x26E7310};
	WEAK symbol<int(void* ps, void* weapon/*const playerState_t* ps, const Weapon weapon*/)> BG_GetTotalAmmoReserve{ (uintptr_t)GetModuleHandle(NULL) + 0x26E7AB0 };
	WEAK symbol<bool(void* weapon/*const Weapon weapon*/)> BG_IsLeftHandWeapon{ (uintptr_t)GetModuleHandle(NULL) + 0x26F4A90 };

	WEAK symbol<int(void*/*const DObj*/ obj, ScrString_t name, BoneIndex* index, int modelNum)> DObjGetBoneIndex{ (uintptr_t)GetModuleHandle(NULL) + 0x233DF70 };
	WEAK symbol<int(void*/*const DObj*/ obj, int* partBits, uint16_t boneIndex, const vec3_t* trans, const vec3_t* angles)> DObjSetLocalTag{ (uintptr_t)GetModuleHandle(NULL) + 0x233EDE0 };
	WEAK symbol<LocalClientNum_t (void*/*const DObj*/ obj)> DObjGetLocalClientIndex{ (uintptr_t)GetModuleHandle(NULL) + 0x2337A30 };

	WEAK symbol<game::cmd_function_t*> cmd_functions{ (uintptr_t)GetModuleHandle(NULL) + 0x1689FF58 };
}
