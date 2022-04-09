#include "../../Module/ModuleManager.h"
#include "Flight.h"
#include <cmath>
uintptr_t ViewBobbing = FindSignature("0F B6 80 DB 01 00 00");

Flight::Flight() : IModule(0, Category::MOVEMENT, "Fly wow!") {
	registerEnumSetting("Mode", &mode, 0);
	mode.addEntry("Vanilla", 0);
	mode.addEntry("Airwalk", 1);
	//mode.addEntry("Teleport", 2); // removed for now ig
	mode.addEntry("Jetpack", 3);
	mode.addEntry("Hive", 4);
	registerBoolSetting("ViewBobbing", &viewBobbing, viewBobbing);
	registerBoolSetting("Damage", &damage, damage);
	registerBoolSetting("Boost", &boost, boost);
	registerFloatSetting("Speed", &speed, speed, 0.2f, 5.f);
	registerFloatSetting("value", &value, value, -0.15f, 0.00);
}

Flight::~Flight() {
}

const char* Flight::getRawModuleName() {
	return "Flight";
}

const char* Flight::getModuleName() {
	if (mode.getSelectedValue() == 0) name = std::string("Flight ") + std::string(GRAY) + std::string("Vanilla");
	if (mode.getSelectedValue() == 1) name = std::string("Flight ") + std::string(GRAY) + std::string("Airwalk");
	//if (mode.getSelectedValue() == 2) name = std::string("Flight ") + std::string(GRAY) + std::string("Teleport");
	if (mode.getSelectedValue() == 3) name = std::string("Flight ") + std::string(GRAY) + std::string("Jetpack");
	if (mode.getSelectedValue() == 4) name = std::string("Flight ") + std::string(GRAY) + std::string("Hive");
	return name.c_str();
}

void Flight::onEnable() {
	auto speed = moduleMgr->getModule<Speed>();
	if (speed->isEnabled()) speedWasEnabled = true;
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	PointingStruct* pointing = g_Data.getLocalPlayer()->pointingStruct;
	if (damage) {
		pointing->playSound("game.player.hurt", *player->getPos(), 1, 1);
		player->animateHurt();
	}
}

bool Flight::isFlashMode() {
	return mode.getSelectedValue() == 3;
}

void Flight::onTick(C_GameMode* gm) {
	if (viewBobbing) {
		Utils::patchBytes((unsigned char*)ViewBobbing, (unsigned char*)"\xB8\x01\x00\x00\x00\x90\x90", 7);
		if (value >= 0.00)
			value = -0.0000000001; // just dw about it lol
	}
	else Utils::patchBytes((unsigned char*)ViewBobbing, (unsigned char*)"\x0F\xB6\x80\xDB\x01\x00\x00", 7);
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = false;
	auto speedMod = moduleMgr->getModule<Speed>();
	if (speedMod->isEnabled()) {
		auto notification = g_Data.addNotification("Flight:", "Disabled Speed to prevent flags/errors");
		notification->duration = 5;
		speedMod->setEnabled(false);
	}

	// Math
	float yaw = player->yaw;
	float calcYaw = (gm->player->yaw + 90) * (PI / 180);
	float calcPitch = (gm->player->pitch) * -(PI / 180);
	vec3_t moveVec;
	moveVec.x = cos(calcYaw) * cos(calcPitch) * speed;
	moveVec.y = sin(calcPitch) * speed;
	moveVec.z = sin(calcYaw) * cos(calcPitch) * speed;

	// Vanilla
	if (mode.getSelectedValue() == 0) { 
		if (g_Data.canUseMoveKeys()) {
			if (GameData::isKeyDown(*input->spaceBarKey))
				effectiveValue += speed;
			if (GameData::isKeyDown(*input->sneakKey))
				effectiveValue -= speed;
		}
		if (input->forwardKey && input->backKey && input->rightKey && input->leftKey) {
			gm->player->velocity = vec3_t(0, 0, 0);
		}
		gm->player->velocity.y = effectiveValue;
		effectiveValue = value;
	}

	// Airwalk
	if (mode.getSelectedValue() == 1) {
		if (speedMod->isEnabled() || GameData::isKeyDown(*input->spaceBarKey)) 
			player->onGround = false;
		else 
			player->onGround = true;
		gm->player->velocity.y = effectiveValue;
		effectiveValue = value;
	}

	// Jetpack
	if (mode.getSelectedValue() == 3) gm->player->lerpMotion(moveVec);
}

void Flight::onMove(C_MoveInputHandler* input) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	// meth
	vec2_t moveVec2d = { input->forwardMovement, -input->sideMovement };
	bool pressed = moveVec2d.magnitude() > 0.01f;

	float calcYaw = (player->yaw + 90) * (PI / 180);
	vec3_t moveVec;
	float c = cos(calcYaw);
	float s = sin(calcYaw);
	moveVec2d = { moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c };

	// Vanilla
	if (mode.getSelectedValue() == 0) {
		moveVec.x = moveVec2d.x * speed;
		moveVec.y = player->velocity.y;
		moveVec.z = moveVec2d.y * speed;
		if (pressed) player->lerpMotion(moveVec);
	}

}

void Flight::onSendPacket(C_Packet* packet) {
}


void Flight::onDisable() {
	Utils::patchBytes((unsigned char*)ViewBobbing, (unsigned char*)"\x0F\xB6\x80\xDB\x01\x00\x00", 7);
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (viewBobbing) player->onGround = false;
	auto speed = moduleMgr->getModule<Speed>();
	if (speedWasEnabled) {
		speed->setEnabled(true);
		speedWasEnabled = false;
	}
	player->velocity = vec3_t(0, 0, 0);
}