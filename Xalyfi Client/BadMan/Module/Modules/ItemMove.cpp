#include "ItemMove.h"

#include "../ModuleManager.h"

ItemMove::ItemMove() : IModule(0, Category::COMBAT, "AutoCrystal by ShinXe") {
	registerIntSetting("Where", &this->place, this->place, 0, 8);
}

ItemMove::~ItemMove() {
}

const char* ItemMove::getModuleName() {
	return ("AutoCrystal");
}

void ItemMove::onTick(C_GameMode* gm) {
	int crystalId = 0;
	crystalId = 615;

	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	supplies->selectedHotbarSlot = place;
	int item = 0;
	for (int i = 0; i < 36; i++) {
		C_ItemStack* stack = inv->getItemStack(i);
		if (stack->item != nullptr) {
			if (stack->getItem()->itemId == crystalId) {
				item = i;
			}
		}
	}

	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	if (item != 0 && item != crystalId && player->getSelectedItemId() != crystalId) inv->moveItem(item, place);
}
