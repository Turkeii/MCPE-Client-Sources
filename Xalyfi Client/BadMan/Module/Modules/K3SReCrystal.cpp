#include "K3SReCrystal.h"
K3SReCrystal::K3SReCrystal() : IModule(0x0, Category::COMBAT, "CrystalAura Developed by KaeruClient & sogeda & SBreality & ShinXe") {
	dmgEnum = SettingEnum(this)
				  .addEntry(EnumEntry("Vanilla", dmg_vanilla))
				  .addEntry(EnumEntry("Java", dmg_java));
	registerEnumSetting("Damage Mode", &dmgEnum, dmg_java);
	registerBoolSetting("Spoof", &spoof, spoof);
	registerIntSetting("Range", &range, range, 1, 10);
	registerBoolSetting("AutoPlace", &autoplace, autoplace);
	registerIntSetting("Delay", &delay, delay, 0, 20);
	//registerBoolSetting("bool", &bool1, bool1);
}

K3SReCrystal::~K3SReCrystal() {
}

int K3SRC = 0;
int K3SRC2 = 0;
int K3SRC3 = 0;
const char* K3SReCrystal::getModuleName() {
	return ("K3SReCrystal");
}

/* const char* K3SReCrystal::getModName() {
	int dmgMode = dmgEnum.GetSelectedEntry().GetValue();

	if (dmgMode == dmg_java) {
		return ("Java");
	} else if (dmgMode == dmg_vanilla) {
		return ("Vanilla");
	}
}*/
static std::vector<C_Entity*> targetList7;

void findEntityK3R(C_Entity* currentEntity, bool isRegularEntity) {
	static auto K3SReCrystalMod = moduleMgr->getModule<K3SReCrystal>();

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

	if (dist < K3SReCrystalMod->range) {
		targetList7.push_back(currentEntity);
	}
}

bool checkTargCollision12(vec3_t* block, C_Entity* ent) {
	std::vector<vec3_t*> corners;
	corners.clear();

	corners.push_back(new vec3_t(ent->aabb.lower.x, ent->aabb.lower.y, ent->aabb.lower.z));
	corners.push_back(new vec3_t(ent->aabb.lower.x, ent->aabb.lower.y, ent->aabb.upper.z));
	corners.push_back(new vec3_t(ent->aabb.upper.x, ent->aabb.lower.y, ent->aabb.upper.z));
	corners.push_back(new vec3_t(ent->aabb.upper.x, ent->aabb.lower.y, ent->aabb.lower.z));
	int n = 0;
	if (!corners.empty())
		for (auto corner : corners) {
			//DrawUtils::drawText(DrawUtils::worldToScreen(*corners[n]), &std::to_string(n + 1), MC_Color(1.f, 1.f, 1.f));
			//DrawUtils::setColor(1.f, 0.f, 0.f, 1.f);
			//if (g_Data.getLocalPlayer()->region->getBlock(vec3_ti(corners[n]->x, corners[n]->y - 0.5f, corners[n]->z))->toLegacy()->blockId != 0) {
			//DrawUtils::drawBox(vec3_t(floor(corners[n]->x), floor(corners[n]->y - 0.5f), floor(corners[n]->z)), g_Data.getLocalPlayer()->region->getBlock(vec3_ti(corners[n]->x, corners[n]->y - 0.5f, corners[n]->z))->toLegacy()->aabb.upper, 2.f);
			//DrawUtils::drawBox(vec3_t(floor(corners[n]->x), floor(corners[n]->y - 0.5f), floor(corners[n]->z)), vec3_t(floor(corners[n]->x) + 1.f, floor(corners[n]->y - 0.5f) + 1.f, floor(corners[n]->z) + 1.f), 2.f);
			n++;

			if ((floor(corner->x) == floor(block->x)) && (floor(corner->y) == floor(block->y)) && (floor(corner->z) == floor(block->z))) {
				//	DrawUtils::setColor(1.f, 0.f, 0.f, 0.5f);
				//	DrawUtils::drawBox(block->floor(), {floor(block->x) + 1.f, floor(block->y) + 1.f, floor(block->z) + 1.f}, 0.7f, false);
				return true;
				//	}
			}
		}

	return false;
}

