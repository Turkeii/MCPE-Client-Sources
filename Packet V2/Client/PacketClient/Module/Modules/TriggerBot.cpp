#include "TriggerBot.h"

#include "../../../Utils/Target.h"

TriggerBot::TriggerBot() : IModule(0, Category::COMBAT, "Attacks entities you're looking at") {
	registerFloatSetting("Range", &range, range, 3, 8);
	registerIntSetting("Delay", &delay, delay, 0, 10);
}

TriggerBot::~TriggerBot() {
}

const char* TriggerBot::getModuleName() {
	return ("TriggerBot");
}

static std::vector<C_Entity*> targetListTB;

void findEntityTB(C_Entity* currentEntity, bool isRegularEntity) {
	if ((GameData::canUseMoveKeys())) {
		static auto triggerBot = moduleMgr->getModule<Killaura>();

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

		if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 63)
			return;
		if (currentEntity->width <= 0.01f || currentEntity->height <= 0.01f)  // Don't hit this pesky antibot on 2b2e.org
			return;
		if (currentEntity->getEntityTypeId() == 64)  //item
			return;

		if (!Target::isValidTarget(currentEntity))
			return;

		float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

		if (dist < triggerBot->range) {
			targetListTB.push_back(currentEntity);
		}
	}
}

void TriggerBot::onTick(C_GameMode* gm) {
	PointingStruct* pointing = g_Data.getClientInstance()->getPointerStruct();
	C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
	if (GameData::canUseMoveKeys()) {
		//Loop through all our players and retrieve their information
		targetListTB.clear();
		g_Data.forEachEntity(findEntityTB);

		if (!moduleMgr->getModule<NoSwing>()->isEnabled()) {
			localPlayer->swingArm();
		}

		Odelay++;
		if (!targetListTB.empty() && Odelay >= delay) {
			// Attack all entitys in targetList
			for (auto& i : targetListTB) {
				if (!(i->damageTime > 1 && hurttime)) {
					g_Data.leftclickCount++;
					if (pointing->hasEntity())
						gm->attack(pointing->getEntity());
				}
			}
			Odelay = 0;
		}
		for (auto& i : targetListTB) {
			C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
			PointingStruct* pointing = g_Data.getClientInstance()->getPointerStruct();
			Odelay++;
			if (Odelay >= delay) {
				g_Data.leftclickCount++;
				if (pointing->hasEntity())
					gm->attack(pointing->getEntity());
			}
		}
	}
}
