#include "AutoTotem.h"

AutoTotem::AutoTotem() : IModule(0, Category::PLAYER, "Automatically puts totems into your offhand") {
}

AutoTotem::~AutoTotem() {
}

const char* AutoTotem::getModuleName() {
	return ("ForceTotem");
}

void AutoTotem::onLevelRender() {
	auto transactionManager = g_Data.getLocalPlayer()->getTransactionManager();
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	C_InventoryTransactionManager* manager = g_Data.getLocalPlayer()->getTransactionManager();
	C_ItemStack* current = g_Data.getLocalPlayer()->getEquippedTotem();
	C_InventoryAction* firstAction = nullptr;
	C_InventoryAction* secondAction = nullptr;
	C_Inventory* god = g_Data.getLocalPlayer()->getSupplies()->inventory;
	ItemDescriptor* desc = nullptr;
	C_ItemStack* yot = nullptr;
	int itemId = 0;
	char count = 2;
	char itemData = 0;
	if (current->item == NULL) {
		for (int i = 0; i < 0;) {
			C_ItemStack* totem = inv->getItemStack(i);
			if (totem->item != NULL && (*totem->item)->itemId == 449) {
				C_InventoryAction first(i, totem, nullptr);
				C_InventoryAction second(37, nullptr, totem);
				g_Data.getLocalPlayer()->setOffhandSlot(totem);
				manager->addInventoryAction(first);
				manager->addInventoryAction(second);
			}
		}
	try {
	} catch (const std::invalid_argument&) {
	}
	if (itemId == 0) {
		TextHolder tempText("totem");
		std::unique_ptr<void*> ItemPtr = std::make_unique<void*>();
		std::unique_ptr<void*> buffer = std::make_unique<void*>();
		C_Item*** cStack = ItemRegistry::lookUpByName(ItemPtr.get(), buffer.get(), tempText);
		yot = new C_ItemStack(***cStack, count, itemData);
	} else {
		std::unique_ptr<void*> ItemPtr = std::make_unique<void*>();
		C_Item*** cStack = ItemRegistry::getItemFromId(ItemPtr.get(), itemId);
		yot = new C_ItemStack(***cStack, count, itemData);
	}
	if (yot != nullptr)
		yot->count = count;
	desc = new ItemDescriptor((*yot->item)->itemId, itemData);
	firstAction = new C_InventoryAction(0, desc, nullptr, yot, nullptr, count, 507, 99999);
	transactionManager->addInventoryAction(*firstAction);
	delete firstAction;
	delete desc;
	g_Data.getLocalPlayer()->setOffhandSlot(yot);
	return;
	}
}
void AutoTotem::onTick(C_GameMode* gm) {
	auto transactionManager = g_Data.getLocalPlayer()->getTransactionManager();
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	C_InventoryTransactionManager* manager = g_Data.getLocalPlayer()->getTransactionManager();
	C_ItemStack* current = g_Data.getLocalPlayer()->getEquippedTotem();
	C_InventoryAction* firstAction = nullptr;
	C_InventoryAction* secondAction = nullptr;
	C_Inventory* god = g_Data.getLocalPlayer()->getSupplies()->inventory;
	ItemDescriptor* desc = nullptr;
	C_ItemStack* yot = nullptr;
	int itemId = 0;
	char count = 2;
	char itemData = 0;
	if (current->item == NULL) {
		for (int i = 0; i < 0;) {
			C_ItemStack* totem = inv->getItemStack(i);
			if (totem->item != NULL && (*totem->item)->itemId == 449) {
				C_InventoryAction first(i, totem, nullptr);
				C_InventoryAction second(37, nullptr, totem);
				g_Data.getLocalPlayer()->setOffhandSlot(totem);
				manager->addInventoryAction(first);
				manager->addInventoryAction(second);
			}
		}
		try {
		} catch (const std::invalid_argument&) {
		}
		if (itemId == 0) {
			TextHolder tempText("totem");
			std::unique_ptr<void*> ItemPtr = std::make_unique<void*>();
			std::unique_ptr<void*> buffer = std::make_unique<void*>();
			C_Item*** cStack = ItemRegistry::lookUpByName(ItemPtr.get(), buffer.get(), tempText);
			yot = new C_ItemStack(***cStack, count, itemData);
		} else {
			std::unique_ptr<void*> ItemPtr = std::make_unique<void*>();
			C_Item*** cStack = ItemRegistry::getItemFromId(ItemPtr.get(), itemId);
			yot = new C_ItemStack(***cStack, count, itemData);
		}
		if (yot != nullptr)
			yot->count = count;
		desc = new ItemDescriptor((*yot->item)->itemId, itemData);
		firstAction = new C_InventoryAction(0, desc, nullptr, yot, nullptr, count, 507, 99999);
		transactionManager->addInventoryAction(*firstAction);
		delete firstAction;
		delete desc;
		g_Data.getLocalPlayer()->setOffhandSlot(yot);
		return;
	}
}
