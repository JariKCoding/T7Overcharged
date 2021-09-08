#pragma once

extern struct lua_State;
extern struct lua_Debug;

typedef hksInt32(*lua_CFunction)(lua_State*);
typedef void (*lua_Hook)(lua_State*, lua_Debug*);