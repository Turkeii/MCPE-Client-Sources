#include "AutoTotem.h"

AutoTotem::AutoTotem() : IModule(0, Category::PLAYER, "Automatically puts totems into your offhand") {
	registerBoolSetting("Totem", &this->totem, this->totem);
	registerBoolSetting("Shield", &this->shield, this->shield);
}

AutoTotem::~AutoTotem() {
}

const char* AutoTotem::getModuleName() {
	return ("Offhand");
}

void AutoTotem::onTick(C_GameMode* gm) {
	if (!(totem || shield))
		return;

	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	C_InventoryTransactionManager* manager = g_Data.getLocalPlayer()->getTransactionManager();
	using getOffhandSlot_t = C_ItemStack*(__fastcall*)(C_Entity*);
	static getOffhandSlot_t getOffhandSlot = (getOffhandSlot_t)FindSignature("48 8B 89 ?? ?? ?? ?? BA 01 00 00 00 48 8B 01 48 FF 60 ??");

	C_ItemStack* current = getOffhandSlot(g_Data.getLocalPlayer());
	
	bool run = false;
	
	if (current->item == NULL)
		run = true;

	else if ((*current->item)->itemId != (this->totem ? 558 : 355))
		run = true;

	if (run) {
		for (int i = 0; i < 36; i++) {
			C_ItemStack* totem = inv->getItemStack(i);
			if (totem->item != NULL && (*totem->item)->itemId == (this->totem ? 558 : 355)) {
				C_InventoryAction first(i, totem, nullptr);
				C_InventoryAction second(37, nullptr, totem);
				g_Data.getLocalPlayer()->setOffhandSlot(totem);
				manager->addInventoryAction(first);
				manager->addInventoryAction(second);
				break;
			}
		}
	}
}