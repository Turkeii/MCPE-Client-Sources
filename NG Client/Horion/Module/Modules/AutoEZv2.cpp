#include "AutoEZv2.h"
#include "../../../Utils/Utils.h"
#include <stdlib.h>     /* srand, rand */
#include<time.h>

//Private this; Made by eKowz
AutoEZv2::AutoEZv2() : IModule(0x0, Category::SERVER, "troll enemies by saying ur lagging") {
}

AutoEZv2::~AutoEZv2() {}

const char* AutoEZv2::getModuleName() {
	return ("AutoEZv2");
}

void AutoEZv2::onEnable() {
	srand(time(NULL));
	kc = rand() % 156;
	send = true;
}

void AutoEZv2::onDisable() {
	srand(time(NULL));
	kc = rand() % 156;
}

void AutoEZv2::onTick(C_GameMode* gm) {
	if (kc > 156) {
		kc = 0;
	}

	if (send) {
		auto autoezv2 = moduleMgr->getModule<AutoEZv2>();
		C_TextPacket textPacket;
		if (kc == 0) {
			textPacket.message.setText(m1);
		}
		if (kc == 1) {
			textPacket.message.setText(m2);
		}
		if (kc == 2) {
			textPacket.message.setText(m3);
		}
		if (kc == 3) {
			textPacket.message.setText(m4);
		}
		if (kc == 4) {
			textPacket.message.setText(m5);
		}
		if (kc == 5) {
			textPacket.message.setText(m6);
		}
		if (kc == 6) {
			textPacket.message.setText(m7);
		}
		if (kc == 7) {
			textPacket.message.setText(m8);
		}
		if (kc == 8) {
			textPacket.message.setText(m9);
		}
		if (kc == 9) {
			textPacket.message.setText(m10);
		}
		if (kc == 10) {
			textPacket.message.setText(m11);
		}
		if (kc == 11) {
			textPacket.message.setText(m12);
		}
		if (kc == 12) {
			textPacket.message.setText(m13);
		}
		if (kc == 13) {
			textPacket.message.setText(m14);
		}
		if (kc == 14) {
			textPacket.message.setText(m15);
		}
		if (kc == 15) {
			textPacket.message.setText(m16);
		}
		if (kc == 16) {
			textPacket.message.setText(m17);
		}
		if (kc == 17) {
			textPacket.message.setText(m18);
		}
		if (kc == 18) {
			textPacket.message.setText(m19);
		}
		if (kc == 19) {
			textPacket.message.setText(m20);
		}
		if (kc == 20) {
			textPacket.message.setText(m21);
		}
		if (kc == 21) {
			textPacket.message.setText(m22);
		}
		if (kc == 22) {
			textPacket.message.setText(m23);
		}
		if (kc == 23) {
			textPacket.message.setText(m24);
		}
		if (kc == 24) {
			textPacket.message.setText(m25);
		}
		if (kc == 25) {
			textPacket.message.setText(m26);
		}
		if (kc == 26) {
			textPacket.message.setText(m27);
		}
		if (kc == 27) {
			textPacket.message.setText(m28);
		}
		if (kc == 28) {
			textPacket.message.setText(m29);
		}
		if (kc == 29) {
			textPacket.message.setText(m30);
		}
		if (kc == 30) {
			textPacket.message.setText(m31);
		}
		if (kc == 31) {
			textPacket.message.setText(m32);
		}
		if (kc == 32) {
			textPacket.message.setText(m33);
		}
		if (kc == 33) {
			textPacket.message.setText(m34);
		}
		if (kc == 34) {
			textPacket.message.setText(m35);
		}
		if (kc == 35) {
			textPacket.message.setText(m36);
		}
		if (kc == 36) {
			textPacket.message.setText(m37);
		}
		if (kc == 37) {
			textPacket.message.setText(m38);
		}
		if (kc == 38) {
			textPacket.message.setText(m39);
		}
		if (kc == 39) {
			textPacket.message.setText(m40);
		}
		if (kc == 40) {
			textPacket.message.setText(m41);
		}
		if (kc == 41) {
			textPacket.message.setText(m42);
		}
		if (kc == 42) {
			textPacket.message.setText(m43);
		}
		if (kc == 43) {
			textPacket.message.setText(m44);
		}
		if (kc == 44) {
			textPacket.message.setText(m45);
		}
		if (kc == 45) {
			textPacket.message.setText(m46);
		}
		if (kc == 46) {
			textPacket.message.setText(m47);
		}
		if (kc == 47) {
			textPacket.message.setText(m48);
		}
		if (kc == 48) {
			textPacket.message.setText(m49);
		}
		if (kc == 49) {
			textPacket.message.setText(m50);
		}
		if (kc == 50) {
			textPacket.message.setText(m51);
		}
		if (kc == 51) {
			textPacket.message.setText(m52);
		}
		if (kc == 52) {
			textPacket.message.setText(m53);
		}
		if (kc == 53) {
			textPacket.message.setText(m54);
		}
		if (kc == 54) {
			textPacket.message.setText(m55);
		}
		if (kc == 55) {
			textPacket.message.setText(m56);
		}
		if (kc == 56) {
			textPacket.message.setText(m57);
		}
		if (kc == 57) {
			textPacket.message.setText(m58);
		}
		if (kc == 58) {
			textPacket.message.setText(m59);
		}
		if (kc == 59) {
			textPacket.message.setText(m60);
		}
		if (kc == 60) {
			textPacket.message.setText(m61);
		}
		if (kc == 61) {
			textPacket.message.setText(m62);
		}
		if (kc == 62) {
			textPacket.message.setText(m63);
		}
		if (kc == 63) {
			textPacket.message.setText(m64);
		}
		if (kc == 64) {
			textPacket.message.setText(m65);
		}
		if (kc == 65) {
			textPacket.message.setText(m66);
		}
		if (kc == 66) {
			textPacket.message.setText(m67);
		}
		if (kc == 67) {
			textPacket.message.setText(m68);
		}
		if (kc == 68) {
			textPacket.message.setText(m69);
		}
		if (kc == 69) {
			textPacket.message.setText(m70);
		}
		if (kc == 70) {
			textPacket.message.setText(m71);
		}
		if (kc == 71) {
			textPacket.message.setText(m72);
		}
		if (kc == 72) {
			textPacket.message.setText(m73);
		}
		if (kc == 73) {
			textPacket.message.setText(m74);
		}
		if (kc == 74) {
			textPacket.message.setText(m75);
		}
		if (kc == 75) {
			textPacket.message.setText(m76);
		}
		if (kc == 76) {
			textPacket.message.setText(m77);
		}
		if (kc == 77) {
			textPacket.message.setText(m78);
		}
		if (kc == 78) {
			textPacket.message.setText(m79);
		}
		if (kc == 79) {
			textPacket.message.setText(m80);
		}
		if (kc == 80) {
			textPacket.message.setText(m81);
		}
		if (kc == 81) {
			textPacket.message.setText(m82);
		}
		if (kc == 82) {
			textPacket.message.setText(m83);
		}
		if (kc == 83) {
			textPacket.message.setText(m84);
		}
		if (kc == 84) {
			textPacket.message.setText(m85);
		}
		if (kc == 85) {
			textPacket.message.setText(m86);
		}
		if (kc == 86) {
			textPacket.message.setText(m87);
		}
		if (kc == 87) {
			textPacket.message.setText(m88);
		}
		if (kc == 88) {
			textPacket.message.setText(m89);
		}
		if (kc == 89) {
			textPacket.message.setText(m90);
		}
		if (kc == 90) {
			textPacket.message.setText(m91);
		}
		if (kc == 91) {
			textPacket.message.setText(m92);
		}
		if (kc == 92) {
			textPacket.message.setText(m93);
		}
		if (kc == 93) {
			textPacket.message.setText(m94);
		}
		if (kc == 94) {
			textPacket.message.setText(m95);
		}
		if (kc == 95) {
			textPacket.message.setText(m96);
		}
		if (kc == 96) {
			textPacket.message.setText(m97);
		}
		if (kc == 97) {
			textPacket.message.setText(m98);
		}
		if (kc == 98) {
			textPacket.message.setText(m99);
		}
		if (kc == 99) {
			textPacket.message.setText(m100);
		}
		if (kc == 100) {
			textPacket.message.setText(m101);
		}
		if (kc == 101) {
			textPacket.message.setText(m102);
		}
		if (kc == 102) {
			textPacket.message.setText(m103);
		}
		if (kc == 103) {
			textPacket.message.setText(m104);
		}
		if (kc == 104) {
			textPacket.message.setText(m105);
		}
		if (kc == 105) {
			textPacket.message.setText(m106);
		}
		if (kc == 106) {
			textPacket.message.setText(m107);
		}
		if (kc == 107) {
			textPacket.message.setText(m108);
		}
		if (kc == 108) {
			textPacket.message.setText(m109);
		}
		if (kc == 109) {
			textPacket.message.setText(m110);
		}
		if (kc == 110) {
			textPacket.message.setText(m111);
		}
		if (kc == 111) {
			textPacket.message.setText(m112);
		}
		if (kc == 112) {
			textPacket.message.setText(m113);
		}
		if (kc == 113) {
			textPacket.message.setText(m114);
		}
		if (kc == 114) {
			textPacket.message.setText(m115);
		}
		if (kc == 115) {
			textPacket.message.setText(m116);
		}
		if (kc == 116) {
			textPacket.message.setText(m117);
		}
		if (kc == 117) {
			textPacket.message.setText(m118);
		}
		if (kc == 118) {
			textPacket.message.setText(m119);
		}
		if (kc == 119) {
			textPacket.message.setText(m120);
		}
		if (kc == 120) {
			textPacket.message.setText(m121);
		}
		if (kc == 121) {
			textPacket.message.setText(m122);
		}
		if (kc == 122) {
			textPacket.message.setText(m123);
		}
		if (kc == 123) {
			textPacket.message.setText(m124);
		}
		if (kc == 124) {
			textPacket.message.setText(m125);
		}
		if (kc == 125) {
			textPacket.message.setText(m126);
		}
		if (kc == 126) {
			textPacket.message.setText(m127);
		}
		if (kc == 127) {
			textPacket.message.setText(m128);
		}
		if (kc == 128) {
			textPacket.message.setText(m129);
		}
		if (kc == 129) {
			textPacket.message.setText(m130);
		}
		if (kc == 130) {
			textPacket.message.setText(m131);
		}
		if (kc == 131) {
			textPacket.message.setText(m132);
		}
		if (kc == 132) {
			textPacket.message.setText(m133);
		}
		if (kc == 133) {
			textPacket.message.setText(m134);
		}
		if (kc == 134) {
			textPacket.message.setText(m135);
		}
		if (kc == 135) {
			textPacket.message.setText(m136);
		}
		if (kc == 136) {
			textPacket.message.setText(m137);
		}
		if (kc == 137) {
			textPacket.message.setText(m138);
		}
		if (kc == 138) {
			textPacket.message.setText(m139);
		}
		if (kc == 139) {
			textPacket.message.setText(m140);
		}
		if (kc == 140) {
			textPacket.message.setText(m141);
		}
		if (kc == 141) {
			textPacket.message.setText(m142);
		}
		if (kc == 142) {
			textPacket.message.setText(m143);
		}
		if (kc == 143) {
			textPacket.message.setText(m144);
		}
		if (kc == 144) {
			textPacket.message.setText(m145);
		}
		if (kc == 145) {
			textPacket.message.setText(m146);
		}
		if (kc == 146) {
			textPacket.message.setText(m147);
		}
		if (kc == 147) {
			textPacket.message.setText(m148);
		}
		if (kc == 148) {
			textPacket.message.setText(m149);
		}
		if (kc == 149) {
			textPacket.message.setText(m150);
		}
		if (kc == 150) {
			textPacket.message.setText(m151);
		}
		if (kc == 151) {
			textPacket.message.setText(m152);
		}
		if (kc == 152) {
			textPacket.message.setText(m153);
		}
		if (kc == 153) {
			textPacket.message.setText(m154);
		}
		if (kc == 154) {
			textPacket.message.setText(m155);
		}
		if (kc == 155) {
			textPacket.message.setText(m156);
		}
		if (kc == 156) {
			textPacket.message.setText(m157);
		}
		textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
		textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
		send = false;
		kc = 0;
		if (autoezv2->isEnabled()) autoezv2->setEnabled(false);
	}
}