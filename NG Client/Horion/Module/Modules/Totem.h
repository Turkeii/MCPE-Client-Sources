#pragma once
#include "Module.h"

class Totem : public IModule {
public:
	Totem() : IModule(0x0, Category::COMBAT, "Automatically puts totems from your inventory into your offhand") {}
	~Totem(){}

	virtual const char* getModuleName() override { return ("AutoTotem"); }
	virtual void onTick(C_GameMode* gm) override {
		C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
		C_Inventory* inv = supplies->inventory;
		C_InventoryTransactionManager* manager = g_Data.getLocalPlayer()->getTransactionManager();
		C_ItemStack* current = g_Data.getLocalPlayer()->getEquippedTotem();
		if (current->item == NULL) {
			for (int i = 0; i < 36; i++) {
				C_ItemStack* totem = inv->getItemStack(i);
				if (totem->item != NULL && (*totem->item)->itemId == 568) {
					int from = i;
					int to = 36;
					if (to != from) {
						C_InventoryTransactionManager* manager = g_Data.getLocalPlayer()->getTransactionManager();
						C_ItemStack* i1 = inv->getItemStack(from);
						C_ItemStack* i2 = inv->getItemStack(to);
						C_InventoryAction first(from, i1, nullptr);
						C_InventoryAction second(to, i2, i1);
						C_InventoryAction third(from, nullptr, i2);
						manager->addInventoryAction(first);
						manager->addInventoryAction(second);
						manager->addInventoryAction(third);
					}
				}
			}
		}
	}
};