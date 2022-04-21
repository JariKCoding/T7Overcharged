#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include "game/game.hpp"
#include "utils/string.hpp"

namespace bullet_depletion
{
	utils::hook::detour cg_updateviewmodeldynamicbones_hook;
	utils::hook::detour cg_processclientnote_hook;

	bool bullet_depletion_enabled[2] = { true, true };

	game::ScrString_t disable_bullet_depletion_str = game::GScr_AllocString("disable bullet depletion");
	game::ScrString_t enable_bullet_depletion_str = game::GScr_AllocString("enable bullet depletion");

	void cg_updateviewmodeldynamicbones_internal(void* cgameGlob, void* ps, void* obj, void* weapon, void* cent)
	{
		cg_updateviewmodeldynamicbones_hook.invoke<void>(cgameGlob, ps, obj, weapon, cent);

		game::LocalClientNum_t localClientNum = game::DObjGetLocalClientIndex(obj);
		if (!bullet_depletion_enabled[localClientNum])
			return;

		int ammoInClip = game::BG_GetAmmoInClip(ps, weapon);
		int ammoStock = game::BG_GetTotalAmmoReserve(ps, weapon);

		bool isLeftHandWeapon = game::BG_IsLeftHandWeapon(weapon);

		game::vec3_t newOrigin = { 0, 0, -1000 };
		game::vec3_t angles = { 0, 0, 0 };

		int i = 0;
		game::BoneIndex bone;
		while (i < ammoStock)
		{
			game::ScrString_t tname = game::GScr_AllocString(utils::string::va("tag_bullet_deplete_sqtl_%02d_animate%s", i, isLeftHandWeapon ? "_le" : ""));
			if (game::DObjGetBoneIndex(obj, tname, &bone, -1))
			{
				if (ammoInClip <= i)
				{
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
		while (i < ammoStock)
		{
			game::ScrString_t tname = game::GScr_AllocString(utils::string::va("tag_bullet_deplete_swap_%02d_animate%s", i, isLeftHandWeapon ? "_le" : ""));
			if (game::DObjGetBoneIndex(obj, tname, &bone, -1))
			{
				if (ammoInClip != i)
				{
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

	void cg_processclientnote_internal(void* obj, const game::XAnimNotifyInfo* notifyInfo, void* info, const unsigned int notifyFilter, bool shutdown, bool skipNonImportantNotifies)
	{
		cg_processclientnote_hook.invoke<void>(obj, notifyInfo, info, notifyFilter, shutdown, skipNonImportantNotifies);

		if (notifyInfo->type == enable_bullet_depletion_str)
		{
			game::LocalClientNum_t localClientNum = game::DObjGetLocalClientIndex(obj);
			bullet_depletion_enabled[localClientNum] = true;
		}
		else if (notifyInfo->type == disable_bullet_depletion_str)
		{
			game::LocalClientNum_t localClientNum = game::DObjGetLocalClientIndex(obj);
			bullet_depletion_enabled[localClientNum] = false;
		}
	}

	class component final : public component_interface
	{
	public:
		//void start_hooks() override
		//{
		//	cg_updateviewmodeldynamicbones_hook.create(0x126EE90, &cg_updateviewmodeldynamicbones_internal);
		//	cg_processclientnote_hook.create(0x255C70, &cg_processclientnote_internal);
		//}

		//void destroy_hooks() override
		//{
		//	cg_updateviewmodeldynamicbones_hook.clear();
		//	cg_processclientnote_hook.clear();
		//}
	};
}

REGISTER_COMPONENT(bullet_depletion::component)