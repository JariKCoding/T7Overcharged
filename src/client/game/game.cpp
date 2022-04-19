#include <std_include.hpp>
#include "game.hpp"
#include "dvars.hpp"
#include "havok/hks_api.hpp"
#include "havok/lua_api.hpp"
#include "utils/string.hpp"
#include "utils/io.hpp"
#include "utils/hook.hpp"
#include "utils/thread.hpp"
#include "components/console.hpp"

#include <string>
#include <map>

namespace game
{
    uintptr_t base = (uintptr_t)GetModuleHandle(NULL);
	MinLog minlog = MinLog();
	std::unordered_map<game::dvarStrHash_t, std::string> dvarHashMap_s;

	void LoadDvarHashMap()
	{
		auto file = utils::io::read_file("dvar_hash_list.txt");
		// remove carriage return because std::getline is lame
		file.erase(std::ranges::remove(file, '\r').begin(), file.end());
		
		std::istringstream file_str{ file };
		std::string line;
		
		while (std::getline(file_str, line, '\n'))
		{
			const auto separator = line.find(',');

			if (separator == std::string::npos)
				continue;

			// doing name (hash),debugName since we search for the hash instead
			const auto hashValue = strtoul(line.substr(separator + 1).c_str(), nullptr, 16);
			const auto debugName = line.substr(0, separator);

			dvarHashMap_s.emplace(std::make_pair(hashValue, debugName));
		}
	}
}
