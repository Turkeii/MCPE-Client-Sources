#include "Switcher.h"

Switcher::Switcher() : IModule(0x0, Category::COMBAT, "Switches to first hotbar on attack (Meant for Pocketmine [PMMP] Servers)") {
	registerIntSetting("Slots", &this->ternary, 1, 0, 8);
}

Switcher::~Switcher() {
}

const char* Switcher::getModuleName() {
	return ("Switcher");
}

void Switcher::onAttack(C_Entity* attackedEnt) {
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	ternary1++;
	//int slot = supplies->selectedHotbarSlot;
	//supplies->selectedHotbarSlot = slot;
	if (ternary1 >= ternary+1) {
		ternary1 = 0;
	}
	supplies->selectedHotbarSlot = ternary1;
}
