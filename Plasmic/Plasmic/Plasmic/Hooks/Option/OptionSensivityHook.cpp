#include "OptionSensivityHook.h"
#include "../../Modules/ZoomModule.h"


ZoomModule* zoomMod = nullptr;

float getSensivity(float sensivity) {

	if (zoomMod == nullptr)
		zoomMod = (ZoomModule*)ModuleManager::getModuleByName("Zoom");
	else
		if (zoomMod->isEnabled()) {
			return sensivity / (zoomMod->zoomValue * (sensivity/ zoomMod->SensivityReduced));
		}

		
		

	//Get the normal senisvity value
	
	return sensivity; //returning the original function will crash.
}


void OptionSensivityHook::init() {
	name = "OptionSensivityHook";
#ifndef _1_16_40
	uintptr_t hookAddress = mem::FindSignature("33 C0 48 85 C0 49 0F 44 C1 F3 0F 10 40 14 C3");
	hookAddress += 14;
#else
	uintptr_t hookAddress = mem::FindSignature("74 11 44 39 48 10 74 05 48 8B 00 EB DE F3 0F 10 40 14 C3");
	hookAddress += 18;
	DWORD oldp;
	VirtualProtect((LPVOID)(hookAddress - 14), 20, PAGE_EXECUTE_READWRITE, &oldp);
	memset((void*)(hookAddress+1), 0, 7);
	DWORD flemmewarning;
	VirtualProtect((LPVOID)(hookAddress - 14), 20, oldp, &flemmewarning);// will still miss some bytes but I never saw it used, ik this is horrible

	//hookAddress += 13;
#endif

	if (hookAddress == NULL) {
		Logf("Unable to hook!\n Sig of %s is broken", name);
		return;
	}
	//Logf("%s: %p", name, (void*)hookAddress);

	isInit = true;

	

	MH_CreateHook((LPVOID)hookAddress, (LPVOID)getSensivity, 0);
	MH_EnableHook((LPVOID)hookAddress);
}



