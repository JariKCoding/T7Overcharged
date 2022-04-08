#include <std_include.hpp>
#include "hks_api.hpp"

namespace hks
{
	int execute_raw_lua(std::string source, const char* chunkName)
	{
		lua::HksCompilerSettings hks_compiler_settings;
		// Enable compiling with source lua
		game::UI_luaVM->m_global->m_bytecodeSharingMode = lua::HKS_BYTECODE_SHARING_ON;
		// Compile the source lua
		hks::hksi_hksL_loadbuffer(game::UI_luaVM, &hks_compiler_settings, source.c_str(), source.size(), chunkName);
		// Turn off raw compiling so compiled files can be loaded again
		game::UI_luaVM->m_global->m_bytecodeSharingMode = lua::HKS_BYTECODE_SHARING_SECURE;

		return hks::hksi_lua_pcall(game::UI_luaVM, 0, 0, 0);
	}
}