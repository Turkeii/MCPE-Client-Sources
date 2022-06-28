#include "HoleFiller.h"

HoleFiller::HoleFiller() : IModule(0x0, Category::WORLD, "Fills holes around people") {
	rotations = SettingEnum(this)
					.addEntry(EnumEntry("Off", rotations_off))
					.addEntry(EnumEntry("Arora", rotations_arora));
	registerEnumSetting("Rotations", &rotations, rotations_off);
	registerIntSetting("Range", &range, 1, 1, 6);
	registerIntSetting("Delay", &delay, 1, 1, 20);
	registerBoolSetting("Use Any Block", &allBlocks, allBlocks);
	registerBoolSetting("Obsidian Holes", &obsidian, obsidian);
	registerBoolSetting("Bedrock Holes", &bedrock, bedrock);
	registerBoolSetting("Mix Holes", &mix, mix);
}

HoleFiller::~HoleFiller() {
}

const char* HoleFiller::getModuleName() {
	return ("HoleFiller");
}
const char* HoleFiller::getModName() {
	return "";
}

static std::vector<C_Entity*> targetDaNiggas;

void findDaNiggas(C_Entity* currentEntity, bool isRegularEntity) {
	static auto HoleFillerMod = moduleMgr->getModule<HoleFiller>();

	if (currentEntity == nullptr)
		return;

	if (currentEntity == g_Data.getLocalPlayer())  // Skip Local player
		return;

	if (!g_Data.getLocalPlayer()->canAttack(currentEntity, false))
		return;

	if (!g_Data.getLocalPlayer()->isAlive())
		return;

	if (!currentEntity->isAlive())
		return;

	if (!Target::isValidTarget(currentEntity))
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < 7)
		targetDaNiggas.push_back(currentEntity);
}

bool FillDaHole(vec3_t posThatItPlacesAtBEcImBlack) {
	posThatItPlacesAtBEcImBlack = posThatItPlacesAtBEcImBlack.floor();

	C_Block* block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(posThatItPlacesAtBEcImBlack));
	C_BlockLegacy* blockLegacy = (block->blockLegacy);
	if (blockLegacy->material->isReplaceable) {
		vec3_ti blok(posThatItPlacesAtBEcImBlack);
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
			bool urMomsHasBigTitties = false;
			g_Data.getCGameMode()->buildBlock(&blok, i, urMomsHasBigTitties);
			return true;
		}
	}
	return false;
}

bool HoleFiller::findDaBlocks() {
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	auto prevSlot = supplies->selectedHotbarSlot;
	for (int n = 0; n < 9; n++) {
		C_ItemStack* stack = inv->getItemStack(n);
		if (stack->item != nullptr) {
			if (allBlocks && stack->getItem()->isBlock()) {
				if (prevSlot != n)
					supplies->selectedHotbarSlot = n;
				return true;
			} else if (!allBlocks && stack->getItem()->isBlock() && stack->getItem()->itemId == 49) {
				if (prevSlot != n)
					supplies->selectedHotbarSlot = n;
				return true;
			}
		}
	}
	return false;
}

void HoleFiller::onLevelRender() {
	targetDaNiggas.clear();
	g_Data.forEachEntity(findDaNiggas);
	if (!(g_Data.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
		if (!targetDaNiggas.empty() && g_Data.isInGame()) {
			if (rotations.GetSelectedEntry().GetValue() == rotations_arora) {
				if (moduleMgr->getModule<Disabler>()->Server.selected != 0)
					moduleMgr->getModule<Disabler>()->Server.selected = 0;
				if (!moduleMgr->getModule<Disabler>()->isEnabled())
					moduleMgr->getModule<Disabler>()->setEnabled(true);
			}
			findDaBlocks();
			vec3_t* pos = targetDaNiggas[0]->getPos();
			for (int x = (int)pos->x - range; x < pos->x + range; x++) {
				for (int z = (int)pos->z - range; z < pos->z + range; z++) {
					for (int y = (int)pos->y - range; y < pos->y + range; y++) {
						vec3_t blockPos = vec3_t(x, y, z);
						vec3_t blockPos2 = vec3_t(x + 1, y, z);
						vec3_t blockPos3 = vec3_t(x, y, z + 1);
						vec3_t blockPos4 = vec3_t(x, y - 1, z);
						vec3_t blockPos5 = vec3_t(x - 1, y, z);
						vec3_t blockPos6 = vec3_t(x, y, z - 1);

						C_Block* block = targetDaNiggas[0]->region->getBlock(blockPos);
						C_Block* block2 = targetDaNiggas[0]->region->getBlock(blockPos2);
						C_Block* block3 = targetDaNiggas[0]->region->getBlock(blockPos3);
						C_Block* block4 = targetDaNiggas[0]->region->getBlock(blockPos4);
						C_Block* block5 = targetDaNiggas[0]->region->getBlock(blockPos5);
						C_Block* block6 = targetDaNiggas[0]->region->getBlock(blockPos6);

						if (block != nullptr && block2 != nullptr && block3 != nullptr && block4 != nullptr) {
							int blockId = block->toLegacy()->blockId;
							int blockId2 = block2->toLegacy()->blockId;
							int blockId3 = block3->toLegacy()->blockId;
							int blockId4 = block4->toLegacy()->blockId;
							int blockId5 = block5->toLegacy()->blockId;
							int blockId6 = block6->toLegacy()->blockId;

							bool obs = false;

							if (blockId == 0) obs = true;

							// Fill Obsidian Holes
							Odelay++;
							if (Odelay >= delay) {
								if (obsidian) {
									if ((blockId2 == 49 && blockId3 == 49 && blockId4 == 49 && blockId5 == 49 && blockId6 == 49 && blockId == 0)) {
										if (g_Data.getLocalPlayer()->region->getBlock(blockPos.add(0, 1, 0))->blockLegacy->blockId != 0)
											continue;

										if (g_Data.getLocalPlayer()->region->getBlock(blockPos.add(0, 2, 0))->blockLegacy->blockId)
											continue;

										FillDaHole(blockPos);
									}
								}

								// Fill Mixed Holes
								if (mix) {
									if ((blockId2 == 49 || blockId2 == 7) && (blockId3 == 49 || blockId3 == 7) && (blockId4 == 49 || blockId4 == 7) && (blockId5 == 49 || blockId5 == 7) && (blockId6 == 49 || blockId6 == 7) && (blockId == 0)) {
										if (g_Data.getLocalPlayer()->region->getBlock(blockPos.add(0, 1, 0))->blockLegacy->blockId != 0)
											continue;

										if (g_Data.getLocalPlayer()->region->getBlock(blockPos.add(0, 2, 0))->blockLegacy->blockId)
											continue;

										FillDaHole(blockPos);
									}
								}

								// Fill Bedrock Holes
								if (bedrock) {
									if ((blockId2 == 7 && blockId3 == 7 && blockId4 == 7 && blockId5 == 7 && blockId6 == 7 && blockId == 0)) {
										if (g_Data.getLocalPlayer()->region->getBlock(blockPos.add(0, 1, 0))->blockLegacy->blockId != 0)
											continue;

										if (g_Data.getLocalPlayer()->region->getBlock(blockPos.add(0, 2, 0))->blockLegacy->blockId)
											continue;

										FillDaHole(blockPos);
									}
								}
								Odelay = 0;
							}
						}
					}
				}
			}
		}
	}
}
void HoleFiller::onPlayerTick(C_Player* plr) {
}