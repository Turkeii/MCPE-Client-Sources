#include "GameModeHook.h"
#include "../VisualModules/ReachDisplay.h"
#include "../VisualModules/ComboCounter.h"

volatile bool isOtherGamemodeHookInit = false;
extern void updateSelection(BlockPos* pos, bool isPos1);


typedef void(__fastcall* _gamemodeTick)(Gamemode* gm);
_gamemodeTick ogamemodeTick;
_gamemodeTick osurvivalTick;



typedef bool(__fastcall* _GamemodeUseItemOn)(Gamemode* gm, ItemStack* item, BlockPos* pos, uint8_t idk, Vec3* precisePos, Block* interactedBlock);
_GamemodeUseItemOn ogamemodeUseOn;
typedef bool(__fastcall* _GamemodeDestroyBlock)(Gamemode* gm, BlockPos* pos, uint8_t idk);
_GamemodeDestroyBlock ogamemodeDestroyBlock;



volatile bool GMH_WaitForRightclick = false;
bool HookGamemodeUseItemOn(Gamemode* gm, ItemStack* item, BlockPos* pos, uint8_t idk, Vec3* precisePos, Block* interactedBlock) {
	if (gm == nullptr || gm->Player == nullptr || game::localPlayer == nullptr)
		return ogamemodeUseOn(gm, item, pos, idk, precisePos, interactedBlock);
	if (game::localPlayer != gm->Player)
		return ogamemodeUseOn(gm, item, pos, idk, precisePos, interactedBlock);


	if (item && item->item && (*item->item)) 
		if ((*item->item)->id == 311) 
			if (GMH_WaitForRightclick) {
				updateSelection(pos, false);
				game::sendClientChat("§§dSecond position set to %d %d %d", pos->x, pos->y, pos->z);
				GMH_WaitForRightclick = false;
				return false;
			}
		

	return ogamemodeUseOn(gm, item, pos, idk, precisePos, interactedBlock);
}
uint8_t HookGamemodeDestroyBlock(Gamemode* gm, BlockPos* pos, uint8_t idk) {
	if (gm == nullptr || gm->Player == nullptr || game::localPlayer == nullptr)
		return ogamemodeDestroyBlock(gm, pos, idk);
	if (game::localPlayer != gm->Player)
		return ogamemodeDestroyBlock(gm, pos, idk);

	if (gm->Player->selectedItemID == 311) {
		updateSelection(pos, true);
		game::sendClientChat("§§dFirst position set to %d %d %d", pos->x, pos->y, pos->z);
		return 0;
	}
	
	return ogamemodeDestroyBlock(gm, pos, idk);
}


typedef bool(__fastcall* _GamemodeAttack)(Gamemode* gm, Actor* actor);
_GamemodeAttack ogamemodeAttack;
_GamemodeAttack ogamemodeSurvivalAttack;



extern ReachDisplay* rdp;
ComboCounter* combocounter;
bool HookGamemodeAttack(Gamemode* gm, Actor* actor) {
	if (gm == nullptr)
		return ogamemodeAttack(gm, actor);
	if (gm->Player != game::localPlayer)
		return ogamemodeAttack(gm, actor);


	getvisualmodbyname(rdp, "Reach Display", ReachDisplay)
		rdp->CalcHitValue(); //when we hit we want to calc the last hit value with the info we got in packet 33

	getvisualmodbyname(combocounter, "Combo Counter", ComboCounter)
			combocounter->onAttack(actor);

	return ogamemodeAttack(gm, actor);
}
bool HookGamemodeSurvivalAttack(Gamemode* gm, Actor* actor) {
	if (gm == nullptr)
		return ogamemodeSurvivalAttack(gm, actor);
	if (gm->Player != game::localPlayer)
		return ogamemodeSurvivalAttack(gm, actor);


	getvisualmodbyname(rdp, "Reach Display", ReachDisplay)
		rdp->CalcHitValue(); //when we hit we want to calc the last hit value with the info we got in packet 33

	getvisualmodbyname(combocounter, "Combo Counter", ComboCounter)
			combocounter->onAttack(actor);

	return ogamemodeSurvivalAttack(gm, actor);
}



