#include <std_include.hpp>
#include "game.hpp"
#include "dvars.hpp"
#include "havok/hks_api.hpp"
#include "havok/lua_api.hpp"
#include "utils/string.hpp"
#include "utils/io.hpp"
#include "utils/hook.hpp"
#include "utils/thread.hpp"
#include "components/console.hpp"

#include <string>
#include <map>

namespace game
{
    uintptr_t base = (uintptr_t)GetModuleHandle(NULL);
	MinLog minlog = MinLog();
}
