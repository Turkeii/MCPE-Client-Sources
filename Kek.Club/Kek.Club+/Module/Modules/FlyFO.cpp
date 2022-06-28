#include "FlyFO.h"

uintptr_t ViewBobbingSig = FindSignature("0F B6 80 DB 01 00 00");
FlyFO::FlyFO() : IModule(0, Category::MOVEMENT, "Fly by Founder") {
	registerBoolSetting("ViewBobbing", &doViewBobbing, doViewBobbing);
	registerBoolSetting("Halt", &haltMovement, haltMovement);
	registerBoolSetting("ExtraPacket", &addPacket, addPacket);
	registerBoolSetting("Rotation", &rots, rots);
	antiDetectMode = (*new SettingEnum(this)).
		addEntry(EnumEntry("None", 0)).
		addEntry(EnumEntry("Drop", 1)).
		addEntry(EnumEntry("SpoofUp", 2));
	registerEnumSetting("Mode", &antiDetectMode, 0);
	registerFloatSetting("MaxDrop", &maxDrop, maxDrop, .1f, .5f);
	registerFloatSetting("Speed", &speed, speed, 0.4f, 2.5f);
}
FlyFO::~FlyFO() {
}

const char* FlyFO::getModuleName() {
	return "FlyFO";
}

void FlyFO::onEnable() {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	if (addPacket) {
		C_MovePlayerPacket offG(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos(), false);
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&offG);
	}
}

void FlyFO::onDisable() {
	Utils::patchBytes((unsigned char*)ViewBobbingSig, (unsigned char*)"\x0F\xB6\x80\xDB\x01\x00\x00", 7);
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	if (haltMovement) {
		player->velocity.z *= 0;
		player->velocity.x *= 0;
	}
}

void FlyFO::onTick(C_GameMode* gm) {
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	auto value = 0.f;
	value = speed;

	gm->player->onGround = true;

	if (doViewBobbing) {
		Utils::patchBytes((unsigned char*)ViewBobbingSig, (unsigned char*)"\xB8\x01\x00\x00\x00\x90\x90", 7);
		if (value >= 0.00)
			value = -0.0000000001;
	} else
		Utils::patchBytes((unsigned char*)ViewBobbingSig, (unsigned char*)"\x0F\xB6\x80\xDB\x01\x00\x00", 7);

	if (g_Data.canUseMoveKeys()) {
		if (GameData::isKeyDown(*input->spaceBarKey))
			speedEffective = speed;
		else if (GameData::isKeyDown(*input->sneakKey))
			speedEffective = -speed;
		else
			speedEffective = -0.f;
	}
	gm->player->velocity.y = speedEffective;
	if (!gm->player->isSprinting() && gm->player->velocity.magnitudexz() > 0.01f)
		gm->player->setSprinting(true);

	if (addPacket) {
		C_MovePlayerPacket onG(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos(), true);
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&onG);
	}

	if (antiDetectMode.selected == 1) {
		antiDetectTime++;
		if (antiDetectTime >= random(12, 75)) {
			C_MovePlayerPacket onG(g_Data.getLocalPlayer(), g_Data.getLocalPlayer()->getPos()->add(vec3_t(0.f, RandomFloat(-.1f, -maxDrop), 0.f)), false);
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&onG);
			antiDetectTime = 0;
		}
	}
	if (antiDetectMode.selected == 2) {
		antiDetectTime++;
		if (antiDetectTime >= random(12, 75)) {
			C_MovePlayerPacket onG(g_Data.getLocalPlayer(), g_Data.getLocalPlayer()->getPos()->add(vec3_t(0.f, RandomFloat(.1f, maxDrop), 0.f)), true);
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&onG);
			antiDetectTime = 0;
		}
	}
}

void FlyFO::onMove(C_MoveInputHandler* input) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	float yaw = player->yaw;
	bool pressed = input->forward || input->backward || input->right || input->left;

	if (input->forward && input->backward)
		return;
	if (input->right) {
		yaw += 90.f;
		if (input->forward)
			yaw -= 45.f;
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

	float calcYaw = (yaw + 90) * (PI / 180);
	vec3_t moveVec;
	moveVec.x = cos(calcYaw) * speed;
	moveVec.y = player->velocity.y;
	moveVec.z = sin(calcYaw) * speed;
	if (pressed) player->lerpMotion(moveVec);
}

void FlyFO::onSendPacket(C_Packet* packet) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	float yaw = player->yaw;
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();

	if (input->forwardKey && input->backKey)
		return;
	if (input->rightKey) {
		yaw += 90.f;
		if (input->forwardKey)
			yaw -= 45.f;
		else if (input->backKey)
			yaw += 45.f;
	}
	if (input->leftKey) {
		yaw -= 90.f;
		if (input->forwardKey)
			yaw += 45.f;
		else if (input->backKey)
			yaw -= 45.f;
	}
	if (input->backKey && !input->leftKey && !input->rightKey)
		yaw += 180.f;

	if (packet->isInstanceOf<C_MovePlayerPacket>()) {
		C_MovePlayerPacket* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
		if (rots) {
			movePacket->yaw = yaw;
			movePacket->headYaw = yaw;
		}
	}
}