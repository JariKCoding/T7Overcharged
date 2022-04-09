#pragma once

#define WEAK __declspec(selectany)

namespace game
{
	WEAK symbol<char(const char* file, int line, lua::ErrorCode code, const char* fmt, ...)> Com_Error_{ (uintptr_t)GetModuleHandle(NULL) + 0x20F8BD0 };
	WEAK symbol<bool()> Com_IsRunningUILevel{ (uintptr_t)GetModuleHandle(NULL) + 0x2148DB0 };


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


	WEAK symbol<void()> OpenExternalConsole{ (uintptr_t)GetModuleHandle(NULL) + 0x2333F80 }; // Opens the console but not repsonding


	WEAK symbol<game::LUIElement* (const char* rootName, lua::lua_State* luaVM)> UI_GetRootElement{ (uintptr_t)GetModuleHandle(NULL) + 0x27056C0 };
	WEAK symbol<void(LUIScopedEvent* event, lua::lua_State* luaVM, const char* rootName, const char* eventName)> GetLUIScopedEvent{ (uintptr_t)GetModuleHandle(NULL) + 0x26FF350 };
	WEAK symbol<void(LUIScopedEvent* event)> ExecuteLUIScopedEvent{ (uintptr_t)GetModuleHandle(NULL) + 0x26FF580 };

}