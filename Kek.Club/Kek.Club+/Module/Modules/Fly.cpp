#include "Fly.h"
bool mineplexMode = false;
bool packet = false;
bool vanilla = false;
bool cube = false;
bool riptide = false;
bool onlyjump = false;
uintptr_t ViewBobbing = FindSignature("0F B6 80 DB 01 00 00");
Fly::Fly() : IModule(0, Category::MOVEMENT, "Enables fly like in creative mode") {
	mode = (*new SettingEnum(this)).addEntry(EnumEntry("PacketFly", 1)).addEntry(EnumEntry("Mineplex", 2)).addEntry(EnumEntry("CubeGlide", 3)).addEntry(EnumEntry("Vanilla", 4)).addEntry(EnumEntry("Riptide", 5));
	registerEnumSetting("Mode", &mode, 0);
	registerBoolSetting("ViewBobbing", &viewBobbing, viewBobbing);
	registerBoolSetting("OnlyWhenJumping", &onlyjump, onlyjump);
	registerFloatSetting("CubeGlide Speed", &speed, speed, 1.f, 3.f);
	registerFloatSetting("value", &value, value, -0.15f, 0.00);
}

Fly::~Fly() {
}



const char* Fly::getModuleName() {
	return ("Flight");
}

bool Fly::isFlashMode() {
	if (!(g_Data.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
		if (g_Data.isInGame()) {
			if (vanilla) {
				return false;
			} else if (cube || mineplexMode) {
				return true;
			} else {
				return false;
			}
		}
	}
	return false;
}

void Fly::onEnable() {
	if (mode.selected == 1) {
		g_Data.getLocalPlayer()->setPos((*g_Data.getLocalPlayer()->getPos()).add(vec3_t(0, 1, 0)));
	}
}


void Fly::onTick(C_GameMode* gm) {
	switch (mode.selected) {
	case 0:
		vanilla = false;
		mineplexMode = false;
		cube = false;
		packet = true;
		riptide = false;
		break;
	case 1:
		vanilla = true;
		mineplexMode = false;
		cube = false;
		packet = false;
		riptide = false;
		break;
	case 2:
		vanilla = false;
		mineplexMode = false;
		cube = true;
		packet = false;
		riptide = false;
		break;
	case 3:
		vanilla = false;
		mineplexMode = true;
		cube = false;
		packet = false;
		riptide = false;
		break;
	case 4:
		vanilla = false;
		mineplexMode = false;
		cube = false;
		packet = true;
		riptide = false;
		break;
	case 5:
		vanilla = false;
		mineplexMode = false;
		cube = false;
		packet = false;
		riptide = true;
		break;
	}
	if (viewBobbing) {
		Utils::patchBytes((unsigned char*)ViewBobbing, (unsigned char*)"\xB8\x01\x00\x00\x00\x90\x90", 7);
		if (value >= 0.00)
			value = -0.0000000001;  // just dw about it lol
	} else
		Utils::patchBytes((unsigned char*)ViewBobbing, (unsigned char*)"\x0F\xB6\x80\xDB\x01\x00\x00", 7);
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = false;

	gm->player->canFly = true;

	if (vanilla) {
		gm->player->canFly = true;

	}		
	if (riptide) {
		bool onlyJump = onlyjump;

		if (onlyJump && !player->isJumping())
			return;
		player->setDamageNearbyMobs(true);
	}

	if (cube) {
	
		float calcYaw = (gm->player->yaw + 90) * (PI / 180);

		gameTick++;

		vec3_t pos = *g_Data.getLocalPlayer()->getPos();
		pos.y += 1.3f;
		C_MovePlayerPacket a(g_Data.getLocalPlayer(), pos);
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);
		pos.y -= 1.3f;
		C_MovePlayerPacket a2(g_Data.getLocalPlayer(), pos);
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a2);

		vec3_t moveVec;
		moveVec.x = cos(calcYaw) * speed;
		moveVec.z = sin(calcYaw) * speed;

		gm->player->lerpMotion(moveVec);

		if (gameTick >= 5) {
			gameTick = 0;
			float yaw = gm->player->yaw * (PI / 180);
			float length = 4.f;

			float x = -sin(yaw) * length;
			float z = cos(yaw) * length;

			gm->player->setPos(pos.add(vec3_t(x, 0.5f, z)));
		}
		if (mineplexMode) {  // by Kow
			vec3_t moveVec;
			moveVec.x = cos(calcYaw) * speed;
			moveVec.y = -0.0f;
			moveVec.z = sin(calcYaw) * speed;

			gm->player->lerpMotion(moveVec);
		}
	}
}


void Fly::onDisable() {
	Utils::patchBytes((unsigned char*)ViewBobbing, (unsigned char*)"\x0F\xB6\x80\xDB\x01\x00\x00", 7);
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (viewBobbing) player->onGround = false;

	if (vanilla) {
		if (g_Data.getLocalPlayer() != nullptr)
			if (g_Data.getLocalPlayer()->gamemode != 1)
				g_Data.getLocalPlayer()->canFly = false;
	}
	if (cube || mineplexMode) {
		g_Data.getLocalPlayer()->velocity = vec3_t(0, 0, 0);
	}
}

void Fly::onMove(C_MoveInputHandler* input) {
	if (packet) {
		auto player = g_Data.getLocalPlayer();
		player->canFly = false;
		if (player == nullptr) return;
		player->onGround = true;
		if (player->isInLava() == 1 || player->isInWater() == 1)
			return;
		if (player->isSneaking())
			return;
		vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
		bool pressed = moveVec2d.magnitude() > 0.01f;
		float calcYaw = (player->yaw + 90) * (PI / 180);
		vec3_t moveVec = *g_Data.getLocalPlayer()->getPos();
		float c = cos(calcYaw);
		float s = sin(calcYaw);
		moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};
		moveVec.x += player->velocity.x;
		moveVec.z += player->velocity.z;
		player->setSprinting(false);
		moveVec.y += -0.02f;
		if (player->fallDistance >= 0.02) {
			vec3_t nig;
			nig.x = player->velocity.x * 1.4f;
			nig.z = player->velocity.z * 1.4f;
			nig.y = 0.02f;
			player->lerpMotion(nig);
		}
	}
};

//made by rj