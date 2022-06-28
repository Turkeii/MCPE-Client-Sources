#include "MidClick.h"
bool alert;
MidClick::MidClick() : IModule(0, Category::MISC, "you press button and the world becomes a better place :D") {
	registerBoolSetting("Message", &alert, false);
}

MidClick::~MidClick() {
}

const char* MidClick::getModuleName() {
	return "MCF";
}

void MidClick::onTick(C_GameMode* gm) {
	C_Entity* entity = g_Data.getLocalPlayer()->pointingStruct->getEntity();
	if (entity == nullptr) 
		return;

	std::string name = entity->getNameTag()->getText();

	if (GameData::isWheelDown() && !hasClicked) {
		if (!FriendList::findPlayer(name)) {
			FriendList::addPlayerToList(name);
			g_Data.getGuiData()->displayClientMessageF("%sSuccessfully added %s %sto your friendlist.", GREEN, name.c_str(), GREEN);
			if (alert) {
				C_TextPacket textPacket;
				textPacket.message.setText("/msg " + name + " You Have Been Friended On Kek.Club+.");
				textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
				textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			}
		} else {
			std::transform(name.begin(), name.end(), name.begin(), ::tolower);
			FriendList::removePlayer(name);
			g_Data.getGuiData()->displayClientMessageF("%sSuccessfully removed %s %sfrom your friendlist.", RED, name.c_str(), RED);
		}
		hasClicked = true;		
	} else if (!GameData::isWheelDown()) {
		hasClicked = false;
	}
}
