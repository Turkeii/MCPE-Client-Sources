#include "NoFall.h"

NoFall::NoFall() : IModule(0x0, Category::MOVEMENT, "NoFall") {
	registerBoolSetting("OnGround", &this->groundy, this->groundy);
	registerBoolSetting("I-Frame", &this->smart, this->smart);
	registerBoolSetting("Motion", &this->motion, this->motion);
	//registerBoolSetting("X Auto Elytra", &this->elytra, this->elytra);
	//registerIntSetting("Elytra Distance", &this->distance, this->distance, 1, 30);  //allows you to ajust your speed.
}

NoFall::~NoFall() {
}

const char* NoFall::getModuleName() {
	return ("NoFall");
}

static std::vector<C_Entity*> targetKool;

void findKool(C_Entity* currentEntity, bool isRegularEntity) {
	static auto nofallMod = moduleMgr->getModule<NoFall>();

	if (currentEntity == nullptr)
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < nofallMod->range) {
		targetKool.push_back(currentEntity);
	}
}
void NoFall::onTick(C_GameMode* gm) {
	targetKool.clear();
	g_Data.forEachEntity(findKool);

	if (!targetKool.empty()) {
		if (smart) {
			C_LocalPlayer* player = g_Data.getLocalPlayer();
			vec3_t myPos = *gm->player->getPos();
			int dildo = player->fallDistance;
			if (g_Data.getLocalPlayer() != nullptr && g_Data.getLocalPlayer()->fallDistance > 3.f && player->region->getBlock(vec3_t{myPos.x, myPos.y - dildo - 1, myPos.z})->toLegacy()->blockId != 0) {
				g_Data.getCGameMode()->attack(targetKool[0]);
				g_Data.getCGameMode()->attack(targetKool[0]);
				g_Data.getCGameMode()->attack(targetKool[0]);
				g_Data.getCGameMode()->attack(targetKool[0]);
				g_Data.getLocalPlayer()->velocity.y -= 0.7f;
				g_Data.getCGameMode()->attack(targetKool[0]);
				g_Data.getCGameMode()->attack(targetKool[0]);
				g_Data.getCGameMode()->attack(targetKool[0]);
				g_Data.getCGameMode()->attack(targetKool[0]);
				g_Data.getCGameMode()->attack(targetKool[0]);
			}
		}
		auto player = g_Data.getLocalPlayer();
		if (counter == 5) {
			counter = 0;
		} else {
			counter++;
		}
		if (groundy) {
			gm->player->onGround = true;
			return;
		}
		if (motion) {
			if (player->fallDistance > 4) {
				//!player->onGround;
				glideModEffective = glideMod;
				gm->player->velocity.y = glideModEffective;
				g_Data.getLocalPlayer()->setPos((*g_Data.getLocalPlayer()->getPos()).add(0, 0.25, 0));  //sets how much u need
			}
		}
		if (elytra) {
			if (g_Data.getLocalPlayer() != nullptr && g_Data.getLocalPlayer()->fallDistance > distance) {
				C_PlayerActionPacket p;
				p.action = 15;  //start flying
				p.entityRuntimeId = g_Data.getLocalPlayer()->entityRuntimeId;
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
			}
		}
	}
}