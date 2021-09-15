#include "MegaDupe.h"

#include "../ModuleManager.h"

MegaDupe::MegaDupe() : IModule(0, Category::PLAYER, "Automatically throws not needed stuff out of your inventory") {
	registerFloatSetting("Dupe Amount", &this->amount, 1, 1.f, 128.f);
}

MegaDupe::~MegaDupe() {
}

const char* MegaDupe::getModuleName() {
	return ("MegaDupe");
}

void MegaDupe::onTick(C_GameMode* gm) {
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	auto transactionManager = g_Data.getLocalPlayer()->getTransactionManager();
	C_Inventory* inv = supplies->inventory;
	int selectedSlot = supplies->selectedHotbarSlot;
	C_ItemStack* item = inv->getItemStack(selectedSlot);
	int count = item->count;
	bool isGive = true;
		item->count = amount;
	if (isGive) {
		C_InventoryAction* firstAction = nullptr;
		C_InventoryAction* secondAction = nullptr;
		firstAction = new C_InventoryAction(0, item, nullptr, 507, 99999);
		transactionManager->addInventoryAction(*firstAction);
		inv->addItemToFirstEmptySlot(item);
	}
	for (int n = 0; n <= 0; n++) {
		supplies->selectedHotbarSlot = n;
	}
	if (g_Data.getLocalPlayer()->canOpenContainerScreen() && openInv)
		return;

	// Drop useless items
	std::vector<int> dropSlots = findUselessItems();
	if (!dropSlots.empty()) {
		for (int i : dropSlots) {
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(1);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(2);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(3);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(4);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(5);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(6);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(7);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(8);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(9);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(10);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(11);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(12);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(13);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(14);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(15);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(16);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(17);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(18);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(19);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(20);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(21);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(22);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(23);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(24);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(25);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(26);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(27);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(28);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(29);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(30);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(31);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(32);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(33);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(34);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(35);
			g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(36);
		}
	}
}

std::vector<int> MegaDupe::findStackableItems() {
	std::vector<int> stackableSlot;
	return stackableSlot;
}

std::vector<int> MegaDupe::findUselessItems() {
	std::vector<int> uselessItems;
	std::vector<C_ItemStack*> items;
	{
		for (int i = 0; i < 36; i++) {
			C_ItemStack* itemStack = g_Data.getLocalPlayer()->getSupplies()->inventory->getItemStack(i);
			if (itemStack->item != nullptr) {
				if (!stackIsUseful(itemStack)) {
					if (std::find(items.begin(), items.end(), itemStack) == items.end())
						uselessItems.push_back(i);
					else
						items.push_back(itemStack);
				} else if (std::find(items.begin(), items.end(), itemStack) == items.end()) {
					if ((*itemStack->item)->itemId == 261 && !isLastItem(*itemStack->item))
						uselessItems.push_back(i);
					else
						items.push_back(itemStack);
				}
			}
		}
	}
	return uselessItems;
}

bool MegaDupe::stackIsUseful(C_ItemStack* itemStack) {
	return false;
}

bool MegaDupe::isLastItem(C_Item* item) {
	return true;
}