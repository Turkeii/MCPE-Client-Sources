#include "Speed.h"
Speed::Speed() : IModule(0, Category::MOVEMENT, "sped lol") {
	registerEnumSetting("Mode", &mode, 0);
	mode.addEntry("Vanilla", 0);
	mode.addEntry("Hive", 1);
	mode.addEntry("HiveLowhop", 3);
	mode.addEntry("HiveOnground", 5);
	//mode.addEntry("Inviscow", 4); // temp removed
	registerIntSetting("Timer", &timer, timer, 20, 35);
	registerFloatSetting("Height", &height, height, 0.000001f, 0.40f);
	registerFloatSetting("Speed", &speed, speed, 0.2f, 2.f);
}

Speed::~Speed() {
}

const char* Speed::getRawModuleName() {
	return "Speed";
}

const char* Speed::getModuleName() {
	if (mode.getSelectedValue() == 0) {  // Vanilla
		name = std::string("Speed ") + std::string(GRAY) + std::string("Vanilla");
		return name.c_str();
	}
	if (mode.getSelectedValue() == 1) {  // Hive
		name = std::string("Speed ") + std::string(GRAY) + std::string("Hive");
		return name.c_str();
	}
	if (mode.getSelectedValue() == 3) {  // Kow
		name = std::string("Speed ") + std::string(GRAY) + std::string("HiveLow");
		return name.c_str();
	}
	if (mode.getSelectedValue() == 4) {  // Inviscow
		name = std::string("Speed ") + std::string(GRAY) + std::string("Inviscow");
		return name.c_str();
	}
	if (mode.getSelectedValue() == 5) {  // Kow - Onground
		name = std::string("Speed ") + std::string(GRAY) + std::string("HiveGround");
		return name.c_str();
	}
}

void Speed::onEnable() {
	if (mode.getSelectedValue() == 3) {
		auto box = g_Data.addNotification("Speed:", "Speed: Gamer Mode Enabled!");
		box->duration = 5;
	}
}

void Speed::onTick(C_GameMode* gm) {
	if (g_Data.getLocalPlayer() == nullptr)
		return;

	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	*g_Data.getClientInstance()->minecraft->timer = static_cast<float>(timer);
	if (mode.getSelectedValue() == 1) {
		if (gm->player->onGround) {
			lhtick++;
			if (lhtick >= 3)
				lhtick = 0;
			if (g_Data.getLocalPlayer()->velocity.squaredxzlen() >= 0.200 && lhtick == 0) {
				gm->player->velocity.x *= .387f;
				gm->player->velocity.z *= .387f;
			} else if (g_Data.getLocalPlayer()->velocity.squaredxzlen() <= 0.1 && lhtick == 0)
				return;
		}
	}
	if (mode.getSelectedValue() == 1) {
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
		if (lowerObstructed || upperObstructed) intersect = true;
		else intersect = false;

		auto player = g_Data.getLocalPlayer();
		float yaw = player->yaw;
		if (input->spaceBarKey) {
			if (input->forwardKey && input->backKey && input->rightKey && input->leftKey) {
			}
		}
	}

	if (mode.getSelectedValue() == 3 && g_Data.isInGame()) {
		if (g_Data.getLocalPlayer()->fallDistance >= 2 && !preventKick) {
			//player->velocity = vec3_t(0.f, -.8f, 0.f);
			*g_Data.getClientInstance()->minecraft->timer = 20;
			g_Data.getLocalPlayer()->velocity.x = 0.f;
			g_Data.getLocalPlayer()->velocity.z = 0.f;
			g_Data.getLocalPlayer()->fallDistance = 0;
			preventKick = true;
			moduleMgr->getModule<Speed>()->setEnabled(false);
			auto boxWarn = g_Data.addNotification("Speed:", "Speed: Disabled to prevent kick");
			boxWarn->duration = 7;
		}
	}
}

