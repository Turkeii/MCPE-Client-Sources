#include "Switcher.h"
#include "../pch.h"

Switcher::Switcher() : IModule(0, Category::COMBAT, "Switches between hotbar slots") {
	registerBoolSetting("DoubleSwitch", &ss, ss);
	registerBoolSetting("AutoSwitch", &autos, autos);
	registerIntSetting("Slots", &ternary, 1, 0, 8);
}

const char* Switcher::getModuleName() {
	return ("AutoSword");
}

void Switcher::onEnable() {
}

void Switcher::onAttack(C_Entity* attackedEnt) {
		C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
		C_Inventory* inv = supplies->inventory;
		if (!ownage && !ss) {
		ternary1++;
		if (ternary1 >= ternary + 1) {
			ternary1 = 0;
		}
	}
	supplies->selectedHotbarSlot = ternary1;

	if (ownage && !autos) {
			if (ternaryO == false) {
				if (toggler == false) {
					toggler = true;
					supplies->selectedHotbarSlot = 0;
				} else {
					toggler = false;
					supplies->selectedHotbarSlot = 4;
					ternaryO = true;
				}
			} else {
				supplies->selectedHotbarSlot = 5;
				ternaryO = false;
			}
		}

	if (ss && !autos) {
			if (swap == false) {
				swap = true;
				supplies->selectedHotbarSlot = 0;
			} else {
				swap = false;
				supplies->selectedHotbarSlot = 1;
			}
		}
}

void Switcher::onTick(C_GameMode* gm) {
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	if (autos && !ownage) {
		ternary1++;
		if (ternary1 >= ternary + 1) {
			ternary1 = 0;
		}
		supplies->selectedHotbarSlot = ternary1;
	}
	if (autos && ownage){
		if (ternaryO == false) {
			if (toggler == false) {
				toggler = true;
				supplies->selectedHotbarSlot = 0;
			} else {
				toggler = false;
				supplies->selectedHotbarSlot = 4;
				ternaryO = true;
			}
		} else {
			supplies->selectedHotbarSlot = 5;
			ternaryO = false;
		}
		}
	if (ss && autos) {
		if (swap == false) {
			swap = true;
			supplies->selectedHotbarSlot = 0;
		} else {
			swap = false;
			supplies->selectedHotbarSlot = 1;
		}
	}
}

