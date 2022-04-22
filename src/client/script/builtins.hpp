#pragma once

namespace builtins
{
	void register_function(const char* name, void(*funcPtr)(game::scriptInstance_t inst));
}