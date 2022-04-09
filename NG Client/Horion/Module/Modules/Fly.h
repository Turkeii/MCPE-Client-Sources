#pragma once
#include "Module.h"
class Flight : public IModule {
private:
	bool speedWasEnabled = false;
	bool viewBobbing = true;
	bool damage = false;
	bool boost = false;

public:
	float effectiveValue = 0.f;
	float value = 0.f;
	float duration = 1.f;
	float speed = 1.f;

	std::string name = "Flight";
	C_MovePlayerPacket* jetpack = nullptr;
	SettingEnum mode = this;

	std::vector<C_MovePlayerPacket> movePacket1;
	std::vector<PlayerAuthInputPacket> authPacket1;
	std::vector<C_MovePlayerPacket*> MovePlayerPacketHolder;
	std::vector<PlayerAuthInputPacket*> PlayerAuthInputPacketHolder;
	inline std::vector<C_MovePlayerPacket*>* getMovePlayerPacketHolder() { return &MovePlayerPacketHolder; };
	inline std::vector<PlayerAuthInputPacket*>* getPlayerAuthInputPacketHolder() { return &PlayerAuthInputPacketHolder; };

	Flight() : IModule(0x0, Category::FLYS, "become birb") {
		registerEnumSetting("Mode", &mode, 0);
		mode.addEntry("Vanilla", 0);
		mode.addEntry("Airwalk", 1);
		mode.addEntry("Jetpack", 3);
		registerBoolSetting("ViewBobbing", &viewBobbing, viewBobbing);
		registerBoolSetting("Damage", &damage, damage);
		registerBoolSetting("Boost", &boost, boost);
		registerFloatSetting("Speed", &speed, speed, 0.2f, 5.f);
		registerFloatSetting("value", &value, value, -0.15f, 0.00);
	};

	~Flight(){};

	void onEnable() {
		auto player = g_Data.getLocalPlayer();
		if (player == nullptr) return;

		PointingStruct* pointing = g_Data.getLocalPlayer()->pointingStruct;
		if (damage) {
			pointing->playSound("game.player.hurt", *player->getPos(), 1, 1);
			player->animateHurt();
		}
	}

	bool isFlashMode() {
		return mode.getSelectedValue() == 3;
	}

	void onTick(C_GameMode* gm) {
		auto player = g_Data.getLocalPlayer();
		if (player == nullptr) return;

		C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
		g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = false;

		// Math
		float yaw = player->yaw;
		float calcYaw = (gm->player->yaw + 90) * (PI / 180);
		float calcPitch = (gm->player->pitch) * -(PI / 180);
		vec3 moveVec;
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
				gm->player->velocity = vec3(0, 0, 0);
			}
			gm->player->velocity.y = effectiveValue;
			effectiveValue = value;
		}

		// Airwalk
		if (mode.getSelectedValue() == 1) {
				player->onGround = true;
			gm->player->velocity.y = effectiveValue;
			effectiveValue = value;
		}

		// Jetpack
		if (mode.getSelectedValue() == 3) gm->player->lerpMotion(moveVec);
	}

	void onMove(C_MoveInputHandler* input) {
		auto player = g_Data.getLocalPlayer();
		if (player == nullptr) return;

		// meth
		vec2 moveVec2d = {input->forwardMovement, -input->sideMovement};
		bool pressed = moveVec2d.magnitude() > 0.01f;

		float calcYaw = (player->yaw + 90) * (PI / 180);
		vec3 moveVec;
		float c = cos(calcYaw);
		float s = sin(calcYaw);
		moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};

		// Vanilla
		if (mode.getSelectedValue() == 0) {
			moveVec.x = moveVec2d.x * speed;
			moveVec.y = player->velocity.y;
			moveVec.z = moveVec2d.y * speed;
			if (pressed) player->lerpMotion(moveVec);
		}
	}

	void onSendPacket(C_Packet* packet) {
	}

	void onDisable() {
		auto player = g_Data.getLocalPlayer();
		if (player == nullptr) return;
		player->velocity = vec3(0, 0, 0);
	}
	const char* getModuleName() {
		//Vanilla
		if (mode.getSelectedValue() == 0) name = std::string("Flight ") + std::string("Vanilla");

		//Airwalk
		if (mode.getSelectedValue() == 1) name = std::string("Flight ") + std::string("Airwalk");
		
		//Jetpack
		if (mode.getSelectedValue() == 3) name = std::string("Flight ") + std::string("Jetpack");
		return name.c_str();
	}
};