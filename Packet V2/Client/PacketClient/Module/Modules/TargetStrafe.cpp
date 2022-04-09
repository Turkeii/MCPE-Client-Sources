#include "TargetStrafe.h"

TargetStrafe::TargetStrafe() : IModule(0, Category::MOVEMENT, "Strafe around the target") {
	registerEnumSetting("Support", &mode, 0);
	mode.addEntry("None", 0);
	mode.addEntry("Speed", 1);
	registerBoolSetting("Controllable", &control, control);
	registerBoolSetting("DrawCircle", &drawCircle, drawCircle);
	registerBoolSetting("EdgeCheck", &edgeCheck, edgeCheck);
	registerBoolSetting("OnKey", &onKey, onKey);
	//registerBoolSetting("SetRot", &test, test);
	registerFloatSetting("Radius", &radius, radius, 1, 4.5);
	registerFloatSetting("Speed", &speed, speed, 0.2, 1);
}

TargetStrafe::~TargetStrafe() {
}

const char* TargetStrafe::getModuleName() {
	return ("TargetStrafe");
}

static std::vector<C_Entity*> taregtList69420;

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
	if (!Target::isValidTarget(currentEntity))
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < targetstrafeMod->range) {
		taregtList69420.push_back(currentEntity);
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
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
	}
};

void TargetStrafe::onEnable() {
	if (g_Data.getLocalPlayer() == nullptr)
		setEnabled(false);
	initRender = true;
}

void TargetStrafe::onTick(C_GameMode* gm) {
	targetListEmpty = taregtList69420.empty();
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	float speedXZ = g_Data.getLocalPlayer()->velocity.magnitudexz();
	auto speedMod = moduleMgr->getModule<Speed>();
	taregtList69420.clear();
	g_Data.forEachEntity(findEntityTSS);
	playerVel = gm->player->velocity;
	if (input == nullptr || !g_Data.canUseMoveKeys()) return;
	if (mode.getSelectedValue() == 1 && !speedMod->isEnabled())
		return;
	if (onKey && !GameData::isKeyDown(*input->spaceBarKey))
		return;

	if (initRender) {
		renderTimer++;
		if (renderTimer >= 200) renderTimer = 200;
	}

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

	std::sort(taregtList69420.begin(), taregtList69420.end(), CompareTargetEnArray());
	for (auto& i : taregtList69420) {
		vec2_t angle2 = g_Data.getLocalPlayer()->getPos()->CalcAngle(*taregtList69420[0]->getPos());
		vec2_t angle = getAngles34(*gm->player->getPos(), *taregtList69420[0]->getPos());
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();

		float distance = 99;
		float distanc = 999;
		vec3_t playerPos = *gm->player->getPos();
		vec3_t entPos = *i->getPos();
		if (distanc > distance) {
			distance = i->getPos()->dist(playerPos);
			distanc = distance;
		}

		if (control) {
			if (GameData::isKeyDown(*input->leftKey) && !GameData::isKeyDown(*input->rightKey)) {
				clockwise = false;
			} else if (GameData::isKeyDown(*input->rightKey) && !GameData::isKeyDown(*input->leftKey)) {
				clockwise = true;
			}
		}

		C_LocalPlayer* player = g_Data.getLocalPlayer();
		vec2_t CalcRot = getAngles34(*player->getPos(), entPos);
		if (clockwise) {
			CalcRot.y += 90.0f;
			if (distanc > radius) CalcRot.y -= 45.0f;
		} else {
			CalcRot.y -= 90.0f;
			if (distanc > radius) CalcRot.y += 45.0f;
		}

		if (edgeCheck) {
			bool onvoid = false;
			vec3_t* pos = gm->player->getPos();
			auto player = g_Data.getLocalPlayer();
			vec3_t blockBelow = g_Data.getLocalPlayer()->eyePos0;
			blockBelow.y -= g_Data.getLocalPlayer()->height;
			blockBelow.y -= 2.f;  // the block its checking
			for (int y = (int)pos->y - 3; y < pos->y + 0; y++) {
				if (player->region->getBlock(vec3_t{blockBelow})->toLegacy()->blockId == 0) {
					onvoid = true;
					intersectingTimer2++;
				}
			}

			if (onvoid) {
				//g_Data.getClientInstance()->getMoveTurnInput()->forward = true; // sometimes very annoying
				if (clockwise && intersectingTimer2 >= 5) {
					clockwise = false;
					intersectingTimer2 = 0;
				}
				if (!clockwise && intersectingTimer2 >= 5) {
					clockwise = true;
					intersectingTimer2 = 0;
				}
				onvoid = false;
			} else {
			}
		}

		if (test) {
			if (taregtList69420.empty())
				return;
			int dist2 = (int)(*taregtList69420[0]->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
			vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*i->getPos());
			auto player = g_Data.getLocalPlayer();

			player->setRot(angle);
			if (dist2 >= radius) {
				g_Data.getClientInstance()->getMoveTurnInput()->forward = true;
			} else {
				g_Data.getClientInstance()->getMoveTurnInput()->forward = false;
			}
		} else {
			vec2_t CalcAngles = vec2_t((CalcRot.x) * -(PI / 180.f), (CalcRot.y + 90.0f) * (PI / 180.f));
			if (mode.getSelectedValue() == 1) {  // Support: Speed
				player->velocity = vec3_t(cos(CalcAngles.y) * cos(CalcAngles.x) * speed, player->velocity.y, sin(CalcAngles.y) * cos(CalcAngles.x) * speed);
			} else {
				player->velocity = vec3_t(cos(CalcAngles.y) * cos(CalcAngles.x) * speed, player->velocity.y, sin(CalcAngles.y) * cos(CalcAngles.x) * speed);
			}
		}
	}
}

