/*#include "CAtwo.h"

CAtwo::CAtwo() : IModule(VK_NUMPAD0, Category::COMBAT, "Destroys nearby Crystals") {
	registerIntSetting("Range", &this->range, this->range, 1, 10);
	registerIntSetting("Crystal range", &this->cRange, this->cRange, 1, 15);
	registerIntSetting("Place range", &this->eRange, this->eRange, 1, 5);
	registerIntSetting("Player range", &this->pRange, this->pRange, 1, 10);
	registerBoolSetting("Auto select", &this->AutoSelect, this->AutoSelect);
	registerBoolSetting("Autoplace", &this->autoplace, this->autoplace);
	registerBoolSetting("Enhance place", &this->pEnhanced, this->pEnhanced);
	registerBoolSetting("Enhance destroy", &this->dEnhanced, this->dEnhanced);
	registerBoolSetting("preview", &this->Preview, this->Preview);
	delay = 0;
}
CAtwo::~CAtwo() {
}
const char* CAtwo::getModuleName() {
	return ("OldAutoCrystal");
}

static std::vector<C_Entity*> targetList;

void CAtwo::onEnable() {
	targetList.clear();
	this->delay = 0;
}

static std::vector<C_Entity*> targetList7;

void findEntity3(C_Entity* currentEntity, bool isRegularEntity) {
	static auto CrystalAuraWTAMod = moduleMgr->getModule<CAtwo>();

	if (currentEntity == nullptr)
		return;

	if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 71)  // crystal
		return;

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

	if (dist < CrystalAuraWTAMod->range) {
		targetList7.push_back(currentEntity);
	}
}

void CrystalAura::DestroyC(C_Entity* ent21, int range) {
	if (g_Data.getLocalPlayer()->getPos()->dist(*ent21->getPos()) < range && !dEnhanced) {
		g_Data.getCGameMode()->attack(ent21);
		g_Data.getLocalPlayer()->swingArm();
	} else if (dEnhanced) {
		for (auto& i : targetList)
			if (ent21->getPos()->dist(*i->getPos()) < range) {
				g_Data.getCGameMode()->attack(ent21);
				g_Data.getLocalPlayer()->swingArm();
				return;
			}
	}
}
bool space2 = true;
vec3_t _pos21;
bool CanPlaceC(vec3_ti* pos21) {
	space2 = true;
	_pos21 = pos21->toVec3t();
	g_Data.forEachEntity([](C_Entity* ent2, bool b) {
		//if (!space)
			//return;
		if (ent2->aabb.intersects(AABB(_pos21, _pos21.add(1.f))))
			space2 = false;
	});
	return space2;
}

void CrystalAura::CPlace(C_GameMode* gm, vec3_t* pos21) {
	if (!pEnhanced) {
#pragma warning(push)
#pragma warning(disable : 4244)
		vec3_ti blockPos = vec3_ti(pos21->x, pos21->y, pos21->z);
		vec3_ti upperBlockPos = vec3_ti(pos21->x, pos21->y + 1, pos21->z);
#pragma warning(pop)
		C_Block* block = gm->player->region->getBlock(blockPos);
		C_Block* upperBlock = gm->player->region->getBlock(upperBlockPos);
		gm->buildBlock(&blockPos, g_Data.getClientInstance()->getPointerStruct()->blockSide);
		return;
	}
	vec3_ti bestPos;
	bool ValidPos = false;
	for (int x = (int)pos21->x - eRange; x < pos21->x + eRange; x++) {
		for (int z = (int)pos21->z - eRange; z < pos21->z + eRange; z++) {
			for (int y = (int)pos21->y - eRange; y < pos21->y + eRange; y++) {
				vec3_ti blockPos = vec3_ti(x, y, z + 1);
				vec3_ti upperBlockPos = vec3_ti(x, y + 1, z);
				vec3_ti sitaBlockPos = vec3_ti(x, y - 1, z);
				C_Block* block = gm->player->region->getBlock(blockPos);
				C_Block* upperBlock = gm->player->region->getBlock(upperBlockPos);
				C_Block* sitaBlock = gm->player->region->getBlock(sitaBlockPos);

				if (block != nullptr) {
					auto blockId = block->toLegacy()->blockId;
					auto upperBlockId = upperBlock->toLegacy()->blockId;
					auto sitaBlockId = sitaBlock->toLegacy()->blockId;
					if ((blockId == 49 || blockId == 7) && CanPlaceC(&blockPos)) {  //Check for awailable block
						if (!ValidPos) {
							ValidPos = true;
							bestPos = blockPos;

						} else if (blockPos.toVec3t().dist(*pos21) < bestPos.toVec3t().dist(*pos21)) {
							bestPos = blockPos;
						}
					}
				}
			}
		}
	}

	if (ValidPos)
		gm->buildBlock(&bestPos, 0);
}
*/