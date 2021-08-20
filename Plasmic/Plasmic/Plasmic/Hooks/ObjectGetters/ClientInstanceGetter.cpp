#include "ClientInstanceGetter.h"



typedef void(*_ClientInstanceGetter)(__int64 someGaming, ClientInstance* instance);
_ClientInstanceGetter oClientInstanceGetter;

bool isClientInstanceAddressLoggerInTheLogs = false;
void HookClientInstanceGetter(__int64 someGaming, ClientInstance* instance) {
	game::clientinstance = instance;
	game::localPlayer = instance->localPlayer;
	game::minecraftGame = instance->minecraftGame;

	return oClientInstanceGetter(someGaming, instance);
}



void ClientInstanceGetterHook::init() {
	if (isInit)
		return;

	name = "Getter - ClientInstance";

	uintptr_t hookAddress = mem::FindSignature("48 83 EC 28 48 8B 02 48 8B CA FF 90 ?? ?? ?? ?? C6 80");
	if (hookAddress == NULL) {
		Logf("Unable to hook!\n Sig of %s is broken", name);
		return;
	}
	Logf("%s: %p", name, (void*)hookAddress);

	isInit = true;

	MH_CreateHook((LPVOID)hookAddress, (LPVOID)HookClientInstanceGetter, (LPVOID*)&oClientInstanceGetter);
	MH_EnableHook((LPVOID)hookAddress);

}

