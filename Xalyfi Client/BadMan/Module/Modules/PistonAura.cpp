#include "PistonAura.h"

#include "../../../Utils/Target.h"
#include "../ModuleManager.h"

PistonAura::PistonAura() : IModule(0x0, Category::COMBAT, "PistonAura By Kaeru") {
	this->registerIntSetting("radius", &this->PlacerRadius, this->PlacerRadius, 1, 10);
	//this->registerBoolSetting("Place on Water", &this->inWater, this->inWater);
	this->registerBoolSetting("Place on Air", &this->inAir, this->inAir);
	//this->registerBoolSetting("Target Players", &this->TargetPlayer, this->TargetPlayer);
	this->registerFloatSetting("range", &this->range, this->range, 3.f, 12.f);
}

PistonAura::~PistonAura() {
}

const char* PistonAura::getModuleName() {
	return ("PistonAura");
}

static std::vector<C_Entity*> targetList2;

void findEntity9b(C_Entity* currentEntity1b, bool isRegularEntityb) {
	static auto TargetMod = moduleMgr->getModule<PistonAura>();
	if (TargetMod->TargetPlayer) {
		if (currentEntity1b == nullptr)
			return;

		if (currentEntity1b == g_Data.getLocalPlayer())  // Skip Local player
			return;

		if (!g_Data.getLocalPlayer()->canAttack(currentEntity1b, false))
			return;

		if (!g_Data.getLocalPlayer()->isAlive())
			return;

		if (!currentEntity1b->isAlive())
			return;

		if (!Target::isValidTarget(currentEntity1b))
			return;

		float dist = (*currentEntity1b->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
		if (dist < TargetMod->range) {
			targetList2.push_back(currentEntity1b);
		}
	}
}

void PistonAura::onTick(C_GameMode* gm) {
	if (TargetPlayer) {
		targetList2.clear();
		g_Data.forEachEntity(findEntity9b);

		if (!targetList2.empty()) {
			vec3_ti tempPos = *targetList2[0]->getPos();
			for (int x = -PlacerRadius; x < PlacerRadius; x++) {
				for (int y = -PlacerRadius; y < PlacerRadius; y++) {
					for (int z = -PlacerRadius; z < PlacerRadius; z++) {
						tempPos.x = (int)targetList2[0]->getPos()->x + 1;
						tempPos.y = (int)targetList2[0]->getPos()->y + 1;
						tempPos.z = (int)targetList2[0]->getPos()->z + 0;
						gm->buildBlock(&tempPos, 1);
					}
				}
			}
		}
	} else {
		vec3_ti tempPos = *gm->player->getPos();
		for (int x = -PlacerRadius; x < PlacerRadius; x++) {
			for (int y = -PlacerRadius; y < PlacerRadius; y++) {
				//for (int z = -PlacerRadius; z < PlacerRadius; z++) {
				tempPos.x = (int)gm->player->getPos()->x + x;
				tempPos.y = (int)gm->player->getPos()->y + y;
				if (inWater) {
					if (tempPos.y > 0 && gm->player->region->getBlock(tempPos)->toLegacy()->material->isLiquid) {
						gm->buildBlock(&tempPos, 1);
					}
				} else if (inAir) {
					gm->buildBlock(&tempPos, 1);

				} else {
					if (tempPos.y > 0 && gm->player->region->getBlock(tempPos)->toLegacy()->material->isSolid) {
						gm->buildBlock(&tempPos, 1);
					}
				}
			}
		}
	}
}