#pragma once
#include "Module.h"
#include "../../../SDK/CAttribute.h"

class AutoPot : public IModule {
private:
	int health = 5;
	bool findPot() {
		C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
		C_Inventory* inv = supplies->inventory;
		auto prevSlot = supplies->selectedHotbarSlot;
		for (int n = 0; n < 9; n++) {
			C_ItemStack* stack = inv->getItemStack(n);
			if (stack->item != nullptr) {
				if (isPot(stack)) {
					if (prevSlot != n) {
						supplies->selectedHotbarSlot = n;
						C_MobEquipmentPacket p;
						p.hotbarSlot = n;
						g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
					}
					return true;
				}
			}
		}
		return false;
	}
	bool isPot(C_ItemStack* itemStack) { return itemStack->getItem()->name.getText() == (std::string) "splash_potion"; }

public:
	AutoPot() : IModule(0x0, Category::COMBAT, "Auto throws potions at the selected health") {
		registerIntSetting("Health", &health, health, 1, 20);
	}
	~AutoPot(){}

	virtual void onTick(C_GameMode* gm) override {
		//Atributes
		static HealthAttribute attribute = HealthAttribute();
		auto Health = g_Data.getLocalPlayer()->getAttribute(&attribute)->currentValue;
		auto HealthMax = g_Data.getLocalPlayer()->getAttribute(&attribute)->maximumValue;

		C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
		C_Inventory* inv = supplies->inventory;
		if (g_Data.getLocalPlayer()->isAlive() && g_Data.isInGame()) {
			if (!g_Data.getLocalPlayer()->canOpenContainerScreen()) {
				int slot;
				int potSlot;
				for (int n = 0; n < 36; n++) {
					C_ItemStack* stack = inv->getItemStack(n);
					if (stack->item != nullptr && isPot(stack)) {
						auto PotSlot = inv->getFirstEmptySlot();
						potSlot = PotSlot;
						slot = n;
					}
				}
				if (slot != 0) {
					inv->swapSlots(slot, potSlot);
				}
			}

			//checks if it can throw yet
			if (Health < health) {
				findPot();

				//Rots to look down
				float rotChange = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 2.f)) + 1.f;
				C_LocalPlayer* player = g_Data.getLocalPlayer();
				C_MovePlayerPacket mpp(player, *player->getPos());
				mpp.onGround = player->onGround;
				mpp.pitch = 90.f - rotChange;
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&mpp);

				Utils::rightClick();
			}
		}
	}
	const char* getModuleName() override { return "AutoPot"; }
};
