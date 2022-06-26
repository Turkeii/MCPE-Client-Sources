#include "HitEffects.h"
#include "../../../../Utils/TimerUtil.h"
#include "../pch.h"

using namespace std;
HitEffects::HitEffects() : IModule(0, Category::OTHER, "Renders an effect when you hit an entity") {
	registerEnumSetting("Sound", &sound, 0);
	sound.addEntry("Blood", 0);
	sound.addEntry("Old", 1);
	sound.addEntry("WTF", 2);
	registerFloatSetting("Volume", &volume, volume, 0.05f, 1.f);
}

const char* HitEffects::getRawModuleName() {
	return "HitEffects";
}

const char* HitEffects::getModuleName() {
	if (sound.getSelectedValue() == 0) name = string("HitEffects ") + string(GRAY) + string("Blood");
	if (sound.getSelectedValue() == 1) name = string("HitEffects ") + string(GRAY) + string("Old");
	if (sound.getSelectedValue() == 2) name = string("HitEffects ") + string(GRAY) + string("WTF");
	return name.c_str();
}

static vector<C_Entity*> targetList;
void findEntityHitEffects(C_Entity* currentEntity, bool isRegularEntity) {
	static auto hitEffects = moduleMgr->getModule<HitEffects>();

	if (currentEntity == nullptr)
		return;

	if (currentEntity == g_Data.getLocalPlayer())
		return;

	if (!g_Data.getLocalPlayer()->canAttack(currentEntity, false))
		return;

	if (!g_Data.getLocalPlayer()->isAlive())
		return;

	if (!currentEntity->isAlive())
		return;

	if (currentEntity->getEntityTypeId() == 69)  // XP
		return;

	if (currentEntity->getEntityTypeId() == 80)  // Arrows
		return;

	if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 63)
		return;

	if (currentEntity->width <= 0.01f || currentEntity->height <= 0.01f)
		return;

	if (currentEntity->getEntityTypeId() == 64)  //item
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < 8) targetList.push_back(currentEntity);
}

struct CompareTargetEnArray {
	bool operator()(C_Entity* lhs, C_Entity* rhs) {
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
	}
};

void HitEffects::onEnable() {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	delay = 0;
}

void HitEffects::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	targetList.clear();
	g_Data.forEachEntity(findEntityHitEffects);
}

void HitEffects::onAttack(C_Entity* entity) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (g_Data.canUseMoveKeys() && !targetList.empty()) {
		PointingStruct* level = g_Data.getLocalPlayer()->pointingStruct;
		if (targetList[0]->damageTime > 9) {
			switch (sound.getSelectedValue()) {
			case 0: // Blood
				level->playSound("dig.stone", *player->getPos(), volume, 1);
				break;
			case 1: // Old
				level->playSound("random.hurt", *player->getPos(), volume, 1);
				break;
			case 2: // LOL
				for (int i = 0; i < 44; i++) {
					level->playSound("game.player.hurt", *player->getPos(), volume, 1);
				}
				break;
			}
		}
	}
}