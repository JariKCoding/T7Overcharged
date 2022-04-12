#include <std_include.hpp>
#include "loader/component_loader.hpp"
#include "havok/hks_api.hpp"
#include "havok/lua_api.hpp"
#include "game/dvars.hpp"

#include "utils/io.hpp"
#include "utils/string.hpp"
#include "utils/thread.hpp"
#include "utils/hook.hpp"

namespace hotreload
{
	// Folder where we are going to be looking for lua files
	static std::string reloadPath;
	// Map that stores when each lua files was last edited/inserted into the vm
	static std::map<std::string, std::filesystem::file_time_type> luaFilesMap = {};
	// Thread that run the hotreload every second
	bool hot_reload_running = false;
	std::thread hot_reload_thread;

	std::vector<std::filesystem::directory_entry> search_for_new_files()
	{
		std::vector<std::filesystem::directory_entry> newFiles;

		for (auto& file : std::filesystem::recursive_directory_iterator(reloadPath)) {
			auto extension = file.path().extension();
			if (extension != ".lua")
				continue;

			std::string filePath = file.path().string();
			auto modifiedTime = std::filesystem::last_write_time(file);
			if (luaFilesMap.count(filePath) == 0)
			{
				luaFilesMap.insert({ filePath, modifiedTime });
				newFiles.push_back(file);
			}
			else if (luaFilesMap[filePath] < modifiedTime)
			{
				luaFilesMap[filePath] = modifiedTime;
				newFiles.push_back(file);
			}
		}

		return newFiles;
	}

	void UI_DebugReload(const char* rootName, lua::lua_State* luaVM)
	{
		/*game::LUIElement* element;
		game::LUIScopedEvent luaEventStruct;
		element = game::UI_GetRootElement(rootName, luaVM);
		if (element)
		{
			element->currentAnimationState.flags &= 0xFFFFFFFFFFFFFFFDLL;
			game::GetLUIScopedEvent(&luaEventStruct, luaVM, rootName, "debug_reload");
			while (!luaEventStruct._finished)
			{
				lua::Lua_SetTableString("mapname", game::Dvar_GetString(dvars::sv_mapname), luaEventStruct._vm);
				luaEventStruct._finished = 1;
			}
			game::ExecuteLUIScopedEvent(&luaEventStruct);
		}*/
		auto mapname = game::Dvar_GetString(dvars::sv_mapname);
		auto eventCode = utils::string::va("LUI.roots.%s:processEvent( { name = 'debug_reload', mapname = '%s' } )", rootName, mapname);
		hks::execute_raw_lua(eventCode, "DebugReload");
	}

	bool refreshGameplayRoots = false;

	int check_for_new_files(lua::lua_State* s)
	{
		std::vector<std::filesystem::directory_entry> newFiles = search_for_new_files();

		if (newFiles.empty())
			return 0;

		game::minlog.WriteLine(utils::string::va("Found: %d files to reload", newFiles.size()));

		for (unsigned int i = 0; i < newFiles.size(); ++i)
		{
			auto file = newFiles[i];
			std::string filePath = file.path().string();

			// Read the raw lua file
			std::string data;
			utils::io::read_file(filePath.c_str(), &data);
			// Get a proper chunkname
			auto fileName = filePath.erase(0, reloadPath.size()).c_str();

			// Execute the lua from the rawfile
			if (hks::execute_raw_lua(data, fileName))
				game::minlog.WriteLine(utils::string::va("Error reloading file:  %s", fileName));
			else
				game::minlog.WriteLine(utils::string::va("Reloaded file: %s", fileName));
		}

		UI_DebugReload("UIRootFull", game::UI_luaVM);
		if (refreshGameplayRoots)
		{
			UI_DebugReload("UIRoot0", game::UI_luaVM);
			UI_DebugReload("UIRoot1", game::UI_luaVM);
		}

		return 1;
	}

	int start_hot_reload(lua::lua_State* s)
	{
		reloadPath = lua::lua_tostring(s, 1);

		check_for_new_files(s);

		std::string luaThreadCode = "local UIRootFull = LUI.roots.UIRootFull;"
			"UIRootFull.HUDRefreshTimer = LUI.UITimer.newElementTimer(1000, false, function()"
				"HotReload.CheckForNewFiles();"
			"end);"
			"UIRootFull:addElement(UIRootFull.HUDRefreshTimer);";
		hks::execute_raw_lua(luaThreadCode, "HotReloadThread");
		// Tried using a new thread to run this but that crashes the game when making lua calls
		// Another solution that doing loops in lua?
		/*/if (!hot_reload_running)
		{
			hot_reload_thread = utils::thread::create_named_thread("Lua Hot Reload", []
			{
				while (hot_reload_running) {
					check_for_new_files();
					std::this_thread::sleep_for(1000ms);
				}
				std::this_thread::yield();
			});
			hot_reload_running = true;
		}*/
		hot_reload_running = true;

		return 1;
	}

	class component final : public component_interface
	{
	public:
		void lua_start() override
		{
			const lua::luaL_Reg HotReloadLibrary[] =
			{
				{"Start", start_hot_reload},
				{"CheckForNewFiles", check_for_new_files},
				{nullptr, nullptr},
			};
			hks::hksI_openlib(game::UI_luaVM, "HotReload", HotReloadLibrary, 0, 1);
		}

		void start_hooks() override
		{
			refreshGameplayRoots = true;
			if (hot_reload_running)
			{
				UI_DebugReload("UIRoot0", game::UI_luaVM);
				UI_DebugReload("UIRoot1", game::UI_luaVM);
			}
		}

		void destroy_hooks() override
		{
			refreshGameplayRoots = false;
		}
	};
}

REGISTER_COMPONENT(hotreload::component)