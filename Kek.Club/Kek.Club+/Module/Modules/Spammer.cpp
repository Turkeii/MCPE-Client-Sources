#include "Spammer.h"

#include "../../../Utils/Utils.h"

Spammer::Spammer() : IModule(0, Category::MISC, "Spams a message in a specified delay") {
	registerIntSetting("delay", &this->delay, this->delay, 1, 10);
	registerIntSetting("length", &this->length, this->length, 1, 60);
	registerBoolSetting("bypass", &this->bypass, this->bypass);
}

Spammer::~Spammer() {
}
const char* Spammer::getModName() {
	if (bypass) {
		return " Bypass";
	} else {
		return "";
	}
}
const char* Spammer::getModuleName() {
	return ("Spammer");
}

void Spammer::onTick(C_GameMode* gm) {
	Odelay++;
	if (changer == 0) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message + " | " + Utils::randomString(length)) : message);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 1;  // this will make the spammer go to the next text after sending the first one
		}
	}
	if (changer == 1) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message2 + " | " + Utils::randomString(length)) : message2);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 2;  // this one will go to the next
		}
	}
	if (changer == 2) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message3 + " | " + Utils::randomString(length)) : message3);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 3;
		}
	}
	if (changer == 3) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message4 + " | " + Utils::randomString(length)) : message4);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 4;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 4) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message5 + " | " + Utils::randomString(length)) : message5);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 5;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 5) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message6 + " | " + Utils::randomString(length)) : message6);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 6;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 6) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message7 + " | " + Utils::randomString(length)) : message7);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 7;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 7) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message8 + " | " + Utils::randomString(length)) : message8);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 8;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 8) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message9 + " | " + Utils::randomString(length)) : message9);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 9;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 9) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message10 + " | " + Utils::randomString(length)) : message10);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 10;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 10) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message11 + " | " + Utils::randomString(length)) : message11);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 11;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 11) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message12 + " | " + Utils::randomString(length)) : message12);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 12;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 12) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message13 + " | " + Utils::randomString(length)) : message13);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 13;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 13) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message14 + " | " + Utils::randomString(length)) : message14);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 14;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 14) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message15 + " | " + Utils::randomString(length)) : message15);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 15;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 15) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message16 + " | " + Utils::randomString(length)) : message16);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 16;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 16) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message17 + " | " + Utils::randomString(length)) : message17);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 17;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 17) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message18 + " | " + Utils::randomString(length)) : message18);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 18;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 18) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message19 + " | " + Utils::randomString(length)) : message19);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 19;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 19) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message19 + " | " + Utils::randomString(length)) : message19);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 20;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 20) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message20 + " | " + Utils::randomString(length)) : message20);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 21;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 21) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message21 + " | " + Utils::randomString(length)) : message21);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 22;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 22) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message22 + " | " + Utils::randomString(length)) : message22);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 23;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 23) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message23 + " | " + Utils::randomString(length)) : message23);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 24;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 24) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message24 + " | " + Utils::randomString(length)) : message24);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 25;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 25) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message25 + " | " + Utils::randomString(length)) : message25);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 26;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 26) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message26 + " | " + Utils::randomString(length)) : message26);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 27;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 27) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message27 + " | " + Utils::randomString(length)) : message27);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 28;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 28) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message28 + " | " + Utils::randomString(length)) : message28);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 29;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 29) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message29 + " | " + Utils::randomString(length)) : message29);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 30;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 30) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message30 + " | " + Utils::randomString(length)) : message30);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 31;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 31) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message31 + " | " + Utils::randomString(length)) : message31);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 32;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 32) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message32 + " | " + Utils::randomString(length)) : message32);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 33;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 33) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message33 + " | " + Utils::randomString(length)) : message33);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 34;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 34) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message34 + " | " + Utils::randomString(length)) : message34);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 35;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 35) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message35 + " | " + Utils::randomString(length)) : message35);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 36;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 36) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message36 + " | " + Utils::randomString(length)) : message36);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 37;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 37) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message37 + " | " + Utils::randomString(length)) : message37);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 38;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 38) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message38 + " | " + Utils::randomString(length)) : message38);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 39;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 39) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message39 + " | " + Utils::randomString(length)) : message39);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 40;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 40) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message40 + " | " + Utils::randomString(length)) : message40);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 41;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 41) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message41 + " | " + Utils::randomString(length)) : message41);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 42;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 42) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message42 + " | " + Utils::randomString(length)) : message42);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 43;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 43) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message43 + " | " + Utils::randomString(length)) : message43);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 44;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 44) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message44 + " | " + Utils::randomString(length)) : message44);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 45;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 45) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message45 + " | " + Utils::randomString(length)) : message45);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 46;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 46) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message46 + " | " + Utils::randomString(length)) : message46);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 47;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 47) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message47 + " | " + Utils::randomString(length)) : message47);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 48;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 48) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message48 + " | " + Utils::randomString(length)) : message48);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 49;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 49) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message49 + " | " + Utils::randomString(length)) : message49);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 50;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 50) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message50 + " | " + Utils::randomString(length)) : message50);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 51;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 51) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message51 + " | " + Utils::randomString(length)) : message51);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 52;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 52) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message52 + " | " + Utils::randomString(length)) : message52);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 53;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 53) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message53 + " | " + Utils::randomString(length)) : message53);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 54;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 54) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message54 + " | " + Utils::randomString(length)) : message54);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 55;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 55) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message55 + " | " + Utils::randomString(length)) : message55);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 56;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 56) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message56 + " | " + Utils::randomString(length)) : message56);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 57;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 57) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message57 + " | " + Utils::randomString(length)) : message57);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 58;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 58) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message58 + " | " + Utils::randomString(length)) : message58);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 59;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 59) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message59 + " | " + Utils::randomString(length)) : message59);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 60;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 60) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message60 + " | " + Utils::randomString(length)) : message60);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 61;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 61) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message61 + " | " + Utils::randomString(length)) : message61);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 62;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 62) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message62 + " | " + Utils::randomString(length)) : message62);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 63;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 63) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message63 + " | " + Utils::randomString(length)) : message63);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 64;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 64) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message64 + " | " + Utils::randomString(length)) : message64);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 65;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 65) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message65 + " | " + Utils::randomString(length)) : message65);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 66;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 66) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message66 + " | " + Utils::randomString(length)) : message66);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 67;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 67) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message67 + " | " + Utils::randomString(length)) : message67);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 68;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 68) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message68 + " | " + Utils::randomString(length)) : message68);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 69;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 69) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message69 + " | " + Utils::randomString(length)) : message69);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 70;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 70) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message70 + " | " + Utils::randomString(length)) : message70);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 71;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 71) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message71 + " | " + Utils::randomString(length)) : message71);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 72;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 72) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message72 + " | " + Utils::randomString(length)) : message72);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 73;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 73) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message73 + " | " + Utils::randomString(length)) : message73);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 74;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 74) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message74 + " | " + Utils::randomString(length)) : message74);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 75;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 75) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message75 + " | " + Utils::randomString(length)) : message75);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 76;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 76) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message76 + " | " + Utils::randomString(length)) : message76);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 77;  // and this will make the spammer go to the first text
		}
	}
	if (changer == 77) {
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message77 + " | " + Utils::randomString(length)) : message77);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
			changer = 0;  // and this will make the spammer go to the first text
		}
	}
}