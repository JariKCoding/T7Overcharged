#include <std_include.hpp>
#include "axios.hpp"
#include "console.hpp"
#include "fastfiles.hpp"
#include "hotreload.hpp"
#include "ui_error_hash.hpp"

namespace components
{
	void initialize(lua::lua_State* s)
	{
		axios::initialize(s);
		console::initialize(s);
		fastfiles::initialize(s);
		hotreload::initialize(s);
		ui_error_hash::initialize(s);
	}
}
