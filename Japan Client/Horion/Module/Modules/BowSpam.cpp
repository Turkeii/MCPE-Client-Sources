#include "BowSpam.h"
#include "Module.h"

BowSpam::BowSpam() : IModule(0x0, Category::COMBAT, "Send so much arrows that even the Iron Dome can't get them all") {
	//registerBoolSetting("AutoShot", &this->autoshot, this->autoshot);

	registerIntSetting("Charge", &this->charge, this->charge, 0, 15);
}

BowSpam::~BowSpam() {
}

// WHAT I LEARNED: some functions are blocked because they are declared as private (i.e. releaseUsingItem())
// To get around this, simply declare it as private...bruh this simple thing really took 3 hours XD :(

const char* BowSpam::getModuleName() {
	return ("BowSpam");
}
const char* BowSpam::getModeName() {
	if (charge == 0) return ("NoCharge");
	static char modName[30];
	sprintf_s(modName, 30, "%.0f", charge);

	if (charge != 0) return modName; 
}
bool BowSpam::findUseItem() {
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	for (int n = 0; n < 9; n++) {
		auto prevSlot = supplies->selectedHotbarSlot;

		C_ItemStack* stack = inv->getItemStack(n);
		C_ItemStack item = *(stack);
		if (stack->item != nullptr) {
			if (stack->getItem()->isBlock()) {
				if (prevSlot != n)
					g_Data.getCGameMode()->useItem(item);
				return true;
			}
		}
	}
	return false;
}
void BowSpam::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	//auto itemInHand = player->getCarriedItem();
	if (autoshot) findUseItem();
	if ((player->getSelectedItemId() == 300)) {
		i++;
		//clientMessageF("Bow use: %f", i);

		if (i >= charge + 5) {
			g_Data.getCGameMode()->releaseUsingItem();
			i = 0;
			if (shotOnce) player->completeUsingItem();
		}
		shotOnce = true;
	}
	shotOnce = false;
}
