
#include "pch.h"

#include <MinHook.h>

#include "hapi.h"
#include "hotreload.h"
#include "initialization.h"
#include "lapi.h"
#include "lstate.h"
#include "uierrorfix.h"

extern "C"
{
	int __declspec(dllexport) init(lua_State* L)
	{
		// Initialize the api like set the baseaddress
		hks::InitializeApi();
		// Add the library to lua
		const luaL_Reg t7OverchargedLibrary[] =
		{
			{"RemoveUiErrorHash", hks::RemoveUiErrorHash},
			{"CheckForHotReload", hks::CheckForHotReload},
			{"InitHotReload", hks::InitHotReload},
			{nullptr, nullptr},
		};
		hksI_openlib(L, "T7Overcharged", t7OverchargedLibrary, 0, 1);
		return 1;
	}
}
