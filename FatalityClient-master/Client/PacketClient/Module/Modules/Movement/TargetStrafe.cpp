#include "TargetStrafe.h"
#include "../pch.h"

using namespace std;
TargetStrafe::TargetStrafe() : IModule(0, Category::MOVEMENT, "Strafes around your target") {
	registerEnumSetting("Mode", &mode, 0);
	mode.addEntry("(Normal)", 0);
	mode.addEntry("(Adpaptive)", 1);
	registerBoolSetting("Controllable", &control, control);
	registerBoolSetting("Visualize", &visualize, visualize);
	registerBoolSetting("EdgeCheck", &edgeCheck, edgeCheck);
	registerBoolSetting("OnKey", &onKey, onKey);
	registerFloatSetting("Radius", &radius, radius, 0.f, 4.5f);
	registerFloatSetting("Speed", &speed, speed, 0.2f, 1.f);
}

const char* TargetStrafe::getRawModuleName() {
	return "TargetStrafe";
}

const char* TargetStrafe::getModuleName() {
	name = string("TargetStrafe ") + string(GRAY) + mode.GetEntry(mode.getSelectedValue()).GetName();
	return name.c_str();
}

static vector<C_Entity*> targetList;
void findEntityTSS(C_Entity* currentEntity, bool isRegularEntity) {
	static auto targetstrafeMod = moduleMgr->getModule<TargetStrafe>();

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
	if (currentEntity->width <= 0.01f || currentEntity->height <= 0.01f)  // Don't strafe this pesky antibot on 2b2e.org
		return;
	if (currentEntity->getEntityTypeId() == 64)  //item
		return;
	if (!TargetUtil::isValidTarget(currentEntity))
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist <= targetstrafeMod->range) {
		targetList.push_back(currentEntity);
	}
}

vec2_t getAngles34(vec3_t PlayerPosition, vec3_t EntityPosition) {
	vec2_t Angles;
	float dX = PlayerPosition.x - EntityPosition.x;
	float dY = PlayerPosition.y - EntityPosition.y;
	float dZ = PlayerPosition.z - EntityPosition.z;
	double distance = sqrt(dX * dX + dY * dY + dZ * dZ);
	Angles.x = (float)(atan2(dY, distance) * 180.0f / PI);
	Angles.y = (float)(atan2(dZ, dX) * 180.0f / PI) + 90.0f;
	return Angles;
};

struct CompareTargetEnArray {
	bool operator()(C_Entity* lhs, C_Entity* rhs) {
		auto player = g_Data.getLocalPlayer();
		return (int)((*lhs->getPos()).dist(*player->getPos())) < (int)((*rhs->getPos()).dist(*player->getPos()));
	}
};

void TargetStrafe::onEnable() {
	if (g_Data.getLocalPlayer() == nullptr)
		setEnabled(false);
}

