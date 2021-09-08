#pragma once
#include "lstate.h"

int lua_pcall(lua_State* s, long nargs, long nresults);
void luaL_register(lua_State* s, const char* libname, const luaL_Reg* l);
void lua_pop(lua_State* s, int n);
void lua_setglobal(lua_State* s, const char* k);
void lua_setfield(lua_State* s, int index, const char* k);
HksNumber lua_tonumber(lua_State* s, int index);
const char* lua_tostring(lua_State* s, int index);
const void* lua_topointer(lua_State* s, int index);
int lua_toboolean(lua_State* s, int index);
void lua_pushnumber(lua_State* s, HksNumber n);
void lua_pushinteger(lua_State* s, int n);
void lua_pushnil(lua_State* s);
void lua_pushboolean(lua_State* s, int b);
void lua_pushvalue(lua_State* s, int index);
void lua_pushlstring(lua_State* s, const char* str, size_t l);
void lua_pushfstring(lua_State* s, const char* fmt, ...);
void lua_pushvfstring(lua_State* s, const char* fmt, va_list* argp);