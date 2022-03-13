#include "AutoTotem.h"

AutoTotem::AutoTotem() : IModule(0, Category::COMBAT, "Automatically puts totems or shields into your offhand") {
	type = SettingEnum(this)
			   .addEntry(EnumEntry("Totem", 0))
			   .addEntry(EnumEntry("Shield", 1));
	registerEnumSetting("Type", &type, 0);
}

AutoTotem::~AutoTotem() {
}

const char* AutoTotem::getModName() {
	if (totem) {
		return "Totem";
	}
	if (shield) {
		return "Shield";
	}
}

const char* AutoTotem::getModuleName() {
	return ("Offhand");
}

void AutoTotem::onTick(C_GameMode* gm) {
	switch (type.selected) {
	case 0:
		totem = true;
		shield = false;
		break;
	case 1:
		totem = false;
		shield = true;
		break;
	}

	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	C_InventoryTransactionManager* manager = g_Data.getLocalPlayer()->getTransactionManager();
	C_ItemStack* current = g_Data.getLocalPlayer()->getEquippedTotem();


	if (totem) {
		if (current->item == NULL) {
			for (int i = 0; i < 36; i++) {
				C_ItemStack* totem = inv->getItemStack(i);
				if (totem->item != NULL && (*totem->item)->itemId == 568) {
					ItemDescriptor* desc = nullptr;
					desc = new ItemDescriptor((*totem->item)->itemId, 0);
					C_InventoryAction first(i, desc, nullptr, totem, nullptr, 1);
					C_InventoryAction second(37, nullptr, desc, nullptr, totem, 1);
					g_Data.getLocalPlayer()->setOffhandSlot(totem);
					manager->addInventoryAction(first);
					manager->addInventoryAction(second);
				}
			}
		}
	} 
	if (shield) {
		if (current->item == NULL) {
			for (int i = 0; i < 36; i++) {
				C_ItemStack* totem = inv->getItemStack(i);
				if (totem->item != NULL && (*totem->item)->itemId == 355) {
					ItemDescriptor* desc = nullptr;
					desc = new ItemDescriptor((*totem->item)->itemId, 0);
					C_InventoryAction first(i, desc, nullptr, totem, nullptr, 1);
					C_InventoryAction second(37, nullptr, desc, nullptr, totem, 1);
					g_Data.getLocalPlayer()->setOffhandSlot(totem);
					manager->addInventoryAction(first);
					manager->addInventoryAction(second);
				}
			}
		}
	}
}
