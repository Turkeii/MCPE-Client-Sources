#include "AutoTotem.h"

AutoTotem::AutoTotem() : IModule(0, Category::PLAYER, "Automatically puts totems into your offhand") {
	Mode.addEntry(EnumEntry("Vanilla", 0));
	Mode.addEntry(EnumEntry("Open Inv", 1));
	registerEnumSetting("Mode", &Mode, 0);
}

AutoTotem::~AutoTotem() {
}

const char* AutoTotem::getModuleName() {
	return ("AutoTotem");
}
const char* AutoTotem::getModName() {
	if (Mode.selected == 0) {
		return " [Vanilla]";
	} else {
		return " [OpenInv]";
	}
}

void AutoTotem::onTick(C_GameMode* gm) {
	setOffhand = false;
	if (Mode.selected != 0 && Mode.selected != 1)
		Mode.selected = 0;
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	C_InventoryTransactionManager* manager = g_Data.getLocalPlayer()->getTransactionManager();
	C_ItemStack* current = g_Data.getLocalPlayer()->getEquippedTotem();
	if (current->item == NULL) {
		for (int i = 0; i < 36; i++) {
			C_ItemStack* totem = inv->getItemStack(i);
			if (totem->item != NULL && (*totem->item)->itemId == 568) {
				if (Mode.selected == 0) {
					C_InventoryAction first(i, totem, nullptr);
					C_InventoryAction second(37, nullptr, totem);
					manager->addInventoryAction(first);
					manager->addInventoryAction(second);
					g_Data.getLocalPlayer()->setOffhandSlot(totem);
				} else if (Mode.selected == 1) {
					C_InteractPacket openInv;
					openInv.actionid = 6;
					openInv.entityRuntimeId = g_Data.getLocalPlayer()->entityRuntimeId;
					openInv.pos = *g_Data.getLocalPlayer()->getPos();
					g_Data.getClientInstance()->getLoopbackPacketSender()->sendToServer(&openInv);
					setOffhand = true;
				}
			}
		}
	}
}

void AutoTotem::craftingScreenController_tick(C_CraftingScreenController* c) {
	if (Mode.selected == 1 && setOffhand) {
		for (int i = 9; i < 37; i++) {
			C_ItemStack* stack = c->_getItemStack(TextHolder("inventory_items"), i);
			if (stack != nullptr && stack->item != NULL)
				if ((*stack->item)->itemId == 568)
					if (g_Data.getLocalPlayer()->getEquippedTotem()->item == NULL) {
						c->handleAutoPlace(0x7FFFFFFF, "inventory_items", i);
						break;
					}
		}
		for (int i = 0; i < 9; i++) {
			C_ItemStack* stack = c->_getItemStack(TextHolder("hotbar_items"), i);
			if (stack != nullptr && stack->item != NULL)
				if ((*stack->item)->itemId == 568)
					if (g_Data.getLocalPlayer()->getEquippedTotem()->item == NULL) {
						c->handleAutoPlace(0x7FFFFFFF, "hotbar_items", i);
						break;
					}
		}
		c->tryExit();
		setOffhand = false;
	}
}