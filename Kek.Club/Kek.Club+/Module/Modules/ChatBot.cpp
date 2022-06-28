#include "ChatBot.h"

ChatBot::ChatBot() : IModule(0, Category::MISC, "Spammer but cooler") {
	registerBoolSetting("Bypass", &bypass, bypass);
	registerIntSetting("BP-Length", &length, length, 1, 10);
	messageMode = (*new SettingEnum()).
		addEntry(EnumEntry("Kek", 0)).
		addEntry(EnumEntry("Toxic", 1)).
		addEntry(EnumEntry("Fadeaway", 2));
	registerEnumSetting("Mode", &messageMode, 0);
	registerIntSetting("DelaySeconds", &delay, delay, 1, 10);
}
ChatBot::~ChatBot() {
}

const char* ChatBot::getModuleName() {
	return "ChatBot";
}

void ChatBot::onEnable() {
	messageIndex = 0;
}

void ChatBot::onTick(C_GameMode* gm) {
	C_TextPacket textPacket;
	messageTimer++;
	if (messageIndex <= 0)
		messageIndex = 1;//Prevent invis msgs

	if (messageMode.selected == 0) {
		if (messageIndex > 13)
			messageIndex = 0;
		if (messageTimer >= delay * 20) {
			for (int i = 0; i < messageIndex; i++)
				textPacket.message.setText(bypass ? (Utils::randomString(length) + " | " + kekList[i] + " | " + Utils::randomString(length)) : kekList[i]);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			messageIndex++;
			messageTimer = 0;
		}
	}
	if (messageMode.selected == 1) {
		if (messageIndex > 15)
			messageIndex = 0;
		if (messageTimer >= delay * 20) {
			for (int i = 0; i < messageIndex; i++)
				textPacket.message.setText(bypass ? (Utils::randomString(length) + " | " + toxicList[i] + " | " + Utils::randomString(length)) : toxicList[i]);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			messageIndex++;
			messageTimer = 0;
		}
	}
	if (messageMode.selected == 2) {
		if (messageIndex > 11)
			messageIndex = 0;
		if (messageTimer >= delay * 20) {
			for (int i = 0; i < messageIndex; i++)
				textPacket.message.setText(bypass ? (Utils::randomString(length) + " | " + fadedList[i] + " | " + Utils::randomString(length)) : fadedList[i]);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			messageIndex++;
			messageTimer = 0;
		}
	}

}
