#include "BowSpam.h"
#include "Module.h"

BowSpam::BowSpam() : IModule(0x0, Category::COMBAT, "Send so much arrows that even the Iron Dome can't get them all") {
	registerIntSetting("Delay", &this->charge, this->charge, 5, 20);
}

BowSpam::~BowSpam() {
}

// WHAT I LEARNED: some functions are blocked because they are declared as private (i.e. releaseUsingItem())
// To get around this, simply declare it as private...bruh this simple thing really took 3 hours XD :(

const char* BowSpam::getModuleName() {
	return ("BowSpam");
}

void BowSpam::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	auto itemInHand = player->getCarriedItem();

	if (g_Data.isLeftClickDown && (player->getSelectedItemId() == 300)) {
		i++;
		//clientMessageF("Bow use: %f", i);

		if (i >= charge) {
			g_Data.getCGameMode()->releaseUsingItem();
			i = 0;
			if (shotOnce) player->completeUsingItem();
		}
		shotOnce = true;
	}
	shotOnce = false;
}