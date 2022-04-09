#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include "game/game.hpp"
#include "utils/hook.hpp"
#include "utils/string.hpp"

namespace fastfiles
{
	utils::hook::detour db_try_load_x_file_internal_hook;

	void db_try_load_x_file_internal(const char* zoneName, const int zone_flags, const int is_base_map)
	{
		game::minlog.WriteLine(utils::string::va("Loading fastfile %s\n", zoneName));
		return db_try_load_x_file_internal_hook.invoke<void>(zoneName, zone_flags, is_base_map);
	}
	
	class component final : public component_interface
	{
	public:
		void start_hooks() override
		{
			db_try_load_x_file_internal_hook.create(0x1425010, &db_try_load_x_file_internal);
		}

		void destroy_hooks() override
		{
			db_try_load_x_file_internal_hook.clear();
		}
	};
}

#ifdef DEBUG
REGISTER_COMPONENT(fastfiles::component)
#endif