bool survivalAttackHooked = false;
bool gmAttackHooked = false;
void InitOtherHooks(Gamemode* gm, bool isSurvival) {
	uintptr_t** gmvtable = mem::getVtable(gm);
	

	if (isSurvival && !survivalAttackHooked) {
		MH_CreateHook((LPVOID)gmvtable[14], (LPVOID)HookGamemodeSurvivalAttack, (LPVOID*)&ogamemodeSurvivalAttack);
		MH_EnableHook((LPVOID)gmvtable[14]);
		survivalAttackHooked = true;
	}


	if (!isSurvival && !gmAttackHooked) {
		MH_CreateHook((LPVOID)gmvtable[14], (LPVOID)HookGamemodeAttack, (LPVOID*)&ogamemodeAttack);
		MH_EnableHook((LPVOID)gmvtable[14]);
		gmAttackHooked = true;
	}

	if (isOtherGamemodeHookInit)
		return;
#ifndef NDEBUG
	MH_CreateHook((LPVOID)gmvtable[12], (LPVOID)HookGamemodeUseItemOn, (LPVOID*)&ogamemodeUseOn);
	MH_EnableHook((LPVOID)gmvtable[12]);
	MH_CreateHook((LPVOID)gmvtable[2], (LPVOID)HookGamemodeDestroyBlock, (LPVOID*)&ogamemodeDestroyBlock);
	MH_EnableHook((LPVOID)gmvtable[2]);
#endif

	isOtherGamemodeHookInit = true;
}

extern void UpdateRealTime();
void GamemodeTickHookf(Gamemode* gm) {
	if (gm == nullptr || gm->Player == nullptr || game::localPlayer == nullptr)
		return;
	InitOtherHooks(gm, false);
	UpdateRealTime();


		if (game::localPlayer == gm->Player) {
			game::gm = gm;
			
			for (uint16_t i = 0; i < ModuleManager::moduleList.size(); i++)
				if (ModuleManager::moduleList[i] != nullptr)
					if (ModuleManager::moduleList[i]->isEnabled())
						ModuleManager::moduleList[i]->onTick(gm);
			for (uint16_t i = 0; i < ModuleManager::visualModuleList.size(); i++)
				if (ModuleManager::visualModuleList[i] != nullptr)
					if (ModuleManager::visualModuleList[i]->isEnabled())
						ModuleManager::visualModuleList[i]->onTick(gm);
		}	
	
	ogamemodeTick(gm);
}

void SurvivalModeTickHookf(Gamemode* gm) {
	if (gm == nullptr || gm->Player == nullptr || game::localPlayer == nullptr)
		return;
	InitOtherHooks(gm, true);
	UpdateRealTime();


		if (game::localPlayer == gm->Player) {
			game::gm = gm;

			for (uint16_t i = 0; i < ModuleManager::moduleList.size(); i++)
				if (ModuleManager::moduleList[i] != nullptr)
					if (ModuleManager::moduleList[i]->isEnabled())
						ModuleManager::moduleList[i]->onTick(gm);
			for (uint16_t i = 0; i < ModuleManager::visualModuleList.size(); i++)
				if (ModuleManager::visualModuleList[i] != nullptr)
					if (ModuleManager::visualModuleList[i]->isEnabled())
						ModuleManager::visualModuleList[i]->onTick(gm);
		}
	
	osurvivalTick(gm);
}


void GamemodeTickHook::init() {
	name = "GamemodeTickHook";

	uintptr_t hookAddress = mem::FindSignature("8B 41 20 89 41 1C C3");
	if (hookAddress == NULL) {
		Logf("Unable to hook!\n Sig of %s is broken", name);
		return;
	}
	Logf("%s: %p", name, (void*)hookAddress);

	isInit = true;

	MH_CreateHook((LPVOID)hookAddress, (LPVOID)GamemodeTickHookf, (LPVOID*)&ogamemodeTick);
}



void SurvivalModeTickHook::init() {
	name = "SurvivalModeTickHook";

#ifndef _1_16_40
	uintptr_t hookAddress = mem::FindSignature("48 89 5C 24 ?? 48 89 74 24 ?? 55 57 41 56 48 8D 6C 24 B9 48 81 ?? ?? ?? ?? ?? 48 8B 05 0F F3 8A 01 48 33 C4 48 89 45 37");
#else
	uintptr_t hookAddress = mem::FindSignature("48 8B C4 55 57 41 56 48 8D 68 A1 48 81 EC ?? ?? ?? ?? 48 C7 45 F7 ?? ?? ?? ?? 48 89 58 10 48 89 70 18 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 45 3F 48 8B F9");
#endif
	if (hookAddress == NULL) {
		Logf("Unable to hook!\n Sig of %s is broken", name);
		return;
	}
	Logf("%s: %p", name, (void*)hookAddress);

	isInit = true;

	MH_CreateHook((LPVOID)hookAddress, (LPVOID)SurvivalModeTickHookf, (LPVOID*)&osurvivalTick);
}


