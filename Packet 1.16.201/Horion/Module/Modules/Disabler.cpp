#include "Disabler.h"

#include "../../../Utils/Target.h"
#include "../ModuleManager.h"

Disabler::Disabler() : IModule(0, Category::MISC, "Nethergames Fly Disabler") {
	this->registerBoolSetting("Nethergames", &this->netherDis, this->netherDis);
	//this->registerBoolSetting("Cubecraft", &this->ccDis, this->ccDis);
	//this->registerBoolSetting("Mineplex", &this->mineDis, this->mineDis);
	this->registerBoolSetting("Mineville", &this->minevilleDis, this->minevilleDis);
}

Disabler::~Disabler() {
}

const char* Disabler::getModuleName() {
	return "Disabler";
}

void Disabler::onTick(C_GameMode* gm) {
	if (netherDis && !gm->player->onGround) {
		C_MovePlayerPacket pNether(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&pNether);
	}
	if (mineDis) {
		C_MovePlayerPacket p(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
	}
	if (ccDis) {
		C_MovePlayerPacket p(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
	}
	if (minevilleDis && !gm->player->onGround) {
		C_MovePlayerPacket pMineville(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&pMineville);
	}
}

void Disabler::onSendPacket(C_Packet* packet) {
	if (packet->isInstanceOf<C_MovePlayerPacket>()) {
		auto player = g_Data.getLocalPlayer();
		if (minevilleDis && !player->onGround) {
			C_MovePlayerPacket* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
			movePacket->onGround = true;
		}
	}
	if (packet->isInstanceOf<C_MovePlayerPacket>()) {
		auto player = g_Data.getLocalPlayer();
		if (minevilleDis && !player->onGround) {
			C_MovePlayerPacket* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
			movePacket->onGround = true;
		}
	}
}