#include <std_include.hpp>
#include "axios.hpp"

namespace components
{
	void initialize(lua::lua_State* s)
	{
		axios::initialize(s);
	}
}