#include "TargetStrafeOld.h"
#include "../pch.h"

TargetStrafeOld::TargetStrafeOld() : IModule(0, Category::MOVEMENT, "TargetStrafeOld - Made by Little Kow (holy this is old)") {
	//registerFloatSetting("ChaseRange", &range, range, 2.f, 500.f);
	registerBoolSetting("RequireSpeed", &speedCheck, speedCheck);
	registerBoolSetting("CollideCheck", &collide, collide);
	registerBoolSetting("EdgeCheck", &avoidvoid, avoidvoid);
	registerBoolSetting("AutoPlay", &autoplayMode, autoplayMode);
	registerBoolSetting("OnKey", &spacekeyMode, spacekeyMode);
	registerFloatSetting("Speed", &speedMod, speedMod, 0.3f, 10.f);
	registerFloatSetting("Radius", &StrafeDistance, StrafeDistance, 1.f, 5.f);
}

const char* TargetStrafeOld::getModuleName() {
	return ("TargetStrafeOld");
}

void TargetStrafeOld::onMove(C_MoveInputHandler* input) {
	auto player = g_Data.getLocalPlayer();
	vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
	bool pressed = moveVec2d.magnitude() > 0.01f;
	if (!speedCheck) {
		if (spacekeyMode)
			if (player->onGround && pressed)
				player->jumpFromGround();
	}
}

static std::vector<C_Entity*> targetList;

void findEntityTSOLD(C_Entity* currentEntity, bool isRegularEntity) {
	static auto TargetStrafeOldMod = moduleMgr->getModule<TargetStrafeOld>();

	if (currentEntity == nullptr)
		return;

	if (currentEntity == g_Data.getLocalPlayer())  // Skip Local player
		return;

	if (!g_Data.getLocalPlayer()->canAttack(currentEntity, false))
		return;

	if (!g_Data.getLocalPlayer()->isAlive())
		return;

	if (!currentEntity->isAlive())
		return;

	if (TargetStrafeOldMod->isMobAura) {
		if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 63)
			return;
		if (currentEntity->width <= 0.01f || currentEntity->height <= 0.01f)  // Don't hit this pesky antibot on 2b2e.org
			return;
		if (currentEntity->getEntityTypeId() == 64)  // item
			return;
	} else {
		if (!TargetUtil::isValidTarget(currentEntity))
			return;
	}

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < TargetStrafeOldMod->range) {
		targetList.push_back(currentEntity);
	}
}

vec2_t getAngles3(vec3_t PlayerPosition, vec3_t EntityPosition) {
	vec2_t Angles;
	float dX = PlayerPosition.x - EntityPosition.x;
	float dY = PlayerPosition.y - EntityPosition.y;
	float dZ = PlayerPosition.z - EntityPosition.z;
	double distance = sqrt(dX * dX + dY * dY + dZ * dZ);
	Angles.x = (float)(atan2(dY, distance) * 180.0f / PI);
	Angles.y = (float)(atan2(dZ, dX) * 180.0f / PI) + 90.0f;
	return Angles;
};

