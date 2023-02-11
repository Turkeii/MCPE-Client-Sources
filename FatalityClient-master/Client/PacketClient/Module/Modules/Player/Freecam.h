#pragma once
#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"
#include "../pch.h"

class Freecam : public IModule {
public:
	bool cancelPackets = false;
	Freecam() : IModule::IModule(0, Category::PLAYER, "Allows you to view your surroundings") {
		registerBoolSetting("CancelPackets", &cancelPackets, cancelPackets);
		registerFloatSetting("Speed", &speed, speed, 0.1f, 2.f);
		this->lvlRenderWrite = nullptr;
		this->lvlLoaderWrite = nullptr;
	};
	vec2_t cameraRot = { 0.f, 0.f };
	bool wasDisabled = false;
	vec3_t targetPos;
	void* lvlRenderWrite;
	void* lvlLoaderWrite;
	float speed = 0.5f;
	vec2_t oldCamRot;

	virtual const char* getModuleName() override {
		return "Freecam";
	}

	void onEnable() {
		wasDisabled = true;
		if (lvlRenderWrite == nullptr)
			lvlRenderWrite = (void*)FindSignature("F3 0F 11 87 10 05");  //f3 0f 11 87 ? ? ? ? f3 0f 11 8f ? ? ? ? f3 0f 11 97 ? ? ? ? 49 8b 0c 24 
		if (lvlLoaderWrite == nullptr)
			lvlLoaderWrite = (void*)FindSignature("89 81 C0 00 00 00 8B 82 C4 00 00 00 89 81 C4 00 00 00 8B 82 C8 00 00 00 89 81 C8 00 00 00 49 8B 57 08");  //89 81 ? ? ? ? 8b 82 ? ? ? ? 89 81 ? ? ? ? 8b 82 ? ? ? ? 89 81 ? ? ? ? 49 8b 57

		if (lvlRenderWrite != nullptr) {
			Utils::nopBytes((unsigned char*)((uintptr_t)lvlRenderWrite), 24);
		}
		if (lvlLoaderWrite != nullptr) {
			Utils::nopBytes((unsigned char*)((uintptr_t)lvlLoaderWrite), 30);
		}

		targetPos = g_Data.getClientInstance()->levelRenderer->getOrigin();
		oldCamRot = g_Data.getLocalPlayer()->viewAngles;
	}

	void onDisable() {
		targetPos = g_Data.getLocalPlayer()->eyePos0;
		wasDisabled = true;
		if (lvlRenderWrite != nullptr) {
			// may need to update the patch later
			unsigned char* patch = (unsigned char*)"\xF3\x0F\x11\x87\x10\x05\x00\x00\xF3\x0F\x11\x8F\x14\x05\x00\x00\xF3\x0F\x11\x97\x18\x05\x00\x00";
			Utils::patchBytes((unsigned char*)((uintptr_t)lvlRenderWrite), patch, 24);
		}
		if (lvlLoaderWrite != nullptr) {
			// may need to update the patch later
			unsigned char* patch = (unsigned char*)"\x89\x81\xC0\x00\x00\x00\x8B\x82\xC4\x00\x00\x00\x89\x81\xC4\x00\x00\x00\x8B\x82\xC8\x00\x00\x00\x89\x81\xC8\x00\x00\x00\x49\x8B\x57\x08";
			Utils::patchBytes((unsigned char*)((uintptr_t)lvlLoaderWrite), patch, 30);
		}
	}

	void onPlayerTick(C_Player* p) {
		if (p = g_Data.getLocalPlayer()) {
			g_Data.getClientInstance()->getMoveTurnInput()->clearMovementState();
			g_Data.getClientInstance()->getMoveTurnInput()->isJumping = 0;
			g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = 0;
			g_Data.getClientInstance()->getMoveTurnInput()->forwardMovement = 0;
			g_Data.getClientInstance()->getMoveTurnInput()->sideMovement = 0;
			g_Data.getClientInstance()->getMoveTurnInput()->backward = 0;
			g_Data.getLocalPlayer()->setSneaking(false);
		}
	}

	void onPostRender(C_MinecraftUIRenderContext*) {
		static auto prevTime = std::chrono::high_resolution_clock::now();
		auto now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> tDiff = now - prevTime;
		prevTime = now;
		float TimeMultiplier = tDiff.count() / 0.05f;
		if (wasDisabled) {
			TimeMultiplier = 1.f;
			wasDisabled = false;
		}
		cameraRot = g_Data.getLocalPlayer()->viewAngles;
		float yaw = cameraRot.y;
		C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
		if (GameData::isKeyDown(*input->sneakKey)) {
			targetPos.y -= speed * TimeMultiplier;
		}
		if (GameData::isKeyDown(*input->spaceBarKey)) {
			targetPos.y += speed * TimeMultiplier;
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
			moveVec.y = 0;
			moveVec.z = sin(calcYaw) * speed;
			targetPos = targetPos.add(moveVec.mul(TimeMultiplier));
		}
		g_Data.getClientInstance()->levelRenderer->getOrigin() = targetPos;
		g_Data.getClientInstance()->levelRenderer->getLoader() = targetPos;
	}
};