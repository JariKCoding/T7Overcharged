#include <std_include.hpp>
#include "axios.hpp"
#include "fastfiles.hpp"
#include "console.hpp"

namespace components
{
	void initialize(lua::lua_State* s)
	{
		axios::initialize(s);
		fastfiles::initialize(s);
		console::initialize(s);
		console::PrintInfo("Test Info");
		console::PrintError("Test Error");
		console::PrintWarning("Test warning");
	}
}
