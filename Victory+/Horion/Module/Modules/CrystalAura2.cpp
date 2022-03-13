#include "../../../Utils/Logger.h"
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "CrystalAura2.h"

CrystalAura2::CrystalAura2() : IModule(0x0, Category::COMBAT, " ") {
	//mode = SettingEnum(this)
	/*		   .addEntry(EnumEntry("Vanilla", 1))
			   .addEntry(EnumEntry("Java", 2));*/
	//registerEnumSetting("Mode", &mode, 0);

	registerBoolSetting("autoplace", &autoplace, autoplace);
	//registerBoolSetting("Swap", &blockSwap, blockSwap);
	//registerBoolSetting("LockY", &yLock, yLock);
	registerIntSetting("delay", &delay, delay, 0, 20);
	//registerBoolSetting("onClick", &isClick, isClick);
	this->registerIntSetting("range", &this->range, this->range, 3, 15);
}

int crystalDelay12 = 0;
int crystalDelay22 = 0;
int crystalDelay32 = 0;

CrystalAura2::~CrystalAura2() {
}

const char* CrystalAura2::getModName() {
     return " Vanilla";
}

const char* CrystalAura2::getModuleName() {
	return ("CrystalAura");
}

static std::vector<C_Entity*> targetList7;

void findEntity31(C_Entity* currentEntity, bool isRegularEntity) {
	static auto CrystalAura2Mod = moduleMgr->getModule<CrystalAura2>();

	if (currentEntity == nullptr)
		return;

	if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 71)  // crystal
		return;

	if (currentEntity->getNameTag()->getText() == "KaeruKing188")  
		return;

	if (currentEntity->getNameTag()->getText() == "MugichaXD")  
		return;
	
	if (currentEntity->getNameTag()->getText() == "kamisugiru")
		return;


	if (currentEntity->getNameTag()->getText() == "FireXX0001")  //‚¦‚É‚®‚ÜenigmaDev!!!!
		return;


//‚Î‚®‚Å‚·‚ä‚é‚µ‚Ä()
	if (currentEntity == g_Data.getLocalPlayer())  // Skip Local player
		return;

	//if (!g_Data.getLocalPlayer()->canAttack(currentEntity, false))
	//return;

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

	//how hard is it to play fair? add back the badman check if its hard

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < CrystalAura2Mod->range) {
		targetList7.push_back(currentEntity);
	}
}

bool checkTargCollisions(vec3_t* block, C_Entity* ent) {
	std::vector<vec3_t*> corners;
	corners.clear();

	corners.push_back(new vec3_t(ent->aabb.lower.x, ent->aabb.lower.y, ent->aabb.lower.z));
	corners.push_back(new vec3_t(ent->aabb.lower.x, ent->aabb.lower.y, ent->aabb.upper.z));
	corners.push_back(new vec3_t(ent->aabb.upper.x, ent->aabb.lower.y, ent->aabb.upper.z));
	corners.push_back(new vec3_t(ent->aabb.upper.x, ent->aabb.lower.y, ent->aabb.lower.z));
	int n = 0;
	if (!corners.empty())
		for (auto corner : corners) {
			n++;
			if ((floor(corner->x) == floor(block->x)) && (floor(corner->y) == floor(block->y)) && (floor(corner->z) == floor(block->z))) {
				return true;
			}
		}

	return false;
}

bool checkSurrounded2s(C_Entity* ent) {
	vec3_t entPos = ent->getPos()->floor();
	entPos.y;

	std::vector<vec3_ti*> blockChecks;
	blockChecks.clear();

	if (blockChecks.empty()) {
		blockChecks.push_back(new vec3_ti(entPos.x, entPos.y, entPos.z + 1));
		blockChecks.push_back(new vec3_ti(entPos.x, entPos.y, entPos.z - 1));
		blockChecks.push_back(new vec3_ti(entPos.x + 1, entPos.y, entPos.z));
		blockChecks.push_back(new vec3_ti(entPos.x - 1, entPos.y, entPos.z));
	}

	for (auto blocks : blockChecks) {
		if (!checkTargCollisions(&blocks->toVec3t(), ent)) {
			return false;
		}
	}
	return true;
}

