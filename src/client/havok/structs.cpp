#include <std_include.hpp>
#include "structs.hpp"

namespace lua
{
	int hks_identity_map(const char*, int lua_line)
	{
		return lua_line;
	}
}
