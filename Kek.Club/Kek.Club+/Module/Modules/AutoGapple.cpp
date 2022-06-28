#include "AutoGapple.h"

AutoGapple::AutoGapple() : IModule(0, Category::PLAYER, "Auto eat gapples if you're low health") {
	registerIntSetting("health", &health, 10, 1, 20);
}

AutoGapple::~AutoGapple() {
}

const char* AutoGapple::getModuleName() {
	return ("AutoGapple");
}

void AutoGapple::onTick(C_GameMode* gm) {
	int healthy = g_Data.getLocalPlayer()->getHealth();
	if (healthy < health) {
		auto inv = g_Data.getLocalPlayer()->getSupplies()->inventory;
		for (int i = 0; i < 9; i++) {
			C_ItemStack* stack = inv->getItemStack(i);
			if (stack->item != nullptr) {
				if (stack->getItem()->itemId == 259) {
					g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot = i;
					g_Data.getCGameMode()->baseUseItem(*stack);
					return;
				}
			}
		}
	} else
		return;
}