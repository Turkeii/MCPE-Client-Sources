//CrystalReplenishment

#include "CrystalReplenishment.h"

CrystalReplenishment::CrystalReplenishment() : IModule(0, Category::PLAYER, "Automatically puts totems into your offhand") {
}

CrystalReplenishment::~CrystalReplenishment() {
}

const char* CrystalReplenishment::getModuleName() {
	return ("CrystalReplenishment");
}

void CrystalReplenishment::onTick(C_GameMode* gm) {
	int crystal = 0;
	crystal = 615;
	crystal = 616;
	crystal = 629;
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	C_InventoryTransactionManager* manager = g_Data.getLocalPlayer()->getTransactionManager();
	C_ItemStack* current = g_Data.getLocalPlayer()->getEquippedTotem();

	if (current->item == NULL) {
		for (int i = 0; i < 36; i++) {
			C_ItemStack* totem = inv->getItemStack(i);
			if (totem->item != NULL && (*totem->item)->itemId == crystal) {
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
