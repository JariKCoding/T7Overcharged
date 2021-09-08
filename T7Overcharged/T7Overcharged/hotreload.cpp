

#include "pch.h"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "hapi.h"
#include "lapi.h"

#include <string>
#include <dirent.h>
#include <map>

namespace hks
{
	void* s_openedMenuData = (void* )0x19C78DB0;

	static std::map<std::string, time_t> luaFilesMap = {};
	static std::vector<std::string> newFiles;

	static std::string filePath;

	void SearchForNewFiles(std::string curr_directory)
	{
		DIR* dir_point = opendir(curr_directory.c_str());
		dirent* entry = readdir(dir_point);
		while (entry) {									// if !entry then end of directory
			if (entry->d_type == DT_DIR) {				// if entry is a directory
				std::string fname = entry->d_name;
				if (fname != "." && fname != "..")
					SearchForNewFiles(curr_directory + fname + "\\");
			}
			else if (entry->d_type == DT_REG) {		// if entry is a regular file
				std::string fname = entry->d_name;	// filename
													// if filename's last characters are extension
				if (fname.find(".lua", (fname.length() - 4)) != std::string::npos)
				{
					struct stat attr;
					stat((curr_directory + fname).c_str(), &attr);
					if (luaFilesMap.count(curr_directory + fname) == 0)
					{
						luaFilesMap.insert({ curr_directory + fname, attr.st_mtime });
						newFiles.push_back(curr_directory + fname);
					}
					else if (luaFilesMap[curr_directory + fname] < attr.st_mtime)
					{
						luaFilesMap[curr_directory + fname] = attr.st_mtime;
						newFiles.push_back(curr_directory + fname);
					}
				}
			}
			entry = readdir(dir_point);
		}
	}

	int CheckForHotReload(lua_State* s)
	{
		newFiles.clear();

		SearchForNewFiles(filePath + "ui\\uieditor\\");

		if (!newFiles.empty())
		{
			// Enable lua compiler
			s->m_global->m_bytecodeSharingMode = HKS_BYTECODE_SHARING_ON;
			HksCompilerSettings hks_compiler_settings;

			for (unsigned int i = 0; i < newFiles.size(); ++i)
			{
				std::ostringstream buf;
				std::ifstream input(newFiles[i].c_str());
				buf << input.rdbuf();
				auto str = buf.str();

				auto fileName = newFiles[i].erase(0, filePath.size()).c_str();
				hksi_hksL_loadbuffer(s, &hks_compiler_settings, str.c_str(), str.size(), fileName);
				vm_call_internal(s, 0, 0, 0);
			}

			// Disable lua compiler
			s->m_global->m_bytecodeSharingMode = HKS_BYTECODE_SHARING_SECURE;
		}

		lua_pushnumber(s, !newFiles.empty());

		return 1;
	}

	int InitHotReload(lua_State* s)
	{
		filePath = lua_tostring(s, 1);

		return 1;
	}
}
