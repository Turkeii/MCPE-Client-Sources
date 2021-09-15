#include "MineplexFly.h"

MineplexFly::MineplexFly() : IModule(0, Category::WORLD, "A fly that bypasses Mineplex") {
	registerFloatSetting("Speed", &this->speed2, this->speed2, 0.50f, 1.00f);  //allows you to ajust your speed.
}

MineplexFly::~MineplexFly() {
}

const char* MineplexFly::getModuleName() {
	return ("MineplexFly");
}

bool MineplexFly::isFlashMode() {
	return false;
}

void MineplexFly::onEnable() {
	auto player = g_Data.getLocalPlayer();
	player->animateHurt();
	g_Data.getLocalPlayer()->setPos((*g_Data.getLocalPlayer()->getPos()).add(0, 3.25, 0));  //Sets you in the air 1.25 blocks high.
}

void MineplexFly::onTick(C_GameMode* gm) {
	//keeps you in the air
	auto player = g_Data.getLocalPlayer();
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	float yaw = player->yaw;
	player->stepHeight = 0.f;

	if (counter >= 0) {
		gm->player->velocity = vec3_t(0, 0, 0);  //0 velocity
	}
	if (counter == 5) {
		counter = 0;
	} else {
		counter++;
	}

	if (counter == 5) {
		vec3_t pos = *gm->player->getPos();
		player->velocity.y -= 0.1f;  //goes down a bit every tick because hive will kick you if you ae
		gm->player->setPos(pos);
	}
}

void MineplexFly::onMove(C_MoveInputHandler* input) {
	auto player = g_Data.getLocalPlayer();
	float yaw = player->yaw;
	if (player == nullptr) return;
	if (player->isSneaking())
		return;
	vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
	bool pressed = moveVec2d.magnitude() > 0.01f;

	if (input->right) {
		yaw += 90.f;
		if (input->forward)
			yaw -= 20.f;

		else if (input->backward)
			yaw += 45.f;
	}
	if (input->left) {
		yaw -= 90.f;
		if (input->forward)
			yaw += 45.f;
		else if (input->backward)
			yaw -= 45.f;
	}

	if (input->backward && !input->left && !input->right)
		yaw += 180.f;

	float calcYaw = (yaw + 90.f) * (PI / 180.f);
	vec3_t moveVec;
	moveVec.x = cos(calcYaw) * speed2;
	moveVec.y = player->velocity.y;
	moveVec.z = sin(calcYaw) * speed2;
	if (pressed) player->lerpMotion(moveVec);
}

void MineplexFly::onDisable() {
	auto player = g_Data.getLocalPlayer();
	*g_Data.getClientInstance()->minecraft->timer = 20.f;  //makes sure your timer is noraml (20)
	g_Data.getLocalPlayer()->stepHeight = 0.5625f;         //just leave it like this idk u can remove it
}