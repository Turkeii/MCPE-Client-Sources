#include "Fly.h"

Fly::Fly() : IModule(0, Category::CUSTOM, "Fly like a bird! (Mineplex Fly By Kow)") {
	registerFloatSetting("Fly Speed", &speed, speed, 0.5f, 3.f);
	registerBoolSetting("CreativeFly", &vanilla, vanilla);
	registerBoolSetting("CubeGlide", &cubeMode, cubeMode);
	registerBoolSetting("Mineplex", &mineplexMode, mineplexMode);
	registerBoolSetting("Damage", &this->dmg, this->dmg);
}

Fly::~Fly() {
}

const char* Fly::getModuleName() {
	return ("Fly");
}

bool Fly::isFlashMode() {
	if (!(g_Data.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
		if (g_Data.isInGame()) {
			if (vanilla) {
				return false;
			} else if (cubeMode || mineplexMode) {
				return true;
			} else {
				return false;
			}
		}
	}
}

void Fly::onEnable() {
	if (!(g_Data.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
		if (g_Data.isInGame()) {
			if (this->dmg) {
				auto player = g_Data.getLocalPlayer();
				player->animateHurt();
			}
			if (cubeMode) g_Data.getLocalPlayer()->setPos((*g_Data.getLocalPlayer()->getPos()).add(vec3_t(0, 1, 0)));
		}
	}
}

void Fly::onTick(C_GameMode* gm) {
	if (!(g_Data.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
		if (g_Data.isInGame()) {
			float calcYaw = (gm->player->yaw + 90) * (PI / 180);
			float calcPitch = (gm->player->pitch) * -(PI / 180);

			if (vanilla)
				gm->player->canFly = true;
			if (cubeMode) {
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
			}

			if (mineplexMode) {  //by Kow
				vec3_t moveVec;
				moveVec.x = cos(calcYaw) * speed;
				moveVec.y = -0.0f;
				moveVec.z = sin(calcYaw) * speed;

				gm->player->lerpMotion(moveVec);
			}
		}
	}
}
//E A Sports

void Fly::onDisable() {
	if (vanilla) {
		if (g_Data.getLocalPlayer() != nullptr)
			if (g_Data.getLocalPlayer()->gamemode != 1)
				g_Data.getLocalPlayer()->canFly = false;
	}
	if (cubeMode || mineplexMode)
		g_Data.getLocalPlayer()->velocity = vec3_t(0, 0, 0);
}