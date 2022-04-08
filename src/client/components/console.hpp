#pragma once

namespace console
{
	void print_info(std::string msg);
	void print_error(std::string msg);
	void print_warning(std::string msg);

	void initialize(lua::lua_State*);
}