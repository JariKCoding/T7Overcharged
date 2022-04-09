#include <std_include.hpp>
#include "loader/component_loader.hpp"
#include "console.hpp"
#include "havok/hks_api.hpp"
#include "havok/lua_api.hpp"
#include "utils/string.hpp"

namespace console
{
    void print(std::string msg)
    {
#ifdef DEBUG
        game::minlog.WriteLine(utils::string::va("Print: %s", msg.c_str()));
#endif
        msg = "^7" + msg + "\n";
        game::Com_Printf(0, game::consoleLabel_e::CON_LABEL_DEFAULT_0, msg.c_str());
    }

    void print_info(std::string msg)
    {
#ifdef DEBUG
        game::minlog.WriteLine(utils::string::va("print_info: %s", msg.c_str()));
#endif
        msg = "^4" + msg + "\n";
        game::Com_Printf(0, game::consoleLabel_e::CON_LABEL_DEFAULT_0, msg.c_str());
    }

    void print_error(std::string msg)
    {
#ifdef DEBUG
        game::minlog.WriteLine(utils::string::va("print_error: %s", msg.c_str()));
#endif
        if (game::I_stristr(msg.c_str(), "error"))
            msg = "^1" + msg + "\n";
        else
            msg = "^1Error: " + msg + "\n";

        game::Com_Printf(0, game::consoleLabel_e::CON_LABEL_DEFAULT_0, msg.c_str());
    }

    void print_warning(std::string msg)
    {
#ifdef DEBUG
        game::minlog.WriteLine(utils::string::va("print_warning: %s", msg.c_str()));
#endif
        msg = "^3" + msg + "\n";
        game::Com_Printf(0, game::consoleLabel_e::CON_LABEL_DEFAULT_0, msg.c_str());
    }

    int print(lua::lua_State* s)
    {
        if (hks::hksi_lua_gettop(s) != 1)
        {
            lua::luaL_error(s, "Print required 1 argment. Called with %i argument(s). Arguments expected: ( const char * info )", hks::hksi_lua_gettop(s));
        }
        /*if (!hks::hksi_lua_isstring(s, 1))
        {
            auto type = hks::hksi_lua_type(s, 1);
            lua::luaL_error(s, "Print requires argment 1 ( const char * info ) to be of type const char *. Received type %s.", hks::TypeName[type + 1]);
        }*/
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
    
    class component final : public component_interface
    {
    public:
        void lua_start() override
        {
            const lua::luaL_Reg ConsoleLibrary[] =
            {
                {"Print", print},
                {"PrintInfo", print_info},
                {"PrintError", print_error},
                {"PrintWarning", print_warning},
                {nullptr, nullptr},
            };
            hks::hksI_openlib(game::UI_luaVM, "Console", ConsoleLibrary, 0, 1);
        }
    };
}

REGISTER_COMPONENT(console::component)