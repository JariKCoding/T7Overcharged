#include <std_include.hpp>
#include "loader/component_loader.hpp"
#include "havok/hks_api.hpp"
#include "havok/lua_api.hpp"

namespace axios
{
    int get(lua::lua_State* s)
    {
        auto url = lua::lua_tostring(s, 1);

        http::Request request{ url };
        const auto response = request.send("GET");

        const auto responseBody = std::string{ response.body.begin(), response.body.end() };
        lua::lua_pushstring(s, responseBody.c_str());

        return 1;
    }

    int post(lua::lua_State* s)
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

    class component final : public component_interface
    {
    public:
        void lua_start() override
        {
            const lua::luaL_Reg AxiosLibrary[] =
            {
                {"Get", get},
                {"Post", post},
                {nullptr, nullptr},
            };
            hks::hksI_openlib(game::UI_luaVM, "Axios", AxiosLibrary, 0, 1);
        }
    };
}

REGISTER_COMPONENT(axios::component)