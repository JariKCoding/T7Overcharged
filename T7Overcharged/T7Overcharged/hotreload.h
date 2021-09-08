#pragma once
#include "lstate.h"


namespace hks
{
	int CheckForHotReload(lua_State* s);
	int InitHotReload(lua_State* s);
}