std::vector<vec3_t*> getGucciPlacement2s(C_Entity* ent) {
	vec3_t entPos = ent->getPos()->floor();
	entPos.y -= 1;
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
		auto blkIDL2 = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blocks->x, blocks->y + 1, blocks->z + 1))->toLegacy()->blockId;
		auto blkIDL = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blocks->x, blocks->y - 1, blocks->z))->toLegacy()->blockId;
		auto blkIDLL = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blocks->x, blocks->y - 2, blocks->z))->toLegacy()->blockId;
		auto blkIDLLL = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blocks->x, blocks->y - 3, blocks->z))->toLegacy()->blockId;
		auto blkIDLLLL = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blocks->x, blocks->y - 4, blocks->z))->toLegacy()->blockId;

		if (!checkTargCollisions(&blocks->toVec3t(), ent)) {  //very efficient coding here

			if (blkID == 0 && blkIDL == 0 && (blkIDLL == 49 || blkIDLL == 7) && (blkIDL2 == 7 || blkIDL2 == 49)) {
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
					for (int y = entPos.y - 2; y <= entPos.y + 2; y++) {
						auto blk = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(x, y, z))->toLegacy()->blockId;
						auto lBlk = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(x, y - 1, z))->toLegacy()->blockId;

						//if ((blk == 0 && (lBlk == 49 || lBlk == 7))) {
						if (!(blk == 7 || blk == 49)) {
							finalBlocks.push_back(new vec3_t(x, y, z));
						}
						//						finalBlocks.push_back(new vec3_t(x, y - 1, z));
						//						finalBlocks.push_back(new vec3_t(x, y + 1, z));
						//}
						if ((blk == 7 || blk == 49)) {
							finalBlocks.push_back(new vec3_t(x, y + 1, z));
						}
					}
				}
			}
		}
	}
	return finalBlocks;
}

