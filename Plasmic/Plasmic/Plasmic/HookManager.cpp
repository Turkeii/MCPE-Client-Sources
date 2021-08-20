#include "Manager.h"
#include <MinHook.h>
#include <thread>

std::vector<Hook*> HookManager::hooks;

void HookManager::DisableAllHooks() {
	MH_DisableHook(MH_ALL_HOOKS);
}
void HookManager::EnableAllHooks() {
	MH_EnableHook(MH_ALL_HOOKS);
}

Hook* HookManager::GetHookByName(const char* NameOfTheHook) {
	for (uint16_t i = 0; i < hooks.size(); i++)
		if (hooks[i] != nullptr)
			if (hooks[i]->name == NameOfTheHook)
				return hooks[i];

	return nullptr;
}

void HookManager::DeInit() {
	MH_Uninitialize();

	for (uint16_t i = 0; i < hooks.size(); i++)
		if (hooks[i] != nullptr)
			delete hooks[i];

}

#include "Hooks/ChatHook.h"

#include "Hooks/InputHook.h"
#include "Hooks/RenderContextHook.h"
#include "Hooks/GameModeHook.h"
#include "Hooks/EnvironementHooks.h"
#include "Modules/FreeLook.h"
#include "Hooks/PacketHook.h"


//Option hooks
#include "Hooks/Option/OptionGammaHook.h"
#include "Hooks/Option/OptionSensivityHook.h"



// Object Getters
#include "Hooks/ObjectGetters/ClientInstanceGetter.h"
#include "Hooks/ObjectGetters/OnScreenChanged.h"

typedef void(*_HookInitFunc)(Hook* hk);
struct InitFuncArgs {
	uintptr_t address;
	Hook* hook;

};

volatile bool CanMoveOn = false;
InitFuncArgs CallInitarg;

void callInit() {
	InitFuncArgs ar;
	ar.address = CallInitarg.address;
	ar.hook = CallInitarg.hook;
	CanMoveOn = true;

	_HookInitFunc hif = (_HookInitFunc)ar.address;
	hif(ar.hook);
}


void HookManager::init() {

	HookManager::hooks.push_back(new ChatHook);
	HookManager::hooks[0]->init();

	// Object Getters
	HookManager::hooks.push_back(new ClientInstanceGetterHook);
	HookManager::hooks[1]->init();
	HookManager::hooks.push_back(new OnScreenChangedHook);



	//"Normal" hook
	HookManager::hooks.push_back(new KeyboardHook);
	HookManager::hooks.push_back(new MouseHook);
	HookManager::hooks.push_back(new RenderContextHook);
	HookManager::hooks.push_back(new GamemodeTickHook);
	HookManager::hooks.push_back(new SurvivalModeTickHook);
	HookManager::hooks.push_back(new TimeOfDayHook);
	HookManager::hooks.push_back(new OverworldGetFogColorHook);
	HookManager::hooks.push_back(new DimensionGetFogColorHook);
	HookManager::hooks.push_back(new PlayerCameraUpdateHeadRotationHook1);
	HookManager::hooks.push_back(new PlayerCameraUpdateHeadRotationHook2);
	HookManager::hooks.push_back(new SendToServerHook);


	//Option hooks
	HookManager::hooks.push_back(new OptionGammaHook);
	HookManager::hooks.push_back(new OptionSensivityHook);


	//Init func

	std::vector<std::thread> hookthreads;
	
	for (uint16_t i = 0; i < HookManager::hooks.size(); i++) {
		CanMoveOn = false;
		CallInitarg.address = (uintptr_t)((uintptr_t**)(*(uintptr_t*)HookManager::hooks[i]))[0];
		CallInitarg.hook = HookManager::hooks[i];
		hookthreads.push_back(std::thread(callInit));
			
		while (CanMoveOn == false);
	}
	for (uint16_t i = 0; i < hookthreads.size(); i++)
		if (hookthreads[i].joinable())
			hookthreads[i].join();

	//for (uint16_t i = 0; i < HookManager::hooks.size(); i++)
		//HookManager::hooks[i]->init();
	
	HookManager::EnableAllHooks();
}