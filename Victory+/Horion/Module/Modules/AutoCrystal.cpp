#include "AutoCrystal.h"

CrystalPlace::CrystalPlace() : IModule(VK_NUMPAD0, Category::COMBAT, "AutoCrystal By Kaeru!") {
	//registerBoolSetting("AuroraServerBypass", &this->ServerMode, this->ServerMode);
	registerIntSetting("Range", &this->range, this->range, 1, 10);
	//registerBoolSetting("Targethud", &this->targethud, this->targethud);
	registerBoolSetting("Autoplace", &this->autoplace, this->autoplace);
	registerBoolSetting("Enhance place", &this->pEnhanced, this->pEnhanced);
	registerBoolSetting("Enhance destroy", &this->dEnhanced, this->dEnhanced);
	//registerBoolSetting("preview", &this->Preview, this->Preview);
	delay = 0;
	Odelay = 0;
}
CrystalPlace::~CrystalPlace() {
}
const char* CrystalPlace::getModuleName() {
	return ("AutoCrystal");
}

static std::vector<C_Entity*> targetList;
static std::vector<C_Entity*> targetList2;

void CrystalPlace::onEnable() {
	targetList.clear();
	this->delay = 0;
	this->Odelay = 0;
}

void findEntity1AC(C_Entity* currentEntity1AC, bool isRegularEntity) {
	static auto killauraMod = moduleMgr->getModule<CrystalPlace>();

	if (currentEntity1AC == nullptr)
		return;

	if (currentEntity1AC == g_Data.getLocalPlayer())  // Skip Local player
		return;

	if (!g_Data.getLocalPlayer()->canAttack(currentEntity1AC, false))
		return;

	if (!g_Data.getLocalPlayer()->isAlive())
		return;

	if (!currentEntity1AC->isAlive())
		return;

	if (currentEntity1AC->getEntityTypeId() == 71)  // crystal
		return;

	if (currentEntity1AC->getEntityTypeId() == 69)  // xp
		return;
	if (killauraMod->isMobAura) {
		if (currentEntity1AC->getNameTag()->getTextLength() <= 1 && currentEntity1AC->getEntityTypeId() == 63)
			return;
		if (currentEntity1AC->width <= 0.01f || currentEntity1AC->height <= 0.01f)  // Don't hit this pesky antibot on 2b2e.org
			return;
		if (currentEntity1AC->getEntityTypeId() == 64)  // item
			return;

	} else {
		if (!Target::isValidTarget(currentEntity1AC))
			return;
	}

	float dist = (*currentEntity1AC->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < killauraMod->range) {
		targetList.push_back(currentEntity1AC);
	}
}
struct CompareTargetEnArray {
	bool operator()(C_Entity* lhs, C_Entity* rhs) {
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
	}
};

