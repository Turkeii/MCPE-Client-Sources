#include "KillInsults.h"

KillInsults::KillInsults() : IModule(0, Category::MISC, "Funny Message") {
	registerEnumSetting("Mode", &mode, 0);
	mode.addEntry(EnumEntry("Normal", 0));
}

const char* KillInsults::getModuleName() {
	return "KillInsults";
}

void KillInsults::onEnable() {
	killed = false;
}

void KillInsults::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	srand(time(NULL));
	int random = rand() % 20;
	std::string messages[27] = {
			"Kek on top!!!!",
			"What's yellow and can't swim? A bus full of children",
			"Horion moment",
			"Touch grass",
			"jajajaja",
			"F",
			"L",
			"You just got naynayed by Kek.Club+",
			"EZZZZZZ",
			"stay mad",
			"cope harder",
			"trash",
			"trashed",
			"so bad",
			"who? who?",
			"nn alert",
			"ew get that nn client outta here",
			"how can you be so bad",
			"Kek.Club+",
			"Must be using packet",
			"you where never going to win :(",
			"stay trash",
			"i am the best jajaja",
			"zephyr moment", // despi is a good dev thou
			"360 noscoped ez",
			"unistall the game",
			"^ kekless LMFAO"};

	if (killed) {
		C_TextPacket textPacket;
		textPacket.message.setText(messages[random]);
		textPacket.sourceName.setText(player->getNameTag()->getText());
		textPacket.xboxUserId = std::to_string(player->getUserId());
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
		killed = false;
	}
}