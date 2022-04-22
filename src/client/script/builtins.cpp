#include <std_include.hpp>

#include "loader/component_loader.hpp"
#include "game/game.hpp"
#include "utils/string.hpp"

namespace builtins
{
    static std::unordered_map<int, void(__fastcall*)(game::scriptInstance_t)> custom_functions;

    void register_function(const char* name, void(*funcPtr)(game::scriptInstance_t inst))
    {
        custom_functions[fnv1a(name)] = funcPtr;
    }

    void is_profile_build_interval(game::scriptInstance_t inst)
    {
        auto functionHash = game::Scr_GetInt(inst, 0);
        if (custom_functions.find(functionHash) == custom_functions.end())
            return game::minlog.WriteLine(utils::string::va("Unknown built-in function: %h", functionHash));

        custom_functions[functionHash](inst);
    }

    class component final : public component_interface
    {
    public:
        void post_start() override
        {
	        game::isProfileBuildFunctionDef->max_args = 255;
            game::isProfileBuildFunctionDef->actionFunc = is_profile_build_interval;
        }
    };
}

REGISTER_COMPONENT(builtins::component)