#include <std_include.hpp>
#include "game.hpp"
#include "dvars.hpp"
#include "havok/hks_api.hpp"
#include "havok/lua_api.hpp"
#include "utils/string.hpp"
#include "utils/io.hpp"
#include "utils/hook.hpp"

#include <string>
#include <map>

namespace game
{
    uintptr_t base = (uintptr_t)GetModuleHandle(NULL);
	MinLog minlog = MinLog();

	int RemoveUiErrorHash(lua::lua_State*)
	{
        if (dvars::ui_error_callstack_ship->flags == 0)
            return 1;

		dvars::ui_error_callstack_ship->flags = 0;
        game::Dvar_SetFromStringByName("ui_error_callstack_ship", "1", true);

		dvars::ui_error_report_delay->flags = 0;
		game::Dvar_SetFromStringByName("ui_error_report_delay", "0", true);

        return 0;
	}

	static std::map<std::string, std::filesystem::file_time_type> luaFilesMap = {};
	static std::vector<std::string> newFiles;

	static std::string filePath;

	void SearchForNewFiles(std::string curr_directory)
	{
		for (auto &file : std::filesystem::recursive_directory_iterator(curr_directory)) {
			std::string filePStr = file.path().string();
			if (file.path().extension() != ".lua")
				continue;

			auto modifiedTime = std::filesystem::last_write_time(file);
			if (luaFilesMap.count(filePStr) == 0)
			{
				luaFilesMap.insert({ filePStr, modifiedTime });
				newFiles.push_back(filePStr);
			}
			else if (luaFilesMap[filePStr] < modifiedTime)
			{
				luaFilesMap[filePStr] = modifiedTime;
				newFiles.push_back(filePStr);
			}
		}
	}

	int CheckForHotReload(lua::lua_State* s)
	{
		newFiles.clear();

		SearchForNewFiles(filePath + "ui\\");

		if (!newFiles.empty())
		{
			// Enable lua compiler
			s->m_global->m_bytecodeSharingMode = lua::HKS_BYTECODE_SHARING_ON;
			lua::HksCompilerSettings hks_compiler_settings;

			game::minlog.WriteLine(utils::string::va("Found: %d files to reload", newFiles.size()));

			for (unsigned int i = 0; i < newFiles.size(); ++i)
			{
				std::string data;
				utils::io::read_file(newFiles[i].c_str(), &data);

				auto fileName = newFiles[i].erase(0, filePath.size()).c_str();
				hks::hksi_hksL_loadbuffer(s, &hks_compiler_settings, data.c_str(), data.size(), fileName);

				if (hks::hksi_lua_pcall(s, 0, 0, 0))
					game::minlog.WriteLine(utils::string::va("Error reloading file:  %s", fileName));
				else
					game::minlog.WriteLine(utils::string::va("Reloaded file: %s", fileName));
				
			}

			// Disable lua compiler
			s->m_global->m_bytecodeSharingMode = lua::HKS_BYTECODE_SHARING_SECURE;
		}

		lua::lua_pushnumber(s, !newFiles.empty());

		return 1;
	}

    int InitHotReload(lua::lua_State* s)
    {
        filePath = lua::lua_tostring(s, 1);

        return 1;
    }
}
