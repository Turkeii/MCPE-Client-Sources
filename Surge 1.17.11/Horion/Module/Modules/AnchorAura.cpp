#include "AnchorAura.h"
#include "../../../SDK/Tag.h"

AnchorAura::AnchorAura() : IModule(VK_NUMPAD0, Category::COMBAT, "Absolutly destoys kids") {
	registerIntSetting("Range", &this->range, this->range, 1, 7);
	registerIntSetting("Anchor range", &this->cRange, this->cRange, 1, 7);
	registerIntSetting("Place range", &this->eRange, this->eRange, 1, 7);
	registerIntSetting("Player range", &this->pRange, this->pRange, 1, 7);
	registerBoolSetting("Auto select", &this->AutoSelect, this->AutoSelect);
	registerBoolSetting("Autoplace", &this->autoplace, this->autoplace);
	registerBoolSetting("Force Anchor", &this->Give, this->Give);
	registerBoolSetting("Suicide", &this->dump, this->dump);
	registerBoolSetting("Enhance place", &this->pEnhanced, this->pEnhanced);
	registerBoolSetting("preview", &this->Preview, this->Preview);
	delay = 0;
}
AnchorAura::~AnchorAura() {
}
const char* AnchorAura::getModuleName() {
	return ("AnchorAura");
}

static std::vector<C_Entity*> targetList;

void AnchorAura::onEnable() {
	targetList.clear();
	this->delay = 0;
}

bool CfindEntityy(C_Entity* curEnt, bool isRegularEntity) {
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
	if (dist <= moduleMgr->getModule<AnchorAura>()->pRange) {
		targetList.push_back(curEnt);
		return true;
	}
	return false;
}

bool spacee = true;
vec3_t _poss;
bool CanPlaceCC(vec3_ti* pos) {
	spacee = true;
	return spacee;
}

void AnchorAura::CPlace(C_GameMode* gm, vec3_t* pos) {
	int i = 0;
	if (!pEnhanced) {
#pragma warning(push)
#pragma warning(disable : 4244)
		vec3_ti blockPos = vec3_ti(pos->x, pos->y, pos->z);
		vec3_ti upperBlockPos = vec3_ti(pos->x, pos->y + 1, pos->z);
#pragma warning(pop)
		C_Block* block = gm->player->region->getBlock(blockPos);
		C_Block* upperBlock = gm->player->region->getBlock(upperBlockPos);
		gm->buildBlock(&blockPos, g_Data.getClientInstance()->getPointerStruct()->blockSide);
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
					if (CanPlaceCC(&blockPos)) {  //Check for awailable block
						if (!ValidPos) {
							ValidPos = true;
							bestPos = blockPos;
						} else if (blockPos.toVec3t().dist(*pos) < bestPos.toVec3t().dist(*pos)) {
							bestPos = blockPos;
						}
					}
					if (dump) {
						g_Data.getCGameMode()->buildBlock(&blockPos, i);
						gm->buildBlock(&blockPos, 0);
					}
				}
			}
		}
	}
		C_Block* blocck = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(bestPos));
			vec3_ti blok(bestPos);
			if (ValidPos) {
				g_Data.getCGameMode()->buildBlock(&blok, i);
			} else {
				static std::vector<vec3_ti*> checklist;
				bool foundCandidate = false;
				if (checklist.empty()) {
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
					g_Data.getCGameMode()->buildBlock(&blok, i);
					return;
			}
		}

void AnchorAura::DestroyC(C_Entity* ent, int range) {
}

bool shouldChangee = false;
void AnchorAura::onLevelRender() {
	if (shouldChangee) {
		shouldChangee = false;
	}
	this->delay++;
	if (supplies == nullptr)
		supplies = g_Data.getLocalPlayer()->getSupplies();
	if (inv == nullptr)
		inv = supplies->inventory;
	targetList.clear();
	g_Data.forEachEntity(CfindEntityy);

	if (this->delay == 1) {
		if (Give) {
			C_ItemStack* yot = new C_ItemStack(***ItemRegistry::lookUpByName(std::make_unique<uintptr_t>().get(), std::make_unique<uintptr_t>().get(), TextHolder("respawn_anchor")), 64, 4);
			g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, nullptr, nullptr, yot, nullptr, 1, 507, 99999));
			g_Data.getLocalPlayer()->getSupplies()->inventory->addItemToFirstEmptySlot(yot);
		}
		if (AutoSelect){
		prevSlot = supplies->selectedHotbarSlot;
		FinishSelect = true;
		for (int n = 0; n < 9; n++) {
			C_ItemStack* stack = inv->getItemStack(n);
			if (stack->item != nullptr) {
				if (stack->getItem()->itemId == -272) {
					if (prevSlot != n)
						supplies->selectedHotbarSlot = n;
					return;
				}
			}
		}
		return;
	}
}
	if (this->delay == 2) {
	if (autoplace && g_Data.getLocalPlayer()->getSelectedItemId() == -272) {  //endcrystal
			if (pEnhanced)
				for (auto& i : targetList)
					CPlace(g_Data.getCGameMode(), i->getPos());
			else {
				auto ptr = g_Data.getClientInstance()->getPointerStruct();
				if (ptr->getEntity() == nullptr && ptr->rayHitType == 0)
					CPlace(g_Data.getCGameMode(), &ptr->block.toFloatVector());
			}
		}
	}
	if (this->delay == 3) {
		g_Data.forEachEntity([](C_Entity* ent, bool b) {
			if (ent->getEntityTypeId() != 71)
				return;
			int range;
			if (moduleMgr->getModule<AnchorAura>()->dEnhanced)
				range = moduleMgr->getModule<AnchorAura>()->cRange;
			else
				range = moduleMgr->getModule<AnchorAura>()->range;
			moduleMgr->getModule<AnchorAura>()->DestroyC(ent, range);
		});
		return;
	}
	if (this->delay >= 3) {
		this->delay = 0;
		return;
	}
}

void AnchorAura::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	if (!Preview || (!pEnhanced && autoplace) ||
		g_Data.getClientInstance() == nullptr ||
		g_Data.getPtrLocalPlayer() == nullptr ||
		g_Data.getLocalPlayer() == nullptr)
		return;

	auto ptr = g_Data.getClientInstance()->getPointerStruct();
	if (ptr != nullptr)
		if (ptr->getEntity() == nullptr && ptr->rayHitType == 0)
			if (g_Data.getLocalPlayer()->region->getBlock(ptr->block)->blockLegacy->material->isSolid ||
				g_Data.getLocalPlayer()->region->getBlock(ptr->block)->blockLegacy->material->isReplaceable) {
				DrawUtils::setColor(.75f, 0.f, .75f, 1.f);
				DrawUtils::drawBox(ptr->block.toVec3t().add(0.f, 1.f, 0.f),
								   ptr->block.add(1).toVec3t().add(0.f, 1.f, 0.f), .3f);
			}
}

void AnchorAura::onDisable() {
	this->delay = 0;
}