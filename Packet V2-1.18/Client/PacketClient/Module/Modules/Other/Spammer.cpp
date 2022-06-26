#include "Spammer.h"
#include "../pch.h"

Spammer::Spammer() : IModule(0, Category::OTHER, "Spams a message in a specified delay") {
	registerBoolSetting("bypass", &bypass, bypass);;
	registerIntSetting("delay", &delay, delay, 0, 30);
	registerIntSetting("Length", &length, length, 1, 40);
}

const char* Spammer::getModuleName() {
	return ("Spammer");
}

void Spammer::onTick(C_GameMode* gm) {
	Odelay++;
	if (Odelay > delay * 20) {
		C_TextPacket textPacket;
		textPacket.message.setText(bypass ? (message + " | " + Utils::randomString(length)) : message);
		textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
		textPacket.messageType = 69;
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
		Odelay = 0;
	}
}