bool checkSurrounded21(C_Entity* ent) {
	vec3_t entPos = ent->getPos()->floor();
	entPos.y -= 1;

	std::vector<vec3_ti*> blockChecks;
	blockChecks.clear();

	if (blockChecks.empty()) {
		blockChecks.push_back(new vec3_ti(entPos.x, entPos.y, entPos.z + 1));
		blockChecks.push_back(new vec3_ti(entPos.x, entPos.y, entPos.z - 1));
		blockChecks.push_back(new vec3_ti(entPos.x + 1, entPos.y, entPos.z));
		blockChecks.push_back(new vec3_ti(entPos.x - 1, entPos.y, entPos.z));
	}

	for (auto blocks : blockChecks) {
		if (!checkTargCollision12(&blocks->toVec3t(), ent)) {
			return false;
		}
	}
	return true;
}


std::vector<vec3_t*> getGucciPlacement21(C_Entity* ent) {
	std::vector<vec3_t> SurChecker = {
		vec3_t(1, 0, 0),
		vec3_t(0, 0, 1),
		vec3_t(-1, 0, 0),
		vec3_t(0, 0, -1),
		vec3_t(0, -1, 0),
	};

	vec3_t entPos = ent->getPos()->floor();
		//for (int y = entPos.y - 2; y <= entPos.y + 0; y++) {
	int y;

	bool sendBack = false;

	for (auto checkThis : SurChecker) {
		auto playerOn = targetList7[0]->getPos();
		auto rndOffPlayerOn = playerOn->floor();
		rndOffPlayerOn.y -= 1.f;

		auto calcSides = rndOffPlayerOn.add(checkThis);
		if (g_Data.getLocalPlayer()->region->getBlock(vec3_ti(calcSides))->toLegacy()->blockId == 0) {
			sendBack = true;
		}
	}
	if (!sendBack) {
		y = entPos.y;
	} else {
		y = entPos.y -= 1;
	}
			std::vector<vec3_t*> finalBlocks;
			std::vector<vec3_ti*> blockChecks;
			blockChecks.clear();
			finalBlocks.clear();
			if (blockChecks.empty()) {
				blockChecks.push_back(new vec3_ti(entPos.x, entPos.y, entPos.z + 1));
				blockChecks.push_back(new vec3_ti(entPos.x, entPos.y, entPos.z - 1));
				blockChecks.push_back(new vec3_ti(entPos.x + 1, entPos.y, entPos.z));
				blockChecks.push_back(new vec3_ti(entPos.x - 1, entPos.y, entPos.z));
			}

			for (auto blocks : blockChecks) {
				auto blkID = g_Data.getLocalPlayer()->region->getBlock(*blocks)->toLegacy()->blockId;
				auto blkIDL = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blocks->x, blocks->y - 1, blocks->z))->toLegacy()->blockId;
				auto blkIDLL = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blocks->x, blocks->y - 2, blocks->z))->toLegacy()->blockId;
				auto blkIDLLL = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blocks->x, blocks->y - 3, blocks->z))->toLegacy()->blockId;
				auto blkIDLLLL = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blocks->x, blocks->y - 4, blocks->z))->toLegacy()->blockId;
				auto blkIDLLLLL = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blocks->x, y, blocks->z))->toLegacy()->blockId;

				if (!checkTargCollision12(&blocks->toVec3t(), ent)) {  //very efficient coding here

					if (blkID == 0 && blkIDL == 0 && (blkIDLL == 49 || blkIDLL == 7)) {
						finalBlocks.push_back(new vec3_t(blocks->x, blocks->y - 1, blocks->z));
					} else if (blkID == 0 && (blkIDL == 7 || blkIDL == 49)) {
						finalBlocks.push_back(new vec3_t(blocks->x, blocks->y, blocks->z));
					}

					/*if (blkID == 0 && blkIDL == 0 && (blkIDLL == 49 || blkIDLL == 7)) {
				finalBlocks.push_back(new vec3_t(blocks->x, blocks->y - 1, blocks->z));
			} else if (blkID == 0 && (blkIDL == 7 || blkIDL == 49)) {
				finalBlocks.push_back(new vec3_t(blocks->x, blocks->y, blocks->z));
			} else if (blkID == 0 && blkIDL == 0 && blkIDLL == 0 && (blkIDLLL == 7 || blkIDLLL == 49)) {
				finalBlocks.push_back(new vec3_t(blocks->x, blocks->y - 2, blocks->z));
			} else if (blkID == 0 && blkIDL == 0 && blkIDLL == 0 && & blkIDLLL == 0 && (blkIDLLLL == 7 || blkIDLLLL == 49)) {
				finalBlocks.push_back(new vec3_t(blocks->x, blocks->y - 3, blocks->z));
			}*/
				} else {
					for (int x = entPos.x - 2; x <= entPos.x + 2; x++) {
						for (int z = entPos.z - 2; z <= entPos.z + 2; z++) {
							int y = entPos.y;
							auto blk = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(x, y, z))->toLegacy()->blockId;
							auto lBlk = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(x, y - 1, z))->toLegacy()->blockId;

							if ((blk == 0 && (lBlk == 49 || lBlk == 7))) {
								finalBlocks.push_back(new vec3_t(x, y, z));
							}
						}
					}
				}
			}
			return finalBlocks;
		}
    
