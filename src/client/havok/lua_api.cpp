#include <std_include.hpp>
#include "lua_api.hpp"
#include "hks_api.hpp"

namespace lua
{
	HksObject getObjectForIndex(lua_State* s, int index)
	{
		//HksNumber result;
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
				s->m_cEnv.v.cClosure = (cclosure*)s->m_apistack.base[-1].v.cClosure->m_env;
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

	void luaL_register(lua_State* s, const char* libname, const luaL_Reg* l)
	{
		hks::hksI_openlib(s, libname, l, 0, 1);
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
		return hks::hks_obj_tolstring(s, &object, 0);
	}

	void lua_pushnumber(lua_State* s, HksNumber n)
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

	void lua_pushnil(lua_State* s)
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

	void lua_pushfstring(lua_State* s, const char* fmt, ...)
	{
		va_list va;
		va_start(va, fmt);
		hks::hksi_lua_pushvfstring(s, fmt, &va);
	}

	void lua_pushvfstring(lua_State* s, const char* fmt, va_list* argp)
	{
		hks::hksi_lua_pushvfstring(s, fmt, argp);
	}

	void lua_getfield(lua_State* s, int index, const char*)
	{
		auto object = getObjectForIndex(s, index);

		//const HksRegister v16;

		auto top = --s->m_apistack.top;
		top->v.cClosure = object.v.cClosure;
		s->m_apistack.top = top++;
	}

	void lua_getglobal(lua_State* s, const char* k)
	{
		lua_getfield(s, LUA_GLOBALSINDEX, k);
	}
}