void TargetStrafeOld::onTick(C_GameMode* gm) {
	if (autoplayMode) {
		range = 500;
} else {
	range = 10;
}
	targetList.clear();
	g_Data.forEachEntity(findEntityTSOLD);
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	if (input == nullptr) return;

	if (collide) {
		std::vector<vec3_ti> sideBlocks;
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
			C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
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

		if (upperObstructed || lowerObstructed) {
			intersectingTimer++;
		}
		if ((upperObstructed || lowerObstructed)) {
			if (clockwise && intersectingTimer >= 1) {
				//clientMessageF("changed");
				intersectingTimer = 0;
				clockwise = false;
			}
			if (!clockwise && intersectingTimer >= 1) {
				clockwise = true;
				//clientMessageF("changed-2");
				intersectingTimer = 0;
			}
		}
	}

	for (auto& i : targetList) {
		vec2_t angle2 = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos());
		vec2_t angle = getAngles3(*gm->player->getPos(), *targetList[0]->getPos());
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		if (packetMode && localPlayer->yaw != 0 && localPlayer->pitch != 0) {
			localPlayer->setRot(angle2);
		}
		if (jump && gm->player->onGround) {
			gm->player->jumpFromGround();
		}

		if (testMode) {
			float distance = 99;
			float distanc = 999;
			vec3_t myPos = *gm->player->getPos();
			vec3_t EntPos = *i->getPos();
			if (distanc > distance) {
				distance = i->getPos()->dist(myPos);
				distanc = distance;
			}
			if (GameData::isKeyDown(*input->leftKey) && !GameData::isKeyDown(*input->rightKey)) {
				clockwise = false;
			} else if (GameData::isKeyDown(*input->rightKey) && !GameData::isKeyDown(*input->leftKey)) {
				clockwise = true;
			}
			C_LocalPlayer* player = g_Data.getLocalPlayer();

			vec2_t CalcRot = getAngles3(*player->getPos(), EntPos);
			if (clockwise) {
				CalcRot.y += 90.0f;
				if (distanc > StrafeDistance) CalcRot.y -= 45.0f;
			} else {
				CalcRot.y -= 90.0f;
				if (distanc > StrafeDistance) CalcRot.y += 45.0f;
			}

			if (avoidvoid) {
				bool onvoid = false;
				if (player->region->getBlock(vec3_t{myPos.x, myPos.y - 3, myPos.z})->toLegacy()->blockId == 0) {
					onvoid = true;
					intersectingTimer2++;
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
				}
			}
			if (!speedCheck) {
				if (spacekeyMode)
					if (GameData::isKeyDown(*input->spaceBarKey)) {
						vec2_t CalcAngles = vec2_t((CalcRot.x) * -(PI / 180.f), (CalcRot.y + 90.0f) * (PI / 180.f));
						player->velocity = vec3_t(cos(CalcAngles.y) * cos(CalcAngles.x) * speedMod, player->velocity.y, sin(CalcAngles.y) * cos(CalcAngles.x) * speedMod);
					}
			}
			if (!speedCheck) {
				if (!spacekeyMode) {
					vec2_t CalcAngles = vec2_t((CalcRot.x) * -(PI / 180.f), (CalcRot.y + 90.0f) * (PI / 180.f));
					player->velocity = vec3_t(cos(CalcAngles.y) * cos(CalcAngles.x) * speedMod, player->velocity.y, sin(CalcAngles.y) * cos(CalcAngles.x) * speedMod);
				}
			}
			if (spacekeyMode) {
				auto bhopMod = moduleMgr->getModule<Speed>();
				if (speedCheck)
					if (this->isEnabled()) {
						if (GameData::isKeyDown(*input->spaceBarKey)) {
							vec2_t CalcAngles = vec2_t((CalcRot.x) * -(PI / 180.f), (CalcRot.y + 90.0f) * (PI / 180.f));
							player->velocity = vec3_t(cos(CalcAngles.y) * cos(CalcAngles.x) * speedMod, player->velocity.y, sin(CalcAngles.y) * cos(CalcAngles.x) * speedMod);
						}
					}
			}

			if (!spacekeyMode) {
				auto bhopMod = moduleMgr->getModule<Speed>();
				if (speedCheck)
					if (this->isEnabled()) {
						vec2_t CalcAngles = vec2_t((CalcRot.x) * -(PI / 180.f), (CalcRot.y + 90.0f) * (PI / 180.f));
						player->velocity = vec3_t(cos(CalcAngles.y) * cos(CalcAngles.x) * speedMod, player->velocity.y, sin(CalcAngles.y) * cos(CalcAngles.x) * speedMod);
					}
			}
		}
	}
}

void TargetStrafeOld::onEnable() {
	if (g_Data.getLocalPlayer() == nullptr)
		this->setEnabled(false);
}

void TargetStrafeOld::onSendPacket(C_Packet* packet) {
}

void TargetStrafeOld::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
}

void TargetStrafeOld::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
}