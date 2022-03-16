#include "Placer.h"

#include "../../../Utils/Target.h"
#include "../ModuleManager.h"

Placer::Placer() : IModule(VK_NUMPAD8, Category::WORLD, "Place multiple blocks at once") {
	this->registerIntSetting("radius", &this->PlacerRadius, this->PlacerRadius, 1, 10);
	this->registerBoolSetting("Place on Water", &this->inWater, this->inWater);
	this->registerBoolSetting("WithCrystal", &this->inAir, this->inAir);
	this->registerBoolSetting("Target Players", &this->TargetPlayer, this->TargetPlayer);
	this->registerFloatSetting("range", &this->range, this->range, 3.f, 12.f);
}

Placer::~Placer() {
}

const char* Placer::getModuleName() {
	return ("Placer");
}

static std::vector<C_Entity*> targetList2;

void findEntity9(C_Entity* currentEntity1, bool isRegularEntity) {
	static auto TargetMod = moduleMgr->getModule<Placer>();
	if (TargetMod->TargetPlayer) {
		if (currentEntity1 == nullptr)
			return;

		if (currentEntity1 == g_Data.getLocalPlayer())  // Skip Local player
			return;

		if (!g_Data.getLocalPlayer()->canAttack(currentEntity1, false))
			return;

		if (!g_Data.getLocalPlayer()->isAlive())
			return;

		if (!currentEntity1->isAlive())
			return;

		if (!Target::isValidTarget(currentEntity1))
			return;

		float dist = (*currentEntity1->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
		if (dist < TargetMod->range) {
			targetList2.push_back(currentEntity1);
		}
	}
}

void Placer::onTick(C_GameMode* gm) {
	if (TargetPlayer) {
		targetList2.clear();
		g_Data.forEachEntity(findEntity9);

		if (!targetList2.empty()) {
			vec3_ti tempPos = *targetList2[0]->getPos();
			for (int x = -PlacerRadius; x < PlacerRadius; x++) {
				for (int y = -PlacerRadius; y < PlacerRadius; y++) {
					for (int z = -PlacerRadius; z < PlacerRadius; z++) {
						tempPos.x = (int)targetList2[0]->getPos()->x + x;
						tempPos.y = (int)targetList2[0]->getPos()->y + y;
						tempPos.z = (int)targetList2[0]->getPos()->z + z;
						if (GameData::isRightClickDown()) {
							gm->buildBlock(&tempPos, 1,false);
						}
					}
				}
			}
		}

	} else {
		vec3_ti tempPos = *gm->player->getPos();
		for (int x = -PlacerRadius; x < PlacerRadius; x++) {
			for (int y = -PlacerRadius; y < PlacerRadius; y++) {
				for (int z = -PlacerRadius; z < PlacerRadius; z++) {
					tempPos.x = (int)gm->player->getPos()->x + x;
					tempPos.y = (int)gm->player->getPos()->y + y;
					tempPos.z = (int)gm->player->getPos()->z + z;
					if (inWater) {
						if (tempPos.y > 0 && gm->player->region->getBlock(tempPos)->toLegacy()->material->isLiquid) {
							if (GameData::isRightClickDown()) {
								gm->buildBlock(&tempPos, 1, false);
							}
						}
					} else if (inAir) {
						if (GameData::isRightClickDown()) {
							gm->buildBlock(&tempPos, 1, false);
						}
					} else {
						if (tempPos.y > 0 && gm->player->region->getBlock(tempPos)->toLegacy()->material->isSolid) {
							if (GameData::isRightClickDown()) {
								gm->buildBlock(&tempPos, 1, false);
							}
						}
					}
				}
			}
		}
	}
}