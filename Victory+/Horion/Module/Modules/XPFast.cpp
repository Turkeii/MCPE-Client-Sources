#include "XPFast.h"
#include "Module.h"

XPFast::XPFast() : IModule(0x0, Category::VISUAL, "Motion!?") {
//registerIntSetting("Delay", &this->charge, this->charge, 1, 32);
}

XPFast::~XPFast() {
}

// WHAT I LEARNED: some functions are blocked because they are declared as private (i.e. releaseUsingItem())
// To get around this, simply declare it as private...bruh this simple thing really took 3 hours XD :(

const char* XPFast::getModuleName() {
	return ("NoEatMotion");
}

void XPFast::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	auto itemInHand = player->getCarriedItem();

	if (!(player->getSelectedItemId() == 300)) {
		i++;
		//clientMessageF("Bow use: %f", i);

    //g_Data.getCGameMode()->releaseUsingItem();
    player->completeUsingItem();
	}
}