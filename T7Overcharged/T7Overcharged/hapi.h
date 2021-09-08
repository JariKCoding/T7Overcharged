#pragma once
#include "lstate.h"

int hksi_hksL_loadbuffer(lua_State* s, HksCompilerSettings* options, char const* buff, size_t sz, char const* name);
void hksI_openlib(lua_State* s, const char* libname, const luaL_Reg l[], int nup, int isHksFunc);
void hks_pushnamedcclosure(lua_State* s, lua_CFunction fn, int n, const char* functionName, int treatClosureAsFuncForProf);
const char* hksi_lua_pushvfstring(lua_State* s, const char* fmt, va_list* argp);
const char* hks_obj_tolstring(lua_State* s, HksObject* obj, size_t* len);
char Com_Error_(const char* file, int line, ErrorCode code, const char* fmt, ...);
void hksi_luaL_error(lua_State* s, const char* fmt, ...);
void luaL_argerror(lua_State* s, int narg, const char* extramsg);
void Lua_CoD_LuaStateManager_Error(const char* error, lua_State* luaVM);


namespace hks
{
	int vm_call_internal(lua_State* s, int nargs, int nresults, const hksInstruction* pc);
}