#include "Longjump.h"

Longjump::Longjump() : IModule('G', Category::MOVEMENT, "Jump farther with speed") {
	registerFloatSetting("speed", &this->speedMod, 1, 0.5f, 4.f);
	registerFloatSetting("up", &this->upvel, 1, 0.1f, 4.f);
	this->registerBoolSetting("Packet", &this->isBypass, this->isBypass);
}

Longjump::~Longjump() {
}

const char* Longjump::getModuleName() {
	return ("LongJump");
}

void Longjump::onTick(C_GameMode* gm) {
	float calcYaw = (gm->player->yaw + 90) * (PI / 180);
	float calcPitch = (gm->player->pitch) * -(PI / 180);
	C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();

	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();

	if (input == nullptr)
		return;

	C_MovePlayerPacket teleportPacket;
	float teleportX = 0.0;
	float teleportZ = 0.0;
	float teleportY = 0.001;

	if (!isBypass) {
		if (localPlayer->onGround == true && GameData::isKeyDown(*input->spaceBarKey) && hasJumped == 0) {
			vec3_t moveVec;
			moveVec.x = cos(calcYaw) * cos(calcPitch) * speedMod;
			moveVec.y = +upvel;
			moveVec.z = sin(calcYaw) * cos(calcPitch) * speedMod;

			gm->player->lerpMotion(moveVec);
			hasJumped = 1;
		} else if (!GameData::isKeyDown(*input->spaceBarKey) && localPlayer->onGround == true) {
			hasJumped = 0;
		}
	} else {
		if (localPlayer->onGround == true && GameData::isKeyDown(*input->spaceBarKey) && hasJumped == 0) {
			vec3_t moveVec;
			moveVec.x = cos(calcYaw) * cos(calcPitch) * speedMod;
			moveVec.y = +upvel;
			moveVec.z = sin(calcYaw) * cos(calcPitch) * speedMod;

			gm->player->lerpMotion(moveVec);
			hasJumped = 1;
			yoight = true;
			if (yoight == true) {
				doot++;
				vec3_t pos = *gm->player->getPos();
				C_MovePlayerPacket p = C_MovePlayerPacket(g_Data.getLocalPlayer(), vec3_t(pos.x - teleportX, pos.y - teleportY, pos.z - teleportZ));
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
				if (doot == 5) {
					yoight = false;
					doot = 0;
				}
			}
			vec3_t pos = *gm->player->getPos();
			C_MovePlayerPacket p = C_MovePlayerPacket(g_Data.getLocalPlayer(), vec3_t(pos.x - teleportX, pos.y - teleportY, pos.z - teleportZ));
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
		} else if (!GameData::isKeyDown(*input->spaceBarKey) && localPlayer->onGround == true) {
			hasJumped = 0;
		}
	}
}
