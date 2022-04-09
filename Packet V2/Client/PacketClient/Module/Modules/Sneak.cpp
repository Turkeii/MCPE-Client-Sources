#include "Sneak.h"

Sneak::Sneak() : IModule(0, Category::MOVEMENT, "Automatically sneak without holding the key") {
	//this->registerBoolSetting("silent", &this->doSilent, doSilent);
	doSilent = false;
}

Sneak::~Sneak() {
}

const char* Sneak::getModuleName() {
	return ("Sneak");
}

void Sneak::onEnable() {
	if (g_Data.getLocalPlayer() == nullptr)
		return;  //fixed crash

	if (doSilent) {
		C_PlayerActionPacket p;
		p.action = 11;  //start crouch packet
		p.entityRuntimeId = g_Data.getLocalPlayer()->entityRuntimeId;
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
	}
}

void Sneak::onTick(C_GameMode* gm) {
	if (!doSilent)
		g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = true;
}

void Sneak::onDisable() {
	if (g_Data.getLocalPlayer() == nullptr)
		return;

	if (!doSilent) {
		g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = false;
		return;
	}

	C_PlayerActionPacket p;
	p.action = 12;  //stop crouch packet
	p.entityRuntimeId = g_Data.getLocalPlayer()->entityRuntimeId;
	g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
}