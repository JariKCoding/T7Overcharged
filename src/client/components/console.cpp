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
		game::Com_Printf(game::consoleChannel_e::CON_CHANNEL_DONT_FILTER, game::consoleLabel_e::CON_LABEL_DEFAULT, msg.c_str());
	}

	void print_info(std::string msg)
	{
#ifdef DEBUG
		game::minlog.WriteLine(utils::string::va("print_info: %s", msg.c_str()));
#endif
		msg = "^4" + msg + "\n";
		game::Com_Printf(game::consoleChannel_e::CON_CHANNEL_DONT_FILTER, game::consoleLabel_e::CON_LABEL_DEFAULT, msg.c_str());
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

		game::Com_Printf(game::consoleChannel_e::CON_CHANNEL_DONT_FILTER, game::consoleLabel_e::CON_LABEL_DEFAULT, msg.c_str());
	}

	void print_warning(std::string msg)
	{
#ifdef DEBUG
		game::minlog.WriteLine(utils::string::va("print_warning: %s", msg.c_str()));
#endif
		msg = "^3" + msg + "\n";
		game::Com_Printf(game::consoleChannel_e::CON_CHANNEL_DONT_FILTER, game::consoleLabel_e::CON_LABEL_DEFAULT, msg.c_str());
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

	bool Dvar_IsSessionModeBaseDvar(const game::dvar_t* dvar)
	{
		return dvar->type == game::DVAR_TYPE_SESSIONMODE_BASE_DVAR;
	}

	bool Dvar_IsSessionModeSpecificDvar(const game::dvar_t* dvar)
	{
		return (dvar->flags & 0x8000) != 0;
	}

	utils::hook::detour Dvar_ForEachName_1_hook;
	utils::hook::detour Dvar_ForEachName_2_hook;

	//void Dvar_ForEachName_Complete(void (*callback)(const char*)) // this is for CompleteCommand only
	//{
	//	const char* DebugName;
	//	game::dvar_t* dvar;
	//	int dvarIter;

	//	for (dvarIter = 0; dvarIter < *game::g_dvarCount; ++dvarIter)
	//	{
	//		dvar = &*game::s_dvarPool[dvarIter];
	//		if ((!game::Com_SessionMode_IsMode(game::MODE_COUNT) || !Dvar_IsSessionModeBaseDvar(dvar))
	//			&& !Dvar_IsSessionModeSpecificDvar(dvar))
	//		{
	//			DebugName = Dvar_GetDebugName(dvar);
	//			callback(DebugName);
	//		}
	//	}
	//}

	void Dvar_ForEachName_Match(game::LocalClientNum_t localClientNum, void (*callback)(game::LocalClientNum_t, const char*))
	{
		for (int dvarIter = 0; dvarIter < *game::g_dvarCount; ++dvarIter)
		{
			//TODO: don't ask
			auto dvar = reinterpret_cast<const game::dvar_t*>(&game::s_dvarPool[160 * dvarIter]);

			if ((!game::Com_SessionMode_IsMode(game::MODE_COUNT) || !Dvar_IsSessionModeBaseDvar(dvar))
				&& !Dvar_IsSessionModeSpecificDvar(dvar))
			{
				const char* DebugName = Dvar_GetDebugName(dvar);
				callback(localClientNum, DebugName);
			}
		}
	}

	utils::hook::detour Dvar_CanSetConfigDvar_hook;

	bool Dvar_CanSetConfigDvar(const game::dvar_t* dvar)
	{
		//TODO: ???
		return true;
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
			utils::hook::nop(REBASE(0x1420EEFB0), 6);	// Cmd_List_f, remove i->unknown
			utils::hook::nop(REBASE(0x1420EDED1), 10);	// Cmd_ExecuteSingleCommandInternal, remove next->unknown
			utils::hook::nop(REBASE(0x1420EDF90), 6);	// Cmd_ForEach, remove i->unknown
			utils::hook::nop(REBASE(0x142152652), 13);	// Com_DvarDumpSingle, remove Dvar_GetFlags call
			utils::hook::nop(REBASE(0x1422B92B0), 6);	// Dvar_CanChangeValue, remove (dvar->flags & 1) != 0
			utils::hook::nop(REBASE(0x142152973), 7);	// Dvar_Command, remove (dvar->flags & 1) == 0
			//utils::hook::nop(REBASE(0x1422BD82A), 16);	// Dvar_ForEachName_Match, remove (dvar->flags & 1) != 0, don't need rewrote function
			utils::hook::nop(REBASE(0x142152C80), 13);	// Dvar_ListSingle, remove Dvar_GetFlags call
			utils::hook::nop(REBASE(0x142153233), 9);	// Dvar_ToggleInternal, remove (dvar->flags & 1) == 0

			Com_EventLoop_hook.create(REBASE(0x1420F94B0), &Com_EventLoop);
			Dvar_CanSetConfigDvar_hook.create(REBASE(0x1422B92F0), &Dvar_CanSetConfigDvar);
			//Dvar_ForEachName_1_hook.create(0x22BD890, &Dvar_ForEachName_Complete);
			Dvar_ForEachName_2_hook.create(REBASE(0x1422BD7E0), &Dvar_ForEachName_Match);
			Dvar_GetDebugName_hook.create(REBASE(0x1422BDCB0), &Dvar_GetDebugName);
		}

		void destroy_hooks() override
		{
			Com_EventLoop_hook.clear();
			Dvar_CanSetConfigDvar_hook.clear();
			//Dvar_ForEachName_1_hook.clear();
			Dvar_ForEachName_2_hook.clear();
			Dvar_GetDebugName_hook.clear();
		}
	};
}

REGISTER_COMPONENT(console::component)