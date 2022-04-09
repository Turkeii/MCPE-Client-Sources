#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "MidClick.h"

MidClick::MidClick() : IModule(0, Category::MISC, "Click a player with your mouse wheel to add as friend") {
}

MidClick::~MidClick() {
}

const char* MidClick::getModuleName() {
	return "MidClick";
}

void MidClick::onTick(C_GameMode* gm) {
	C_Entity* entity = g_Data.getClientInstance()->getPointerStruct()->getEntity();
	if (entity == nullptr) 
		return;

	std::string name = entity->getNameTag()->getText();

	if (GameData::isWheelDown() && !hasClicked) {
		name = Utils::sanitize(name);
		if (!FriendList::findPlayer(name)) {
			FriendList::addPlayerToList(name);
			g_Data.getGuiData()->displayClientMessageF("%sSuccessfully added %s %sto your friendlist.", GREEN, name.c_str(), GREEN);
		} else {
			std::transform(name.begin(), name.end(), name.begin(), ::tolower);
			FriendList::removePlayer(name);
			g_Data.getGuiData()->displayClientMessageF("%sSuccessfully removed %s %sfrom your friendlist.", GREEN, name.c_str(), GREEN);
		}
		hasClicked = true;
	} else if (!GameData::isWheelDown()) {
		hasClicked = false;
	}
}