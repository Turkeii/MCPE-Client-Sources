#include "Spammer.h"

#include "../../../Utils/Utils.h"
#include "../ModuleManager.h"

Spammer::Spammer() : IModule(0x0, Category::MISC, "Spams a message in a specified delay") {
	registerIntSetting("delay", &this->delay, this->delay, 0, 10);

	registerEnumSetting("Text Modes", &spamMode, 0);
	spamMode = SettingEnum(this)
				.addEntry(EnumEntry("Default", 0))
				.addEntry(EnumEntry("Gloat", 1))
				.addEntry(EnumEntry("Excuse", 2))
				.addEntry(EnumEntry("Honour", 3))
				.addEntry(EnumEntry("Xalyfi", 4))
				.addEntry(EnumEntry("Symbol", 5));

	registerEnumSetting("Extensions", &extensionMode, 0);
	extensionMode = SettingEnum(this)
				.addEntry(EnumEntry("None", 0))
				.addEntry(EnumEntry("#Xalyfi", 1))
				.addEntry(EnumEntry("Discord", 2))
				.addEntry(EnumEntry("Bypass", 3))
				.addEntry(EnumEntry("BypassV2", 4));

	registerBoolSetting("Custom Message", &this->custom, this->custom);

}

Spammer::~Spammer() {
}

const char* Spammer::getModuleName() {
	return ("Spammer");
}

