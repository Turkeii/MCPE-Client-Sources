#include <string>

#include "../../../Utils/Utils.h"
#include "Verify.h"
//Added this her ebec no point in fill rebuild each time we add a name
std::string allowedNames[] = {"Xello12121", "Stereoskopia", "IbeetBlacksWhip", "Kcom04", "Olioq", "TofuReggieBonz", "CommieComrade69", "BailaIsLameSmh", "Deadtros", "Morning3475", "R1ester", "HiveBasher140", "Desireeqq", "NRG Jobro", "NRG_Jobro", "Intoprelised", "brushpod", "maybefog", "ClientCarried", "SCOttIe001sc", "JTAOZ", "Liittle Kow", "Hydwogen"};

Verification::Verification() : IModule(0, Category::MISC, "Checks if you are pro and based") {
}

Verification::~Verification() {
}

const char* Verification::getModuleName() {
	return ("Verify");
}

void Verification::onTick(C_GameMode* gm) {
	if (g_Data.getLocalPlayer() == nullptr) return;

	if (test == false) {
		clientMessageF("Checking authorization...");

		std::string playerIGN = g_Data.getLocalPlayer()->getNameTag()->getText();

		for (auto checkOne : allowedNames) {
			std::size_t strHas = playerIGN.find(checkOne);

			if (playerIGN == "" /*|| playerIGN == ""*/) {
				return;  // user is offline; let them test in a flatworld XD
			} else if (strHas != std::string::npos) {
				passedTest = true;
				test = true;
				break;
			} else
				passedTest = false;
			test = true;
		}

		if (passedTest) {
			clientMessageF("Authorized Kek.Club+ User.");
		} else if (passedTest == false) {
			clientMessageF("Unauthorized User. Enjected!");
			GameData::terminate();
		}
	}
}

void Verification::onDisable() {
	setEnabled(true);
}