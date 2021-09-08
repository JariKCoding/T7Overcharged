

#include "pch.h"
#include "lapi.h"

#include "hapi.h"
#include "initialization.h"

#define LUA_REGISTRYINDEX	(-10000)
#define LUA_ENVIRONINDEX	(-10001)
#define LUA_GLOBALSINDEX	(-10002)

HksObject getObjectForIndex(lua_State* s, int index)
{
    HksNumber result;
    HksObject* object;
    int failure;

    if (index <= LUA_REGISTRYINDEX)
    {
        failure = 0;
        switch (index)
        {
        case LUA_REGISTRYINDEX:
            object = &s->m_global->m_registry;
            break;
        case LUA_GLOBALSINDEX:
            object = &s->globals;
            break;
        case LUA_ENVIRONINDEX:
            s->m_cEnv.v.cClosure = (hks::cclosure*)s->m_apistack.base[-1].v.cClosure->m_env;
            s->m_cEnv.t = 5;
            object = &s->m_cEnv;
            break;
        default:
            object = (HksObject*)(&s->m_apistack.base[-1].v.cClosure->m_numUpvalues + 8 * (LUA_GLOBALSINDEX - index));
            break;
        }
    }
    else if (index <= 0)
    {
        if (index >= 0)
        {
            failure = 1;
            object = 0LL;
        }
        else if (&s->m_apistack.top[index] < s->m_apistack.base)
        {
            failure = 1;
            object = 0LL;
        }
        else
        {
            failure = 0;
            object = &s->m_apistack.top[index];
        }
    }
    else if (&s->m_apistack.base[index - 1] >= s->m_apistack.top)
    {
        failure = 1;
        object = 0LL;
    }
    else
    {
        failure = 0;
        object = &s->m_apistack.base[index - 1];
    }
    // TODO: Handle failures
    return *object;
}

int lua_pcall(lua_State* s, long nargs, long nresults)
{
	typedef int lua_pcall_t(lua_State* luaState, long, long);
	lua_pcall_t* f2 = (lua_pcall_t*)(hks::baseAddress + 0x1D53E40);
	return f2(s, nargs, nresults);
}

void luaL_register(lua_State* s, const char* libname, const luaL_Reg* l)
{
	hksI_openlib(s, libname, l, 0, 1);
}

void lua_setfield(lua_State* s, int index, const char* k)
{
	typedef void lua_setfield_t(lua_State* luaState, int, const char*);
	auto f = (lua_setfield_t*)(hks::baseAddress + 0x1429680);
	f(s, index, k);
}

void lua_setglobal(lua_State* s, const char* k)
{
	lua_setfield(s, LUA_GLOBALSINDEX, k);
}

void lua_pop(lua_State* s, int n)
{
	s->m_apistack.top -= n;
}

HksNumber lua_tonumber(lua_State* s, int index)
{
    auto object = getObjectForIndex(s, index);
    return object.v.number;
}

const char* lua_tostring(lua_State* s, int index)
{
    auto object = getObjectForIndex(s, index);
    return hks_obj_tolstring(s, &object, 0);
}

const void* lua_topointer(lua_State* s, int index)
{
    typedef const void* lua_topointer_t(lua_State* luaState, int);
    auto f = (lua_topointer_t*)(hks::baseAddress + 0x1D4F020);
    return f(s, index);
}

int lua_toboolean(lua_State* s, int index)
{
    typedef int lua_toboolean_t(lua_State* luaState, int);
    auto f = (lua_toboolean_t*)(hks::baseAddress + 0x14373D0);
    return f(s, index);
}

hksUint64 lua_toui64(lua_State* s, int index)
{
    typedef hksUint64 lua_toui64_t(lua_State* luaState, int);
    auto f = (lua_toui64_t*)(hks::baseAddress + 0x1D4C8A0);
    return f(s, index);
}

void lua_pushnumber(lua_State*s, HksNumber n)
{
    auto top = s->m_apistack.top;
    top->v.number = n;
    top->t = TNUMBER;
    s->m_apistack.top = top + 1;
}

void lua_pushinteger(lua_State* s, int n)
{
    auto top = s->m_apistack.top;
    top->v.number = float(n);
    top->t = TNUMBER;
    s->m_apistack.top = top + 1;
}

void lua_pushnil(lua_State*s)
{
    auto top = s->m_apistack.top;
    top->v.number = 0;
    top->t = TNIL;
    s->m_apistack.top = top + 1;
}

void lua_pushboolean(lua_State* s, int b)
{
    auto top = s->m_apistack.top;
    top->v.boolean = b;
    top->t = TBOOLEAN;
    s->m_apistack.top = top + 1;
}

void lua_pushvalue(lua_State* s, int index)
{
    HksObject* st;
    auto object = getObjectForIndex(s, index);
    st = s->m_apistack.top;
    *st = object;
    s->m_apistack.top = st + 1;
}

void lua_pushlstring(lua_State* s, const char* str, size_t l)
{
    typedef void lua_pushlstring_t(lua_State* luaState, const char*, size_t);
    auto f = (lua_pushlstring_t*)(hks::baseAddress + 0xA18430);
    f(s, str, l);
}

void lua_pushfstring(lua_State* s, const char* fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    hksi_lua_pushvfstring(s, fmt, &va);
}

void lua_pushvfstring(lua_State* s, const char* fmt, va_list* argp)
{
    hksi_lua_pushvfstring(s, fmt, argp);
}

void lua_getfield(lua_State* s, int index, const char* k)
{
    auto object = getObjectForIndex(s, index);

    const HksRegister v16;

    auto top = --s->m_apistack.top;
    top->v.cClosure = object.v.cClosure;
    s->m_apistack.top = top++;
}

void lua_getglobal(lua_State* s, const char* k)
{
    lua_getfield(s, LUA_GLOBALSINDEX, k);
}