#pragma once
#include "Module.h"
class FastEat : public IModule {
public:
	FastEat() : IModule(0x0, Category::PLAYER, "Eat food almost instant") {}
	~FastEat(){};

	// Inherited via IModule
	virtual const char* getModuleName() override { return ("FastEat"); }
	virtual void onTick(C_GameMode* gm) override {
		C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
		C_Inventory* inv = supplies->inventory;
		for (int i = 0; i < 36; i++) {
			C_ItemStack* stack = inv->getItemStack(i);
			if (stack->item != NULL && (*stack->item)->itemId != 261 && (*stack->item)->getMaxUseDuration(stack) == 32) {
				(*stack->item)->setMaxUseDuration(1);
			}
		}
	}
	virtual void onDisable() override {
		if (g_Data.getLocalPlayer() == nullptr)
			return;
		C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
		C_Inventory* inv = supplies->inventory;
		for (int i = 0; i < 36; i++) {
			C_ItemStack* stack = inv->getItemStack(i);
			if (stack->item != NULL && (*stack->item)->itemId != 261 && (*stack->item)->getMaxUseDuration(stack) == 1) {
				(*stack->item)->setMaxUseDuration(32);
			}
		}
	}
};