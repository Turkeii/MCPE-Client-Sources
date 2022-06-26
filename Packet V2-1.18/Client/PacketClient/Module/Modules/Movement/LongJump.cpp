#include "LongJump.h"
#include "../pch.h"

using namespace std;
LongJump::LongJump() : IModule(0, Category::MOVEMENT, "A Long Jump") {
	registerEnumSetting("Mode", &mode, 0);
	mode.addEntry("Vanilla", 0);
	mode.addEntry("Old", 1);
	mode.addEntry("Hive", 2);
	mode.addEntry("Cubecraft", 3);
	registerBoolSetting("Damage", &damage, damage);
	registerFloatSetting("Height", &height, height, 0.2f, 5.f);
	registerFloatSetting("Speed", &speed, speed, 0.5f, 5.f);
}

const char* LongJump::getRawModuleName() {
	return "LongJump";
}

const char* LongJump::getModuleName() {
	if (mode.getSelectedValue() == 0) name = string("LongJump ") + string(GRAY) + string("Vanilla");
	if (mode.getSelectedValue() == 1) name = string("LongJump ") + string(GRAY) + string("Old");
	if (mode.getSelectedValue() == 2) name = string("LongJump ") + string(GRAY) + string("Hive");
	if (mode.getSelectedValue() == 3) name = string("LongJump ") + string(GRAY) + string("Cubecraft");
	return name.c_str();
}

void LongJump::onEnable() {
	auto speedMod = moduleMgr->getModule<Speed>();
	if (speedMod->isEnabled()) speedWasEnabled = true;
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	tick = 0;

	PointingStruct* level = g_Data.getLocalPlayer()->pointingStruct;
	if (damage) { level->playSound("game.player.hurt", *player->getPos(), 1, 1); player->animateHurt(); }

	switch (mode.getSelectedValue()) {
	case 0: // Vanilla
		vanillaTick = 0;
		break;
	case 2: // Hive
		hiveSpeedIndex = 125;
		hiveTick = 0;
		break;
	}
}

void LongJump::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	tick++;

	auto speedMod = moduleMgr->getModule<Speed>();
	if (speedMod->isEnabled()) {
		//auto notification = g_Data.addNotification("LongJump:", "Disabled Speed"); notification->duration = 5;
		speedMod->setEnabled(false);
	}

	switch (mode.getSelectedValue()) {
	case 0: // Vanilla
		if (!gm->player->onGround)
			vanillaTick++;
		break;
    case 3: // Cubecraft
        player->velocity.y = 0;
        break;
	}
}

void LongJump::onMove(C_MoveInputHandler* input) {
    auto player = g_Data.getLocalPlayer();
    if (player == nullptr) return;

    C_GameSettingsInput* input2 = g_Data.getClientInstance()->getGameSettingsInput();
    bool jumping = GameData::isKeyDown(*input2->spaceBarKey);
    bool sneaking = GameData::isKeyDown(*input2->sneakKey);

    // Math
    vec3_t moveVec;
    float calcYaw = (player->yaw + 90) * (PI / 180);
    vec2_t moveVec2d = { input->forwardMovement, -input->sideMovement };
    bool pressed = moveVec2d.magnitude() > 0.01f;
    float c = cos(calcYaw);
    float s = sin(calcYaw);
    moveVec2d = { moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c };

    // Vanilla
    switch (mode.getSelectedValue()) {
    case 0: // Vanilla
        if (player->onGround && pressed) {
            player->jumpFromGround();
            player->velocity.y = height;
        }
        moveVec.x = moveVec2d.x * speed;
        moveVec.y = player->velocity.y;
        moveVec.z = moveVec2d.y * speed;
        if (pressed) player->lerpMotion(moveVec);

        if (vanillaTick >= 3 && player->onGround) {
            vanillaTick = 0;
            setEnabled(false);
            player->velocity = vec3_t(0, 0, 0);
        }
        break;
    case 1: // Old
        if (player->onGround && pressed)
            player->jumpFromGround();
        moveVec.x = moveVec2d.x * speed;
        moveVec.y = height;
        player->velocity.y;
        moveVec.z = moveVec2d.y * speed;
        if (pressed) player->lerpMotion(moveVec);
        setEnabled(false);
        break;
    case 2: // Hive
        if (!player->onGround && hiveTick == 0) return;
        g_Data.getClientInstance()->minecraft->setTimerSpeed(12.5f);
        hiveTick++;

        if (hiveTick == 1) {
            if (player->onGround && pressed)
                player->jumpFromGround();
            moveVec.x = moveVec2d.x * 1.48900537147521973f;
            moveVec.y = 0.4997356939315796f;
            player->velocity.y;
            moveVec.z = moveVec2d.y * 1.48900537147521973f;
            if (pressed) player->lerpMotion(moveVec);
        }
        else if (hiveTick >= 17) setEnabled(false);

        if (hiveTick >= 3 && player->onGround) {
            player->velocity = vec3_t(0, 0, 0);
            setEnabled(false);
            hiveTick = 0;
        }

        if (player->velocity.squaredxzlen() > 0.01) {
            C_MovePlayerPacket p = C_MovePlayerPacket(g_Data.getLocalPlayer(), player->getPos()->add(vec3_t(moveVec.x / 2.1f, moveVec.y / 2, moveVec.z / 2.1f)));
            g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
        }
        break;
    case 3:
        g_Data.getClientInstance()->minecraft->setTimerSpeed(20.f);
        float CCSpeed = 1.94f;

        if (player->onGround && pressed)
            player->jumpFromGround();

        if (jumping) player->velocity.y = CCSpeed / 6;
        if (sneaking) player->velocity.y = -CCSpeed / 6;

        if (tick % 3 == 0) {
            moveVec.x = moveVec2d.x * CCSpeed;
            moveVec.z = moveVec2d.y * CCSpeed;
            moveVec.y = player->velocity.y;
        }
        else {
            g_Data.getClientInstance()->minecraft->setTimerSpeed(80.f);
            moveVec.x = moveVec2d.x * 0;
            moveVec.z = moveVec2d.y * 0;
            moveVec.y = player->velocity.y;
        }

        if (pressed) player->lerpMotion(moveVec);
        else {
            player->velocity.x = 0;
            player->velocity.z = 0;
        }
        break;
    }
}

void LongJump::onDisable() {
	g_Data.getClientInstance()->minecraft->setTimerSpeed(20.f);
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	auto speed = moduleMgr->getModule<Speed>();
	if (speedWasEnabled) {
		speed->setEnabled(true);
		speedWasEnabled = false;
	}
	vanillaTick = 0;
	hiveTick = 0;
	tick = 0;

	// Hive
	if (mode.getSelectedValue() == 2 || mode.getSelectedValue() == 3) {
		if (!player->onGround) {
			player->velocity.x = 0.f;
			player->velocity.z = 0.f;
		}
	}
}