bool CfindEntity1(C_Entity* curEnt1, bool isRegularEntity1) {
	if (curEnt1 == nullptr) return false;
	if (curEnt1 == g_Data.getLocalPlayer()) return false;  // Skip Local player
	if (!curEnt1->isAlive()) return false;
	if (!g_Data.getLocalPlayer()->isAlive()) return false;
	if (curEnt1->getEntityTypeId() == 71) return false;  // endcrystal
	if (curEnt1->getEntityTypeId() == 66) return false;  // falling block
	if (curEnt1->getEntityTypeId() == 64) return false;  // item
	if (curEnt1->getEntityTypeId() == 69) return false;  // xp orb
	if (!Target::isValidTarget(curEnt1)) return false;

	float dist = (*curEnt1->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
	if (dist <= moduleMgr->getModule<CrystalPlace>()->range) {
		targetList.push_back(curEnt1);
		return true;
	}
	return false;
}

bool space1 = true;
vec3_t _pos1;
bool CanPlaceC1(vec3_ti* pos2) {
	space1 = true;
	_pos1 = pos2->toVec3t();
	g_Data.forEachEntity([](C_Entity* ent, bool b) {
		//if (!space1)
			//return;
		if (ent->aabb.intersects(AABB(_pos1, _pos1.add(1.f))))
			space1 = false;
	});
	return space1;
}

void CrystalPlace::CPlace(C_GameMode* gm, vec3_t* pos1) {
	if (!pEnhanced) {
#pragma warning(push)
#pragma warning(disable : 4244)
		vec3_ti blockPos = vec3_ti(pos1->x, pos1->y, pos1->z);
		vec3_ti upperBlockPos = vec3_ti(pos1->x, pos1->y + 1, pos1->z);
#pragma warning(pop)
		C_Block* block = gm->player->region->getBlock(blockPos);
		C_Block* upperBlock = gm->player->region->getBlock(upperBlockPos);
		gm->buildBlock(&blockPos, g_Data.getClientInstance()->getPointerStruct()->blockSide);
		return;
	}
	vec3_ti bestPos;
	vec3_ti bestPos2;
	vec3_ti bestPos3;
	vec3_ti bestPos4;
	vec3_ti bestPos12;
	vec3_ti bestPos22;
	vec3_ti bestPos32;
	vec3_ti bestPos42;
	this->Odelay++;

	bool ValidPos = false;
	for (int x = (int)pos1->x - range; x < pos1->x + range; x++) {
		for (int z = (int)pos1->z - range; z < pos1->z + range; z++) {
			for (int y = (int)pos1->y - range; y < pos1->y + range; y++) {
				vec3_ti blockPos1 = vec3_ti(x, y, z);

				vec3_ti blockPos = vec3_ti(x + 1, y, z);

				vec3_ti blockPos2 = vec3_ti(x, y, z + 1);

				vec3_ti blockPos3 = vec3_ti(x - 1, y, z);

				vec3_ti blockPos4 = vec3_ti(x, y, z - 1);

				vec3_ti blockPos12 = vec3_ti(x + 2, y, z);

				vec3_ti blockPos22 = vec3_ti(x, y, z + 2);

				vec3_ti blockPos32 = vec3_ti(x - 2, y, z);

				vec3_ti blockPos42 = vec3_ti(x, y, z - 2);

				vec3_ti upperBlockPos = vec3_ti(x, y + 1, z + 1);

				vec3_ti upperBlockPos2 = vec3_ti(x, y + 1, z - 1);

				vec3_ti upperBlockPos3 = vec3_ti(x + 1, y + 1, z);

				vec3_ti upperBlockPos4 = vec3_ti(x - 1, y + 1, z);

				vec3_ti lowBlockPos = vec3_ti(x, y + 1, z + 1);

				vec3_ti lowBlockPos2 = vec3_ti(x, y + 1, z - 1);

				vec3_ti lowBlockPos3 = vec3_ti(x + 1, y + 1, z);

				vec3_ti lowBlockPos4 = vec3_ti(x - 1, y + 1, z);

				C_Block* block = gm->player->region->getBlock(blockPos);
				C_Block* block1 = gm->player->region->getBlock(blockPos1);
				C_Block* block2 = gm->player->region->getBlock(blockPos2);
				C_Block* block3 = gm->player->region->getBlock(blockPos3);
				C_Block* block4 = gm->player->region->getBlock(blockPos4);
				C_Block* block12 = gm->player->region->getBlock(blockPos12);
				C_Block* block22 = gm->player->region->getBlock(blockPos22);
				C_Block* block32 = gm->player->region->getBlock(blockPos32);
				C_Block* block42 = gm->player->region->getBlock(blockPos42);

				C_Block* upperBlock = gm->player->region->getBlock(upperBlockPos);
				C_Block* upperBlock2 = gm->player->region->getBlock(upperBlockPos2);
				C_Block* upperBlock3 = gm->player->region->getBlock(upperBlockPos3);
				C_Block* upperBlock4 = gm->player->region->getBlock(upperBlockPos4);

				C_Block* lowBlock = gm->player->region->getBlock(lowBlockPos);
				C_Block* lowBlock2 = gm->player->region->getBlock(lowBlockPos2);
				C_Block* lowBlock3 = gm->player->region->getBlock(lowBlockPos3);
				C_Block* lowBlock4 = gm->player->region->getBlock(lowBlockPos4);

				if (block != nullptr || block2 != nullptr || block3 != nullptr || block4 != nullptr) {
					auto blockIds = block->toLegacy()->blockId;
					auto blockId = block->toLegacy()->blockId;
					auto blockId2 = block2->toLegacy()->blockId;
					auto blockId3 = block3->toLegacy()->blockId;
					auto blockId4 = block4->toLegacy()->blockId;
					auto blockId12 = block->toLegacy()->blockId;
					auto blockId22 = block2->toLegacy()->blockId;
					auto blockId32 = block3->toLegacy()->blockId;
					auto blockId42 = block4->toLegacy()->blockId;

					auto upperBlockId = upperBlock->toLegacy()->blockId;
					auto upperBlockId2 = upperBlock2->toLegacy()->blockId;
					auto upperBlockId3 = upperBlock3->toLegacy()->blockId;
					auto upperBlockId4 = upperBlock4->toLegacy()->blockId;

				    auto lowBlockId = lowBlock->toLegacy()->blockId;
					auto lowBlockId2 = lowBlock2->toLegacy()->blockId;
					auto lowBlockId3 = lowBlock3->toLegacy()->blockId;
					auto lowBlockId4 = lowBlock4->toLegacy()->blockId;

					if ((blockIds == 49 /* || blockId == 7 || blockId2 == 49 || blockId2 == 7 || blockId3 == 49 || blockId3 == 7 || blockId4 == 49 */|| blockIds == 7) /*&& upperBlockId == 0 || upperBlockId2 == 0 || upperBlockId3 == 0 || upperBlockId4 == 0  && CanPlaceC1(&blockPos)*/) {  //Check for awailable block
						if (!ValidPos) {
							ValidPos = true;
							bestPos = blockPos;
							bestPos2 = blockPos2;
							bestPos3 = blockPos3;
							bestPos4 = blockPos4;
							bestPos12 = blockPos12;
							bestPos22 = blockPos22;
							bestPos32 = blockPos32;
							bestPos42 = blockPos42;
						} else if (blockPos.toVec3t().dist(*pos1) < bestPos.toVec3t().dist(*pos1)) {
							bestPos = blockPos;
							bestPos2 = blockPos2;
							bestPos3 = blockPos3;
							bestPos4 = blockPos4;
							bestPos12 = blockPos12;
							bestPos22 = blockPos22;
							bestPos32 = blockPos32;
							bestPos42 = blockPos42;
						}
					}
				}
			}
		}
	}

	//if (ValidPos)
		if (Odelay == 0) {
			gm->buildBlock(&bestPos, 0);
			gm->buildBlock(&bestPos12, 0);
			}
			if (Odelay == 1) {
				gm->buildBlock(&bestPos2, 0);
				gm->buildBlock(&bestPos22, 0);
			}
			if (Odelay == 2) {
				gm->buildBlock(&bestPos3, 0);
				gm->buildBlock(&bestPos32, 0);
			}
			if (Odelay == 3) {
				gm->buildBlock(&bestPos4, 0);
				gm->buildBlock(&bestPos42, 0);
			}


		if (this->Odelay >= 4) {
			this->Odelay = 0;
			return;
		}
	}

void CrystalPlace::DestroyC(C_Entity* ent, int range) {
	if (g_Data.getLocalPlayer()->getPos()->dist(*ent->getPos()) < range && !dEnhanced) {
			g_Data.getCGameMode()->attack(ent);
			g_Data.getLocalPlayer()->swingArm();
	} else if (dEnhanced) {
		for (auto& i : targetList)
			if (ent->getPos()->dist(*i->getPos()) < range) {
				g_Data.getCGameMode()->attack(ent);
				g_Data.getLocalPlayer()->swingArm();
				return;
			}
	}
}

bool shouldChange1 = false;
void CrystalPlace::onTick(C_GameMode* gm) {
	if (targethud) {
		//Loop through all our players and retrieve their information
		targetList2.clear();

		g_Data.forEachEntity(findEntity1AC);

		Odelay2++;

		if (targethud)
			std::sort(targetList2.begin(), targetList2.end(), CompareTargetEnArray());

		// Attack all entitys in targetList
		if (isMulti) {
			for (auto& i : targetList2) {
				if (!(i->damageTime > 1 && hurttime)) {
					//g_Data.getLocalPlayer()->swing();
					//g_Data.getCGameMode()->attack(i);
					targethud2++;
				} else
					targethud2 = 0;
			}
		} else {
			if (!(targetList[0]->damageTime > 1 && hurttime)) {
				//g_Data.getLocalPlayer()->swing();
				//g_Data.getCGameMode()->attack(targetList[0]);
				targethud2++;
			} else
				targethud2 = 0;
		}
		Odelay2 = 0;
	}

	if (shouldChange1) {
		shouldChange1 = false;
	}
	this->delay++;
	if (supplies == nullptr)
		supplies = g_Data.getLocalPlayer()->getSupplies();
	if (inv == nullptr)
		inv = supplies->inventory;
	targetList.clear();
	g_Data.forEachEntity(CfindEntity1);
	if (this->delay == 1) {
		// place block around players?
		return;
	}

	if (this->delay == 1 && AutoSelect) {
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
	if (this->delay == 0) {
		if (autoplace && g_Data.getLocalPlayer()->getSelectedItemId() == 629) {  //endcrystal
			if (pEnhanced)
				for (auto& i : targetList)
					CPlace(gm, i->getPos());

			else {
				auto ptr = g_Data.getClientInstance()->getPointerStruct();
				if (ptr->getEntity() == nullptr && ptr->rayHitType == 0)
					CPlace(gm, &ptr->block.toFloatVector());
			}
		}
		return;
	}
	if (this->delay == 1) {
		if (autoplace && g_Data.getLocalPlayer()->getSelectedItemId() == 629) {  //endcrystal
			if (pEnhanced)
				for (auto& i : targetList)
					CPlace(gm, i->getPos());

			else {
				auto ptr = g_Data.getClientInstance()->getPointerStruct();
				if (ptr->getEntity() == nullptr && ptr->rayHitType == 0)
					CPlace(gm, &ptr->block.toFloatVector());
			}
		}
		return;
	}
	if (this->delay == 2) {
		if (autoplace && g_Data.getLocalPlayer()->getSelectedItemId() == 629) {  //endcrystal
			if (pEnhanced)
				for (auto& i : targetList)
					CPlace(gm, i->getPos());

			else {
				auto ptr = g_Data.getClientInstance()->getPointerStruct();
				if (ptr->getEntity() == nullptr && ptr->rayHitType == 0)
					CPlace(gm, &ptr->block.toFloatVector());
			}
		}
		return;
	}
	if (this->delay == 3 && FinishSelect) {
		supplies->selectedHotbarSlot = prevSlot;
		FinishSelect = false;
		return;
	}
	if (this->delay == 4) {
		g_Data.forEachEntity([](C_Entity* ent, bool b) {
			if (ent->getEntityTypeId() != 71)
				return;
			int range;
			if (moduleMgr->getModule<CrystalPlace>()->dEnhanced)
				range = moduleMgr->getModule<CrystalPlace>()->range;
			else
				range = moduleMgr->getModule<CrystalPlace>()->range;
			moduleMgr->getModule<CrystalPlace>()->DestroyC(ent, range);
		});
		return;
	}
	if (this->delay >= 4) {
		this->delay = 1;
		return;
	}
}

void CrystalPlace::onDisable() {
		this->delay = 1;
		targethud = 0;
	}