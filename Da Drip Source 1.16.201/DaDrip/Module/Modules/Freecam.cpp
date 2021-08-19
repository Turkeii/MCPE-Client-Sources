#include "Freecam.h"

#include <chrono>

Freecam::Freecam() : IModule('V', Category::VISUAL, "Move your cam without moving the player") {
	registerFloatSetting("Horizontal Speed", &this->speed, this->speed, 0.1f, 0.8f);
	registerFloatSetting("Vertical Speed", &this->vspeed, this->vspeed, 0.1f, 0.8f);
}

Freecam::~Freecam() {
}

const char* Freecam::getModuleName() {
	return ("Freecam");
}

int prevGm = -1;

void Freecam::onPostRender(C_MinecraftUIRenderContext*) {
	// How long since the previous frame?
	static auto prevTime = std::chrono::high_resolution_clock::now();
	auto now = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> tDiff = now - prevTime;

	// Update time for the next frame
	prevTime = now;

	// Balance speed depending on how long its been
	float tMultiplier = tDiff.count() / 0.05f;

	// Don't jump 90 miles if the user disabled freecam for a while
	if (wasDisabled) {
		tMultiplier = 1.f;
		wasDisabled = false;
	}

	auto player = g_Data.getLocalPlayer();  // local player

	float yaw = cameraRot.y;                                                          // camera yaw
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();  // Game keys
	player->velocity.y = 0.f;
	player->velocity.x = 0.f;
	player->velocity.z = 0.f;  // Set the velocity if nothing is pressed
	if (GameData::isKeyDown(*input->sneakKey)) {
		targetPos.y -= speed * tMultiplier;
	}
	if (GameData::isKeyDown(*input->spaceBarKey)) {
		targetPos.y += speed * tMultiplier;
	}

	if (GameData::isKeyDown(*input->rightKey)) {
		yaw += 90.f;
		if (GameData::isKeyDown(*input->forwardKey))
			yaw -= 45.f;
		else if (GameData::isKeyDown(*input->backKey))
			yaw += 45.f;
	}
	if (GameData::isKeyDown(*input->leftKey)) {
		yaw -= 90.f;
		if (GameData::isKeyDown(*input->forwardKey))
			yaw += 45.f;
		else if (GameData::isKeyDown(*input->backKey))
			yaw -= 45.f;
	}
	if (GameData::isKeyDown(*input->backKey) && !GameData::isKeyDown(*input->leftKey) && !GameData::isKeyDown(*input->rightKey))
		yaw += 180.f;
	bool pressed = GameData::isKeyDown(*input->forwardKey) || GameData::isKeyDown(*input->backKey) || GameData::isKeyDown(*input->rightKey) || GameData::isKeyDown(*input->leftKey);
	if (pressed) {
		float calcYaw = (yaw + 90) * (PI / 180);
		vec3_t moveVec;
		moveVec.x = cos(calcYaw) * speed;
		moveVec.y = player->velocity.y;
		moveVec.z = sin(calcYaw) * speed;
		targetPos = targetPos.add(moveVec.mul(tMultiplier));
	}
}

void Freecam::onTick(C_GameMode* gm) {
	g_Data.getClientInstance()->getMoveTurnInput()->clearMovementState();
	g_Data.getLocalPlayer()->setSneaking(false);
	g_Data.getLocalPlayer()->velocity = {0.f, 0.f, 0.f};
}

void Freecam::onEnable() {
	targetPos = *g_Data.getLocalPlayer()->getPos();
	lastPos = targetPos;
	wasDisabled = true;
}

void Freecam::onDisable() {
	wasDisabled = true;
}