#include <std_include.hpp>
#include "hks_api.hpp"

namespace hks
{
    int hks_obj_type(const lua::HksObject* obj)
    {
        lua::hksUint32 v2;
        int obj_4;

        v2 = obj->t & 0xF;
        if (v2 == 9 || v2 == 10)
            obj_4 = 6;
        else
            obj_4 = obj->t & 0xF;
        return obj_4;
    }

    int hksi_lua_type(lua::lua_State* s, int index)
    {
        lua::HksErrorFunctionType v2;
        int v4;
        lua::HksObject* v5;
        int failure;

        if (index <= -10000)
        {
            failure = 0;
            switch (index)
            {
            case -10000:
                v5 = &s->m_global->m_registry;
                break;
            case -10002:
                v5 = &s->globals;
                break;
            case -10001:
                s->m_cEnv.v.cClosure = (lua::cclosure*)s->m_apistack.base[-1].v.cClosure->m_env;
                s->m_cEnv.t = 5;
                v5 = &s->m_cEnv;
                break;
            default:
                v5 = (lua::HksObject*)(&s->m_apistack.base[-1].v.cClosure->m_numUpvalues + 8 * (-10002 - index));
                break;
            }
        }
        else if (index <= 0)
        {
            if (index >= 0)
            {
                failure = 1;
                v5 = 0LL;
            }
            else if (&s->m_apistack.top[index] < s->m_apistack.base)
            {
                failure = 1;
                v5 = 0LL;
            }
            else
            {
                failure = 0;
                v5 = &s->m_apistack.top[index];
            }
        }
        else if (&s->m_apistack.base[index - 1] >= s->m_apistack.top)
        {
            failure = 1;
            v5 = 0LL;
        }
        else
        {
            failure = 0;
            v5 = &s->m_apistack.base[index - 1];
        }
        if (failure)
            v4 = -1;
        else
            v4 = hks_obj_type(v5);
        return v4;
    }

    int hks_obj_isstring(const lua::HksObject* x)
    {
        return (x->t & 0xF) == 4 || (x->t & 0xF) == 3;
    }

    int hksi_lua_isstring(lua::lua_State* s, int index)
    {
        lua::HksErrorFunctionType v2;
        int v4;
        lua::HksObject* v5;
        int failure;

        if (index <= -10000)
        {
            failure = 0;
            switch (index)
            {
            case -10000:
                v5 = &s->m_global->m_registry;
                break;
            case -10002:
                v5 = &s->globals;
                break;
            case -10001:
                s->m_cEnv.v.cClosure = (lua::cclosure*)s->m_apistack.base[-1].v.cClosure->m_env;
                s->m_cEnv.t = 5;
                v5 = &s->m_cEnv;
                break;
            default:
                v5 = (lua::HksObject*)(&s->m_apistack.base[-1].v.cClosure->m_numUpvalues + 8 * (-10002 - index));
                break;
            }
        }
        else if (index <= 0)
        {
            if (index >= 0)
            {
                failure = 1;
                v5 = 0LL;
            }
            else if (&s->m_apistack.top[index] < s->m_apistack.base)
            {
                failure = 1;
                v5 = 0LL;
            }
            else
            {
                failure = 0;
                v5 = &s->m_apistack.top[index];
            }
        }
        else if (&s->m_apistack.base[index - 1] >= s->m_apistack.top)
        {
            failure = 1;
            v5 = 0LL;
        }
        else
        {
            failure = 0;
            v5 = &s->m_apistack.base[index - 1];
        }
        if (failure)
            v4 = 0;
        else
            v4 = hks_obj_isstring(v5);
        return v4;
    }

	int hksi_lua_gettop(lua::lua_State* s)
	{
		return s->m_apistack.top - s->m_apistack.base;
	}

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