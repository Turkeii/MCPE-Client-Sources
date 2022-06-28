#include "FastBow.h"
FastBow::FastBow() : IModule(0x0, Category::COMBAT, "Spam arrows nigga") {
	registerIntSetting("Delay", &this->charge, this->charge, 5, 20);
}
FastBow::~FastBow() {
}

const char* FastBow::getModuleName() {
	return ("FastBow");
}

void FastBow::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	auto itemInHand = player->getCarriedC_Item();

	if (g_Data.isLeftClickDown && (player->getSelectedItemId() == 300)) {
		i++;

		if (i >= charge) {
			g_Data.getCGameMode()->releaseUsingItem();
			i = 0;
		}
	}
}