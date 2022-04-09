#include "AutoTotem.h"

AutoTotem::AutoTotem() : IModule(0, Category::PLAYER, "Automatically puts totems into your offhand") {
	registerBoolSetting("Force", &force, force);
}

AutoTotem::~AutoTotem() {
}

const char* AutoTotem::getModuleName() {
	return ("AutoTotem");
}

void AutoTotem::onTick(C_GameMode* gm) {
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	C_InventoryTransactionManager* manager = g_Data.getLocalPlayer()->getTransactionManager();
	C_ItemStack* current = g_Data.getLocalPlayer()->getEquippedTotem();
	if (force) {
		C_InventoryAction* firstAction = nullptr;
		ItemDescriptor* desc = nullptr;
		C_ItemStack* yot = nullptr;
		int itemId = 0;
		if (itemId == 0) {
			TextHolder tempText("totem");
			std::unique_ptr<void*> ItemPtr = std::make_unique<void*>();
			std::unique_ptr<void*> buffer = std::make_unique<void*>();
			C_Item*** cStack = ItemRegistry::lookUpByName(ItemPtr.get(), buffer.get(), tempText);
			yot = new C_ItemStack(***cStack, 1, 0);
		}
		if (yot != nullptr) yot->count = 2;
		desc = new ItemDescriptor((*yot->item)->itemId, 0);
		firstAction = new C_InventoryAction(0, desc, nullptr, yot, nullptr, 1, 507, 99999);
		g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(*firstAction);
		delete firstAction;
		delete desc;
		g_Data.getLocalPlayer()->setOffhandSlot(yot);
		return;
	}
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