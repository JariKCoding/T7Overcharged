#include <std_include.hpp>
#include "loader/component_loader.hpp"
#include "scheduler.hpp"
#include "game/game.hpp"
#include "game/dvars.hpp"
#include "havok/hks_api.hpp"
#include "havok/lua_api.hpp"

#include <utils/string.hpp>

#include <discord_rpc.h>

namespace discord
{
	DiscordRichPresence discord_presence;

	int roundsPlayed;
	int playerScore;
	int enemyScore;
	bool isIngame = false;

	void update_discord()
	{
		Discord_RunCallbacks();

		if (!isIngame)
		{
			discord_presence.details = game::Com_SessionMode_IsMode(game::eModes::MODE_CAMPAIGN) ? "Campaign" : game::Com_SessionMode_IsMode(game::eModes::MODE_MULTIPLAYER) ? "Multiplayer" : "Zombies";
			discord_presence.state = "Lobby";
			roundsPlayed = 0;
			playerScore = 0;
			enemyScore = 0;

			discord_presence.startTimestamp = 0;

			discord_presence.largeImageKey = "t7overcharged";
		}
		else
		{
			auto map = game::UI_SafeTranslateString(game::Com_GameInfo_GetMapRef(dvars::ui_mapname->current.string));

			if (game::Com_SessionMode_IsMode(game::eModes::MODE_CAMPAIGN))
			{
				discord_presence.state = "In-Game";
				discord_presence.details = map;
			}
			else if (game::Com_SessionMode_IsMode(game::eModes::MODE_MULTIPLAYER))
			{
				auto gametype = game::UI_SafeTranslateString(game::Com_GameInfo_GetGameTypeRef(dvars::ui_gametype->current.string));
				discord_presence.details = utils::string::va("%s on %s", gametype, map);
				discord_presence.state = utils::string::va("%d - %d", playerScore, enemyScore);
			}
			else
			{
				discord_presence.state = utils::string::va("Round %d", roundsPlayed);
				discord_presence.details = map;
			}
			

			if (!discord_presence.startTimestamp)
			{
				discord_presence.startTimestamp = std::chrono::duration_cast<std::chrono::seconds>(
					std::chrono::system_clock::now().time_since_epoch()).count();
			}

			discord_presence.largeImageKey = dvars::ui_mapname->current.string;
		}

		discord_presence.partySize = game::LobbySession_GetClientCount(0, game::LobbyClientType::LOBBY_CLIENT_TYPE_ALL);
		discord_presence.partyMax = dvars::com_maxclients->current.integer;

		Discord_UpdatePresence(&discord_presence);
	}

	int enable(lua::lua_State* s);

	int set_rounds_played(lua::lua_State* s)
	{
		roundsPlayed = lua::lua_tonumber(s, 1);
		return 1;
	}

	int set_playerscore(lua::lua_State* s)
	{
		playerScore = lua::lua_tonumber(s, 1);
		return 1;
	}

	int set_enemyscore(lua::lua_State* s)
	{
		enemyScore = lua::lua_tonumber(s, 1);
		return 1;
	}

	class component final : public component_interface
	{
	public:
		static void start_discord_rpc(const char* applicationId)
		{
			if (initialized_)
				return;

			DiscordEventHandlers handlers;
			ZeroMemory(&handlers, sizeof(handlers));
			handlers.ready = ready;
			handlers.errored = errored;
			handlers.disconnected = errored;
			handlers.joinGame = nullptr;
			handlers.spectateGame = nullptr;
			handlers.joinRequest = nullptr;

			Discord_Initialize(applicationId, &handlers, 1, nullptr);
			scheduler::loop(update_discord, scheduler::pipeline::async, 10s);

			initialized_ = true;
		}

		void lua_start() override
		{
			const lua::luaL_Reg HotReloadLibrary[] =
			{
				{"Enable", enable},
				{"SetRoundsPlayed", set_rounds_played},
				{"SetPlayerScore", set_playerscore},
				{"SetEnemyScore", set_enemyscore},
				{nullptr, nullptr},
			};
			hks::hksI_openlib(game::UI_luaVM, "DiscordRPC", HotReloadLibrary, 0, 1);
		}

		void start_hooks() override
		{
			isIngame = true;
			std::string raw_lua = 
				"LUI.roots.UIRoot0:subscribeToGlobalModel(0, 'GameScore', 'roundsPlayed', function(model) "
					"local roundsPlayed = Engine.GetModelValue(model); "
					"if roundsPlayed then "
						"DiscordRPC.SetRoundsPlayed(roundsPlayed - 1); "
					"end; "
				"end); "
				"LUI.roots.UIRoot0:subscribeToGlobalModel(0, 'GameScore', 'playerScore', function(model) "
					"local playerScore = Engine.GetModelValue(model); "
					"if playerScore and not Engine.IsVisibilityBitSet( 0, Enum.UIVisibilityBit.BIT_IN_KILLCAM ) then "
						"DiscordRPC.SetPlayerScore(playerScore); "
					"end; "
				"end); "
				"LUI.roots.UIRoot0:subscribeToGlobalModel(0, 'GameScore', 'enemyScore', function(model) "
					"local enemyScore = Engine.GetModelValue(model); "
					"if enemyScore and not Engine.IsVisibilityBitSet( 0, Enum.UIVisibilityBit.BIT_IN_KILLCAM ) then "
						"DiscordRPC.SetEnemyScore(enemyScore); "
					"end; "
				"end); ";
			hks::execute_raw_lua(raw_lua, "DiscordScoreModels");
		}

		void destroy_hooks() override
		{
			isIngame = false;
		}

	private:
		static inline bool initialized_ = false;

		static void ready(const DiscordUser*)
		{
			ZeroMemory(&discord_presence, sizeof(discord_presence));

			discord_presence.instance = 1;

			Discord_UpdatePresence(&discord_presence);
		}

		static void errored(const int error_code, const char* message)
		{
			printf("Discord: (%i) %s", error_code, message);
		}
	};


	int enable(lua::lua_State* s)
	{
		auto applicationId = lua::lua_tostring(s, 1);
		discord::component::start_discord_rpc(applicationId);
		return 1;
	}
}

REGISTER_COMPONENT(discord::component)