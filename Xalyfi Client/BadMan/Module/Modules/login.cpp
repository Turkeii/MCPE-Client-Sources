#include "../../../Utils/Utils.h"
#include "login.h"

Verify::Verify() : IModule(0, Category::CUSTOM, "if you found , you are hacker") {
}

Verify::~Verify() {
}

const char* Verify::getModuleName() {
	return ("Konichiwa");
}

void Verify::onTick(C_GameMode* gm) {
	if (g_Data.getLocalPlayer() == nullptr) return;
	if (test) return;
	clientMessageF("Checking...");

	if (test == false) {
		std::string playerID = g_Data.getLocalPlayer()->getNameTag()->getText();

		for (auto checkOne : authuser) {
			if (playerID == checkOne) {
				passedTest = true;
				break;
			}
		}
		test = true;
	}

	if (passedTest) {
		clientMessageF("Authenticated Arigatou Xalyfi https://shinxe.cf", GREEN);
		clientMessageF("Authenticated Arigatou Xalyfi https://shinxe.cf", GREEN);
		clientMessageF("Authenticated Arigatou Xalyfi https://shinxe.cf", GREEN);
		clientMessageF("Authenticated Arigatou Xalyfi https://shinxe.cf", GREEN);
		clientMessageF("Authenticated Arigatou Xalyfi https://shinxe.cf", GREEN);
		clientMessageF("Authenticated Arigatou Xalyfi https://shinxe.cf", GREEN);
	}
	if (passedTest == false) {
		clientMessageF("EZZZZZZZZZZZZZ YOU CAN'T USE PLEASE DM ShinXe#9999", RED);
		clientMessageF("EZZZZZZZZZZZZZ YOU CAN'T USE PLEASE DM ShinXe#9999", RED);
		clientMessageF("EZZZZZZZZZZZZZ YOU CAN'T USE PLEASE DM ShinXe#9999", RED);
		clientMessageF("EZZZZZZZZZZZZZ YOU CAN'T USE PLEASE DM ShinXe#9999", RED);
		clientMessageF("EZZZZZZZZZZZZZ YOU CAN'T USE PLEASE DM ShinXe#9999", RED);
		clientMessageF("EZZZZZZZZZZZZZ YOU CAN'T USE PLEASE DM ShinXe#9999", RED);
		GameData::terminate();
	}
}

void Verify::onDisable() {
	this->setEnabled(true);
}