bool hasPlaced2 = false;
void CrystalAura2::onEnable() {
	crystalDelay12 = 0;
	hasPlaced2 = false;
}
bool iFuckedUp22 = false;
int tDelay22 = 0;
vec3_t espPosLower2;
vec3_t espPosUpper2;
vec3_t crystalPos2;
std::vector<vec3_t*> placeArr2;
std::vector<vec3_t*> hitArr2;
void CrystalAura2::onTick(C_GameMode* gm) {

	if (g_Data.getLocalPlayer() == nullptr) return;
	if (isClick && !g_Data.isRightClickDown()) return;

	//if (g_Data.getLocalPlayer()->getSelectedItemId() == 259) return;

	targetList7.clear();

	g_Data.forEachEntity(findEntity31);
	hitArr2.clear();
	placeArr2.clear();

	if (autoplace)
		if ((crystalDelay12 >= this->delay) && !(targetList7.empty())) {
			crystalDelay12 = 0;
			if (!checkSurrounded2s(targetList7[0])) {
				std::vector<vec3_t*> gucciPositions = getGucciPlacement2s(targetList7[0]);

				auto supplies = g_Data.getLocalPlayer()->getSupplies();
				auto inv = supplies->inventory;

				//615 = normal id for crystal || 616 = crystal id for nukkit servers
				/*
				crystal = 615;
				crystal = 616;
				crystal = 639;
				crystal = 629;
*/
				if (!gucciPositions.empty())
					if (g_Data.getLocalPlayer()->getSelectedItemId() == 615 || g_Data.getLocalPlayer()->getSelectedItemId() == 616 || g_Data.getLocalPlayer()->getSelectedItemId() == 629 || g_Data.getLocalPlayer()->getSelectedItemId() == 639) {
						placeArr2.clear();
						for (auto place : gucciPositions) {
							if (hasPlaced2 && !doMultiple) break;
							if (targetList7.empty()) return;
							/*gm->buildBlock(&vec3_ti(place->x, place->y + 2, place->z), 1);
							gm->buildBlock(&vec3_ti(place->x, place->y + 3, place->z), 1);
							gm->buildBlock(&vec3_ti(place->x, place->y + 4, place->z), 1);
							gm->buildBlock(&vec3_ti(place->x, place->y + 1, place->z), 1);
							gm->buildBlock(&vec3_ti(place->x, place->y, place->z), 1);
							gm->buildBlock(&vec3_ti(place->x, place->y - 1, place->z), 1);
							gm->buildBlock(&vec3_ti(place->x, place->y, place->z), 1);
							gm->buildBlock(&vec3_ti(place->x, place->y - 1, place->z), 1);
							gm->buildBlock(&vec3_ti(place->x, place->y, place->z), 1);
							gm->buildBlock(&vec3_ti(place->x, place->y - 1, place->z), 1);
							gm->buildBlock(&vec3_ti(place->x, place->y, place->z), 1);*/
							gm->buildBlock(&vec3_ti(place->x, place->y - 1, place->z), 1);
						//	gm->buildBlock(&vec3_ti(place->x, place->y, place->z), 1);
							/* gm->buildBlock(&vec3_ti(place->x, place->y - 1, place->z), 1);
							gm->buildBlock(&vec3_ti(place->x, place->y - 2, place->z), 1);
							gm->buildBlock(&vec3_ti(place->x, place->y - 3, place->z), 1);
							gm->buildBlock(&vec3_ti(place->x, place->y - 4, place->z), 1);
							*/
							placeArr2.push_back(new vec3_t(place->x, place->y - 1, place->z));

							hasPlaced2 = true;
						}
					}

				gucciPositions.clear();
			}
		} else if (!targetList7.empty()) {
			crystalDelay12++;
		}

	if (this->delay == 1 && blockSwap) {
		prevSlot = supplies->selectedHotbarSlot;
		FinishSelect = true;
		for (int n = 0; n < 9; n++) {
			C_ItemStack* stack = inv->getItemStack(n);
			if (stack->item != nullptr) {
				if (stack->getItem()->itemId == 629) {
					if (prevSlot != n)
						supplies->selectedHotbarSlot = n;
					return;
				}
			}
		}
		return;
	}

	if (FinishSelect) {
		supplies->selectedHotbarSlot = prevSlot;
		FinishSelect = false;
		return;
	}
	//if (crystalDelay2 >= 20) {
	//		hasPlaced = false;
	//}

	g_Data.forEachEntity([](C_Entity* ent, bool b) {
		if (targetList7.empty()) return;
		int id = ent->getEntityTypeId();
		int range = moduleMgr->getModule<CrystalAura2>()->range;
		if (id == 71 && g_Data.getLocalPlayer()->getPos()->dist(*ent->getPos()) <= range) {
			g_Data.getCGameMode()->attack(ent);

			hasPlaced2 = false;

			if (!moduleMgr->getModule<NoSwing>()->isEnabled())
				g_Data.getLocalPlayer()->swingArm();
		}
	});  //*/
}

void CrystalAura2::onDisable() {
	crystalDelay12 = 0;
	hasPlaced2 = false;
}
/*
* 
* //this right here is stuff i was working on but havent been bothered to finish*/

//*/

void CrystalAura2::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
	if (localPlayer != nullptr && GameData::canUseMoveKeys()) {
		if (!placeArr2.empty()) {
			for (auto postt : placeArr2) {
				if (hasPlaced2) {
					DrawUtils::setColor(1.0f, 0.0f, 0.0f, 1.f);
				}

				if (!hasPlaced2) {
					DrawUtils::setColor(0.0f, 1.0f, 0.0f, 1.f);
				}

				DrawUtils::drawBox(postt->floor(), vec3_t(floor(postt->x) + 1.f, floor(postt->y) + 1.f, floor(postt->z) + 1.f), 0.2f, false);
			}
		}
		if (!hitArr2.empty()) {
			for (auto postt : hitArr2) {
				if (hasPlaced2) {
				DrawUtils::setColor(1.0f, 0.0f, 0.0f, 1.f);
				}

				if (!hasPlaced2) {
					DrawUtils::setColor(0.0f, 1.0f, 0.0f, 1.f);
				}

				DrawUtils::drawBox(postt->floor(), vec3_t(floor(postt->x) + 1.f, floor(postt->y) + 1.f, floor(postt->z) + 1.f), 0.2f, false);
			}
		}  //*/
	}
}


