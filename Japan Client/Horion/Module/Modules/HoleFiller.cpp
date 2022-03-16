#include "HoleFiller.h"

HoleFiller::HoleFiller() : IModule(0x0, Category::WORLD, "Target not can hole in! lol") {
	this->registerBoolSetting("Spoof", &this->spoof, this->spoof);
	registerIntSetting("Range", &this->range, 1, 5.f, 15.f);
}

HoleFiller::~HoleFiller() {
}

const char* HoleFiller::getModuleName() {
	return ("HoleFiller");
}

static std::vector<C_Entity*> TargetList;

void findEntity1L(C_Entity* currentEntityHF, bool isRegularEntity1) {
	static auto killauraMod = moduleMgr->getModule<HoleFiller>();

	if (currentEntityHF == nullptr)
		return;

	if (currentEntityHF == g_Data.getLocalPlayer())  // Skip Local player
		return;

	if (!g_Data.getLocalPlayer()->canAttack(currentEntityHF, false))
		return;

	if (!g_Data.getLocalPlayer()->isAlive())
		return;

	if (!currentEntityHF->isAlive())
		return;

	if (currentEntityHF->getEntityTypeId() == 69)  // XP
		return;

	if (killauraMod->isMobAura) {
		if (currentEntityHF->getNameTag()->getTextLength() <= 1 && currentEntityHF->getEntityTypeId() == 63)
			return;
		if (currentEntityHF->width <= 0.01f || currentEntityHF->height <= 0.01f)  // Don't hit this pesky antibot on 2b2e.org
			return;
		if (currentEntityHF->getEntityTypeId() == 64)  // item
			return;
		if (currentEntityHF->getEntityTypeId() == 80)  // Arrows
			return;
		if (currentEntityHF->getEntityTypeId() == 51)  // NPC
			return;
	} else {
		if (!Target::isValidTarget(currentEntityHF))
			return;
	}

	float dist = (*currentEntityHF->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < killauraMod->range) {
		TargetList.push_back(currentEntityHF);
	}
}
bool tryHoleFill(vec3_t blkPlacement) {
	blkPlacement = blkPlacement.floor();

	C_Block* block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blkPlacement));
	C_BlockLegacy* blockLegacy = (block->blockLegacy);
	if (blockLegacy->material->isReplaceable) {
		vec3_ti blok(blkPlacement);
		int i = 0;

		static std::vector<vec3_ti*> checklist;
		bool foundCandidate = false;
		if (checklist.empty()) {
			checklist.push_back(new vec3_ti(0, -1, 0));
			checklist.push_back(new vec3_ti(0, 1, 0));

			checklist.push_back(new vec3_ti(0, 0, -1));
			checklist.push_back(new vec3_ti(0, 0, 1));

			checklist.push_back(new vec3_ti(-1, 0, 0));
			checklist.push_back(new vec3_ti(1, 0, 0));
		}

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
			g_Data.getCGameMode()->buildBlock(&blok, i, false);
			return true;
		}
	}
	return false;
}
bool findObsidian() {
	__int64 id = *g_Data.getLocalPlayer()->getUniqueId();
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	for (int n = 0; n < 9; n++) {
		C_ItemStack* stack = inv->getItemStack(n);
		if (stack->item != nullptr) {
			if ((*stack->item)->itemId == 49 && (*stack->item)->itemId != 0) {
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

bool BackToOldSlot() {
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
void HoleFiller::onTick(C_GameMode* gm) {
	int delays = 0;
	delays++;


	if (!(g_Data.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
		if (g_Data.isInGame()) {
			// Odelay++;
			// if (Odelay > delay * 20) {
			vec3_t* pos = g_Data.getLocalPlayer()->getPos();
			for (int x = (int)pos->x - range; x < pos->x + range; x++) {
				for (int z = (int)pos->z - range; z < pos->z + range; z++) {
					for (int y = (int)pos->y - range; y < pos->y + range; y++) {
						vec3_t blockPos = vec3_t(x, y, z);
						vec3_t air = vec3_t(x, y + 1, z);
						vec3_t air2 = vec3_t(x, y + 2, z);

						vec3_t blockPos2 = vec3_t(x + 1, y, z);
						vec3_t blockPos3 = vec3_t(x, y, z + 1);
						vec3_t blockPos4 = vec3_t(x, y - 1, z);
						vec3_t blockPos5 = vec3_t(x - 1, y, z);
						vec3_t blockPos6 = vec3_t(x, y, z - 1);

						vec3_t blockPos22 = vec3_t(x + 1, y + 1, z);
						vec3_t blockPos32 = vec3_t(x, y + 1, z + 1);
						vec3_t blockPos52 = vec3_t(x - 1, y + 1, z);
						vec3_t blockPos62 = vec3_t(x, y + 1, z - 1);

						C_Block* block = g_Data.getLocalPlayer()->region->getBlock(blockPos);
						C_Block* airpos = g_Data.getLocalPlayer()->region->getBlock(air);
						C_Block* airpos2 = g_Data.getLocalPlayer()->region->getBlock(air2);
						C_Block* block2 = g_Data.getLocalPlayer()->region->getBlock(blockPos2);
						C_Block* block3 = g_Data.getLocalPlayer()->region->getBlock(blockPos3);
						C_Block* block4 = g_Data.getLocalPlayer()->region->getBlock(blockPos4);
						C_Block* block5 = g_Data.getLocalPlayer()->region->getBlock(blockPos5);
						C_Block* block6 = g_Data.getLocalPlayer()->region->getBlock(blockPos6);

						C_Block* block22 = g_Data.getLocalPlayer()->region->getBlock(blockPos22);
						C_Block* block32 = g_Data.getLocalPlayer()->region->getBlock(blockPos32);
						C_Block* block52 = g_Data.getLocalPlayer()->region->getBlock(blockPos52);
						C_Block* block62 = g_Data.getLocalPlayer()->region->getBlock(blockPos62);

						if (block != nullptr && block2 != nullptr && block3 != nullptr && block4 != nullptr) {
							int blockId = block->toLegacy()->blockId;
							int aircheck = airpos->toLegacy()->blockId;
							int aircheck2 = airpos2->toLegacy()->blockId;
							int blockId2 = block2->toLegacy()->blockId;
							int blockId3 = block3->toLegacy()->blockId;
							int blockId4 = block4->toLegacy()->blockId;
							int blockId5 = block5->toLegacy()->blockId;
							int blockId6 = block6->toLegacy()->blockId;

							int blockId22 = block22->toLegacy()->blockId;
							int blockId32 = block32->toLegacy()->blockId;
							int blockId52 = block52->toLegacy()->blockId;
							int blockId62 = block62->toLegacy()->blockId;

							bool obs = false;

							if (blockId == 0) obs = true;

							
							// Draw Obsidian Hole
								if ((blockId2 == 49 || blockId2 == 7) && (blockId3 == 49 || blockId3 == 7) && (blockId4 == 49 || blockId4 == 7) && (blockId5 == 49 || blockId5 == 7) && (blockId6 == 49 || blockId6 == 7) && (blockId == 0) && (aircheck == 0)) {
									// if (targetList[0]->getPos()) {
									//	DrawUtils::setColor(0.f, 0.f, 1.f, Opacity);
									// } else {
									//findObsidian();
									tryHoleFill(blockPos);
									//BackToOldSlot();
									// DrawUtils::setColor(0.f, 0.f, 1.f, Opacity);
									// if ((blockId2 == 49 || blockId2 == 7) && (blockId3 == 49 || blockId3 == 7) && (blockId4 == 49) && (blockId5 == 49 || blockId5 == 7) && (blockId6 == 49 || blockId6 == 7) && (blockId == 0) && (aircheck == 0) && (blockId22 == 49 || blockId22 == 7) && (blockId32 == 49 || blockId32 == 7) && (blockId52 == 49 || blockId52 == 7) && (blockId62 == 49 || blockId62 == 7) && (blockId == 0) && (aircheck2 == 0)) {
									// DrawUtils::drawBox2X(blockPos, vec3_t(blockPos).add(1), (float)LineSize);
								}
							

						}
						// Odelay = 0;
					}
				}
			}
			//if (delays == 2) 
			delays = 0;

		}
	}
}