#include "MCF.h"
#include "../pch.h"

using namespace std;
MCF::MCF() : IModule(0, Category::OTHER, "Middle Click add/remove Friends") {
}
const char* MCF::getModuleName() {
	return "MCF";
}

void MCF::onTick(C_GameMode* gm) {
	C_Entity* entity = g_Data.getLocalPlayer()->pointingStruct->getEntity();
	if (entity == nullptr) 
		return;

	string name = entity->getNameTag()->getText();
	name = Utils::sanitize(name);
	name = name.substr(0, name.find('\n'));

	if (GameData::isWheelDown() && !hasClicked) {
		string removed = "Successfully unfriended " + name;
		string added = "Successfully friended " + name;

		if (!FriendList::findPlayer(name)) {
			FriendList::addPlayerToList(name);
			//auto notififcation = g_Data.addNotification("MCF:", added); notififcation->duration = 5;
		} else {
			transform(name.begin(), name.end(), name.begin(), ::tolower);
			FriendList::removePlayer(name);
			//auto notififcation = g_Data.addNotification("MCF:", removed); notififcation->duration = 5;
		}
		hasClicked = true;
	} else if (!GameData::isWheelDown()) hasClicked = false;
}