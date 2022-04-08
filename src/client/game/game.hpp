#pragma once

#include "utils/minlog.hpp"

namespace game
{
	extern uintptr_t base;
	extern MinLog minlog;

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