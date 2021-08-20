#include "../../../Utils/Logger.h"
#include "CrystalAuraOW.h"
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"

CrystalAuraOW::CrystalAuraOW() : IModule(0x0, Category::COMBAT, "Crystal Aura by OldGreggo5081 & weedelbhoy1") {

this->registerIntSetting("range", &this->range, this->range, 3, 12);
	registerBoolSetting("onClick", &this->onClick, this->onClick);

}

CrystalAuraOW::~CrystalAuraOW() {
}

const char* CrystalAuraOW::getModuleName() {
	return "CrystalAuraOW";
}

static std::vector<C_Entity*> targetList16;

void findEntity16(C_Entity* currentEntity16, bool isRegularEntity) {
	static auto CrystalAuraOWMod = moduleMgr->getModule<CrystalAuraOW>();

	if (currentEntity16 == nullptr)
		return;

	if (currentEntity16 == g_Data.getLocalPlayer())  // Skip Local player
		return;

	if (currentEntity16->getNameTag()->getTextLength() <= 1 && currentEntity16->getEntityTypeId() == 71)  // crystal
		return;

	if (!g_Data.getLocalPlayer()->canAttack(currentEntity16, false))
		return;

	//if (!g_Data.getLocalPlayer()->isAlive())
		//return;

	if (!currentEntity16->isAlive())
		return;
	
	if (currentEntity16->getNameTag()->getTextLength() <= 1 && currentEntity16->getEntityTypeId() == 63)
		return;

	if (currentEntity16->width <= 0.01f || currentEntity16->height <= 0.01f)  // Don't hit this pesky antibot on 2b2e.org
		return;
	
	if (!Target::isValidTarget(currentEntity16))
		return;

	float dist = (*currentEntity16->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
	if (dist < CrystalAuraOWMod->range) {
		targetList16.push_back(currentEntity16);

		float dist = (*currentEntity16->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

		if (dist < CrystalAuraOWMod->range) {
			targetList16.push_back(currentEntity16);
		}
	}
}

bool CrystalAuraOW::tryCrystalAuraOW(vec3_t CrystalAuraOW) {
	CrystalAuraOW = CrystalAuraOW.floor();

	C_Block* block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(CrystalAuraOW));
	C_BlockLegacy* blockLegacy = (block->blockLegacy);
			if (blockLegacy->material->isReplaceable) {
				vec3_ti blok(CrystalAuraOW);
				// Find neighbour
				static std::vector<vec3_ti*> checklist;
				if (checklist.empty()) {
					checklist.push_back(new vec3_ti(0, -1, 0));
					checklist.push_back(new vec3_ti(0, 1, 0));

					checklist.push_back(new vec3_ti(0, 0, -1));
					checklist.push_back(new vec3_ti(0, 0, 1));

					checklist.push_back(new vec3_ti(-1, 0, 0));
					checklist.push_back(new vec3_ti(1, 0, 0));
				}

				bool foundCandidate = false;
				int i = 0;
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
					g_Data.getCGameMode()->buildBlock(&blok, i);

					return true;
				}
			}

	return false;
}		
	


	void CrystalAuraOW::onTick(C_GameMode* gm) {
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	if (g_Data.getLocalPlayer() == nullptr)
		return;
	if (!g_Data.canUseMoveKeys())
		return;

	targetList16.clear();
	g_Data.forEachEntity(findEntity16);

	int place = 1;

	if (onClick) {
		if (GameData::isRightClickDown()) {
			place = 0;
		} else {
			place = 1;
		}
	}

	if (!onClick) {
		place = 0;
	}

	int crystal = 0;

		crystal = 615;
		crystal = 616;

	if (!targetList16.empty()) {
		if (g_Data.getLocalPlayer()->getSelectedItemId() == crystal) {
			//ground level
			vec3_t blockSide1 = targetList16[0]->eyePos0;

			vec3_t blockSide2 = targetList16[0]->eyePos0;

			vec3_t blockSide3 = targetList16[0]->eyePos0;

			vec3_t blockSide4 = targetList16[0]->eyePos0;

			//middle level
			vec3_t blockSide5 = targetList16[0]->eyePos0;

			vec3_t blockSide6 = targetList16[0]->eyePos0;

			vec3_t blockSide7 = targetList16[0]->eyePos0;

			vec3_t blockSide8 = targetList16[0]->eyePos0;

			//top level
			vec3_t blockSide9 = targetList16[0]->eyePos0;

			vec3_t blockSide10 = targetList16[0]->eyePos0;

			vec3_t blockSide11 = targetList16[0]->eyePos0;

			vec3_t blockSide12 = targetList16[0]->eyePos0;

			//ground level
			blockSide1.x -= targetList16[0]->height - 1;
			blockSide1.y -= targetList16[0]->height - 1;

			blockSide2.x += targetList16[0]->height - 1;
			blockSide2.y -= targetList16[0]->height - 1;

			blockSide3.z -= targetList16[0]->height - 1;
			blockSide3.y -= targetList16[0]->height - 1;

			blockSide4.z += targetList16[0]->height - 1;
			blockSide4.y -= targetList16[0]->height - 1;

			//middle level
			blockSide5.x -= targetList16[0]->height - 1;
			blockSide6.x += targetList16[0]->height - 1;
			blockSide7.z -= targetList16[0]->height - 1;
			blockSide8.z += targetList16[0]->height - 1;

			//under level
			blockSide9.x -= targetList16[0]->height + 1;
			blockSide9.y -= targetList16[0]->height - 3;

			blockSide10.x += targetList16[0]->height + 1;
			blockSide10.y -= targetList16[0]->height - 3;

			blockSide11.z -= targetList16[0]->height + 1;
			blockSide11.y -= targetList16[0]->height - 3;

			blockSide12.z += targetList16[0]->height - 1;
			blockSide12.y -= targetList16[0]->height + 1;
			
			if (place == 0) {
						//blockSide 1 to 4 are placing at ground level around the player
						if (!tryCrystalAuraOW(blockSide1)) {
							blockSide1.y -= 0;
							blockSide1.x -= 0;
						}

						if (!tryCrystalAuraOW(blockSide2)) {
							blockSide2.y += 0;
							blockSide2.x += 0;
						}

						if (!tryCrystalAuraOW(blockSide3)) {
							blockSide3.y -= 0;
							blockSide3.z -= 0;
						}

						if (!tryCrystalAuraOW(blockSide4)) {
							blockSide4.y += 0;
							blockSide4.z += 0;
						}

						//blockSide 5 to 8 are placing 1 up around the player
						if (!tryCrystalAuraOW(blockSide5)) {
							blockSide5.x -= 0;
						}

						if (!tryCrystalAuraOW(blockSide6)) {
							blockSide6.x += 0;
						}

						if (!tryCrystalAuraOW(blockSide7)) {
							blockSide7.z -= 0;
						}

						if (!tryCrystalAuraOW(blockSide8)) {
							blockSide8.z += 0;
						}

						//blockSide 9 to 12 at players below and around
						if (!tryCrystalAuraOW(blockSide9)) {
							blockSide9.y -= 0;
							blockSide9.x -= 0;
						}

						if (!tryCrystalAuraOW(blockSide10)) {
							blockSide10.y -= 0;
							blockSide10.x += 0;
						}

						if (!tryCrystalAuraOW(blockSide11)) {
							blockSide11.y -= 0;
							blockSide11.z -= 0;
						}

						if (!tryCrystalAuraOW(blockSide12)) {
							blockSide12.y -= 0;
							blockSide12.z += 0;
						}
					}
				}
			}
			g_Data.forEachEntity([](C_Entity* ent, bool b) {
				if (targetList16.empty()) return;
				int id = ent->getEntityTypeId();
				int range = moduleMgr->getModule<CrystalAuraOW>()->range;
				if (id == 71 && g_Data.getLocalPlayer()->getPos()->dist(*ent->getPos()) <= range) {
					g_Data.getCGameMode()->attack(ent);

					if (!moduleMgr->getModule<NoSwing>()->isEnabled())
						g_Data.getLocalPlayer()->swingArm();
				}
			});
}