void Spammer::onTick(C_GameMode* gm) {
	switch (spamMode.selected) {

	case 0:
		message = "Why don't we use Xalyfi";
		message2 = "Chronos Badman ezzz << Xalyfi";
		message3 = "Xalyfi on TOP";
		message4 = "All of us love Xalyfi";
		message5 = "If you don't use Xalyfi,You are weak";
		message6 = "We are beat Chronos";
		message7 = "Xalyfi is really strong";
		message8 = "They use ez client";
		message9 = "what is the strongest client";
		message10 = "answer is Xalyfi";
		message11 = "I love Xalyfi";
		message12 = "If you don't know Xalyfi";
		message13 = "You must leave here";
		message14 = "Many people uses Xalyfi";
		message15 = "Xalyfiiiiiiiiiiiii";
		break;

	case 1:
		message = "Why don't we use Xalyfi";
		message2 = "Chronos Badman ezzz << Xalyfi";
		message3 = "Xalyfi on TOP";
		message4 = "All of us love Xalyfi";
		break;

	case 2:
		message = ">Why don't we use Xalyfi";
		message2 = ">Chronos Badman ezzz << Xalyfi";
		message3 = ">Xalyfi on TOP";
		message4 = ">All of us love Xalyfi";
		break;

	case 3:
		message = ">Why don't we use Xalyfi";
		message2 = ">Chronos Badman ezzz << Xalyfi";
		message3 = ">Xalyfi on TOP";
		message4 = ">All of us love Xalyfi";
		break;

	case 4:
		if (g_Data.isInGame()) {
			playerName = g_Data.getLocalPlayer()->getNameTag()->getText();
		}

		message = ">Hi my name is " + playerName + " and love Xalyfi ";
		message2 = ">Did you know that " + playerName + " is a Xalyfi fan";
		message3 = ">Guess what? " + playerName + " is a Xalyfi user and theres nothing you can do about it :O";
		message4 = ">Bro just stfu " + playerName + " Xalyfiiiiiii";
		break;

	case 5:
		message = "î€„î€…î€†îƒ§î€‡îƒ¨î€‹îƒ¦î€Šîƒ¥î€€î€î€‚î€ƒî€Œî€î€Žî€î€ˆî€‰î€ î€¡î€¢î€£î€¤î€¥î€¦î€§î€¨î€©î€ªî€«î€¬î€­î€®î€¯î€îî‚îƒî„î…î†î‡îˆî‰îŠîƒ†îƒ‡î‹îƒ‰îƒŠîŒîîŽîî î¡î¢î£î°î±î²î³î¥î¦î§î¨îƒîƒ î©îªî«î¬î­î‚€î‚î‚‚î‚ƒî‚„î‚…î‚†î‚‡î‚ î‚¡î„€î„î„‚î„…î„ƒî„„îƒ€îƒîƒ¡îƒ¢îƒ©îƒªî€„î€…î€†îƒ§î€‡îƒ¨î€‹îƒ¦î€Šîƒ¥î€€î€î€‚î€ƒî€Œî€î€Žî€î€ˆî€‰î€ î€¡î€¢î€£î€¤î€¥î€¦î€§î€¨î€©î€ªî€«î€¬î€­î€®î€¯î€îî‚îƒî„î…î†î‡îˆî‰îŠîƒ†îƒ‡î‹îƒ‰îƒŠîŒîîŽîî î¡î¢î£î°î±î²î³î¥î¦î§î¨îƒîƒ î©îªî«î¬î­î‚€î‚î‚‚î‚ƒî‚„î‚…î‚†î‚‡î‚ î‚¡î„€î„î„‚î„…î„ƒî„„îƒ€îƒîƒ¡îƒ¢îƒ©îƒªî€„î€…î€†îƒ§î€‡îƒ¨î€‹îƒ¦î€Šîƒ¥î€€î€î€‚î€ƒî€Œî€î€Žî€î€ˆî€‰î€ î€¡î€¢î€£î€¤î€¥î€¦î€§î€¨î€©î€ªî€«î€¬î€­î€®î€¯î€îî‚îƒî„î…î†î‡îˆî‰îŠîƒ†îƒ‡î‹îƒ‰îƒŠîŒîîŽîî î¡î¢î£î°î±î²î³î¥î¦î§î¨îƒîƒ î©îªî«î¬î­î‚€î‚î‚‚î‚ƒî‚„î‚…î‚†î‚‡î‚ î‚¡î„€î„î„‚î„…î„ƒî„„îƒ€îƒîƒ¡îƒ¢îƒ©îƒªî€„î€…î€†îƒ§î€‡îƒ¨î€‹îƒ¦î€Šîƒ¥î€€î€î€‚î€ƒî€Œî€î€Žî€î€ˆî€‰î€ î€¡î€¢î€£î€¤î€¥î€¦î€§î€¨î€©î€ªî€«î€¬î€­î€®î€¯î€îî‚îƒî„î…î†î‡îˆî‰îŠîƒ†îƒ‡î‹îƒ‰îƒŠîŒîîŽîî î¡î¢î£î°î±î²î³î¥î¦î§î¨îƒîƒ î©îªî«î¬î­î‚€î‚î‚‚î‚ƒî‚„î‚…î‚†î‚‡î‚ î‚¡î„€î„î„‚î„…î„ƒî„„îƒ€îƒîƒ¡îƒ¢îƒ©îƒªî€„î€…î€†îƒ§î€‡îƒ¨î€‹îƒ¦î€Šîƒ¥î€€î€î€‚î€ƒî€Œî€î€Žî€î€ˆî€‰î€ î€¡î€¢î€£î€¤î€¥î€¦î€§î€¨î€©î€ªî€«î€¬î€­î€®î€¯î€îî‚îƒî„î…î†î‡îˆî‰îŠîƒ†îƒ‡î‹îƒ‰îƒŠîŒîîŽîî î¡î¢î£î°î±î²î³î¥î¦î§î¨îƒîƒ î©îªî«î¬î­î‚€î‚î‚‚î‚ƒî‚„î‚…î‚†î‚‡î‚ î‚¡î„€î„î„‚î„…î„ƒî„„îƒ€îƒîƒ¡îƒ¢îƒ©îƒª";
		message2 = "î€„î€…î€†îƒ§î€‡îƒ¨î€‹îƒ¦î€Šîƒ¥î€€î€î€‚î€ƒî€Œî€î€Žî€î€ˆî€‰î€ î€¡î€¢î€£î€¤î€¥î€¦î€§î€¨î€©î€ªî€«î€¬î€­î€®î€¯î€îî‚îƒî„î…î†î‡îˆî‰îŠîƒ†îƒ‡î‹îƒ‰îƒŠîŒîîŽîî î¡î¢î£î°î±î²î³î¥î¦î§î¨îƒîƒ î©îªî«î¬î­î‚€î‚î‚‚î‚ƒî‚„î‚…î‚†î‚‡î‚ î‚¡î„€î„î„‚î„…î„ƒî„„îƒ€îƒîƒ¡îƒ¢îƒ©îƒªî€„î€…î€†îƒ§î€‡îƒ¨î€‹îƒ¦î€Šîƒ¥î€€î€î€‚î€ƒî€Œî€î€Žî€î€ˆî€‰î€ î€¡î€¢î€£î€¤î€¥î€¦î€§î€¨î€©î€ªî€«î€¬î€­î€®î€¯î€îî‚îƒî„î…î†î‡îˆî‰îŠîƒ†îƒ‡î‹îƒ‰îƒŠîŒîîŽîî î¡î¢î£î°î±î²î³î¥î¦î§î¨îƒîƒ î©îªî«î¬î­î‚€î‚î‚‚î‚ƒî‚„î‚…î‚†î‚‡î‚ î‚¡î„€î„î„‚î„…î„ƒî„„îƒ€îƒîƒ¡îƒ¢îƒ©îƒªî€„î€…î€†îƒ§î€‡îƒ¨î€‹îƒ¦î€Šîƒ¥î€€î€î€‚î€ƒî€Œî€î€Žî€î€ˆî€‰î€ î€¡î€¢î€£î€¤î€¥î€¦î€§î€¨î€©î€ªî€«î€¬î€­î€®î€¯î€îî‚îƒî„î…î†î‡îˆî‰îŠîƒ†îƒ‡î‹îƒ‰îƒŠîŒîîŽîî î¡î¢î£î°î±î²î³î¥î¦î§î¨îƒîƒ î©îªî«î¬î­î‚€î‚î‚‚î‚ƒî‚„î‚…î‚†î‚‡î‚ î‚¡î„€î„î„‚î„…î„ƒî„„îƒ€îƒîƒ¡îƒ¢îƒ©îƒªî€„î€…î€†îƒ§î€‡îƒ¨î€‹îƒ¦î€Šîƒ¥î€€î€î€‚î€ƒî€Œî€î€Žî€î€ˆî€‰î€ î€¡î€¢î€£î€¤î€¥î€¦î€§î€¨î€©î€ªî€«î€¬î€­î€®î€¯î€îî‚îƒî„î…î†î‡îˆî‰îŠîƒ†îƒ‡î‹îƒ‰îƒŠîŒîîŽîî î¡î¢î£î°î±î²î³î¥î¦î§î¨îƒîƒ î©îªî«î¬î­î‚€î‚î‚‚î‚ƒî‚„î‚…î‚†î‚‡î‚ î‚¡î„€î„î„‚î„…î„ƒî„„îƒ€îƒîƒ¡îƒ¢îƒ©îƒªî€„î€…î€†îƒ§î€‡îƒ¨î€‹îƒ¦î€Šîƒ¥î€€î€î€‚î€ƒî€Œî€î€Žî€î€ˆî€‰î€ î€¡î€¢î€£î€¤î€¥î€¦î€§î€¨î€©î€ªî€«î€¬î€­î€®î€¯î€îî‚îƒî„î…î†î‡îˆî‰îŠîƒ†îƒ‡î‹îƒ‰îƒŠîŒîîŽîî î¡î¢î£î°î±î²î³î¥î¦î§î¨îƒîƒ î©îªî«î¬î­î‚€î‚î‚‚î‚ƒî‚„î‚…î‚†î‚‡î‚ î‚¡î„€î„î„‚î„…î„ƒî„„îƒ€îƒîƒ¡îƒ¢îƒ©îƒª";
		message3 = "î€„î€…î€†îƒ§î€‡îƒ¨î€‹îƒ¦î€Šîƒ¥î€€î€î€‚î€ƒî€Œî€î€Žî€î€ˆî€‰î€ î€¡î€¢î€£î€¤î€¥î€¦î€§î€¨î€©î€ªî€«î€¬î€­î€®î€¯î€îî‚îƒî„î…î†î‡îˆî‰îŠîƒ†îƒ‡î‹îƒ‰îƒŠîŒîîŽîî î¡î¢î£î°î±î²î³î¥î¦î§î¨îƒîƒ î©îªî«î¬î­î‚€î‚î‚‚î‚ƒî‚„î‚…î‚†î‚‡î‚ î‚¡î„€î„î„‚î„…î„ƒî„„îƒ€îƒîƒ¡îƒ¢îƒ©îƒªî€„î€…î€†îƒ§î€‡îƒ¨î€‹îƒ¦î€Šîƒ¥î€€î€î€‚î€ƒî€Œî€î€Žî€î€ˆî€‰î€ î€¡î€¢î€£î€¤î€¥î€¦î€§î€¨î€©î€ªî€«î€¬î€­î€®î€¯î€îî‚îƒî„î…î†î‡îˆî‰îŠîƒ†îƒ‡î‹îƒ‰îƒŠîŒîîŽîî î¡î¢î£î°î±î²î³î¥î¦î§î¨îƒîƒ î©îªî«î¬î­î‚€î‚î‚‚î‚ƒî‚„î‚…î‚†î‚‡î‚ î‚¡î„€î„î„‚î„…î„ƒî„„îƒ€îƒîƒ¡îƒ¢îƒ©îƒªî€„î€…î€†îƒ§î€‡îƒ¨î€‹îƒ¦î€Šîƒ¥î€€î€î€‚î€ƒî€Œî€î€Žî€î€ˆî€‰î€ î€¡î€¢î€£î€¤î€¥î€¦î€§î€¨î€©î€ªî€«î€¬î€­î€®î€¯î€îî‚îƒî„î…î†î‡îˆî‰îŠîƒ†îƒ‡î‹îƒ‰îƒŠîŒîîŽîî î¡î¢î£î°î±î²î³î¥î¦î§î¨îƒîƒ î©îªî«î¬î­î‚€î‚î‚‚î‚ƒî‚„î‚…î‚†î‚‡î‚ î‚¡î„€î„î„‚î„…î„ƒî„„îƒ€îƒîƒ¡îƒ¢îƒ©îƒªî€„î€…î€†îƒ§î€‡îƒ¨î€‹îƒ¦î€Šîƒ¥î€€î€î€‚î€ƒî€Œî€î€Žî€î€ˆî€‰î€ î€¡î€¢î€£î€¤î€¥î€¦î€§î€¨î€©î€ªî€«î€¬î€­î€®î€¯î€îî‚îƒî„î…î†î‡îˆî‰îŠîƒ†îƒ‡î‹îƒ‰îƒŠîŒîîŽîî î¡î¢î£î°î±î²î³î¥î¦î§î¨îƒîƒ î©îªî«î¬î­î‚€î‚î‚‚î‚ƒî‚„î‚…î‚†î‚‡î‚ î‚¡î„€î„î„‚î„…î„ƒî„„îƒ€îƒîƒ¡îƒ¢îƒ©îƒªî€„î€…î€†îƒ§î€‡îƒ¨î€‹îƒ¦î€Šîƒ¥î€€î€î€‚î€ƒî€Œî€î€Žî€î€ˆî€‰î€ î€¡î€¢î€£î€¤î€¥î€¦î€§î€¨î€©î€ªî€«î€¬î€­î€®î€¯î€îî‚îƒî„î…î†î‡îˆî‰îŠîƒ†îƒ‡î‹îƒ‰îƒŠîŒîîŽîî î¡î¢î£î°î±î²î³î¥î¦î§î¨îƒîƒ î©îªî«î¬î­î‚€î‚î‚‚î‚ƒî‚„î‚…î‚†î‚‡î‚ î‚¡î„€î„î„‚î„…î„ƒî„„îƒ€îƒîƒ¡îƒ¢îƒ©îƒª";
		message4 = "î€„î€…î€†îƒ§î€‡îƒ¨î€‹îƒ¦î€Šîƒ¥î€€î€î€‚î€ƒî€Œî€î€Žî€î€ˆî€‰î€ î€¡î€¢î€£î€¤î€¥î€¦î€§î€¨î€©î€ªî€«î€¬î€­î€®î€¯î€îî‚îƒî„î…î†î‡îˆî‰îŠîƒ†îƒ‡î‹îƒ‰îƒŠîŒîîŽîî î¡î¢î£î°î±î²î³î¥î¦î§î¨îƒîƒ î©îªî«î¬î­î‚€î‚î‚‚î‚ƒî‚„î‚…î‚†î‚‡î‚ î‚¡î„€î„î„‚î„…î„ƒî„„îƒ€îƒîƒ¡îƒ¢îƒ©îƒªî€„î€…î€†îƒ§î€‡îƒ¨î€‹îƒ¦î€Šîƒ¥î€€î€î€‚î€ƒî€Œî€î€Žî€î€ˆî€‰î€ î€¡î€¢î€£î€¤î€¥î€¦î€§î€¨î€©î€ªî€«î€¬î€­î€®î€¯î€îî‚îƒî„î…î†î‡îˆî‰îŠîƒ†îƒ‡î‹îƒ‰îƒŠîŒîîŽîî î¡î¢î£î°î±î²î³î¥î¦î§î¨îƒîƒ î©îªî«î¬î­î‚€î‚î‚‚î‚ƒî‚„î‚…î‚†î‚‡î‚ î‚¡î„€î„î„‚î„…î„ƒî„„îƒ€îƒîƒ¡îƒ¢îƒ©îƒªî€„î€…î€†îƒ§î€‡îƒ¨î€‹îƒ¦î€Šîƒ¥î€€î€î€‚î€ƒî€Œî€î€Žî€î€ˆî€‰î€ î€¡î€¢î€£î€¤î€¥î€¦î€§î€¨î€©î€ªî€«î€¬î€­î€®î€¯î€îî‚îƒî„î…î†î‡îˆî‰îŠîƒ†îƒ‡î‹îƒ‰îƒŠîŒîîŽîî î¡î¢î£î°î±î²î³î¥î¦î§î¨îƒîƒ î©îªî«î¬î­î‚€î‚î‚‚î‚ƒî‚„î‚…î‚†î‚‡î‚ î‚¡î„€î„î„‚î„…î„ƒî„„îƒ€îƒîƒ¡îƒ¢îƒ©îƒªî€„î€…î€†îƒ§î€‡îƒ¨î€‹îƒ¦î€Šîƒ¥î€€î€î€‚î€ƒî€Œî€î€Žî€î€ˆî€‰î€ î€¡î€¢î€£î€¤î€¥î€¦î€§î€¨î€©î€ªî€«î€¬î€­î€®î€¯î€îî‚îƒî„î…î†î‡îˆî‰îŠîƒ†îƒ‡î‹îƒ‰îƒŠîŒîîŽîî î¡î¢î£î°î±î²î³î¥î¦î§î¨îƒîƒ î©îªî«î¬î­î‚€î‚î‚‚î‚ƒî‚„î‚…î‚†î‚‡î‚ î‚¡î„€î„î„‚î„…î„ƒî„„îƒ€îƒîƒ¡îƒ¢îƒ©îƒªî€„î€…î€†îƒ§î€‡îƒ¨î€‹îƒ¦î€Šîƒ¥î€€î€î€‚î€ƒî€Œî€î€Žî€î€ˆî€‰î€ î€¡î€¢î€£î€¤î€¥î€¦î€§î€¨î€©î€ªî€«î€¬î€­î€®î€¯î€îî‚îƒî„î…î†î‡îˆî‰îŠîƒ†îƒ‡î‹îƒ‰îƒŠîŒîîŽîî î¡î¢î£î°î±î²î³î¥î¦î§î¨îƒîƒ î©îªî«î¬î­î‚€î‚î‚‚î‚ƒî‚„î‚…î‚†î‚‡î‚ î‚¡î„€î„î„‚î„…î„ƒî„„îƒ€îƒîƒ¡îƒ¢îƒ©îƒª";
		break;
	}

	switch (extensionMode.selected) {
	case 0:
		bypass = false;
		hash = false;
		discord = false;
		break;

	case 1:
		bypass = false;
		hash = true;
		discord = false;
		break;

	case 2:
		bypass = false;
		hash = false;
		discord = true;
		break;

	case 3:
		bypass = true;
		hash = false;
		discord = false;
		break;

	case 4:
		bypassv2 = true;
		bypass = false;
		hash = false;
		discord = false;
		break;
	}

	if (!custom) {
		Odelay++;
		if (gamer == 0) {
			if (Odelay > delay * 20) {
				C_TextPacket textPacket;
				textPacket.message.setText(bypass ? (message + " | " + Utils::randomString(8)) : bypassv2 ? (Utils::randomString(8) + " | " + message) : hash ? (message + " #BadManOnTop") : discord ? (message + " | discord.gg/B6rHK2yXdU") : message);
				textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
				textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
				Odelay = 0;
				gamer = 1;
			}
		}
		if (gamer == 1) {
			if (Odelay > delay * 20) {
				C_TextPacket textPacket;
				textPacket.message.setText(bypass ? (message2 + " | " + Utils::randomString(8)) : bypassv2 ? (Utils::randomString(8) + " | " + message2) : hash ? (message2 + " #BadManOnTop") : discord ? (message2 + " | discord.gg/B6rHK2yXdU") : message2);
				textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
				textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
				Odelay = 0;
				gamer = 2;
			}
		}
		if (gamer == 2) {
			if (Odelay > delay * 20) {
				C_TextPacket textPacket;
				textPacket.message.setText(bypass ? (message3 + " | " + Utils::randomString(8)) : bypassv2 ? (Utils::randomString(8) + " | " + message3) : hash ? (message3 + " #BadManOnTop") : discord ? (message3 + " | discord.gg/B6rHK2yXdU") : message3);
				textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
				textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
				Odelay = 0;
				gamer = 3;
			}
		}
		if (gamer == 3) {
			if (Odelay > delay * 20) {
				C_TextPacket textPacket;
				textPacket.message.setText(bypass ? (message4 + " | " + Utils::randomString(8)) : bypassv2 ? (Utils::randomString(8) + " | " + message4) : hash ? (message4 + " #BadManOnTop") : discord ? (message4 + " | discord.gg/B6rHK2yXdU") : message4);
				textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
				textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
				Odelay = 0;
				gamer = 0;
			}
		}
	} else {
		Odelay++;
			if (Odelay > delay * 20) {
				C_TextPacket textPacket;
				textPacket.message.setText(bypass ? (customMessage + " | " + Utils::randomString(8)) : bypassv2 ? (Utils::randomString(8) + " | " + customMessage) : hash ? (customMessage + " #BadManOnTop") : discord ? (customMessage + " | discord.gg/B6rHK2yXdU") : customMessage);
				textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
				textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
				Odelay = 0;
			}

	}
}

void Spammer::onEnable() {
gamer = 0;
}
