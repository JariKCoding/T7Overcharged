#include "game/game.hpp"
#define WEAK __declspec(selectany)

namespace hks
{
	WEAK game::symbol<void (lua::lua_State* s, const char* libname, const lua::luaL_Reg l[], int nup, int isHksFunc)> hksI_openlib { (uintptr_t)GetModuleHandle(NULL) + 0x1D49440 };
	WEAK game::symbol<int (lua::lua_State* s, lua::HksCompilerSettings* options, char const* buff, size_t sz, char const* name)> hksi_hksL_loadbuffer{ (uintptr_t)GetModuleHandle(NULL) + 0x1D4BD80 };
	WEAK game::symbol<void (lua::lua_State* s, lua::lua_CFunction fn, int n, const char* functionName, int treatClosureAsFuncForProf)> hks_pushnamedcclosure{ (uintptr_t)GetModuleHandle(NULL) + 0x1D4BA70 };
	WEAK game::symbol<const char* (lua::lua_State* s, const char* fmt, va_list* argp)> hksi_lua_pushvfstring{ (uintptr_t)GetModuleHandle(NULL) + 0x1D4E630 };
	WEAK game::symbol<const char* (lua::lua_State* s, lua::HksObject* obj, size_t* len)> hks_obj_tolstring{ (uintptr_t)GetModuleHandle(NULL) + 0x1D4B6C0 };
	WEAK game::symbol<void (lua::lua_State* s, const char* fmt, ...)> hksi_luaL_error{ (uintptr_t)GetModuleHandle(NULL) + 0x1D4D050 };
	WEAK game::symbol<int (lua::lua_State* s, int nargs, int nresults, const lua::hksInstruction* pc)> vm_call_internal{ (uintptr_t)GetModuleHandle(NULL) + 0x1D71070 };
	WEAK game::symbol<int(lua::lua_State* s, int nargs, int nresults, int errfunc)> hksi_lua_pcall{ (uintptr_t)GetModuleHandle(NULL) + 0x1D4E420 };


	WEAK game::symbol<void (const char* error, lua::lua_State* luaVM)> Lua_CoD_LuaStateManager_Error{ (uintptr_t)GetModuleHandle(NULL) + 0x1F12640 };


	static const char** TypeName = ((const char**)((*(INT64*)(((uintptr_t)GetModuleHandle(NULL) + 0x337D4B8)))));

	int hks_obj_type(const lua::HksObject* obj);
	int hksi_lua_type(lua::lua_State* s, int index);
	int hks_obj_isstring(const lua::HksObject* x);
	int hksi_lua_isstring(lua::lua_State* s, int index);
	int hksi_lua_gettop(lua::lua_State* s);
	int execute_raw_lua(std::string source, const char* chunkName);
}