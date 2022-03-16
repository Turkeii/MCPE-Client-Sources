#include "AutoCrystalKari.h"

AutoCrystalKari::AutoCrystalKari() : IModule('R', Category::COMBAT, "Place End Crystals faster(Place only)") {
	this->registerBoolSetting("SilentSwitch", &this->silentswitch, this->silentswitch);
	this->registerBoolSetting("OnClick", &this->onclick, this->onclick);

	registerFloatSetting("delay", &this->delay, this->delay, 0.f, 20.f);
}

AutoCrystalKari::~AutoCrystalKari() {
}

const char* AutoCrystalKari::getModuleName() {
	return ("AutoCrystal");
}
const char* AutoCrystalKari::getModeName() {
	return ("AuroraPVP");
}
bool AutoCrystalKari::findBlock() {
	__int64 id = *g_Data.getLocalPlayer()->getUniqueId();
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	for (int n = 0; n < 9; n++) {
		C_ItemStack* stack = inv->getItemStack(n);
		if (stack->item != nullptr) {
			if ((*stack->item)->isCrystal() && (*stack->item)->itemId != 0) {
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
bool AutoCrystalKari::findBlock2() {
	__int64 id = *g_Data.getLocalPlayer()->getUniqueId();
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	for (int n = 0; n < 9; n++) {
		C_ItemStack* stack = inv->getItemStack(supplies->selectedHotbarSlot);
		if (stack->item != nullptr) {
				C_MobEquipmentPacket a(id, *g_Data.getLocalPlayer()->getSelectedItem(), supplies->selectedHotbarSlot, supplies->selectedHotbarSlot);
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);
				return true;
			}
		
	}
	C_MobEquipmentPacket a(id, *g_Data.getLocalPlayer()->getSelectedItem(), supplies->selectedHotbarSlot, supplies->selectedHotbarSlot);
	g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);
	return false;

}
bool AutoCrystalKari::tryScaffold(vec3_t blockBelow) {
	blockBelow = blockBelow.floor();

	C_Block* block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blockBelow));
	C_BlockLegacy* blockLegacy = (block->blockLegacy);
	if (blockLegacy->material->isReplaceable) {
		vec3_ti blok(blockBelow);

		// Find neighbour
		static std::vector<vec3_ti*> checklist;
		if (checklist.empty()) {
			checklist.push_back(new vec3_ti(0, -1, 0));
			checklist.push_back(new vec3_ti(0, 1, 0));

			checklist.push_back(new vec3_ti(0, 0, -1));
			checklist.push_back(new vec3_ti(0, 0, 1));

			checklist.push_back(new vec3_ti(-1, 0, 0));
			checklist.push_back(new vec3_ti(1, 0, 0));
		}

		bool foundCandidate = false;
		int i = 0;
		for (auto current : checklist) {
			vec3_ti calc = blok.sub(*current);
			bool Y = ((g_Data.getLocalPlayer()->region->getBlock(calc)->blockLegacy))->material->isReplaceable;
			if (!((g_Data.getLocalPlayer()->region->getBlock(calc)->blockLegacy))->material->isReplaceable) {
				// Found a solid block to click
				foundCandidate = true;
				blok = calc;
				break;
			}
			i++;
		}
		if (foundCandidate) {
			if (silentswitch) findBlock();
			bool idk = true;
			//g_Data.getCGameMode()->buildBlock(&blok, i, idk);

			return true;
		}
	}
	return false;
}

void AutoCrystalKari::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	__int64 id = *g_Data.getLocalPlayer()->getUniqueId();

	PointingStruct* pstruct = g_Data.getClientInstance()->getPointerStruct();
	auto selectedItem = g_Data.getLocalPlayer()->getSelectedItem();
	Odelay++;
	if (Odelay > delay) {
		// tryScaffold();
		//if (!GameData::isRightClickDown()) {
			findBlock();
			//bool idk = true;
			//findBlock2();
		//} 
			Odelay = 0;
		
	}
}
void AutoCrystalKari::onDisable() {	
	findBlock2();
}