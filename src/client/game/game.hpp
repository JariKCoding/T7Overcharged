#pragma once

#include "utils/minlog.hpp"

namespace game
{
	static uintptr_t base;
	static MinLog minlog;

	void initialize();
	int RemoveUiErrorHash(lua::lua_State* s);
	int CheckForHotReload(lua::lua_State* s);
	int InitHotReload(lua::lua_State* s);

	template <typename T>
	class symbol
	{
	public:
		symbol(const uintptr_t address)
			: object_(reinterpret_cast<T*>(address))
		{
		}

		T* get() const
		{
			return object_;
		}

		operator T* () const
		{
			return this->get();
		}

		T* operator->() const
		{
			return this->get();
		}

	private:
		T* object_;
	};
}
#include "symbols.hpp"