#include "../../../Utils/Logger.h"
#include "AutoTrap.h"
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"

AutoTrap::AutoTrap() : IModule(0x0, Category::COMBAT, "Automatically traps the nearest player") {

this->registerIntSetting("range", &this->range, this->range, 3, 12);
	registerBoolSetting("onClick", &this->onClick, this->onClick);

}

AutoTrap::~AutoTrap() {
}

const char* AutoTrap::getModuleName() {
	return "AutoTrap";
}

static std::vector<C_Entity*> targetList15;

void findEntity15(C_Entity* currentEntity15, bool isRegularEntity) {
	static auto AutoTrapMod = moduleMgr->getModule<AutoTrap>();

	if (currentEntity15 == nullptr)
		return;

	if (currentEntity15 == g_Data.getLocalPlayer())  // Skip Local player
		return;

	if (!g_Data.getLocalPlayer()->canAttack(currentEntity15, false))
		return;

	if (!g_Data.getLocalPlayer()->isAlive())
		return;

	if (!currentEntity15->isAlive())
		return;
	
	
	if (!Target::isValidTarget(currentEntity15))
		return;

	float dist = (*currentEntity15->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
	if (dist < AutoTrapMod->range) {
		targetList15.push_back(currentEntity15);

		float dist = (*currentEntity15->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

		if (dist < AutoTrapMod->range) {
			targetList15.push_back(currentEntity15);
		}
	}
}

bool AutoTrap::tryAutoTrap(vec3_t AutoTrap) {
	AutoTrap = AutoTrap.floor();

	C_Block* block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(AutoTrap));
	C_BlockLegacy* blockLegacy = (block->blockLegacy);
	if (blockLegacy->material->isReplaceable) {
		vec3_ti blok(AutoTrap);

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

void AutoTrap::onTick(C_GameMode* gm) {
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	if (g_Data.getLocalPlayer() == nullptr)
		return;
	if (!g_Data.canUseMoveKeys())
		return;

	auto selectedItem = g_Data.getLocalPlayer()->getSelectedItem();
	if ((selectedItem == nullptr || selectedItem->count == 0 || selectedItem->item == nullptr || !selectedItem->getItem()->isBlock()))  // Block in hand?
		return;

	targetList15.clear();
	g_Data.forEachEntity(findEntity15);

	int place = 1;

	if (onClick) {
		if (GameData::isRightClickDown()) {
			place = 0;
		} else {
			place = 1;
		}
	}
	
	
	if(!onClick) {
		place = 0;
	}

	if (!targetList15.empty()) {
			//ground level
			vec3_t blockSideL1 = targetList15[0]->eyePos0;

			vec3_t blockSideR1 = targetList15[0]->eyePos0;

			vec3_t blockSideL2 = targetList15[0]->eyePos0;

			vec3_t blockSideL3 = targetList15[0]->eyePos0;

			vec3_t blockSideL4 = targetList15[0]->eyePos0;

			vec3_t blockSideR2 = targetList15[0]->eyePos0;

			vec3_t blockSideR3 = targetList15[0]->eyePos0;

			vec3_t blockSideR4 = targetList15[0]->eyePos0;

			//middle level
			vec3_t blockSideL1M = targetList15[0]->eyePos0;

			vec3_t blockSideR1M = targetList15[0]->eyePos0;

			vec3_t blockSideL2M = targetList15[0]->eyePos0;

			vec3_t blockSideL3M = targetList15[0]->eyePos0;

			vec3_t blockSideL4M = targetList15[0]->eyePos0;

			vec3_t blockSideR2M = targetList15[0]->eyePos0;

			vec3_t blockSideR3M = targetList15[0]->eyePos0;

			vec3_t blockSideR4M = targetList15[0]->eyePos0;

			//top level
			vec3_t blockSideL1T = targetList15[0]->eyePos0;

			vec3_t blockSideR1T = targetList15[0]->eyePos0;

			vec3_t blockSideL2T = targetList15[0]->eyePos0;

			vec3_t blockSideL3T = targetList15[0]->eyePos0;

			vec3_t blockSideL4T = targetList15[0]->eyePos0;

			vec3_t blockSideR2T = targetList15[0]->eyePos0;

			vec3_t blockSideR3T = targetList15[0]->eyePos0;

			vec3_t blockSideR4T = targetList15[0]->eyePos0;

			//above head level
			vec3_t blockAboveH1 = targetList15[0]->eyePos0;
			vec3_t blockAboveH2 = targetList15[0]->eyePos0;
			vec3_t blockAboveH3 = targetList15[0]->eyePos0;
			vec3_t blockAboveH4 = targetList15[0]->eyePos0;

			//blocks below player
			vec3_t blockBelowB1 = targetList15[0]->eyePos0;
			vec3_t blockBelowB2 = targetList15[0]->eyePos0;
			vec3_t blockBelowB3 = targetList15[0]->eyePos0;
			vec3_t blockBelowB4 = targetList15[0]->eyePos0;

			//ground level
			vec3_t blockSide1 = targetList15[0]->eyePos0;

			vec3_t blockSide2 = targetList15[0]->eyePos0;

			vec3_t blockSide3 = targetList15[0]->eyePos0;

			vec3_t blockSide4 = targetList15[0]->eyePos0;

			//middle level
			vec3_t blockSide5 = targetList15[0]->eyePos0;

			vec3_t blockSide6 = targetList15[0]->eyePos0;

			vec3_t blockSide7 = targetList15[0]->eyePos0;

			vec3_t blockSide8 = targetList15[0]->eyePos0;

			//top level
			vec3_t blockSide9 = targetList15[0]->eyePos0;

			vec3_t blockSide10 = targetList15[0]->eyePos0;

			vec3_t blockSide11 = targetList15[0]->eyePos0;

			vec3_t blockSide12 = targetList15[0]->eyePos0;

			//above players head
			vec3_t blockAbove = targetList15[0]->eyePos0;
			vec3_t blockAbove1 = targetList15[0]->eyePos0;
			vec3_t blockAbove2 = targetList15[0]->eyePos0;
			vec3_t blockAbove3 = targetList15[0]->eyePos0;
			vec3_t blockAbove4 = targetList15[0]->eyePos0;

			//block below player
			vec3_t blockBelow = targetList15[0]->eyePos0;
			vec3_t blockBelow1 = targetList15[0]->eyePos0;
			vec3_t blockBelow2 = targetList15[0]->eyePos0;
			vec3_t blockBelow3 = targetList15[0]->eyePos0;
			vec3_t blockBelow4 = targetList15[0]->eyePos0;

			//ground level
			blockSideL1.x -= targetList15[0]->height + 0;
			blockSideL1.z -= targetList15[0]->height - 1;
			blockSideL1.y -= targetList15[0]->height - 1;

			blockSideR1.x -= targetList15[0]->height + 0;
			blockSideR1.z += targetList15[0]->height - 1;
			blockSideR1.y -= targetList15[0]->height - 1;

			blockSideL2.x += targetList15[0]->height + 0;
			blockSideL2.z -= targetList15[0]->height - 1;
			blockSideL2.y -= targetList15[0]->height - 1;

			blockSideR2.x += targetList15[0]->height + 0;
			blockSideR2.z += targetList15[0]->height - 1;
			blockSideR2.y -= targetList15[0]->height - 1;

			blockSideL3.x -= targetList15[0]->height - 1;
			blockSideL3.z -= targetList15[0]->height + 0;
			blockSideL3.y -= targetList15[0]->height - 1;

			blockSideR3.x -= targetList15[0]->height - 1;
			blockSideR3.z += targetList15[0]->height + 0;
			blockSideR3.y -= targetList15[0]->height - 1;

			blockSideL4.x += targetList15[0]->height - 1;
			blockSideL4.z -= targetList15[0]->height + 0;
			blockSideL4.y -= targetList15[0]->height - 1;

			blockSideR4.x += targetList15[0]->height - 1;
			blockSideR4.z += targetList15[0]->height + 0;
			blockSideR4.y -= targetList15[0]->height - 1;

			//middle level
			blockSideL1M.x -= targetList15[0]->height + 0;
			blockSideL1M.z -= targetList15[0]->height - 1;
			blockSideL1M.y += targetList15[0]->height - 2;

			blockSideR1M.x -= targetList15[0]->height + 0;
			blockSideR1M.z += targetList15[0]->height - 1;
			blockSideR1M.y += targetList15[0]->height - 2;

			blockSideL2M.x += targetList15[0]->height + 0;
			blockSideL2M.z -= targetList15[0]->height - 1;
			blockSideL2M.y += targetList15[0]->height - 2;

			blockSideR2M.x += targetList15[0]->height + 0;
			blockSideR2M.z += targetList15[0]->height - 1;
			blockSideR2M.y += targetList15[0]->height - 2;

			blockSideL3M.x -= targetList15[0]->height - 1;
			blockSideL3M.z -= targetList15[0]->height + 0;
			blockSideL3M.y += targetList15[0]->height - 2;

			blockSideR3M.x -= targetList15[0]->height - 1;
			blockSideR3M.z += targetList15[0]->height + 0;
			blockSideR3M.y += targetList15[0]->height - 2;

			blockSideL4M.x += targetList15[0]->height - 1;
			blockSideL4M.z -= targetList15[0]->height + 0;
			blockSideL4M.y += targetList15[0]->height - 2;

			blockSideR4M.x += targetList15[0]->height - 1;
			blockSideR4M.z += targetList15[0]->height + 0;
			blockSideR4M.y += targetList15[0]->height - 2;

			//top level
			blockSideL1T.x -= targetList15[0]->height + 0;
			blockSideL1T.z -= targetList15[0]->height - 1;
			blockSideL1T.y -= targetList15[0]->height - 3;

			blockSideR1T.x -= targetList15[0]->height + 0;
			blockSideR1T.z += targetList15[0]->height - 1;
			blockSideR1T.y -= targetList15[0]->height - 3;

			blockSideL2T.x += targetList15[0]->height + 0;
			blockSideL2T.z -= targetList15[0]->height - 1;
			blockSideL2T.y -= targetList15[0]->height - 3;

			blockSideR2T.x += targetList15[0]->height + 0;
			blockSideR2T.z += targetList15[0]->height - 1;
			blockSideR2T.y -= targetList15[0]->height - 3;

			blockSideL3T.x -= targetList15[0]->height - 1;
			blockSideL3T.z -= targetList15[0]->height + 0;
			blockSideL3T.y -= targetList15[0]->height - 3;

			blockSideR3T.x -= targetList15[0]->height - 1;
			blockSideR3T.z += targetList15[0]->height + 0;
			blockSideR3T.y -= targetList15[0]->height - 3;

			blockSideL4T.x += targetList15[0]->height - 1;
			blockSideL4T.z -= targetList15[0]->height + 0;
			blockSideL4T.y -= targetList15[0]->height - 3;

			blockSideR4T.x += targetList15[0]->height - 1;
			blockSideR4T.z += targetList15[0]->height + 0;
			blockSideR4T.y -= targetList15[0]->height - 3;

			//H1 x + z above head level
			blockAboveH1.y -= targetList15[0]->height - 3;
			blockAboveH1.x -= targetList15[0]->height - 1;
			blockAboveH1.z -= targetList15[0]->height - 1;

			blockAboveH2.y -= targetList15[0]->height - 3;
			blockAboveH2.x -= targetList15[0]->height - 1;
			blockAboveH2.z += targetList15[0]->height - 1;

			blockAboveH3.y -= targetList15[0]->height - 3;
			blockAboveH3.x += targetList15[0]->height - 1;
			blockAboveH3.z -= targetList15[0]->height - 1;

			blockAboveH4.y -= targetList15[0]->height - 3;
			blockAboveH4.x += targetList15[0]->height - 1;
			blockAboveH4.z += targetList15[0]->height - 1;

			//below Player B1 to B4
			blockBelowB1.y -= targetList15[0]->height + 0;
			blockBelowB1.x -= targetList15[0]->height - 1;
			blockBelowB1.z -= targetList15[0]->height - 1;

			blockBelowB2.y -= targetList15[0]->height + 0;
			blockBelowB2.x -= targetList15[0]->height - 1;
			blockBelowB2.z += targetList15[0]->height - 1;

			blockBelowB3.y -= targetList15[0]->height + 0;
			blockBelowB3.x += targetList15[0]->height - 1;
			blockBelowB3.z -= targetList15[0]->height - 1;

			blockBelowB4.y -= targetList15[0]->height + 0;
			blockBelowB4.x += targetList15[0]->height - 1;
			blockBelowB4.z += targetList15[0]->height - 1;

			//ground level
			blockSide1.x -= targetList15[0]->height + 0;
			blockSide1.y -= targetList15[0]->height - 1;

			blockSide2.x += targetList15[0]->height + 0;
			blockSide2.y -= targetList15[0]->height - 1;

			blockSide3.z -= targetList15[0]->height + 0;
			blockSide3.y -= targetList15[0]->height - 1;

			blockSide4.z += targetList15[0]->height + 0;
			blockSide4.y -= targetList15[0]->height - 1;

			//middle level
			blockSide5.x -= targetList15[0]->height + 0;
			blockSide6.x += targetList15[0]->height + 0;
			blockSide7.z -= targetList15[0]->height + 0;
			blockSide8.z += targetList15[0]->height + 0;

			//top level
			blockSide9.x -= targetList15[0]->height + 0;
			blockSide9.y -= targetList15[0]->height - 3;

			blockSide10.x += targetList15[0]->height + 0;
			blockSide10.y -= targetList15[0]->height - 3;

			blockSide11.z -= targetList15[0]->height + 0;
			blockSide11.y -= targetList15[0]->height - 3;

			blockSide12.z += targetList15[0]->height + 0;
			blockSide12.y -= targetList15[0]->height - 3;

			//above players head
			blockAbove.y -= targetList15[0]->height - 3;

			blockAbove1.y -= targetList15[0]->height - 3;
			blockAbove1.x -= targetList15[0]->height - 1;

			blockAbove2.y -= targetList15[0]->height - 3;
			blockAbove2.x += targetList15[0]->height - 1;

			blockAbove3.y -= targetList15[0]->height - 3;
			blockAbove3.z -= targetList15[0]->height - 1;

			blockAbove4.y -= targetList15[0]->height - 3;
			blockAbove4.z += targetList15[0]->height - 1;

			//block below player
			blockBelow.y -= targetList15[0]->height + 0;

			blockBelow1.y -= targetList15[0]->height + 0;
			blockBelow1.x -= targetList15[0]->height - 1;

			blockBelow2.y -= targetList15[0]->height + 0;
			blockBelow2.x += targetList15[0]->height - 1;

			blockBelow3.y -= targetList15[0]->height + 0;
			blockBelow3.z -= targetList15[0]->height - 1;

			blockBelow4.y -= targetList15[0]->height + 0;
			blockBelow4.z += targetList15[0]->height - 1;

			if (place == 0) {
			// L1 to R4 are x + z sides ground level
			if (!tryAutoTrap(blockSideL1)) {
				blockSideL1.x -= 0;
				blockSideL1.z -= 0;
			}

			if (!tryAutoTrap(blockSideR1)) {
				blockSideR1.x -= 0;
				blockSideR1.z -= 0;
			}

			if (!tryAutoTrap(blockSideL2)) {
				blockSideL2.x -= 0;
				blockSideL2.z -= 0;
			}

			if (!tryAutoTrap(blockSideR2)) {
				blockSideR2.x -= 0;
				blockSideR2.z -= 0;
			}

			if (!tryAutoTrap(blockSideL3)) {
				blockSideL3.x -= 0;
				blockSideL3.z -= 0;
			}

			if (!tryAutoTrap(blockSideR3)) {
				blockSideR3.x -= 0;
				blockSideR3.z -= 0;
			}

			if (!tryAutoTrap(blockSideL4)) {
				blockSideL4.x -= 0;
				blockSideL4.z -= 0;
			}

			if (!tryAutoTrap(blockSideR4)) {
				blockSideR4.x -= 0;
				blockSideR4.z -= 0;
			}

			//L1M to R4M are x + z sides middle level
			if (!tryAutoTrap(blockSideL1M)) {
				blockSideL1M.x -= 0;
				blockSideL1M.z -= 0;
			}

			if (!tryAutoTrap(blockSideR1M)) {
				blockSideR1M.x -= 0;
				blockSideR1M.z -= 0;
			}

			if (!tryAutoTrap(blockSideL2M)) {
				blockSideL2M.x -= 0;
				blockSideL2M.z -= 0;
			}

			if (!tryAutoTrap(blockSideR2M)) {
				blockSideR2M.x -= 0;
				blockSideR2M.z -= 0;
			}

			if (!tryAutoTrap(blockSideL3M)) {
				blockSideL3M.x -= 0;
				blockSideL3M.z -= 0;
			}

			if (!tryAutoTrap(blockSideR3M)) {
				blockSideR3M.x -= 0;
				blockSideR3M.z -= 0;
			}

			if (!tryAutoTrap(blockSideL4M)) {
				blockSideL4M.x -= 0;
				blockSideL4M.z -= 0;
			}

			if (!tryAutoTrap(blockSideR4M)) {
				blockSideR4M.x -= 0;
				blockSideR4M.z -= 0;
			}

			//L1T to R4T are x + z sides top level
			if (!tryAutoTrap(blockSideL1T)) {
				blockSideL1T.x -= 0;
				blockSideL1T.z -= 0;
			}

			if (!tryAutoTrap(blockSideR1T)) {
				blockSideR1T.x -= 0;
				blockSideR1T.z -= 0;
			}

			if (!tryAutoTrap(blockSideL2T)) {
				blockSideL2T.x -= 0;
				blockSideL2T.z -= 0;
			}

			if (!tryAutoTrap(blockSideR2T)) {
				blockSideR2T.x -= 0;
				blockSideR2T.z -= 0;
			}

			if (!tryAutoTrap(blockSideL3T)) {
				blockSideL3T.x -= 0;
				blockSideL3T.z -= 0;
			}

			if (!tryAutoTrap(blockSideR3T)) {
				blockSideR3T.x -= 0;
				blockSideR3T.z -= 0;
			}

			if (!tryAutoTrap(blockSideL4T)) {
				blockSideL4T.x -= 0;
				blockSideL4T.z -= 0;
			}

			if (!tryAutoTrap(blockSideR4T)) {
				blockSideR4T.x -= 0;
				blockSideR4T.z -= 0;
			}

			//H1 to H4 are above players head
			if (!tryAutoTrap(blockAboveH1)) {
				blockAboveH1.x -= 0;
				blockAboveH1.z -= 0;
			}

			if (!tryAutoTrap(blockAboveH2)) {
				blockAboveH2.x -= 0;
				blockAboveH2.z -= 0;
			}

			if (!tryAutoTrap(blockAboveH3)) {
				blockAboveH3.x -= 0;
				blockAboveH3.z -= 0;
			}

			if (!tryAutoTrap(blockAboveH4)) {
				blockAboveH4.x -= 0;
				blockAboveH4.z -= 0;
			}

			//B1 to B4 below the player
			if (!tryAutoTrap(blockBelowB1)) {
				blockBelowB1.x -= 0;
				blockBelowB1.z -= 0;
			}

			if (!tryAutoTrap(blockBelowB2)) {
				blockBelowB2.x -= 0;
				blockBelowB2.z -= 0;
			}

			if (!tryAutoTrap(blockBelowB3)) {
				blockBelowB3.x -= 0;
				blockBelowB3.z -= 0;
			}

			if (!tryAutoTrap(blockBelowB4)) {
				blockBelowB4.x -= 0;
				blockBelowB4.z -= 0;
			}

			//blockSide 1 to 4 are placing at ground level around the player
			if (!tryAutoTrap(blockSide1)) {
				blockSide1.y -= 0;
				blockSide1.x -= 0;
			}

			if (!tryAutoTrap(blockSide2)) {
				blockSide2.y += 0;
				blockSide2.x += 0;
			}

			if (!tryAutoTrap(blockSide3)) {
				blockSide3.y -= 0;
				blockSide3.z -= 0;
			}

			if (!tryAutoTrap(blockSide4)) {
				blockSide4.y += 0;
				blockSide4.z += 0;
			}

			//blockSide 5 to 8 are placing 1 up around the player
			if (!tryAutoTrap(blockSide5)) {
				blockSide5.x -= 0;
			}

			if (!tryAutoTrap(blockSide6)) {
				blockSide6.x += 0;
			}

			if (!tryAutoTrap(blockSide7)) {
				blockSide7.z -= 0;
			}

			if (!tryAutoTrap(blockSide8)) {
				blockSide8.z += 0;
			}

			//blockSide 9 to 12 at players head and around
			if (!tryAutoTrap(blockSide9)) {
				blockSide9.y -= 0;
				blockSide9.x -= 0;
			}

			if (!tryAutoTrap(blockSide10)) {
				blockSide10.y -= 0;
				blockSide10.x += 0;
			}

			if (!tryAutoTrap(blockSide11)) {
				blockSide11.y -= 0;
				blockSide11.z -= 0;
			}

			if (!tryAutoTrap(blockSide12)) {
				blockSide12.y -= 0;
				blockSide12.z += 0;
			}

			//placing block above players head (3blocks up from the ground)
			if (!tryAutoTrap(blockAbove)) {
				blockAbove.y -= 0;
			}

			if (!tryAutoTrap(blockAbove1)) {
				blockAbove1.y -= 0;
			}

			if (!tryAutoTrap(blockAbove2)) {
				blockAbove2.y -= 0;
			}

			if (!tryAutoTrap(blockAbove3)) {
				blockAbove3.y -= 0;
			}

			if (!tryAutoTrap(blockAbove4)) {
				blockAbove4.y -= 0;
			}

			//below the player
			if (!tryAutoTrap(blockBelow)) {
				blockBelow.x -= 0;
				blockBelow.z -= 0;
			}

			if (!tryAutoTrap(blockBelow1)) {
				blockBelow1.x -= 0;
				blockBelow1.z -= 0;
			}

			if (!tryAutoTrap(blockBelow2)) {
				blockBelow2.x -= 0;
				blockBelow2.z -= 0;
			}

			if (!tryAutoTrap(blockBelow3)) {
				blockBelow3.x -= 0;
				blockBelow3.z -= 0;
			}

			if (!tryAutoTrap(blockBelow4)) {
				blockBelow4.x -= 0;
				blockBelow4.z -= 0;
			}
		}
	}
}
