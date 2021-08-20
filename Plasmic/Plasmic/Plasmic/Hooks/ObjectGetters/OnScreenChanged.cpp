#include "OnScreenChanged.h"

//48 89 5C 24 18 48 89 6C 24 20 56 41 54 41 56 48 83 EC 20



typedef float(*_OnScreenChanged)(Text* screenName, uintptr_t idk, uintptr_t idc);
_OnScreenChanged oScreenChanged;


float HookOnScreenChanged(Text* screenName, uintptr_t idk, uintptr_t idc) {
	memset(game::currentScreen, 0, 128);
	Text* screenText = screenName;

	size_t lenght = screenName->textLength;
	if (lenght > 16) {
		screenName = *(Text**)screenName;
		lenght = screenName->textLength;
		if (lenght > 127) 
			lenght = 127;
	}
	const char* debug = screenName->getText();
	memcpy(game::currentScreen, screenName->getText(), lenght);

	return oScreenChanged(screenText, idk, idc);
}




void OnScreenChangedHook::init() {
	name = "OnScreenChangedHook";
	uintptr_t hookAddress = mem::FindSignature("48 89 5C 24 18 48 89 6C 24 20 56 41 54 41 ?? 48 83 EC 20 48 8B 41 08");
	if (hookAddress == NULL) {
		Logf("Unable to hook!\n Sig of %s is broken", name);
		return;
	}
	Logf("%s: %p", name, (void*)hookAddress);

	isInit = true;
	memcpy(game::currentScreen, "hud_screen", 11);
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)HookOnScreenChanged, (LPVOID*)&oScreenChanged);
}
