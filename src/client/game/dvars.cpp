#include <std_include.hpp>

#define GET_DVAR(ptr) ((game::dvar_t*)((*(INT64*)(((uintptr_t)GetModuleHandle(NULL) + ptr)))))

namespace dvars
{
	game::dvar_t* ui_error_report = GET_DVAR(0x168F0EA8);
	game::dvar_t* ui_error_report_delay = GET_DVAR(0x168F0EB0);
	game::dvar_t* ui_error_callstack_ship = GET_DVAR(0x168EFCA0);

	game::dvar_t* sv_mapname = GET_DVAR(0x177C77D0);
	game::dvar_t* ui_mapname = GET_DVAR(0x179E1AC0);
	game::dvar_t* ui_gametype = GET_DVAR(0x179E1AD0);

	game::dvar_t* com_maxclients = GET_DVAR(0x168EF850);
}