void TargetStrafe::onMove(C_MoveInputHandler* input) {
	auto player = g_Data.getLocalPlayer();
	auto speedd = moduleMgr->getModule<Speed>();
	if (mode.getSelectedValue() == 1 && !speedd->isEnabled() || !g_Data.canUseMoveKeys())
		return;
	if (onKey && !input->isJumping)
		return;
	if (mode.getSelectedValue() == 1 && !targetListEmpty && player->onGround) {
		player->jumpFromGround();
	}
}

void TargetStrafe::onDisable() {
	g_Data.getClientInstance()->getMoveTurnInput()->forward = false;
	initRender = false;
	renderTimer = 0;
}

void TargetStrafe::onSendPacket(C_Packet* packet) {
}

float ttt = 0;
void TargetStrafe::onLevelRender() {
	if (renderTimer >= 4 && !taregtList69420.empty()) {
		std::sort(taregtList69420.begin(), taregtList69420.end(), CompareTargetEnArray());
		ttt++;
		DrawUtils::setColor(1, 1, 1, 0.9f);

		vec3_t permutations[56];
		for (int i = 0; i < 56; i++) {
			permutations[i] = {sinf((i * 10.f) / (180 / PI)), 0.f, cosf((i * 10.f) / (180 / PI))};
		}

		const float coolAnim = 0.9f + 0.9f * sin((ttt / 60) * PI * 1);

		vec3_t* start = taregtList69420[0]->getPosOld();
		vec3_t* end = taregtList69420[0]->getPos();

		auto te = DrawUtils::getLerpTime();
		vec3_t pos = start->lerp(end, te);

		auto yPos = pos.y;
		yPos -= 1.6f;
		yPos += coolAnim;

		std::vector<vec3_t> posList;
		posList.reserve(56);
		for (auto& perm : permutations) {
			vec3_t curPos(pos.x, yPos, pos.z);
			posList.push_back(curPos.add(perm));
		}

		DrawUtils::drawLinestrip3d(posList);
	}
}

void TargetStrafe::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
}

void TargetStrafe::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
}
