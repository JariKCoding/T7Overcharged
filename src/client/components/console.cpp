#include <std_include.hpp>
#include "console.hpp"
#include "havok/hks_api.hpp"
#include "havok/lua_api.hpp"

namespace console
{
    void print(std::string msg)
    {
        msg = "^7" + msg + "\n";
        game::Com_Printf(0, game::consoleLabel_e::CON_LABEL_DEFAULT_0, msg.c_str());
    }

    void print_info(std::string msg)
    {
        msg = "^4" + msg + "\n";
        game::Com_Printf(0, game::consoleLabel_e::CON_LABEL_DEFAULT_0, msg.c_str());
    }

    void print_error(std::string msg)
    {
        if (game::I_stristr(msg.c_str(), "error"))
            msg = "^1" + msg + "\n";
        else
            msg = "^1Error: " + msg + "\n";

        game::Com_Printf(0, game::consoleLabel_e::CON_LABEL_DEFAULT_0, msg.c_str());
    }

    void print_warning(std::string msg)
    {
        msg = "^3" + msg + "\n";
        game::Com_Printf(0, game::consoleLabel_e::CON_LABEL_DEFAULT_0, msg.c_str());
    }

    int print(lua::lua_State* s)
    {
        auto text = lua::lua_tostring(s, 1);
        print(text);
        return 1;
    }

    int print_info(lua::lua_State* s)
    {
        auto text = lua::lua_tostring(s, 1);
        print_info(text);
        return 1;
    }

    int print_error(lua::lua_State* s)
    {
        auto text = lua::lua_tostring(s, 1);
        print_error(text);
        return 1;
    }

    int print_warning(lua::lua_State* s)
    {
        auto text = lua::lua_tostring(s, 1);
        print_warning(text);
        return 1;
    }

	void initialize(lua::lua_State* s)
	{
        // Add the library to lua
        const lua::luaL_Reg ConsoleLibrary[] =
        {
            {"Print", print},
            {"PrintInfo", print_info},
            {"PrintError", print_error},
            {"PrintWarning", print_warning},
            {nullptr, nullptr},
        };
        hks::hksI_openlib(s, "Console", ConsoleLibrary, 0, 1);
	}
}