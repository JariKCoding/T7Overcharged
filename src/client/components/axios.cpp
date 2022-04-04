#include <std_include.hpp>
#include "axios.hpp"
#include "havok/hks_api.hpp"
#include "havok/lua_api.hpp"

namespace axios
{
    int Get(lua::lua_State* s)
    {
        auto url = lua::lua_tostring(s, 1);

        http::Request request{ url };
        const auto response = request.send("GET");

        const auto responseBody = std::string{ response.body.begin(), response.body.end() };
        lua::lua_pushstring(s, responseBody.c_str());

        return 1;
    }

    int Post(lua::lua_State* s)
    {
        auto url = lua::lua_tostring(s, 1);
        auto body = lua::lua_tostring(s, 2);

        http::Request request{ url };
        const auto response = request.send("POST", body, {
            {"Content-Type", "application/json"}
        });

        const auto responseBody = std::string{ response.body.begin(), response.body.end() };
        lua::lua_pushstring(s, responseBody.c_str());

        return 1;
    }

	void initialize(lua::lua_State* s)
	{
        // Add the library to lua
        const lua::luaL_Reg AxiosLibrary[] =
        {
            {"Get", Get},
            {"Post", Post},
            {nullptr, nullptr},
        };
        hks::hksI_openlib(s, "Axios", AxiosLibrary, 0, 1);
	}
}