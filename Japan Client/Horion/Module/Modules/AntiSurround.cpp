#include "AntiSurround.h"
#include "../ModuleManager.h"
AntiSurround::AntiSurround() : IModule(0x0, Category::COMBAT, "X Surround for target") {
	this->registerBoolSetting("MultiBreak", &this->multi, this->multi);
	this->registerBoolSetting("AutoSwitch", &this->spoof, this->spoof);
	this->registerBoolSetting("Bypass", &this->bypass, this->bypass);
	registerIntSetting("Range", &range, range, 1, 20);
}

AntiSurround::~AntiSurround() {
}

const char* AntiSurround::getModuleName() {
	return ("AntiSurround");
}

bool AntiSurround::findBlock() {
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	for (int n = 0; n < 9; n++) {
		auto prevSlot = supplies->selectedHotbarSlot;

		C_ItemStack* stack = inv->getItemStack(n);
		if (stack->item != nullptr) {
			if (stack->getItem()->isPickaxe()) {
				if (prevSlot != n)
					supplies->selectedHotbarSlot = n;
				return true;
			}
		}
	}
	return false;
}
bool AntiSurround::findBlock2() {
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

static std::vector<C_Entity*> targetList7;

void findEntityXSurr(C_Entity* currentEntity, bool isRegularEntity) {
	static auto AntiXCrystalMod = moduleMgr->getModule<AntiSurround>();

	if (currentEntity == nullptr)
		return;

	if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 71)  // crystal
		return;

	if (currentEntity == g_Data.getLocalPlayer())  // Skip Local player
		return;

	if (!g_Data.getLocalPlayer()->isAlive())
		return;

	if (!currentEntity->isAlive())
		return;

	if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 63)
		return;
	if (currentEntity->width <= 0.01f || currentEntity->height <= 0.01f)  // Don't hit this pesky antibot on 2b2e.org
		return;
	if (currentEntity->getEntityTypeId() == 64)  // item
		return;
	if (currentEntity->getEntityTypeId() == 69)  // xp_orb
		return;
	if (currentEntity->getEntityTypeId() == 80)  // arrow
		return;

	if (!Target::isValidTarget(currentEntity))
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < AntiXCrystalMod->range) {
		targetList7.push_back(currentEntity);
	}
}
void AntiSurround::onTick(C_GameMode* gm) {
	targetList7.clear();

	g_Data.forEachEntity(findEntityXSurr);
	if (!(targetList7.empty())) {
		auto supplies = g_Data.getLocalPlayer()->getSupplies();

		auto slot = supplies->selectedHotbarSlot;
		int prevSlot = 0;
		auto playerOn = targetList7[0]->getPos();
		auto floor = playerOn->floor();
		floor.y -= 1.f;
			int x = floor.x;
			int y = floor.y;
			int z = floor.z;
			bool sendBack = false;


			std::vector<vec3_t> SurChecker = {
				vec3_t(x + 1, y, z),
				vec3_t(x, y, z + 1),
				vec3_t(x - 1, y, z),
				vec3_t(x, y, z - 1),
			};
			for (auto checkThis : SurChecker) {
				bool destroy = false;
				if (!multi) {
					gm->player->region->getBlock(vec3_ti(checkThis))->toLegacy()->blockId;

					if (gm->player->region->getBlock(vec3_ti(checkThis))->toLegacy()->blockId) {
						destroy = true;
					}
				} else {
					destroy = true;
				}
				if (g_Data.getLocalPlayer()->region->getBlock(vec3_ti(checkThis))->toLegacy()->blockId == 0) {
					sendBack = true;
				}
				if (multi ? !sendBack || sendBack : !sendBack && destroy) {
					if (spoof) prevSlot = slot;

					if (spoof) findBlock();

					if (g_Data.getLocalPlayer()->region->getBlock(vec3_ti(checkThis))->toLegacy()->blockId == 49) gm->destroyBlock(&vec3_ti(checkThis), 0);
					if (g_Data.getLocalPlayer()->region->getBlock(vec3_ti(checkThis))->toLegacy()->blockId == 0 && spoof) supplies->selectedHotbarSlot = prevSlot;
					//if (spoof) findBlock2(); 
					//
				}
				if (!multi) {
					return;
				}
			}
	}
}