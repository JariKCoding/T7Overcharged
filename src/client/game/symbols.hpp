#pragma once

#define WEAK __declspec(selectany)

namespace game
{
	WEAK symbol<char(const char* file, int line, lua::ErrorCode code, const char* fmt, ...)> Com_Error_{ (uintptr_t)GetModuleHandle(NULL) + 0x20F8BD0 };


	WEAK symbol<void (const char* dvarName, const char* string, bool createIfMissing)> Dvar_SetFromStringByName{ (uintptr_t)GetModuleHandle(NULL) + 0x22C7F60 };
	WEAK symbol<bool (const dvar_t* dvar)> Dvar_GetBool{ (uintptr_t)GetModuleHandle(NULL) + 0x22BD930 };
}