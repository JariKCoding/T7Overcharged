#include <std_include.hpp>
#include "console.hpp"
#include "havok/hks_api.hpp"
#include "havok/lua_api.hpp"

namespace console
{
    void Print(std::string msg)
    {
        msg = "^7" + msg + "\n";
        game::Com_Printf(0, game::consoleLabel_e::CON_LABEL_DEFAULT_0, msg.c_str());
    }

    void PrintInfo(std::string msg)
    {
        msg = "^4" + msg + "\n";
        game::Com_Printf(0, game::consoleLabel_e::CON_LABEL_DEFAULT_0, msg.c_str());
    }

    void PrintError(std::string msg)
    {
        if (game::I_stristr(msg.c_str(), "error"))
            msg = "^1" + msg + "\n";
        else
            msg = "^1Error: " + msg + "\n";

        game::Com_Printf(0, game::consoleLabel_e::CON_LABEL_DEFAULT_0, msg.c_str());
    }

    void PrintWarning(std::string msg)
    {
        msg = "^3" + msg + "\n";
        game::Com_Printf(0, game::consoleLabel_e::CON_LABEL_DEFAULT_0, msg.c_str());
    }

    int Print(lua::lua_State* s)
    {
        auto text = lua::lua_tostring(s, 1);
        Print(text);
        return 1;
    }

    int PrintInfo(lua::lua_State* s)
    {
        auto text = lua::lua_tostring(s, 1);
        PrintInfo(text);
        return 1;
    }

    int PrintError(lua::lua_State* s)
    {
        auto text = lua::lua_tostring(s, 1);
        PrintError(text);
        return 1;
    }

    int PrintWarning(lua::lua_State* s)
    {
        auto text = lua::lua_tostring(s, 1);
        PrintWarning(text);
        return 1;
    }

	void initialize(lua::lua_State* s)
	{
        // Add the library to lua
        const lua::luaL_Reg ConsoleLibrary[] =
        {
            {"Print", Print},
            {"PrintInfo", PrintInfo},
            {"PrintError", PrintError},
            {"PrintWarning", PrintWarning},
            {nullptr, nullptr},
        };
        hks::hksI_openlib(s, "Console", ConsoleLibrary, 0, 1);
	}
}