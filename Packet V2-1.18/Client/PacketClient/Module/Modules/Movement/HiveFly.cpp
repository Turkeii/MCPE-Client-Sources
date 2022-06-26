#include "HiveFly.h"

HiveFly::HiveFly() : IModule(0, Category::MOVEMENT, "How the fuck does this bypass ?!?!?") {
	registerBoolSetting("Clip Up", &clip, clip);
	registerFloatSetting("Clip Height", &clipHeight, clipHeight, 0.f, 5.f);
}

const char* HiveFly::getModuleName() {
	return ("HiveFly");
}

float epicHiveFlySpeedArrayThingy[15] = {
	0.910000,
	0.615559,
	0.583347,
	0.554032,
	0.527356,
	0.503081,
	0.480991,
	0.460887,
	0.442595,
	0.425948,
	0.410799,
	0.397015,
	0.384470,
	0.373055,
	0.362665 };

int flySpeedIndex = 0;

int stopYThingy = 0;

void HiveFly::onEnable() {
	srand(time(NULL));
	counter = 0;
	counter69 = 0;
	flySpeedIndex = 0;
	stopYThingy = 0;
	C_LocalPlayer* player = g_Data.getLocalPlayer();
	if (player != nullptr) {
		if (player->onGround == true) {
			if (clip) {
				vec3_t myPos = *player->getPos();
				myPos.y += clipHeight;
				player->setPos(myPos);
			}
			else {
				counter69++;
				if (counter69 <= 2) {
					vec3_t moveVec;
					moveVec.x = 0;
					moveVec.y = 0.7f;
					moveVec.z = 0;
					g_Data.getLocalPlayer()->lerpMotion(moveVec);
				}
			}
		}
		else {
			counter69 = 8;
		}
	}
}

void HiveFly::onTick(C_GameMode* gm) {
}

void HiveFly::onMove(C_MoveInputHandler* input) {
	counter69++;
	C_LocalPlayer* player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	vec2_t moveVec2d = { input->forwardMovement, -input->sideMovement };
	bool pressed = moveVec2d.magnitude() > 0.01f;

	float calcYaw = (player->yaw + 90) * (PI / 180);
	vec3_t moveVec;
	float c = cos(calcYaw);
	float s = sin(calcYaw);
	moveVec2d = { moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c };
	float moveSpeed = epicHiveFlySpeedArrayThingy[flySpeedIndex++ % 15];
	moveVec.x = moveVec2d.x * moveSpeed;

	if (stopYThingy >= 3) {
		stopYThingy = 0;
		moveVec.y = player->velocity.y;
	}
	else moveVec.y = 0.f;
	stopYThingy++;

	moveVec.z = moveVec2d.y * moveSpeed;

	if (counter69 >= 8 && !clip) {
		if (pressed) player->lerpMotion(moveVec);
		//Utils::patchBytes((BYTE*)ViewBobBoi, (BYTE*)"\xB8\x01\x00\x00\x00\x90\x90", 7);
	}
	else if (clip) {
		if (pressed) player->lerpMotion(moveVec);
	}

	if (!pressed) {
		player->velocity.x = 0;
		player->velocity.z = 0;
	}
}

void HiveFly::onDisable() {
	counter69 = 0;
	counter = 0;
	if (g_Data.getLocalPlayer() != nullptr) {
		C_LocalPlayer* player = g_Data.getLocalPlayer();
		player->velocity.x = 0.f;
		player->velocity.y = 0.f;
		player->velocity.z = 0.f;
		*g_Data.getClientInstance()->minecraft->timer = 20.f;
	}
}