void Speed::onMove(C_MoveInputHandler* input) {
	auto targetStrafe = moduleMgr->getModule<TargetStrafe>();
	if (g_Data.getLocalPlayer() == nullptr)
		return;

	vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
	bool pressed = moveVec2d.magnitude() > 0.f;
	auto player = g_Data.getLocalPlayer();

	if (mode.getSelectedValue() == 0) {  // Vanilla
		static bool velocity = false;
		if (height >= 0.385) {
			if (player->onGround && pressed) player->jumpFromGround();
			velocity = false;
		} else {
			velocity = true;
		}
		if (height <= 0.04 && !input->isJumping) {
			player->velocity.y += height;
			velocity = false;
		}
		if (player->onGround && pressed && !input->isJumping && velocity)
			player->velocity.y = height;
		float calcYaw = (player->yaw + 90) * (PI / 180);
		vec3_t moveVec;
		float c = cos(calcYaw);
		float s = sin(calcYaw);
		moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};
		moveVec.x = moveVec2d.x * speed;
		moveVec.y = player->velocity.y;
		moveVec.z = moveVec2d.y * speed;
		if (targetStrafe->isEnabled() && targetStrafe->mode.getSelectedValue() == 1 && !targetStrafe->targetListEmpty)
			return;
		if (!pressed && player->damageTime == 0) {
			player->velocity.x *= 0;
			player->velocity.z *= 0;
		}
		if (pressed) player->lerpMotion(moveVec);
	}
	if (mode.getSelectedValue() == 1) {  // Hive
		/*isOnGround = player->onGround;
		auto player = g_Data.getLocalPlayer();
		vec2_t movement = {input->forwardMovement, -input->sideMovement};
		bool pressed = movement.magnitude() > 0.f;
		float calcYaw = (player->yaw + 90) * (PI / 180);
		vec3_t moveVec;
		float c = cos(calcYaw);
		float s = sin(calcYaw);
		movement = {movement.x * c - movement.y * s, movement.x * s + movement.y * c};
		if (pressed && player->onGround) {
			//input->isJumping = true;
			player->jumpFromGround();
		}
		moveVec.x = movement.x * 0.305;
		moveVec.y = player->velocity.y;
		moveVec.z = movement.y * 0.305;
		if (targetStrafe->isEnabled() && targetStrafe->mode.getSelectedValue() == 1 && !targetStrafe->targetListEmpty)
			return;
		if (pressed) player->lerpMotion(moveVec);*/
		vec2_t movement = {input->forwardMovement, -input->sideMovement};
		bool pressed = movement.magnitude() > 0.f;
		float calcYaw = (player->yaw + 90) * (PI / 180);
		vec3_t moveVec;
		float c = cos(calcYaw);
		float s = sin(calcYaw);
		movement = {movement.x * c - movement.y * s, movement.x * s + movement.y * c};
		if (pressed && player->onGround) {
			//input->isJumping = true;
			player->jumpFromGround();
		}
		if (input->isJumping) {
			moveVec.x = movement.x * speed;
			moveVec.y = player->velocity.y;
			moveVec.z = movement.y * speed;
			if (!player->onGround) {
				if (intersect) *g_Data.getClientInstance()->minecraft->timer = 16;
				else *g_Data.getClientInstance()->minecraft->timer = 26;
			} else {
				*g_Data.getClientInstance()->minecraft->timer = 16;
				if (pressed) player->lerpMotion(moveVec);
			}
		} else {
			moveVec.x = movement.x * 0.315;
			moveVec.y = player->velocity.y;
			moveVec.z = movement.y * 0.315;
			if (pressed) player->lerpMotion(moveVec);
		}
		if (g_Data.getLocalPlayer()->velocity.squaredxzlen() > 0.01) {
			C_MovePlayerPacket p = C_MovePlayerPacket(g_Data.getLocalPlayer(), player->getPos()->add(vec3_t(moveVec.x / 1.3f, 0.f, moveVec.z / 1.3f)));
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
			C_MovePlayerPacket p2 = C_MovePlayerPacket(g_Data.getLocalPlayer(), player->getPos()->add(vec3_t(player->velocity.x / 3.13f, 0.f, player->velocity.z / 2.3f)));
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p2);
		}
	}
	if (mode.getSelectedValue() == 3 && g_Data.isInGame()) {
		if (player == nullptr) return;

		vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
		bool pressed = moveVec2d.magnitude() > 0.01f;

		/*if (player->onGround && pressed && groundTimer >= 2) {
			player->jumpFromGround();
			player->velocity.y = -0.1f;
			player->velocity.y = 0.23;
			groundTimer = 0;
		}*/
		if (player->onGround && pressed && groundTimer >= 2) {
			player->jumpFromGround();
			player->velocity.y = -0.1f;
			player->velocity.y = 0.144;
			groundTimer = 0;
		}

		if (player->onGround) {
			player->fallDistance = 0;
			preventKick = false;
			groundTimer++;
		}

		float calcYaw = (player->yaw + 90) * (PI / 180);
		float calcYaw2 = (player->yaw - 90) * (PI / 180);
		vec3_t moveVec;
		float c = cos(calcYaw);
		float s = sin(calcYaw);
		float c2 = cos(calcYaw2);
		float s2 = sin(calcYaw2);
		moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};
		moveVec.x = moveVec2d.x * speed;
		moveVec.y = player->velocity.y;
		moveVec.z = moveVec2d.y * speed;

		if (pressed) player->lerpMotion(moveVec);
		if (g_Data.getLocalPlayer()->velocity.squaredxzlen() > 0.01) {
			C_MovePlayerPacket p = C_MovePlayerPacket(g_Data.getLocalPlayer(), player->getPos()->add(vec3_t(moveVec.x / 2.1f, moveVec.y / 2, moveVec.z / 2.1f)));
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
		}

		/*if (player->fallDistance >= 3 && !preventKick) {
			player->fallDistance = 0;
			preventKick = true;
			moduleMgr->getModule<Speed>()->setEnabled(false);
			auto boxWarn = g_Data.addNotification("Speed:", "Speed: Disabled to prevent kick");
			boxWarn->duration = 7;
		}*/

	}

	if (mode.getSelectedValue() == 5 && g_Data.isInGame()) {
		float calcYaw = (player->yaw + 90) * (PI / 180);
		vec3_t moveVec;
		float c = cos(calcYaw);
		float s = sin(calcYaw);
		moveVec2d = { moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c };
		moveVec.x = moveVec2d.x * speed;
		moveVec.y = player->velocity.y;
		moveVec.z = moveVec2d.y * speed;
		if (pressed)
			player->lerpMotion(moveVec);
		if (pressed && player->onGround) {
			if (g_Data.getLocalPlayer()->velocity.squaredxzlen() > 0.01) {
				C_MovePlayerPacket p2 = C_MovePlayerPacket(g_Data.getLocalPlayer(), player->getPos()->add(vec3_t(player->velocity.x / 1.3f, 0.f, player->velocity.z / 2.3f)));
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p2);
				//Made by Founder, don't take, skid, re-purpose, or claim
			}
		}
	}
}

