#pragma once
#include "component_interface.hpp"
#include "utils/hook.hpp"

class component_loader final
{
public:
	class premature_shutdown_trigger final : public std::exception
	{
		[[nodiscard]] const char* what() const noexcept override
		{
			return "Premature shutdown requested";
		}
	};

	template <typename T>
	class installer final
	{
		static_assert(std::is_base_of<component_interface, T>::value, "component has invalid base class");

	public:
		installer()
		{
			register_component(std::make_unique<T>());
		}
	};

	template <typename T>
	static T* get()
	{
		for (const auto& component_ : get_components())
		{
			if (typeid(*component_.get()) == typeid(T))
			{
				return reinterpret_cast<T*>(component_.get());
			}
		}

		return nullptr;
	}

	static void register_component(std::unique_ptr<component_interface>&& component);

	static void initialize_hook_cycle();

	static bool post_start();
	static bool lua_start();
	static bool pre_destroy();
	static bool start_hooks();
	static bool destroy_hooks();

	static void trigger_premature_shutdown();
	
private:
	static std::vector<std::unique_ptr<component_interface>>& get_components();
};

#define REGISTER_COMPONENT(name)                       \
namespace                                           \
{                                                   \
	static component_loader::installer<name> __component; \
}
