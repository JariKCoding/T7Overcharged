#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include "game/dvars.hpp"
#include "havok/hks_api.hpp"
#include "havok/lua_api.hpp"

namespace ui_error_hash
{
	int remove(lua::lua_State* s)
	{
		if (dvars::ui_error_callstack_ship->flags == 0)
			return 1;

		dvars::ui_error_callstack_ship->flags = 0;
		game::Dvar_SetFromStringByName("ui_error_callstack_ship", "1", true);

		dvars::ui_error_report_delay->flags = 0;
		game::Dvar_SetFromStringByName("ui_error_report_delay", "0", true);

		return 0;
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
	};
}

REGISTER_COMPONENT(ui_error_hash::component)