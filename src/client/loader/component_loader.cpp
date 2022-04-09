#include <std_include.hpp>
#include "component_loader.hpp"
#include "havok/hks_api.hpp"
#include "game/game.hpp"
#include "utils/string.hpp"

void component_loader::register_component(std::unique_ptr<component_interface>&& component_)
{
	get_components().push_back(std::move(component_));
}

static utils::hook::detour com_loadfrontend_hook;
static bool com_loadfrontend_hooked = false;

__int64 com_loadfrontend_internal()
{
	game::minlog.WriteLine("Com_LoadFrontEnd hook called, destroying hooks");
	component_loader::destroy_hooks();
	__int64 result = com_loadfrontend_hook.invoke<__int64>();
	com_loadfrontend_hook.clear();
	com_loadfrontend_hooked = false;
	return result;
}

int hook_cycle_create(lua::lua_State* s)
{
	if (com_loadfrontend_hooked)
	{
		game::minlog.WriteDebug("Hooks already active");
		return 0;
	}
	component_loader::start_hooks();
	com_loadfrontend_hook.create(0x2148E20, &com_loadfrontend_internal);
	com_loadfrontend_hooked = true;
	game::minlog.WriteDebug("Hooks started");
	return 1;
}

void component_loader::initialize_hook_cycle()
{
	if (!game::Com_IsRunningUILevel())
	{
		game::minlog.WriteDebug("Creating first snapshot event handler");
		// Add a function that we can call from lua
		const lua::luaL_Reg HookCycleLibrary[] =
		{
			{"Create", hook_cycle_create},
			{nullptr, nullptr},
		};
		hks::hksI_openlib(game::UI_luaVM, "HookCycle", HookCycleLibrary, 0, 1);

		// Create a event handler for when the hud is created, at this point it is safe to start hooks
		std::string hookCycleEvent = "local root = LUI.roots.UIRoot0; "
			"local oldEvent = root.m_eventHandlers['addmenu']; "
			"root:registerEventHandler( 'addmenu', function( element, event ) "
				"oldEvent( element, event ); "
				"local rootChild = element:getFirstChild(); "
				"local oldSnapshotEvent = rootChild.m_eventHandlers['first_snapshot']; "
				"rootChild:registerEventHandler( 'first_snapshot', function( element, event ) "
					"oldSnapshotEvent( element, event ); "
					"HookCycle.Create(); "
				"end ); "
			"end ); ";
		hks::execute_raw_lua(hookCycleEvent, "HookCycleEvent");
	}
	else
	{
		game::minlog.WriteDebug("Frontend active, can't add hooks here");
	}
}

bool component_loader::post_start()
{
	lua_start();

	static auto handled = false;
	if (handled) return true;
	handled = true;

	try
	{
		for (const auto& component_ : get_components())
		{
			component_->post_start();
		}
	}
	catch (premature_shutdown_trigger&)
	{
		return false;
	}

	return true;
}

bool component_loader::lua_start()
{
	try
	{
		for (const auto& component_ : get_components())
		{
			component_->lua_start();
		}
	}
	catch (premature_shutdown_trigger&)
	{
		return false;
	}

	initialize_hook_cycle();

	return true;
}

bool component_loader::pre_destroy()
{
	static auto handled = false;
	if (handled) return true;
	handled = true;

	try
	{
		for (const auto& component_ : get_components())
		{
			component_->pre_destroy();
		}
	}
	catch (premature_shutdown_trigger&)
	{
		return false;
	}

	return true;
}

bool component_loader::start_hooks()
{
	static auto handled = false;
	if (handled) return true;
	handled = true;

	try
	{
		for (const auto& component_ : get_components())
		{
			component_->start_hooks();
		}
	}
	catch (premature_shutdown_trigger&)
	{
		return false;
	}

	return true;
}

bool component_loader::destroy_hooks()
{
	static auto handled = false;
	if (handled) return true;
	handled = true;

	try
	{
		for (const auto& component_ : get_components())
		{
			component_->destroy_hooks();
		}
	}
	catch (premature_shutdown_trigger&)
	{
		return false;
	}

	return true;
}

void component_loader::trigger_premature_shutdown()
{
	throw premature_shutdown_trigger();
}

std::vector<std::unique_ptr<component_interface>>& component_loader::get_components()
{
	using component_vector = std::vector<std::unique_ptr<component_interface>>;
	using component_vector_container = std::unique_ptr<component_vector, std::function<void(component_vector*)>>;

	static component_vector_container components(new component_vector, [](component_vector* component_vector)
		{
			pre_destroy();
			delete component_vector;
		});

	return *components;
}
