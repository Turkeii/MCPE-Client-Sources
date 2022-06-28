#include "AutoPot.h"
AutoPot::AutoPot() : IModule(0, Category::COMBAT, "Throws Harming Pots at Retards") {
	registerBoolSetting("Hold", &hold, false);
	registerIntSetting("Delay", &delay, 6, 1, 50);
	registerIntSetting("health", &health, 10, 1, 20);
}

AutoPot::~AutoPot() {
}

const char* AutoPot::getModuleName() {
	return "AutoPot";
}


void AutoPot::onTick(C_GameMode* gm) {
	int healthy = g_Data.getLocalPlayer()->getHealth();
	if (healthy > health) {
		auto inv = g_Data.getLocalPlayer()->getSupplies()->inventory;
		if ((GameData::isRightClickDown() || !hold) && GameData::canUseMoveKeys()) {
			for (int i = 0; i < 9; i++) {
				C_ItemStack* stack = inv->getItemStack(i);
				if (stack->item != nullptr) {
					if (stack->getItem()->itemId == 561) {
						g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot = i;
						if (Odel >= delay) {
							g_Data.getCGameMode()->baseUseItem(*stack);
							Odel = 0;
							return;
						}
						Odel++;
					}
				}
			}
		}
	}
}