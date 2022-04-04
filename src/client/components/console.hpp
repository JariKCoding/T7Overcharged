#pragma once

namespace console
{
	void PrintInfo(std::string msg);
	void PrintError(std::string msg);
	void PrintWarning(std::string msg);

	void initialize(lua::lua_State*);
}