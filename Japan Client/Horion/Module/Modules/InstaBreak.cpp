#include "InstaBreak.h"

InstaBreak::InstaBreak() : IModule(0, Category::WORLD, "Break block fast working aurorapvp.club | fixed and developed KaeruClient") {
	mode = SettingEnum(this)
			   .addEntry(EnumEntry("Instant", m_instant))
			   .addEntry(EnumEntry("SilentSwitch", m_silent));
					//.addEntry(EnumEntry("Packet(NotWork)", m_packet));
	registerEnumSetting("MineModes", &mode, m_silent);
}

InstaBreak::~InstaBreak() {
}

const char* InstaBreak::getModuleName() {
	return ("JP-Mine");
}
bool InstaBreak::getPick() {
	__int64 id = *g_Data.getLocalPlayer()->getUniqueId();
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	for (int n = 0; n < 9; n++) {
		C_ItemStack* stack = inv->getItemStack(n);
		if (stack->item != nullptr) {
			if ((*stack->item)->isPickaxe() && (*stack->item)->itemId != 0) {
				C_MobEquipmentPacket a(id, *stack, n, n);
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);
				return true;
			}
		}
	}
	C_MobEquipmentPacket a(id, *g_Data.getLocalPlayer()->getSelectedItem(), supplies->selectedHotbarSlot, supplies->selectedHotbarSlot);
	g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);
	return false;
}

void InstaBreak::onLevelRender() {
	if (!(g_Data.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
		if (g_Data.isInGame()) {
			C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
			PointingStruct* pointing = g_Data.getLocalPlayer()->pointingStruct;
			C_PlayerActionPacket p;
			int packe = p.action;
			int entityRuntimeId = p.entityRuntimeId;
			vec3_ti render;
			if (packe == 0 && entityRuntimeId == g_Data.getLocalPlayer()->entityRuntimeId) pre = true;  // startBreaking
			if (pre) {
				int aa = 0;
				aa++;
				if (silent) {
					old = g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot;
					getPick();
				}
				g_Data.getCGameMode()->destroyBlock(&pointing->block, pointing->blockSide);
				render = pointing->block;
				g_Data.getCGameMode()->destroyBlock(&render, 0);

				if (silent) {
					__int64 id = *g_Data.getLocalPlayer()->getUniqueId();
					C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
					C_MobEquipmentPacket a(id, *g_Data.getLocalPlayer()->getSelectedItem(), supplies->selectedHotbarSlot, supplies->selectedHotbarSlot);
					g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);
					if (aa == 20) pre = false;
					// possave = 0;
				}
			}


		}
	}
}
