#include "Derp.h"

Derp::Derp() : IModule(0, Category::MISC, "lol you stupid") {
	this->registerBoolSetting("epic stroke", &this->epicStroke, this->epicStroke);
	this->registerBoolSetting("packet mode", &this->packetMode, this->packetMode);
}

Derp::~Derp() {
}

const char* Derp::getModuleName() {
	return "Derp";
}

void Derp::onTick(C_GameMode* gm) {
	if (packetMode) {
		C_MovePlayerPacket p(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
		if (epicStroke) {
			p.pitch = (float)(rand() % 10000);
			p.yaw = (float)(rand() % -1864);
		} else {
			p.pitch = (float)(counter % 546980567);
			p.yaw = (float)(counter % 3564760);
		}
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
	} else {
		if (epicStroke) {
			gm->player->pitch = (float)(rand() % 1000);
			gm->player->bodyYaw = (float)(rand() % -1000);
		} else {
			gm->player->pitch = (float)(counter % 31110);
			gm->player->bodyYaw = (float)(counter % 3452660);
		}
	}

	if (counter < 360)
		counter++;
	else
		counter = 0;
}
