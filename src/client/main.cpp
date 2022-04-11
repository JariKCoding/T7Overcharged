#include <std_include.hpp>

#include "game/game.hpp"
#include "havok/hks_api.hpp"
#include "loader/component_loader.hpp"

extern "C"
{
	int __declspec(dllexport) init(lua::lua_State* L)
	{
		game::minlog.WriteLine("T7Overchared initiating");

		const lua::luaL_Reg T7OverchargedLibrary[] =
		{
			{nullptr, nullptr},
		};
		hks::hksI_openlib(L, "T7Overcharged", T7OverchargedLibrary, 0, 1);

		if (!component_loader::post_start())
		{
			game::Com_Error_("", 0, 0x200u, "Error while loading T7Overcharged components");
			game::minlog.WriteLine("Error while loading T7Overcharged components");
			return 0;
		}

		*(INT64*)((uintptr_t)GetModuleHandle(NULL) + 0x179C9B68) = game::Material_RegisterHandle("ui_cursor_new", 3, 1, -1);

		game::minlog.WriteLine("T7Overchared initiated");
		return 1;
	}
}