void Speed::onDisable() {
	auto scaffold = moduleMgr->getModule<Scaffold>();
	auto player = g_Data.getLocalPlayer();
	*g_Data.getClientInstance()->minecraft->timer = 20.f;
	if (!player->onGround) {
		player->velocity.x = 0.f;
		player->velocity.z = 0.f;
	}
	preventKick = false;
}

void Speed::onSendPacket(C_Packet* packet) {
	auto player = g_Data.getLocalPlayer();
	if (packet->isInstanceOf<C_MovePlayerPacket>() && g_Data.getLocalPlayer() != nullptr && mode.getSelectedValue() == 3 && g_Data.isInGame()) {
		auto* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
		C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
		if (input == nullptr)
			return;

		float yaw = player->yaw;

		if (GameData::isKeyDown(*input->forwardKey) && GameData::isKeyDown(*input->backKey))
			return;
		else if (GameData::isKeyDown(*input->forwardKey) && GameData::isKeyDown(*input->rightKey) && !GameData::isKeyDown(*input->leftKey)) {
			yaw += 45.f;
		} else if (GameData::isKeyDown(*input->forwardKey) && GameData::isKeyDown(*input->leftKey) && !GameData::isKeyDown(*input->rightKey)) {
			yaw -= 45.f;
		} else if (GameData::isKeyDown(*input->backKey) && GameData::isKeyDown(*input->rightKey) && !GameData::isKeyDown(*input->leftKey)) {
			yaw += 135.f;
		} else if (GameData::isKeyDown(*input->backKey) && GameData::isKeyDown(*input->leftKey) && !GameData::isKeyDown(*input->rightKey)) {
			yaw -= 135.f;
		} else if (GameData::isKeyDown(*input->forwardKey)) {
		} else if (GameData::isKeyDown(*input->backKey)) {
			yaw += 180.f;
		} else if (GameData::isKeyDown(*input->rightKey) && !GameData::isKeyDown(*input->leftKey)) {
			yaw += 90.f;
		} else if (GameData::isKeyDown(*input->leftKey) && !GameData::isKeyDown(*input->rightKey)) {
			yaw -= 90.f;
		}
		if (yaw >= 180)
			yaw -= 360.f;
		float calcYaw = (yaw + 90) * (PI / 180);

		movePacket->headYaw = yaw;
	}
}
