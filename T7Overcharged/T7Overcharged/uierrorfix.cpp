


#include "pch.h"

#include "hapi.h"
#include "initialization.h"
#include "lapi.h"
#include "lstate.h"
#include "MinHook.h"

namespace hks
{
    char Lua_CoD_LuaStateManager_Error_Stub(char const* error, lua_State* s)
    {
        auto luaErrorString = lua_tostring(s, -1);
        lua_pop(s, 1);
        return Com_Error_("", 0, 0x200u, "Unhashed ui error:\n%s", luaErrorString);
    }

    static int hashRemoved = 0;

	int RemoveUiErrorHash(lua_State* s)
	{
        if (hashRemoved)
            return 1;
        hashRemoved = 1;

        void* fpLua_CoD_LuaStateManager_Error = NULL;
        auto hookAddress = reinterpret_cast<LPVOID*>(baseAddress + 0x1F12640);

        if (MH_CreateHook(hookAddress, &Lua_CoD_LuaStateManager_Error_Stub,
            reinterpret_cast<LPVOID*>(&fpLua_CoD_LuaStateManager_Error)) != MH_OK)
        {
            Com_Error_("", 0, 0x200u, "Error with ui error hash fix: MH_CreateHook failed");
            return 1;
        }

        if (MH_EnableHook(hookAddress) != MH_OK)
        {
            Com_Error_("", 0, 0x200u, "Error with ui error hash fix: MH_EnableHook failed");
            return 1;
        }

        return 0;
	}
}