void TargetStrafe::onTick(C_GameMode* gm) {
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	auto player = g_Data.getLocalPlayer();
	if (input == nullptr || !g_Data.canUseMoveKeys()) return;
	if (player == nullptr) return;

	targetListEmpty = targetList.empty();
	auto speedMod = moduleMgr->getModule<Speed>();
	targetList.clear();
	g_Data.forEachEntity(findEntityTSS);
	if (onKey && !GameData::isKeyDown(*input->spaceBarKey))
		return;

	if (collide) {
		vector<vec3_ti> sideBlocks;
		sideBlocks.reserve(8);

		float calcYaw = (gm->player->yaw + 90) * (PI / 180);
		vec3_t moveVec;
		float c = cos(calcYaw);
		float s = sin(calcYaw);

		for (int x = -1; x <= 1; x++) {
			for (int z = -1; z <= 1; z++) {
				if (x == 0 && z == 0)
					continue;

				sideBlocks.push_back(vec3_ti(x, 0, z));
			}
		}

		auto pPos = *gm->player->getPos();
		pPos.y = gm->player->aabb.lower.y;
		auto pPosI = vec3_ti(pPos.floor());

		auto isObstructed = [&](int yOff, AABB* obstructingBlock = nullptr, bool ignoreYcoll = false) {
			for (const auto& current : sideBlocks) {
				vec3_ti side = pPosI.add(0, yOff, 0).add(current);
				if (side.y < 0 || side.y >= 256)
					break;
				auto block = gm->player->region->getBlock(side);
				if (block == nullptr || block->blockLegacy == nullptr)
					continue;
				C_BlockLegacy* blockLegacy = block->toLegacy();
				if (blockLegacy == nullptr)
					continue;
				AABB collisionVec;
				if (!blockLegacy->getCollisionShape(&collisionVec, block, gm->player->region, &side, gm->player))
					continue;
				bool intersects = ignoreYcoll ? collisionVec.intersectsXZ(gm->player->aabb.expandedXZ(0.3f)) : collisionVec.intersects(gm->player->aabb.expandedXZ(0.3f));

				if (intersects) {
					if (obstructingBlock != nullptr)
						*obstructingBlock = collisionVec;
					return true;
				}
			}
			return false;
		};

		AABB lowerObsVec, upperObsVec;
		bool upperObstructed = isObstructed(1, &upperObsVec);

		bool lowerObstructed = isObstructed(0, &lowerObsVec);

		if (upperObstructed || lowerObstructed)
			intersectingTimer++;
		if ((upperObstructed || lowerObstructed)) {
			if (clockwise && intersectingTimer >= 1) {
				intersectingTimer = 0;
				clockwise = false;
			}
			if (!clockwise && intersectingTimer >= 1) {
				clockwise = true;
				intersectingTimer = 0;
			}
		}
	}

	sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
	if (!targetList.empty()) {
		vec2_t angle2 = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos());
		vec2_t angle = getAngles34(*gm->player->getPos(), *targetList[0]->getPos());
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();

		float distance = 99;
		float distanc = 999;
		vec3_t playerPos = *gm->player->getPos();
		vec3_t entPos = *targetList[0]->getPos();
		if (distanc > distance) {
			distance = targetList[0]->getPos()->dist(playerPos);
			distanc = distance;
		}

		if (control) {
			if (GameData::isKeyDown(*input->leftKey) && !GameData::isKeyDown(*input->rightKey)) {
				clockwise = false;
			}
			else if (GameData::isKeyDown(*input->rightKey) && !GameData::isKeyDown(*input->leftKey)) {
				clockwise = true;
			}
		}

		C_LocalPlayer* player = g_Data.getLocalPlayer();
		vec2_t CalcRot = getAngles34(*player->getPos(), entPos);
		if (clockwise) {
			CalcRot.y += 90.0f;
			if (distanc > radius) {
				CalcRot.y -= 45.0f;
			}
		}
		else {
			CalcRot.y -= 90.0f;
			if (distanc > radius) {
				CalcRot.y += 45.0f;
			}
		}

		if (edgeCheck) {
			bool onvoid = false;
			vec3_t* pos = gm->player->getPos();
			auto player = g_Data.getLocalPlayer();
			vec3_t blockBelow = g_Data.getLocalPlayer()->eyePos0;
			blockBelow.y -= g_Data.getLocalPlayer()->height;
			blockBelow.y -= 2.f;  // the block its checking
			for (int y = (int)pos->y - 3; y < pos->y + 0; y++) {
				if (player->region->getBlock(vec3_t{ blockBelow })->toLegacy()->blockId == 0) {
					onvoid = true;
					intersectingTimer2++;
				}
			}

			if (onvoid) {
				if (clockwise && intersectingTimer2 >= 5) {
					clockwise = false;
					intersectingTimer2 = 0;
				}
				if (!clockwise && intersectingTimer2 >= 5) {
					clockwise = true;
					intersectingTimer2 = 0;
				}
				onvoid = false;
			}
		}

		if (targetList.empty() || !g_Data.canUseMoveKeys())
			return;

		// Normal
		if (mode.getSelectedValue() == 0) {
			float dist2 = (*targetList[0]->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
			if (dist2 >= radius) {
				g_Data.getClientInstance()->getMoveTurnInput()->forward = true;
				g_Data.getClientInstance()->getMoveTurnInput()->backward = false;
			}
			else g_Data.getClientInstance()->getMoveTurnInput()->forward = false;
		}
		else if (mode.getSelectedValue() == 1) { // Velocity
			vec2_t CalcAngles = vec2_t((CalcRot.x) * -(PI / 180.f), (CalcRot.y + 90.0f) * (PI / 180.f));
			player->velocity.x = cos(CalcAngles.y) * cos(CalcAngles.x) * speed;
			player->velocity.z = sin(CalcAngles.y) * cos(CalcAngles.x) * speed;
		}
	}
}

void TargetStrafe::onPlayerTick(C_Player* plr) {
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	auto killaura = moduleMgr->getModule<Killaura>();
	if (plr == nullptr) return;
	if (onKey && !GameData::isKeyDown(*input->spaceBarKey))
		return;
	if (targetList.empty() || !g_Data.canUseMoveKeys())
		return;

	// Normal
	vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos());
	if (animYaw > angle.y) animYaw -= ((animYaw - angle.y) / 3);
	else if (animYaw < angle.y) animYaw += ((angle.y - animYaw) / 3);
	plr->yawUnused1 = animYaw;
	plr->bodyYaw = animYaw;
	if (mode.getSelectedValue() == 0)
		plr->yaw = animYaw;
	plr->pitch = angle.x;
}

void TargetStrafe::onMove(C_MoveInputHandler* input) {
}

void TargetStrafe::onDisable() {
	g_Data.getClientInstance()->getMoveTurnInput()->clearMovementState();
}

void TargetStrafe::onLevelRender() {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr || !visualize) return;

	sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
	if (!targetList.empty()) {
		auto player = g_Data.getLocalPlayer();
		if (player == nullptr || targetList[0] == nullptr) return;
		if (g_Data.isInGame()) {
			DrawUtils::setColor(1, 1, 1, 1);
			vec3_t permutations[21];
			for (int i = 0; i < 21; i++) permutations[i] = { sinf(i / PI) * radius, 0.f, cosf(i / PI) * radius };

			vec3_t pos = targetList[0]->getPosOld()->lerp(targetList[0]->getPos(), DrawUtils::getLerpTime());
			pos.y -= targetList[0]->height;  // feetpos

			std::vector<vec3_t> posList;
			for (auto& perm : permutations) posList.push_back(pos.add(perm));

			DrawUtils::drawLineStrip3D(posList, true);
		}
	}
}