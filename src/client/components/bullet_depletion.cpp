#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include "game/game.hpp"
#include "utils/string.hpp"

namespace bullet_depletion
{
	utils::hook::detour cg_updateviewmodeldynamicbones_hook;
	utils::hook::detour cg_viewmodelprocessnote_hook;
	utils::hook::detour xanimprocessclientnotify_hook;

	static bool bullet_depletion_enabled[2][2] = {{true, true}, {true, true}};
	static bool bullet_depletion_reload_mode_enabled[2][2] = { {false, false}, {false, false} };

	game::ScrString_t disable_bullet_depletion_str = game::GScr_AllocString("disable bullet depletion");
	game::ScrString_t enable_bullet_depletion_str = game::GScr_AllocString("enable bullet depletion");
	game::ScrString_t disable_reload_bullet_depletion_str = game::GScr_AllocString("disable mode reload bullet depletion");
	game::ScrString_t enable_reload_bullet_depletion_str = game::GScr_AllocString("enable mode reload bullet depletion");
	game::ScrString_t right_str = game::GScr_AllocString("right");
	game::ScrString_t left_str = game::GScr_AllocString("left");

	void cg_updateviewmodeldynamicbones_internal(game::cg_t* cgameGlob, void* ps, void* obj, void* weapon, void* cent)
	{
		//game::minlog.WriteLine("pre invoke");
		cg_updateviewmodeldynamicbones_hook.invoke<void>(cgameGlob, ps, obj, weapon, cent);
		//game::minlog.WriteLine("post invoke");

		if (!cgameGlob)
			return;
		//game::minlog.WriteLine("post cgameGlob check");

		//if (game::CG_InAnimatedCamera(cgameGlob->localClientNum))
		//	return;
		//game::minlog.WriteLine("post inanimated camera");

		if (!obj || !game::Sys_IsMainThread())
		{
			game::minlog.WriteLine("Freezefix?");
			return;
		}
		//game::minlog.WriteLine("post obj thread");

		game::LocalClientNum_t localClientNum = game::DObjGetLocalClientIndex(obj);
		//game::minlog.WriteLine(utils::string::va("post localClientNum: %d", localClientNum));
		auto isLeftHand = game::BG_IsLeftHandWeapon(weapon);
		//game::minlog.WriteLine(utils::string::va("post isLeftHand", isLeftHand));
		if (!bullet_depletion_enabled[localClientNum][isLeftHand])
			return;

		int clipSize = game::BG_GetClipSize(weapon);
		//game::minlog.WriteLine(utils::string::va("clipSize: %d", clipSize));
		if (clipSize <= 0)
			return;


		int i = 0;
		game::BoneIndex bone;
		while (i < clipSize)
		{
			game::ScrString_t tname = game::GScr_AllocString(utils::string::va("tag_bullet_deplete_sqtl_%02d_animate%s", i, isLeftHand ? "_le" : ""));
			if (game::DObjGetBoneIndex(obj, tname, &bone, -1))
			{
				int maxAmount = game::BG_GetAmmoInClip(ps, weapon);
				if (bullet_depletion_reload_mode_enabled[localClientNum][isLeftHand])
					maxAmount += game::BG_GetTotalAmmoReserve(ps, weapon);
				if (maxAmount <= i)
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
			game::ScrString_t tname = game::GScr_AllocString(utils::string::va("tag_bullet_deplete_swap_%02d_animate%s", i, isLeftHand ? "_le" : ""));
			if (game::DObjGetBoneIndex(obj, tname, &bone, -1))
			{
				int maxAmount = game::BG_GetAmmoInClip(ps, weapon);
				if (bullet_depletion_reload_mode_enabled[localClientNum][isLeftHand])
					maxAmount += game::BG_GetTotalAmmoReserve(ps, weapon);
				if (maxAmount > clipSize)
					maxAmount = clipSize;
				if (maxAmount != i)
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

	bool cg_viewmodelprocessnote_only_when_visible_internal(game::XAnimNotifyInfo* notifyInfo)
	{
		game::minlog.WriteLine("pre cg_viewmodelprocessnote invoke");
		auto result = cg_viewmodelprocessnote_hook.invoke<bool>(notifyInfo);
		
		game::minlog.WriteLine("post cg_viewmodelprocessnoteinvoke");

		return result;
		//if (result == false)
		//	return false;

		/*game::minlog.WriteLine("post cg_viewmodelprocessnoteinvoke true");
		if (!obj || !game::Sys_IsMainThread() || !notifyInfo)
			return false;
		game::minlog.WriteLine("post cg_viewmodelprocessnote obj thread");

		if (notifyInfo->type == enable_bullet_depletion_str)
		{
			game::minlog.WriteLine("enable_bullet_depletion_str");
			bullet_depletion_enabled[localClientNum][notifyInfo->param1 == left_str] = true;
		}
		else if (notifyInfo->type == disable_bullet_depletion_str)
		{
			game::minlog.WriteLine("disable_bullet_depletion_str");
			bullet_depletion_enabled[localClientNum][notifyInfo->param1 == left_str] = false;
		}
		else if (notifyInfo->type == enable_reload_bullet_depletion_str)
		{
			game::minlog.WriteLine("enable_reload_bullet_depletion_str");
			bullet_depletion_reload_mode_enabled[localClientNum][notifyInfo->param1 == left_str] = true;
		}
		else if (notifyInfo->type == disable_reload_bullet_depletion_str)
		{
			game::minlog.WriteLine("disable_reload_bullet_depletion_str");
			bullet_depletion_reload_mode_enabled[localClientNum][notifyInfo->param1 == left_str] = false;
		}
		return true;*/
	}

	void xanimprocessclientnotify_internal(__int64 obj, __int64 info, __int64 dtime, char forceProcess, char skipNonImportantNotifies)
	{
		float v5; // xmm1_4
		float v6; // xmm4_4
		unsigned __int16 notifyFilter; // r11
		bool v11; // zf
		__int64 v12; // rdx
		__int64 v13; // r9
		__int64 v14; // rax
		__int64 v15; // rdx
		float v16; // xmm0_4
		float v17; // xmm5_4
		__int64 v18; // r14
		unsigned __int16 v19; // si
		float v20; // xmm2_4
		float* v21; // rbx
		float v22; // xmm0_4
		int v23; // er15
		int v24; // er15
		float* i; // rbx
		int v26; // er15
		int v27; // er15

		/*v5 = *(float*)(info + 20);
		v6 = 1.0;
		notifyFilter = *(WORD*)(info + 60);
		if (v5 == 1.0)
		{
			if (!*(DWORD*)(info + 48))
			{
				v11 = (*(BYTE*)(info + 8) & 3) == 0;
				v12 = (unsigned int)game::GScr_AllocString("end");
				v13 = notifyFilter;
				if (!v11)
					v12 = (unsigned int)game::GScr_AllocString("loop_end");
			LABEL_5:
				game::CG_ProcessClientEndNote(obj, v12, info, v13);
				return;
			}
			v14 = *(UINT64*)(info + 8);
			if (!v14 || (v15 = (unsigned int)game::GScr_AllocString("loop_end"), !*(BYTE*)(v14 + 36)))
				v15 = (unsigned int)game::GScr_AllocString("end");
			game::CG_ProcessClientEndNote(obj, v15, info, notifyFilter);
		}*/
	}

	void cg_processclientnote_internal(void* obj, const game::XAnimNotifyInfo* notifyInfo, void* info, const unsigned int notifyFilter, bool shutdown, bool skipNonImportantNotifies)
	{
		game::minlog.WriteLine("cg_processclientnote_internal");
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
		/*void start_hooks() override
		{
			cg_updateviewmodeldynamicbones_hook.create(0x126EE90, &cg_updateviewmodeldynamicbones_internal);
			//cg_viewmodelprocessnote_hook.create(0x24E080, &cg_viewmodelprocessnote_only_when_visible_internal);
			//cg_viewmodelprocessnote_hook.create(0x2343710, &xanimprocessclientnotify_internal);
			//utils::hook::call(OFFSET(0x2343866), &cg_processclientnote_internal);
		}

		void destroy_hooks() override
		{
			cg_updateviewmodeldynamicbones_hook.clear();
			cg_viewmodelprocessnote_hook.clear();
		}*/
	};
}

REGISTER_COMPONENT(bullet_depletion::component)