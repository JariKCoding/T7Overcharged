#pragma once

#define WEAK __declspec(selectany)

namespace game
{
	WEAK symbol<char(const char* file, int line, lua::ErrorCode code, const char* fmt, ...)> Com_Error_{ (uintptr_t)GetModuleHandle(NULL) + 0x20F8BD0 };


	WEAK symbol<void (const char* dvarName, const char* string, bool createIfMissing)> Dvar_SetFromStringByName{ (uintptr_t)GetModuleHandle(NULL) + 0x22C7F60 };
	WEAK symbol<bool (const dvar_t* dvar)> Dvar_GetBool{ (uintptr_t)GetModuleHandle(NULL) + 0x22BD930 };



	WEAK symbol<bool(int channel, consoleLabel_e label, const char* fmt, ...)> Com_Printf{ (uintptr_t)GetModuleHandle(NULL) + 0x21499C0 };
	WEAK symbol<bool(int channel, consoleLabel_e label, const char* msg, int error)> Com_PrintMessage{ (uintptr_t)GetModuleHandle(NULL) + 0x2149660 };
	WEAK symbol<const char* (const char* s0, const char* substr)> I_stristr{ (uintptr_t)GetModuleHandle(NULL) + 0x22EA2B0 };


	WEAK symbol<void()> OpenExternalConsole{ (uintptr_t)GetModuleHandle(NULL) + 0x2333F80 }; // Opens the console but not repsonding
}