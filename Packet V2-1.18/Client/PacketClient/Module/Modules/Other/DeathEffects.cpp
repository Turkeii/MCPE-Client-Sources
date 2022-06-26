#include "DeathEffects.h"

using namespace std;
DeathEffects::DeathEffects() : IModule(0, Category::OTHER, "Renders an effect when you kill an entity") {
	registerEnumSetting("Mode", &mode, 0);
	mode.addEntry("Lightning", 0);
	mode.addEntry("Explosion", 1);
}

const char* DeathEffects::getRawModuleName() {
    return "DeathEffects";
}

const char* DeathEffects::getModuleName() {
    if (mode.getSelectedValue() == 0) name = string("DeathEffects ") + string(GRAY) + string("Lightning");
    if (mode.getSelectedValue() == 1) name = string("DeathEffects ") + string(GRAY) + string("Explosion");
    return name.c_str();
}

static vector<C_Entity*> targetList;
void findEntityDeathEffects(C_Entity* currentEntity, bool isRegularEntity) {
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

	if (dist < 255) targetList.push_back(currentEntity);
}

struct CompareTargetEnArray {
	bool operator()(C_Entity* lhs, C_Entity* rhs) {
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
	}
};

void DeathEffects::onEnable() {
	killed = false;
}

void DeathEffects::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	targetList.clear();
	g_Data.forEachEntity(findEntityDeathEffects);

	// still a wip as we need to get the entity
	// a way we could do it is maybe like checking if their hurttime is > 1 then adding them to a list, if they disappear they died or something not sure

	PointingStruct* level = g_Data.getLocalPlayer()->pointingStruct;
	if (killed && !targetList.empty()) {
		sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
		for (auto& i : targetList) {
			switch (mode.getSelectedValue()) {
			case 0: // Lightning
				level->playSound("ambient.weather.lightning.impact", *targetList[0]->getPos(), 1, 0.5);
				break;
			case 1: // Explosion
				level->playSound("random.explode", *targetList[0]->getPos(), 1, 1);
				break;
			}
		}
		killed = false;
	}
}