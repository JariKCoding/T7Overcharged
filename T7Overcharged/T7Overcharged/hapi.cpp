

#include "pch.h"
#include "hapi.h"

#include "initialization.h"
#include "lstate.h"

// TODO: Can we write this shorter without the function functions all the time??

int hksi_hksL_loadbuffer(lua_State* s, HksCompilerSettings* options, char const* buff, size_t sz, char const* name)
{
	typedef int hksi_hksL_loadbuffer_t(lua_State*, HksCompilerSettings*, char const*, size_t, char const*);
	auto* f = (hksi_hksL_loadbuffer_t*)(hks::baseAddress + 0x1D4BD80);
	return f(s, options, buff, sz, name);
}

void hksI_openlib(lua_State* s, const char* libname, const luaL_Reg l[], int nup, int isHksFunc)
{
	typedef void hksI_openlib_t(lua_State*, const char*, const luaL_Reg [], int, int);
	auto* f = (hksI_openlib_t*)(hks::baseAddress + 0x1D49440);
	f(s, libname, l, nup, isHksFunc);
}

void hks_pushnamedcclosure(lua_State* s, lua_CFunction fn, int n, const char* functionName, int treatClosureAsFuncForProf)
{
	typedef void hks_pushnamedcclosure_t(lua_State*, lua_CFunction, int, const char*, int);
	auto* f = (hks_pushnamedcclosure_t*)(hks::baseAddress + 0x1D4BA70);
	f(s, fn, n, functionName, treatClosureAsFuncForProf);
}

const char* hksi_lua_pushvfstring(lua_State* s, const char* fmt, va_list* argp)
{
	typedef const char* hksi_lua_pushvfstring_t(lua_State*, const char*, va_list*);
	auto f = (hksi_lua_pushvfstring_t*)(hks::baseAddress + 0x1D4E630);
	return f(s, fmt, argp);
}

const char* hks_obj_tolstring(lua_State* s, HksObject* obj, size_t* len)
{
	typedef const char* hks_obj_tolstring_t(lua_State*, HksObject*, size_t*);
	auto f = (hks_obj_tolstring_t*)(hks::baseAddress + 0x1D4B6C0);
	return f(s, obj, len);
}

char Com_Error_(const char* file, int line, ErrorCode code, const char* fmt, ...)
{
	typedef char Com_Error_t(char const*, int, int, char const*, ...);
	auto f = (Com_Error_t*)(hks::baseAddress + 0x20F8BD0);
	return f(file, line, code, fmt);
}

void hksi_luaL_error(lua_State* s, const char* fmt, ...)
{
	typedef void hksi_luaL_error_t(lua_State*, const char*, ...);
	auto f = (hksi_luaL_error_t*)(hks::baseAddress + 0x1D4D050);
	f(s, fmt);
}

void luaL_argerror(lua_State* s, int narg, const char* extramsg)
{
	typedef void luaL_argerror_t(lua_State*, int, const char*);
	auto f = (luaL_argerror_t*)(hks::baseAddress + 0x1D4CE50);
	f(s, narg, extramsg);
}

void Lua_CoD_LuaStateManager_Error(const char* error, lua_State* luaVM)
{
	typedef void Lua_CoD_LuaStateManager_Error_t(const char* , lua_State*);
	auto f = (Lua_CoD_LuaStateManager_Error_t*)(hks::baseAddress + 0x1F12640);
	f(error, luaVM);
}

namespace hks
{
	int vm_call_internal(lua_State* s, int nargs, int nresults, const hksInstruction* pc)
	{
		typedef int vm_call_internal_t(lua_State*, int, int, const hksInstruction*);
		auto f = (vm_call_internal_t*)(hks::baseAddress + 0x1D71070);
		return f(s, nargs, nresults, pc);
	}
}
