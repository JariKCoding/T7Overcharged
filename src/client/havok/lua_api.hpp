#pragma once
#include "game/game.hpp"
#define WEAK __declspec(selectany)

#define LUA_REGISTRYINDEX	(-10000)
#define LUA_ENVIRONINDEX	(-10001)
#define LUA_GLOBALSINDEX	(-10002)

namespace lua
{
	WEAK game::symbol<void(lua_State* s, int narg, const char* extramsg)> luaL_argerror{ (uintptr_t)GetModuleHandle(NULL) + 0x1D4CE50 };
	WEAK game::symbol<int (lua_State* s, long nargs, long nresults)> lua_pcall{ (uintptr_t)GetModuleHandle(NULL) + 0x1D53E40 };
	WEAK game::symbol<void(lua_State* s, int index, const char* k)> lua_setfield{ (uintptr_t)GetModuleHandle(NULL) + 0x1429680 };
	WEAK game::symbol<const void*  (lua_State* s, int index)> lua_topointer{ (uintptr_t)GetModuleHandle(NULL) + 0x1D4F020 };
	WEAK game::symbol<int (lua_State* s, int index)> lua_toboolean{ (uintptr_t)GetModuleHandle(NULL) + 0x14373D0 };
	WEAK game::symbol<hksUint64 (lua_State* s, int index)> lua_toui64{ (uintptr_t)GetModuleHandle(NULL) + 0x1D4C8A0 };
	WEAK game::symbol<void (lua_State* s, const char* str, size_t l)> lua_pushlstring{ (uintptr_t)GetModuleHandle(NULL) + 0xA18430 };
	WEAK game::symbol<const char* (lua_State* s, int idx, const char* fname, int szhint)> luaL_findtable{ (uintptr_t)GetModuleHandle(NULL) + 0x1D530E0 };
	WEAK game::symbol<const char* (lua_State* s, const char* str)> lua_pushstring{ (uintptr_t)GetModuleHandle(NULL) + 0xA186B0 };

	//WEAK game::symbol<void* (lua_State* s, int narg, const char* tname)> lua_pushstring{ (uintptr_t)GetModuleHandle(NULL) + 0x1D52F50 };
	WEAK game::symbol<int (lua_State* s, const char* fmt, ...)> luaL_error{ (uintptr_t)GetModuleHandle(NULL) + 0x1D53050 };

	WEAK game::symbol<int(lua_State* s, int index)> lua_isnumber{ (uintptr_t)GetModuleHandle(NULL) + 0x1429350 };

	WEAK game::symbol<__int64 (const char* key, const char* value, lua_State* luaVM)> Lua_SetTableString{ (uintptr_t)GetModuleHandle(NULL) + 0x32534688 };

	void luaL_register(lua_State* s, const char* libname, const luaL_Reg* l);
	void lua_setglobal(lua_State* s, const char* k);
	void lua_pop(lua_State* s, int n);
	HksNumber lua_tonumber(lua_State* s, int index);
	const char* lua_tostring(lua_State* s, int index);
	void lua_pushnumber(lua_State* s, HksNumber n);
	void lua_pushinteger(lua_State* s, int n);
	void lua_pushnil(lua_State* s);
	void lua_pushboolean(lua_State* s, int b);
	void lua_pushvalue(lua_State* s, int index);
	void lua_pushfstring(lua_State* s, const char* fmt, ...);
	void lua_pushvfstring(lua_State* s, const char* fmt, va_list* argp);
	void lua_getfield(lua_State* s, int index, const char* k);
	void lua_getglobal(lua_State* s, const char* k);
}


