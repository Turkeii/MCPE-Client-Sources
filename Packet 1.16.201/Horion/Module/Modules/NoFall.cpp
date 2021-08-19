#include "NoFall.h"

NoFall::NoFall() : IModule(0, Category::MOVEMENT, "NoFuK") {
	this->registerBoolSetting("Motion", &this->motionMode, this->motionMode);
}

const char* NoFall::getModuleName() {
	return "NoFall";
}

void NoFall::onTick(C_GameMode* gm) {
	if (motionMode) {
		C_MovePlayerPacket p(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
	}
}