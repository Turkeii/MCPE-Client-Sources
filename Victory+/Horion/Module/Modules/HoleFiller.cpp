#include "HoleFiller.h"

HoleFiller::HoleFiller() : IModule(0x0, Category::WORLD, "Target not can hole in! lol") {
	this->registerBoolSetting("Obsidian Hole", &this->obsidian, this->obsidian);
	this->registerBoolSetting("Bedrock Hole", &this->bedrock, this->bedrock);
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

void HoleFiller::onTick(C_GameMode* gm) {
	vec3_ti bestPos;
	if (!(g_Data.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
		if (g_Data.isInGame()) {
			//Odelay++;
			//if (Odelay > delay * 20) {
			vec3_t* pos = g_Data.getLocalPlayer()->getPos();
			for (int x = (int)pos->x - range; x < pos->x + range; x++) {
				for (int z = (int)pos->z - range; z < pos->z + range; z++) {
					for (int y = (int)pos->y - range; y < pos->y + range; y++) {
						vec3_t blockPos = vec3_t(x, y - 1, z);
						vec3_t blockPos2 = vec3_t(x + 1, y - 1, z);
						vec3_t blockPos3 = vec3_t(x, y - 1, z + 1);
						vec3_t blockPos4 = vec3_t(x, y - 2, z);
						vec3_t blockPos5 = vec3_t(x - 1, y - 1, z);
						vec3_t blockPos6 = vec3_t(x, y - 1, z - 1);

						C_Block* block = g_Data.getLocalPlayer()->region->getBlock(blockPos);
						C_Block* block2 = g_Data.getLocalPlayer()->region->getBlock(blockPos2);
						C_Block* block3 = g_Data.getLocalPlayer()->region->getBlock(blockPos3);
						C_Block* block4 = g_Data.getLocalPlayer()->region->getBlock(blockPos4);
						C_Block* block5 = g_Data.getLocalPlayer()->region->getBlock(blockPos5);
						C_Block* block6 = g_Data.getLocalPlayer()->region->getBlock(blockPos6);

						if (block != nullptr && block2 != nullptr && block3 != nullptr && block4 != nullptr) {
							int blockId = block->toLegacy()->blockId;
							int blockId2 = block2->toLegacy()->blockId;
							int blockId3 = block3->toLegacy()->blockId;
							int blockId4 = block4->toLegacy()->blockId;
							int blockId5 = block5->toLegacy()->blockId;
							int blockId6 = block6->toLegacy()->blockId;

							bool obs = false;

							if (blockId == 0) obs = true;

							bestPos = blockPos;

							//Draw Obsidian Hole
							if (obsidian) {
								if ((blockId2 == 49 && blockId3 == 49 && blockId4 == 49 && blockId5 == 49 && blockId6 == 49 && blockId == 0)) {
									gm->buildBlock(&bestPos, 0);
								}

								//Draw Bedrock Hole
								if (bedrock) {
									if ((blockId2 == 7 && blockId3 == 7 && blockId4 == 7 && blockId5 == 7 && blockId6 == 7 && blockId == 0)) {
										gm->buildBlock(&bestPos, 0);
									}
								}
							}
							//Odelay = 0;
						}
					}
				}
			}
		}
	}
}