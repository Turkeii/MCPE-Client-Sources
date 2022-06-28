#include "AutoCrystalRewrite.h"

AutoCrystalRewrite::AutoCrystalRewrite() : IModule(VK_NUMPAD0, Category::COMBAT, "Destroys nearby Crystals") {
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
AutoCrystalRewrite::~AutoCrystalRewrite() {
}
const char* AutoCrystalRewrite::getModuleName() {
	return ("AutoCrystalRewrite");
}

static std::vector<C_Entity*> targetList;

void AutoCrystalRewrite::onEnable() {
	targetList.clear();
	this->delay = 0;
}

bool CryfindEntity(C_Entity* curEnt, bool isRegularEntity) {
	if (curEnt == nullptr) return false;
	if (curEnt == g_Data.getLocalPlayer()) return false;  // Skip Local player
	if (!curEnt->isAlive()) return false;
	if (!g_Data.getLocalPlayer()->isAlive()) return false;
	if (curEnt->getEntityTypeId() == 71) return false;  // endcrystal
	if (curEnt->getEntityTypeId() == 66) return false;  // falling block
	if (curEnt->getEntityTypeId() == 64) return false;  // item
	if (curEnt->getEntityTypeId() == 69) return false;  // xp orb
	if (!Target::isValidTarget(curEnt)) return false;

	float dist = (*curEnt->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
	if (dist <= moduleMgr->getModule<AutoCrystalRewrite>()->pRange) {
		targetList.push_back(curEnt);
		return true;
	}
	return false;
}

bool AutoCrystalRewrite::CanPlaceC(vec3_ti* pos) {
	space = true;
	_pos = pos->toVec3t();
	g_Data.forEachEntity([](C_Entity* ent, bool b) {
		auto modd = moduleMgr->getModule<AutoCrystalRewrite>();
		if (!modd->space)
			return;
		if (ent->aabb.intersects(AABB(modd->_pos, modd->_pos.add(1.f))))
			modd->space = false;
	});
	return space;
}

void AutoCrystalRewrite::CPlace(C_GameMode* gm, vec3_t* pos) {
	if (!pEnhanced) {
#pragma warning(push)
#pragma warning(disable : 4244)
		vec3_ti blockPos = vec3_ti(pos->x, pos->y, pos->z);
		vec3_ti upperBlockPos = vec3_ti(pos->x, pos->y + 1, pos->z);
#pragma warning(pop)
		C_Block* block = gm->player->region->getBlock(blockPos);
		C_Block* upperBlock = gm->player->region->getBlock(upperBlockPos);
		bool gay = true;
		g_Data.rightclickCount++;
		gm->buildBlock(&blockPos, g_Data.getLocalPlayer()->pointingStruct->blockSide, true);
		return;
	}
	vec3_ti bestPos;
	bool ValidPos = false;
	for (int x = (int)pos->x - eRange; x < pos->x + eRange; x++) {
		for (int z = (int)pos->z - eRange; z < pos->z + eRange; z++) {
			for (int y = (int)pos->y - eRange; y < pos->y + eRange; y++) {
				vec3_ti blockPos = vec3_ti(x, y, z);
				vec3_ti upperBlockPos = vec3_ti(x, y + 1, z);
				C_Block* block = gm->player->region->getBlock(blockPos);
				C_Block* upperBlock = gm->player->region->getBlock(upperBlockPos);
				if (block != nullptr) {
					auto blockId = block->toLegacy()->blockId;
					auto upperBlockId = upperBlock->toLegacy()->blockId;
					if ((blockId == 49 || blockId == 7) && upperBlockId == 0 && CanPlaceC(&blockPos)) {  // Check for awailable block
						if (!ValidPos) {
							ValidPos = true;
							bestPos = blockPos;
						} else if (blockPos.toVec3t().dist(*pos) < bestPos.toVec3t().dist(*pos)) {
							bestPos = blockPos;
						}
					}
				}
			}
		}
	}
	if (ValidPos) {
		bool gay = true;
		g_Data.rightclickCount++;
		gm->buildBlock(&bestPos, 0, true);
	}
}

void AutoCrystalRewrite::DestroyC(C_Entity* ent, int range) {
	if (g_Data.getLocalPlayer()->getPos()->dist(*ent->getPos()) < range && !dEnhanced) {
		g_Data.getCGameMode()->attack(ent);
		g_Data.getLocalPlayer()->swingArm();
		rots = *ent->getPos();
	} else if (dEnhanced) {
		for (auto& i : targetList)
			if (ent->getPos()->dist(*i->getPos()) < range) {
				g_Data.getCGameMode()->attack(ent);
				g_Data.getLocalPlayer()->swingArm();
				return;
				rots = *i->getPos();
			}
	}
}
float animYaw69 = 0.f;

void AutoCrystalRewrite::onPlayerTick(C_Player* plr) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(rots).normAngles();
	if (animYaw69 > angle.y)
		animYaw69 -= ((animYaw69 - angle.y) / 2);
	else if (animYaw69 < angle.y)
		animYaw69 += ((angle.y - animYaw69) / 2);

		//plr->bodyYaw = animYaw69;
		//plr->yawUnused1 = animYaw69;
		plr->pitch = -90;
}

void AutoCrystalRewrite::onLevelRender() {
	if (shouldChange) {
		shouldChange = false;
	}
	this->delay++;
	if (supplies == nullptr)
		supplies = g_Data.getLocalPlayer()->getSupplies();
	if (inv == nullptr)
		inv = supplies->inventory;
	targetList.clear();
	g_Data.forEachEntity(CryfindEntity);
	if (this->delay == 0) {
		// place block around players?
		return;
	}

	if (this->delay == 1 && AutoSelect) {
		prevSlot = supplies->selectedHotbarSlot;
		FinishSelect = true;
		for (int n = 0; n < 9; n++) {
			C_ItemStack* stack = inv->getItemStack(n);
			if (stack->item != nullptr) {
				if (stack->getItem()->itemId == 637) {
					if (prevSlot != n)
						supplies->selectedHotbarSlot = n;
					return;
				}
			}
		}
		return;
	}
	if (this->delay == 2) {
		if (autoplace && g_Data.getLocalPlayer()->getSelectedItemId() == 637) {  // endcrystal
			if (pEnhanced)
				for (auto& i : targetList)
					CPlace(g_Data.getCGameMode(), i->getPos());
			else {
				auto ptr = g_Data.getLocalPlayer()->pointingStruct;
				if (ptr->getEntity() == nullptr && ptr->rayHitType == 0)
					CPlace(g_Data.getCGameMode(), &ptr->block.toFloatVector());
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
			if (moduleMgr->getModule<AutoCrystalRewrite>()->dEnhanced)
				range = moduleMgr->getModule<AutoCrystalRewrite>()->cRange;
			else
				range = moduleMgr->getModule<AutoCrystalRewrite>()->range;
			moduleMgr->getModule<AutoCrystalRewrite>()->DestroyC(ent, range);
		});
		return;
	}
	if (this->delay >= 5) {
		this->delay = 0;
		return;
	}
}

void AutoCrystalRewrite::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	if (!Preview || (!pEnhanced && autoplace) ||
		g_Data.getClientInstance() == nullptr ||
		g_Data.getPtrLocalPlayer() == nullptr ||
		g_Data.getLocalPlayer() == nullptr)
		return;

	auto ptr = g_Data.getLocalPlayer()->pointingStruct;
	if (ptr != nullptr)
		if (!(ptr->getEntity() != nullptr && ptr->rayHitType != 0))
			if (g_Data.getLocalPlayer()->region->getBlock(ptr->block)->toLegacy()->blockId == 49 ||
				g_Data.getLocalPlayer()->region->getBlock(ptr->block)->toLegacy()->blockId == 7) {
				DrawUtils::setColor(.75f, .25f, .5f, 1.f);
				DrawUtils::drawBox(ptr->block.toVec3t().add(0.f, 1.5f, 0.f),
								   ptr->block.add(1).toVec3t().add(0.f, 1.5f, 0.f), .3f);
			}
}

void AutoCrystalRewrite::onDisable() {
	this->delay = 0;
}