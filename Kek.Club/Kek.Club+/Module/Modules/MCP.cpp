#include "MCP.h"

MCP::MCP() : IModule(0, Category::PLAYER, "Throws a pearl") {
}

MCP::~MCP() {
}

const char* MCP::getModuleName() {
	return "MCP";
}
bool SilentSwapMCP(int Itemid) {
	__int64 id = *g_Data.getLocalPlayer()->getUniqueId();
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	for (int n = 0; n < 9; n++) {
		C_ItemStack* stack = inv->getItemStack(n);
		if (stack->item != nullptr) {
			if ((*stack->item)->itemId != 0) {
				if (stack->getItem()->itemId == Itemid) {
					C_MobEquipmentPacket a(id, *stack, n, n);
					g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);
					return true;
				}
			}
		}
	}
	return false;
}

bool isInInvMCP(int Itemid) {
	__int64 id = *g_Data.getLocalPlayer()->getUniqueId();
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	for (int n = 0; n < 9; n++) {
		C_ItemStack* stack = inv->getItemStack(n);
		if (stack->item != nullptr) {
			if ((*stack->item)->itemId != 0) {
				if (stack->getItem()->itemId == Itemid) {
					return true;
				}
			}
		}
	}
	return false;
}
void MCP::onTick(C_GameMode* gm) {
	if (GameData::isWheelDown() && !hasClicked) {
		auto inv = g_Data.getLocalPlayer()->getSupplies()->inventory;
        for (int i = 0; i < 9; i++) {
            C_ItemStack* stack = inv->getItemStack(i);
            if (stack->item != nullptr) {
                if (stack->getItem()->itemId == 422) {
                   // g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot = i;
					__int64 id = *g_Data.getLocalPlayer()->getUniqueId();
					C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
				   if (isInInvMCP(422)) SilentSwapMCP(422);	
                   g_Data.getCGameMode()->baseUseItem(*stack);
				   if (g_Data.getLocalPlayer()->isAlive() && g_Data.getLocalPlayer()->getSelectedItemId() != 0 && supplies != nullptr && supplies->inventory != nullptr && supplies->selectedHotbarSlot != -1 && supplies->inventory->getItemStack(supplies->selectedHotbarSlot) != nullptr && supplies->inventory->getItemStack(supplies->selectedHotbarSlot)->getItem() != nullptr && supplies->inventory->getItemStack(supplies->selectedHotbarSlot)->item != nullptr && !supplies->inventory->getItemStack(supplies->selectedHotbarSlot)->getItem()->isWeapon() && !supplies->inventory->getItemStack(supplies->selectedHotbarSlot)->getItem()->isShooter()) {
					   C_ItemStack* stack = supplies->inventory->getItemStack(supplies->selectedHotbarSlot);
					   C_MobEquipmentPacket a(id, *stack, supplies->selectedHotbarSlot, supplies->selectedHotbarSlot);
					   g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);
				   }
                    return;
                }
				
            }
        }
		hasClicked = true;
	} else if (!GameData::isWheelDown()) {
		hasClicked = false;
	}
}	