bool hasPlacedA = false;

void K3SReCrystal::onEnable() {
	K3SRC = 0;
	hasPlacedA = false;
}
vec3_t espPosLowerp;
vec3_t espPosUpperp;
vec3_t crystalPosp;
std::vector<vec3_t*> placeArrp;
std::vector<vec3_t*> hitArrp;
void K3SReCrystal::onTick(C_GameMode* gm) {
	if (g_Data.getLocalPlayer() == nullptr) return;
	if (isClick && !g_Data.isRightClickDown()) return;

	if (g_Data.getLocalPlayer()->getSelectedItemId() == 259) return;

	targetList7.clear();

	g_Data.forEachEntity(findEntityK3R);
	hitArrp.clear();
	placeArrp.clear();

	if (autoplace)
		if ((K3SRC >= this->delay) && !(targetList7.empty())) {
			K3SRC = 0;
				std::vector<vec3_t*> gucciPositions = getGucciPlacement21(targetList7[0]);

				auto supplies = g_Data.getLocalPlayer()->getSupplies();
				auto inv = supplies->inventory;

				//615 = normal id for crystal || 616 = crystal id for nukkit servers
				if (!gucciPositions.empty())
					if (g_Data.getLocalPlayer()->getSelectedItemId() == 629 || g_Data.getLocalPlayer()->getSelectedItemId() == 616) {
						placeArrp.clear();
						for (auto place : gucciPositions) {
							if (hasPlacedA && !doMultiple) break;
							if (targetList7.empty()) return;
							if (!checkSurrounded21(targetList7[0])) {
								gm->buildBlock(&vec3_ti(place->x, place->y - 1, place->z), 1);
								placeArrp.push_back(new vec3_t(place->x, place->y - 1, place->z));
							} else {
								gm->buildBlock(&vec3_ti(place->x, place->y, place->z), 1);
								placeArrp.push_back(new vec3_t(place->x, place->y, place->z));
							}

							hasPlacedA = true;
						}
					
				gucciPositions.clear();
			}
		} else if (!targetList7.empty()) {
			K3SRC++;
		}

	//if (K3SRC2 >= 20) {
	//		hasPlaced = false;
	//}

	g_Data.forEachEntity([](C_Entity* ent, bool b) {
		if (targetList7.empty()) return;
		int id = ent->getEntityTypeId();
		int range = moduleMgr->getModule<K3SReCrystal>()->range;
		if (id == 71 && g_Data.getLocalPlayer()->getPos()->dist(*ent->getPos()) <= range) {
			g_Data.getCGameMode()->attack(ent);
			hasPlacedA = false;

			if (!moduleMgr->getModule<NoSwing>()->isEnabled())
				g_Data.getLocalPlayer()->swingArm();
		}
	});  //*/
}

void K3SReCrystal::onDisable() {
	K3SRC = 0;
	hasPlacedA = false;
}
void K3SReCrystal::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
	if (localPlayer != nullptr && GameData::canUseMoveKeys()) {
		if (!placeArrp.empty()) {
			for (auto postt : placeArrp) {
				DrawUtils::setColor(1.0f, 0.0f, 0.0f, 1.f);
				DrawUtils::drawBox(postt->floor(), vec3_t(floor(postt->x) + 1.f, floor(postt->y) + 1.f, floor(postt->z) + 1.f), 1.f, true);
			}
		}
		if (!hitArrp.empty()) {
			for (auto postt : hitArrp) {
				DrawUtils::setColor(1.0f, 1.0f, 0.0f, 1.f);
				DrawUtils::drawBox(postt->floor(), vec3_t(floor(postt->x) + 1.f, floor(postt->y) + 1.f, floor(postt->z) + 1.f), 1.f, true);
			}
		}  //*/
	}
}
