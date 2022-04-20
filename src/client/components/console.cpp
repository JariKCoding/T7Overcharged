#include <std_include.hpp>
#include "loader/component_loader.hpp"
#include "console.hpp"
#include "havok/hks_api.hpp"
#include "havok/lua_api.hpp"
#include "utils/string.hpp"
#include <utils/io.hpp>

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

	utils::hook::detour Com_EventLoop_hook;
	static bool console_init = false;

	int show_external_console(lua::lua_State* s)
	{
		if (!console_init)
		{
			game::Sys_ShowConsole();
			console_init = true;
		}
		return 1;
	}

	void Com_EventLoop(bool poll)
	{
		Com_EventLoop_hook.invoke<void>(poll);

		if (!console_init)
			return;

		MSG msg{};

		while (PeekMessageA(&msg, nullptr, 0, 0, 0))
		{
			if (GetMessageA(&msg, nullptr, 0, 0))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
		}
	}

	utils::hook::detour Dvar_GetDebugName_hook;

	const char* Dvar_GetDebugName(const game::dvar_t* dvar)
	{
		auto result = Dvar_GetDebugName_hook.invoke<const char*>(dvar);

		auto it = game::dvarHashMap_s.find(dvar->name);
		if (it != game::dvarHashMap_s.end())
		{
			return it->second.c_str();
		}

		return result;
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
				{"ShowExternalConsole", show_external_console},
				{nullptr, nullptr},
			};
			hks::hksI_openlib(game::UI_luaVM, "Console", ConsoleLibrary, 0, 1);
		}

		void start_hooks() override
		{
#define REBASE(address) (uintptr_t)((address - 0x140000000) + game::base)
			utils::hook::nop(REBASE(0x142152652), 13);  // Com_DvarDumpSingle Dvar_GetFlags call
			//utils::hook::nop(REBASE(0x142153233), 7); // Dvar_ToggleInternal, remove (dvar->flags & 1) == 0
			//utils::hook::nop(REBASE(0x142152973), 9);	// Dvar_Command, remove (dvar->flags & 1) == 0
			//utils::hook::nop(REBASE(0x1422B92B0), 6);	// Dvar_CanChangeValue, remove (dvar->flags & 1) != 0
			utils::hook::nop(REBASE(0x1420EEFB0), 6);	// Cmd_List_f, remove i->unknown
			utils::hook::nop(REBASE(0x1420EDED1), 10);	// Cmd_ExecuteSingleCommandInternal, remove next->unknown
			utils::hook::nop(REBASE(0x1420EDF90), 6);	// Cmd_ForEach, remove i->unknown

			Com_EventLoop_hook.create(0x20F94B0, Com_EventLoop);
			Dvar_GetDebugName_hook.create(0x22BDCB0, Dvar_GetDebugName);
		}

		void destroy_hooks() override
		{
			Com_EventLoop_hook.clear();
			Dvar_GetDebugName_hook.clear();
		}
	};
}

REGISTER_COMPONENT(console::component)