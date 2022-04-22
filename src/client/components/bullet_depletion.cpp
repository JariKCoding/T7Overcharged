#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include "game/game.hpp"
#include "utils/string.hpp"

namespace bullet_depletion
{
	utils::hook::detour cg_updateviewmodeldynamicbones_hook;
	utils::hook::detour CG_PlayRumbleOnEntity_hook;

	static bool bullet_depletion_enabled[2][2] = {{true, true}, {true, true}};
	static bool bullet_depletion_reload_mode_enabled[2][2] = { {false, false}, {false, false} };

	game::ScrString_t disable_bullet_depletion_right_str = game::GScr_AllocString("disable bullet depletion right");
	game::ScrString_t enable_bullet_depletion_right_str = game::GScr_AllocString("enable bullet depletion right");
	game::ScrString_t disable_reload_bullet_depletion_right_str = game::GScr_AllocString("disable reload mode bullet depletion right");
	game::ScrString_t enable_reload_bullet_depletion_right_str = game::GScr_AllocString("enable reload mode bullet depletion right");
	game::ScrString_t disable_bullet_depletion_left_str = game::GScr_AllocString("disable bullet depletion left");
	game::ScrString_t enable_bullet_depletion_left_str = game::GScr_AllocString("enable bullet depletion left");
	game::ScrString_t disable_reload_bullet_depletion_left_str = game::GScr_AllocString("disable reload mode bullet depletion left");
	game::ScrString_t enable_reload_bullet_depletion_left_str = game::GScr_AllocString("enable reload mode bullet depletion left");

	enum handType : BYTE
	{
		HAND_RIGHT = 0x0,
		HAND_LEFT = 0x1
	};

	void handle_bullet_depletion(game::LocalClientNum_t localClientNum, void* ps, void* obj, void* weapon, handType handType)
	{
		int clipSize = game::BG_GetClipSize(weapon);
		int ammoInClip = game::BG_GetAmmoInClip(ps, weapon);
		if (bullet_depletion_reload_mode_enabled[localClientNum][handType])
			ammoInClip += game::BG_GetTotalAmmoReserve(ps, weapon);

		int i = 0;
		while (i < clipSize)
		{
			game::ScrString_t tname = game::GScr_AllocString(utils::string::va("tag_bullet_deplete_sqtl_%02d_animate%s", i, handType == handType::HAND_LEFT ? "_le" : ""));
			game::BoneIndex bone;
			if (game::DObjGetBoneIndex(obj, tname, &bone, -1))
			{
				if (ammoInClip <= i)
				{
					game::vec3_t newOrigin = { 0, 0, -100000 };
					game::vec3_t angles = { 0, 0, 0 };
					int partBits[12];
					game::PLmemset(partBits, 255LL, 48LL);
					game::DObjSetLocalTag(obj, partBits, bone, &newOrigin, &angles);
				}
			}
			else
			{
				// No bone for depletion
				break;
			}
			i++;
		}

		i = 0;
		while (i < clipSize)
		{
			game::ScrString_t tname = game::GScr_AllocString(utils::string::va("tag_bullet_deplete_swap_%02d_animate%s", i, handType == handType::HAND_LEFT ? "_le" : ""));
			game::BoneIndex bone;
			if (game::DObjGetBoneIndex(obj, tname, &bone, -1))
			{
				if (ammoInClip != i)
				{
					game::vec3_t newOrigin = { 0, 0, -100000 };
					game::vec3_t angles = { 0, 0, 0 };
					int partBits[12];
					game::PLmemset(partBits, 255LL, 48LL);
					game::DObjSetLocalTag(obj, partBits, bone, &newOrigin, &angles);
				}
			}
			else
			{
				// No bone for depletion
				break;
			}
			i++;
		}
	}

	void cg_updateviewmodeldynamicbones_internal(game::cg_t* cgameGlob, void* ps, void* obj, void* weapon, void* cent)
	{
		cg_updateviewmodeldynamicbones_hook.invoke<void>(cgameGlob, ps, obj, weapon, cent);

		if (!cgameGlob)
			return;

		if (!obj || !game::Sys_IsMainThread())
			return;

		auto localClientNum = game::DObjGetLocalClientIndex(obj);

		if (bullet_depletion_enabled[localClientNum][handType::HAND_RIGHT])
		{
			handle_bullet_depletion(localClientNum, ps, obj, weapon, handType::HAND_RIGHT);
		}
		if (bullet_depletion_enabled[localClientNum][handType::HAND_LEFT] && game::BG_IsDualWield(weapon))
		{
			auto leftWeapon = game::BG_GetDualWieldWeapon(weapon);
			handle_bullet_depletion(localClientNum, ps, obj, leftWeapon, handType::HAND_LEFT);
		}
	}

	void CG_PlayRumbleOnEntity_internal(game::LocalClientNum_t localClientNum, game::ScrString_t rumbleName, int entityNum)
	{
		if (rumbleName != enable_bullet_depletion_right_str && rumbleName != enable_bullet_depletion_left_str && rumbleName != disable_bullet_depletion_right_str && rumbleName != disable_bullet_depletion_left_str &&
			rumbleName != enable_reload_bullet_depletion_right_str && rumbleName != enable_reload_bullet_depletion_left_str && rumbleName != disable_reload_bullet_depletion_right_str && rumbleName != disable_reload_bullet_depletion_left_str)
			return CG_PlayRumbleOnEntity_hook.invoke<void>(localClientNum, rumbleName, entityNum);

		auto isLeftHand = rumbleName != enable_bullet_depletion_right_str && rumbleName != disable_bullet_depletion_right_str &&
			rumbleName != enable_reload_bullet_depletion_right_str && rumbleName != disable_reload_bullet_depletion_right_str;

		if (rumbleName == enable_bullet_depletion_right_str || rumbleName == enable_bullet_depletion_left_str)
		{
			bullet_depletion_enabled[localClientNum][isLeftHand] = true;
		}
		else if (rumbleName == disable_bullet_depletion_right_str || rumbleName == disable_bullet_depletion_left_str)
		{
			bullet_depletion_enabled[localClientNum][isLeftHand] = false;
		}
		else if (rumbleName == enable_reload_bullet_depletion_right_str || rumbleName == enable_reload_bullet_depletion_left_str)
		{
			bullet_depletion_reload_mode_enabled[localClientNum][isLeftHand] = true;
		}
		else if (rumbleName == disable_reload_bullet_depletion_right_str || rumbleName == disable_reload_bullet_depletion_left_str)
		{
			bullet_depletion_reload_mode_enabled[localClientNum][isLeftHand] = false;
		}
	}

	class component final : public component_interface
	{
	public:
		void start_hooks() override
		{
			cg_updateviewmodeldynamicbones_hook.create(0x126EE90, &cg_updateviewmodeldynamicbones_internal);
			CG_PlayRumbleOnEntity_hook.create(0x9E6C90, &CG_PlayRumbleOnEntity_internal);
		}

		void destroy_hooks() override
		{
			cg_updateviewmodeldynamicbones_hook.clear();
			CG_PlayRumbleOnEntity_hook.clear();
		}
	};
}

REGISTER_COMPONENT(bullet_depletion::component)