#include "FreeLook.h"
#include "../.../../../Utils/Logger.h"


class FreeLook* freelookmod;


typedef void(*_updatePlayerHeadRot)(LocalPlayer* player, uintptr_t game);
_updatePlayerHeadRot oupdatePlayerHeadRot1;
_updatePlayerHeadRot oupdatePlayerHeadRot2;



//for this one idk if its a vec2* tho
void PlayercameraUpdateHeadRotationHook1(LocalPlayer* player, uintptr_t game) {

	if (freelookmod != nullptr && freelookmod->isEnabled()) {
		float oldRot = game::localPlayer->cameraRotation;
		oupdatePlayerHeadRot1(player, game);
		game::localPlayer->cameraRotation = oldRot;
		return;
	}

	return oupdatePlayerHeadRot1(player, game);
}



void PlayercameraUpdateHeadRotationHook2(LocalPlayer* player, uintptr_t game) {
	if (freelookmod == nullptr)
		return oupdatePlayerHeadRot2(player, game);


	if (freelookmod->isEnabled()) {
		float oldRot = game::localPlayer->cameraRotation;
		oupdatePlayerHeadRot2(player, game);
		game::localPlayer->cameraRotation = oldRot;
		return;
	}

	return oupdatePlayerHeadRot2(player, game);
}


void PlayerCameraUpdateHeadRotationHook1::init() {
	name = "PlayerCameraUpdateHeadRotationHook1";

	uintptr_t hookAddress = mem::FindSignature("48 89 5C 24 18 57 48 83 EC 50 48 8B D9 0F 29 74 24 40 48 8B 89 ?? ?? ?? ?? 48 8B FA 0F 29 7C 24 30 44 0F 29 44 24 20");
	//Logf("Freelook1: %p", (void*)hook1addr);

	if (hookAddress == NULL) {
		Logf("Unable to hook!\n Sig of %s is broken", name);
		return;
	}
	//Logf("%s: %p", name, (void*)hookAddress);

	isInit = true;

	MH_CreateHook((LPVOID)hookAddress, (LPVOID)PlayercameraUpdateHeadRotationHook1, (LPVOID*)&oupdatePlayerHeadRot1);
	MH_EnableHook((LPVOID)hookAddress);
}
//btw this is UpdateFromCam
void PlayerCameraUpdateHeadRotationHook2::init() {
	name = "PlayerCameraUpdateHeadRotationHook2";

#ifndef _1_16_40
	uintptr_t hookAddress = mem::FindSignature("48 89 5C 24 10 57 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 84 24 ?? ?? ?? ?? 80 ?? ?? ?? ?? ?? 00 48 8B FA 48 8B D9");
#else
	uintptr_t hookAddress = mem::FindSignature("48 89 5C 24 10 57 48 83 EC 40 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 44 24 30 80 BA ?? ?? ?? ?? 00 48 8B FA 48 8B D9");
#endif

	//Logf("Freelook2: %p", (void*)hookAddress);
	if (hookAddress == NULL) {
		Logf("Unable to hook!\n Sig of %s is broken", name);
		return;
	}
	//Logf("%s: %p", name, (void*)hookAddress);

	isInit = true;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)PlayercameraUpdateHeadRotationHook2, (LPVOID*)&oupdatePlayerHeadRot2);
	MH_EnableHook((LPVOID)hookAddress);
}


uintptr_t addr = 0;
static int8_t prevState = 0; //for the camera
static bool canEnable = false;
FreeLook::FreeLook() : Module("Freelook", 'N', mltext("You can look whithout changing the way you go.\nUse the ALT key at your own risks.", "Vous pouvez regarder autour de vous sans changer ou vous allez.\nUtilisez la touche ALT a vous risques et perils.")){
	this->isToggle = false;

	addBoolSetting("Toggle", "isToggle", isToggle, &isToggle);
	addBoolSetting(mltext("No perspective change", "Pas de changement de perspective"), "NoPerspective", noPerspectiveChange, &noPerspectiveChange);

	freelookmod = this;
}






void FreeLook::onEnable() {
	if (!game::localPlayer) {
		Disable();
		return;
	}

	if (addr == 0) {
		addr = mem::FindSignature("89 5C 24 08 57 48 83 EC 20 8B 42 04 48 8B F9 48 81");
		if (addr != NULL)
			canEnable = true;
		else {
			addr = 1;
			Logf("Could not find the freelook sig!");
		}
		addr--;
	}

	if (canEnable) {
		BYTE ret = 0xC3;
		mem::writeBytes(addr, &ret, 1);

		//perspective
		if (cameraPerpective != nullptr && !noPerspectiveChange) {
			prevState = *cameraPerpective;
			*cameraPerpective = 1;
		}
	}
}
void FreeLook::onDisable() {

	if (canEnable) {
		BYTE normal = 0x48;
		mem::writeBytes(addr, &normal, 1);

		//perspective
		if (cameraPerpective != nullptr && !noPerspectiveChange) 
			*cameraPerpective = prevState;
		}
		
}
