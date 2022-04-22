#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include "game/dvars.hpp"
#include "havok/hks_api.hpp"
#include "havok/lua_api.hpp"

namespace lua
{
	int remove(lua::lua_State* s)
	{
		if (dvars::ui_error_callstack_ship->flags == 0)
			return 1;

		dvars::ui_error_callstack_ship->flags = (game::dvarFlags_e)0;
		game::Dvar_SetFromStringByName("ui_error_callstack_ship", "1", true);

		dvars::ui_error_report_delay->flags = (game::dvarFlags_e)0;
		game::Dvar_SetFromStringByName("ui_error_report_delay", "0", true);

		return 0;
	}

	utils::hook::detour Lua_CoD_LuaStateManager_Interface_ErrorPrint_hook;

	void Lua_CoD_LuaStateManager_Interface_ErrorPrint(game::consoleLabel_e comLabel, const char* formatString, ...)
	{
		char string[4096]{};
		va_list ap;

		va_start(ap, formatString);
		game::vsnprintf(string, 0x1000u, formatString, ap);
		string[4095] = 0;
		va_end(ap);

		game::Com_Printf(game::CON_CHANNEL_ERROR, game::CON_LABEL_LUA, "%s", string);
	}

	class component final : public component_interface
	{
	public:
		void lua_start() override
		{
			const lua::luaL_Reg UIErrorHashLibrary[] =
			{
				{"Remove", remove},
				{nullptr, nullptr},
			};
			hks::hksI_openlib(game::UI_luaVM, "UIErrorHash", UIErrorHashLibrary, 0, 1);
		}

		void start_hooks() override
		{
			Lua_CoD_LuaStateManager_Interface_ErrorPrint_hook.create(REBASE(0x141F132B0), Lua_CoD_LuaStateManager_Interface_ErrorPrint);
		}

		void destroy_hooks() override
		{
			Lua_CoD_LuaStateManager_Interface_ErrorPrint_hook.clear();
		}
	};
}

REGISTER_COMPONENT(lua::component)