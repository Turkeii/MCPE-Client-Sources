#include "MoveUtil.h"

void MoveUtil::freeze(vec3_t initPos, bool damageTime) {
	// execute in something that ticks fast, like onPlayerTick
	// initPos is the players pos in onEnable

	auto player = g_Data.getLocalPlayer();
	if (player != nullptr) {
		if (!(player->damageTime > 1 && damageTime)) {
			player->setPos(initPos);
			fullStop(false);
		}
	}
}

void MoveUtil::fullStop(bool damageTime) {
	auto player = g_Data.getLocalPlayer();
	if (player != nullptr) {
		if (!(player->damageTime > 1 && damageTime)) {
			player->velocity.x = 0.f;
			player->velocity.y = 0.f;
			player->velocity.z = 0.f;
		}
	}
}


void MoveUtil::stop(bool damageTime) {
	auto player = g_Data.getLocalPlayer();
	if (player != nullptr) {
		if (!(player->damageTime > 1 && damageTime)) {
			player->velocity.x = 0.f;
			player->velocity.z = 0.f;
		}
	}
}

void MoveUtil::setSpeed(float speed) {
	C_MoveInputHandler* input = g_Data.getClientInstance()->getMoveTurnInput();
	auto player = g_Data.getLocalPlayer();
	float calcYaw = (player->yaw + 90) * (PI / 180);
	float c = cos(calcYaw);
	float s = sin(calcYaw);

	vec2_t moveVec2D = { input->forwardMovement, -input->sideMovement };
	moveVec2D = { moveVec2D.x * c - moveVec2D.y * s, moveVec2D.x * s + moveVec2D.y * c };
	vec3_t moveVec;

	moveVec.x = moveVec2D.x * speed;
	moveVec.y = player->velocity.y;
	moveVec.z = moveVec2D.y * speed;
	player->lerpMotion(moveVec);
}

bool MoveUtil::keyPressed() {
	C_MoveInputHandler* input = g_Data.getClientInstance()->getMoveTurnInput();
	vec2_t movement = { input->forwardMovement, -input->sideMovement };
	return movement.magnitude() > 0.f;
}

bool MoveUtil::isMoving() {
	return g_Data.getLocalPlayer()->velocity.magnitudexz() > 0.05f;
}

int MoveUtil::getSpeed() {
	return g_Data.getLocalPlayer()->getBlocksPerSecond();
}