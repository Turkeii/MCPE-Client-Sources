#include "AutoPlay.h"
#include <chrono>
#include <ctime>
#include <Windows.h>
#include <cstdlib>
#include "../../../path/goals/PathGoalXYZ.h"
#include "../../../../Utils/TimerUtil.h"
#include "../pch.h"

using namespace std;
AutoPlay::AutoPlay() : IModule(0, Category::COMBAT, "Plays the game for you") {
	registerEnumSetting("Rotations", &rotations, 0);
	rotations.addEntry("Normal", 0);
	rotations.addEntry("Client", 1);
	rotations.addEntry("None", 2);
	registerEnumSetting("Mode", &server, 0);
	server.addEntry("Legit", 0);
	server.addEntry("Hive", 1);
	server.addEntry("Mineplex", 2);
	registerFloatSetting("Distance", &distance, distance, 0.f, 5.f);
	registerIntSetting("Timer", &timer, timer, 20, 80);
}

const char* AutoPlay::getRawModuleName() {
	return "AutoPlay";
}

const char* AutoPlay::getModuleName() {
	return "AutoPlay";
}

bool checkVoid(C_Entity* ent) {
	auto player = ent;
	vec3_t blockBelow = player->eyePos0;
	blockBelow.y -= player->height;
	blockBelow.y -= 1.f;
	vec3_t bb = vec3_t(blockBelow.x, blockBelow.y, blockBelow.z);
	for (int i = (int)(blockBelow.y); i > -62; i--) {
		if (player->region->getBlock(bb)->blockLegacy->material->isSolid || player->region->getBlock(bb)->blockLegacy->material->isLiquid) {
			return false;
		}
		bb.y -= 1.f;
	}
	return true;
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

	if (!TargetUtil::isValidTarget(currentEntity))
		return;

	if (currentEntity->getEntityTypeId() == 1677999)  // Villager
		return;

	if (currentEntity->getEntityTypeId() == 51)  // NPC
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
	if (dist < 255) {
		if (!checkVoid(currentEntity)) targetList.push_back(currentEntity);
	}
}

struct CompareTargetEnArray {
	bool operator()(C_Entity* lhs, C_Entity* rhs) {
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
	}
};

void AutoPlay::onEnable() {
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

int niga = 0;
void AutoPlay::onTick(C_GameMode* gm) {
	auto clickGUI = moduleMgr->getModule<ClickGUIMod>();
	static TimerUtil* timerUtil = new TimerUtil();
	auto path = moduleMgr->getModule<FollowPath>();
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	if (path->isEnabled())
		g_Data.getClientInstance()->minecraft->setTimerSpeed(timer);

	targetList.clear();
	g_Data.forEachEntity(findPathEntity);
	sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
	if (niga < 5)niga++; else niga = 0;
	if (server.getSelectedValue() == 2) {
		if (!targetList.empty() && niga < 1 && (float)(player->eyePos0.dist(targetList[0]->eyePos0)) > 0.1f) {
			float playerYaw = targetList[0]->bodyYaw;
			float theirYaw = (playerYaw - 180) * (PI / 180);
			float behindX = -sin(theirYaw) * distance;
			float behindZ = cos(theirYaw) * distance;
			if (!checkVoid(targetList[0])) {
				vec3_ti endNode((int)floorf(targetList[0]->eyePos0.x + behindX), (int)roundf(targetList[0]->eyePos0.y - 1.62f), (int)floorf(targetList[0]->eyePos0.z + behindZ));
				path->shouldStartSearch = true;
				path->goal = make_unique<PathGoalXYZ>(endNode);
			}
			if (!path->isEnabled()) path->setEnabled(true);
		}
	}
	else {
		if (!targetList.empty() && niga < 1 && (float)(player->eyePos0.dist(targetList[0]->eyePos0)) > 0.1f && targetList[0]->onGround) {
			float playerYaw = targetList[0]->bodyYaw;
			float theirYaw = (playerYaw - 180) * (PI / 180);
			float behindX = -sin(theirYaw) * distance;
			float behindZ = cos(theirYaw) * distance;
			vec3_ti endNode((int)floorf(targetList[0]->eyePos0.x + behindX), (int)roundf(targetList[0]->eyePos0.y - 1.62f), (int)floorf(targetList[0]->eyePos0.z + behindZ));
			path->shouldStartSearch = true;
			path->goal = make_unique<PathGoalXYZ>(endNode);
			if (!path->isEnabled()) path->setEnabled(true);
		}
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
		//auto notif = g_Data.addNotification("AutoPlay:", "no bitches :cope:");
		//notif->isError = true;
		//notif->duration = 3.f;
		//setEnabled(false);
		targetList.clear();
	}
}

void AutoPlay::onPlayerTick(C_Player* plr) {
	auto player = g_Data.getLocalPlayer();
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	if (input == nullptr || player == nullptr)
		return;

	if (GameData::isKeyDown(*input->rightKey) || GameData::isKeyDown(*input->leftKey) || GameData::isKeyDown(*input->backKey) || GameData::isKeyDown(*input->forwardKey)) isHitingKeys = true;
	else isHitingKeys = false;
	//Velocity based rots
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

	vec2_t newAngle = { animYaw, down.y };

	if (velocityxz > 0.f && rotations.getSelectedValue() == 1) {
		vec2_t appl = down.sub(player->viewAngles).normAngles();
		appl.x = -appl.x;
		if ((appl.x < 180 && appl.x > -180) && (appl.y < 180 && appl.y > -180)) {
			appl.x /= (100.f - 90);
			appl.y /= (100.f - 90);
			if (appl.x >= 1 || appl.x <= -1) appl.div(abs(appl.x));
			if (appl.y >= 1 || appl.y <= -1) appl.div(abs(appl.y));
			player->applyTurnDelta(&vec2_t{ appl.x,appl.y });
			player->applyTurnDelta(&vec2_t{ -appl.x,appl.y });
		}
	}
	if (velocityxz > 0.f && rotations.getSelectedValue() == 0) {
		player->bodyYaw = animYaw;
		player->yawUnused1 = animYaw;
		player->pitch = 0.f;
	}
}

void AutoPlay::onSendPacket(C_Packet* packet) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	targetList.clear();
	g_Data.forEachEntity(findPathEntity);
}

void AutoPlay::onLevelRender() {
	auto targetStrafe = moduleMgr->getModule<TargetStrafe>();
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
}

void AutoPlay::onDisable() {
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