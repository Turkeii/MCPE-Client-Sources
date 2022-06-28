#include "CrystalAuraBot.h"

#include <Windows.h>

#include <chrono>
#include <cstdlib>
#include <ctime>

#include "../../../Utils/TimerUtils.h"
#include "../../path/goals/PathGoalXYZ.h"
#include "../ModuleManager.h"
#include "FollowPath.h"

using namespace std;
CrystalAuraBot::CrystalAuraBot() : IModule(0, Category::COMBAT, "Plays the game for you") {
	registerEnumSetting("Rotations", &rotations, 0);
	rotations.addEntry(EnumEntry("Normal", 0));
	rotations.addEntry(EnumEntry("Client", 1));
	rotations.addEntry(EnumEntry("None", 2));
	registerIntSetting("Timer", &timer, timer, 20, 80);
}

CrystalAuraBot::~CrystalAuraBot() {
}

const char* CrystalAuraBot::getModuleName() {
	return "CrystalAuraBot";
}

static vector<C_Entity*> targetList;
void findPathEntity(C_Entity* currentEntity, bool isRegularEntity) {
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

	if (!Target::isValidTarget(currentEntity))
		return;

	if (currentEntity->getEntityTypeId() == 1677999)  // Villager
		return;

	if (currentEntity->getEntityTypeId() == 51)  // NPC
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
	if (dist < 255) {
		targetList.push_back(currentEntity);
	}
}

struct CompareTargetEnArray {
	bool operator()(C_Entity* lhs, C_Entity* rhs) {
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
	}
};

void CrystalAuraBot::onEnable() {
	auto path = moduleMgr->getModule<FollowPath>();
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	path->shouldStartSearch = false;
	if (path->pathFinder) path->pathFinder->terminateSearch = true;
	path->engageDelay = -1;
	path->pathFinder.reset();
	path->path.reset();
	path->nextPath.reset();
	path->movementController.reset();
	path->goal.reset();
	if (path->isEnabled()) path->setEnabled(false);
}

void CrystalAuraBot::onLevelRender() {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
}

int niga = 0;
void CrystalAuraBot::onTick(C_GameMode* gm) {
	auto clickGUI = moduleMgr->getModule<ClickGuiMod>();
	static TimerUtils* timerUtil = new TimerUtils();
	auto path = moduleMgr->getModule<FollowPath>();
	auto player = g_Data.getLocalPlayer();
	auto autocrystal = moduleMgr->getModule<AutoCrystal>();
	if (player == nullptr) return;
	if (path->isEnabled())
		g_Data.getClientInstance()->minecraft->setTimerSpeed(timer);

	targetList.clear();
	g_Data.forEachEntity(findPathEntity);
	sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
	if (niga < 5)
		niga++;
	else
		niga = 0;

	if (!targetList.empty() && niga < 1 && (player->eyePos0.dist(targetList[0]->eyePos0)) >= autocrystal->placeRange && g_Data.getLocalPlayer()->onGround) {
		vec3_ti endNode((int)floorf(targetList[0]->eyePos0.x - 0.5), (int)floorf(targetList[0]->eyePos0.y - 1.62f), (int)floorf(targetList[0]->eyePos0.z - 0.5));
		path->shouldStartSearch = true;
		path->goal = make_unique<PathGoalXYZ>(endNode);
		if (!path->isEnabled()) path->setEnabled(true);
	}
	if (targetList.empty() || targetList[0] == nullptr) {
		path->shouldStartSearch = false;
		if (path->pathFinder)
			path->pathFinder->terminateSearch = true;
		path->engageDelay = -1;
		path->pathFinder.reset();
		path->path.reset();
		path->nextPath.reset();
		path->goal.reset();
		if (path->isEnabled())
			path->setEnabled(false);
		targetList.clear();
	}
}

void CrystalAuraBot::onPlayerTick(C_Player* plr) {
	auto player = g_Data.getLocalPlayer();
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	if (input == nullptr || player == nullptr)
		return;

	if (GameData::isKeyDown(*input->rightKey) || GameData::isKeyDown(*input->leftKey) || GameData::isKeyDown(*input->backKey) || GameData::isKeyDown(*input->forwardKey))
		isHitingKeys = true;
	else
		isHitingKeys = false;
	// Velocity based rots
	vec3_t vel = g_Data.getLocalPlayer()->velocity;
	vel = vel.normalize();  // Only use values from 0 - 1
	float velocityxz = g_Data.getLocalPlayer()->velocity.magnitudexz();
	vec3_t blockBelow = g_Data.getLocalPlayer()->eyePos0;  // Block 1 block below the player
	blockBelow.y -= g_Data.getLocalPlayer()->height;
	blockBelow.y -= 0.5;

	blockBelow.z -= vel.z * 0.1f;
	blockBelow.x -= vel.x * 0.1f;
	blockBelow.z += vel.z;
	blockBelow.x += vel.x;

	vec2_t down = player->getPos()->CalcAngle(blockBelow);
	if (animYaw > down.y)
		animYaw -= ((animYaw - down.y) / 2.f);
	else if (animYaw < down.y)
		animYaw += ((down.y - animYaw) / 2.f);

	vec2_t newAngle = {animYaw, down.y};

	if (velocityxz > 0.f && rotations.selected == 1) {
		vec2_t appl = down.sub(player->viewAngles).normAngles();
		appl.x = -appl.x;
		if ((appl.x < 180 && appl.x > -180) && (appl.y < 180 && appl.y > -180)) {
			appl.x /= (100.f - 90);
			appl.y /= (100.f - 90);
			if (appl.x >= 1 || appl.x <= -1) appl.div(abs(appl.x));
			if (appl.y >= 1 || appl.y <= -1) appl.div(abs(appl.y));
			player->applyTurnDelta(&vec2_t{appl.x, appl.y});
			player->applyTurnDelta(&vec2_t{-appl.x, appl.y});
		}
	}
	if (velocityxz > 0.f && rotations.selected == 0) {
		player->bodyYaw = animYaw;
		player->yawUnused1 = animYaw;
		player->pitch = 0.f;
	}
}

void CrystalAuraBot::onSendPacket(C_Packet* packet) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	targetList.clear();
	g_Data.forEachEntity(findPathEntity);
}

void CrystalAuraBot::onDisable() {
	g_Data.getClientInstance()->minecraft->setTimerSpeed(20.f);
	auto path = moduleMgr->getModule<FollowPath>();
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (path->shouldStartSearch)
		path->shouldStartSearch = false;
	if (path->pathFinder) path->pathFinder->terminateSearch = true;
	path->engageDelay = -1;
	path->pathFinder.reset();
	path->path.reset();
	path->nextPath.reset();
	path->movementController.reset();
	path->goal.reset();
	if (path->isEnabled()) path->setEnabled(false);
}