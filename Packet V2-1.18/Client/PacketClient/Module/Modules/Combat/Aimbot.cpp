#include "Aimbot.h"
#include "../pch.h"

using namespace std;
Aimbot::Aimbot() : IModule(0, Category::COMBAT, "Automatically aims at the nearest entity") {
	registerBoolSetting("Vertical", &vertical, vertical);
	registerBoolSetting("Lock", &lock, lock);
	registerBoolSetting("Hold", &click, click);
	registerFloatSetting("Range", &range, range, 3.f, 8.f);
	registerFloatSetting("Speed", &speed, speed, 10.f, 90.f);
	registerFloatSetting("Angle", &angleAmount, angleAmount, 20.f, 180.f);
}

const char* Aimbot::getModuleName() {
	return ("Aimbot");
}

static vector<C_Entity*> targetList;
void findEntity_Aimbot(C_Entity* currentEntity, bool isRegularEntity) {
	static auto aimbot = moduleMgr->getModule<Aimbot>();

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

	if (!TargetUtil::isValidTarget(currentEntity))
		return;

	if (currentEntity->getEntityTypeId() == 1677999)  // Villager
		return;

	if (currentEntity->getEntityTypeId() == 51)  // NPC
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < aimbot->range) {
		targetList.push_back(currentEntity);
	}
}

struct CompareTargetEnArray {
	bool operator()(C_Entity* lhs, C_Entity* rhs) {
		auto player = g_Data.getLocalPlayer();
		return (int)((*lhs->getPos()).dist(*player->getPos())) < (int)((*rhs->getPos()).dist(*player->getPos()));
	}
};

void Aimbot::onEnable() {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	targetList.clear();
}

void Aimbot::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	targetList.clear();
	g_Data.forEachEntity(findEntity_Aimbot);
}

void Aimbot::onPlayerTick(C_Player* plr) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (click && !g_Data.isLeftClickDown())
		return;

	if (g_Data.canUseMoveKeys() && !moduleMgr->getModule<ClickGUIMod>()->isEnabled()) {
		sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
		if (!targetList.empty()) {
			vec2_t angle = player->getPos()->CalcAngle(*targetList[0]->getPos());
			vec3_t origin = g_Data.getClientInstance()->levelRenderer->getOrigin();
			vec2_t appl = angle.sub(player->viewAngles).normAngles();

			if (lock) {
				player->setRot(angle);
				player->resetRot();
			}
			else {
				appl.x = -appl.x;
				if ((appl.x < angleAmount && appl.x > -angleAmount) && (appl.y < angleAmount && appl.y > -angleAmount)) {
					appl.x /= (100.f - speed);
					appl.y /= (100.f - speed);
					if (appl.x >= 1 || appl.x <= -1) appl.div(abs(appl.x));
					if (appl.y >= 1 || appl.y <= -1) appl.div(abs(appl.y));
					if (!vertical)
						appl.x = 0;
					player->applyTurnDelta(&appl);
				}
			}
		}
	}
}

void Aimbot::onDisable() {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
}
