#include "AutoGG.h"


void AutoGG::DoGG() {
	if ((time(NULL) - lastGG) < 10) {
		ClickGui::sendNotificationf("There is a 10 seconds cooldown between each gg");
		return;
	}


	TextPacket newpacket("gg", game::localPlayer->username, game::minecraftGame->xuid);
	if (capitalLetters)
		newpacket.message.setText("GG");

	game::sendPacket(&newpacket);
	lastGG = time(NULL);
}


void AutoGG::onTick(Gamemode* gm) {
	if (shouldGG) {
		DoGG();
		shouldGG = false;

		/*ClickGui::sendNotificationf("GGed!");
		game::sendClientChat("Sent gg!");
		game::sendClientChat("Sent gg!");
		game::sendClientChat("Sent gg!");
		game::sendClientChat("Sent gg!");
		game::sendClientChat("Sent gg!");
		game::sendClientChat("Sent gg!");*/
	}
}



extern bool cmpAfterFirstSpace(const char* text, const char* compareTo);
extern bool cmpAfterFirstOrSecondSpace(const char* text, const char* compareTo);

extern bool endWith(const char* text, size_t textLenght, const char* compareTo, size_t compareToLenght);
extern bool startWith(const char* text, size_t textLenght, const char* compareTo, size_t compareToLenght);
bool cmpExternMemEndWith(const char* text, size_t textLenght, const unsigned char* compareTo, size_t compareLenght) {
	if (compareLenght > textLenght)
		return false;
	const unsigned char* ucpt = (const unsigned char*)text;

	for (size_t i = 1; i < compareLenght; i++) 
		if (ucpt[textLenght - i] != compareTo[compareLenght - i]) 
			return false;
		
	return true;
}
bool cmpExternMemStartWith(const char* text, size_t textLenght, const unsigned char* compareTo, size_t compareLenght) {
	if (compareLenght > textLenght)
		return false;
	const unsigned char* ucpt = (const unsigned char*)text;

	for (size_t i = 0; i < compareLenght; i++) 
		if (ucpt[i] != compareTo[i]) 
			return false;
		
	return true;
}


unsigned char cubecraftAutogg[27] = { 194, 167, 114, 194, 167, 97, 32, 119, 111, 110, 32, 116, 104, 101, 32, 103, 97, 109, 101, 33, 194, 167, 114, 194, 167, 114, 00};
unsigned char nethergameAutogg[46] =  { 194, 167, 108, 194, 167, 97, 81, 117, 101, 117, 101, 100, 33, 32, 85, 115, 101, 32, 116, 104, 101, 32, 98, 101, 100, 32, 116, 111, 32, 114, 101, 116, 117, 114, 110, 32, 116, 111, 32, 108, 111, 98, 98, 121, 33, 00 };
unsigned char hyperlandAutogg[51] =  { 194, 167, 97, 194, 167, 108, 81, 117, 101, 117, 101, 100, 44, 32, 116, 101, 108, 101, 112, 111, 114, 116, 105, 110, 103, 32, 121, 111, 117, 32, 116, 111, 32, 97, 32, 110, 101, 119, 32, 103, 97, 109, 101, 32, 105, 110, 32, 51, 115, 33, 00 };

bool AutoGG::onChat(const char* text) {
	size_t textLenght = strlen(text);
	if (textLenght > 200)
		return false;


	if (antiGG) 
		if (endWith(text, textLenght, "gg", 2))
			return true;
		else if (endWith(text, textLenght, "GG", 2))
			return true;

	if (antiToxic) 
		if (endWith(text, textLenght, "ez", 2))
			return true;
		else if (endWith(text, textLenght, "EZ", 2))
			return true;
		else if (text[textLenght - 1] == 'L')
			return true;


	





	//The Hive    - says game over all the time ?
	if (textLenght == 28 && endWith(text, textLenght, "Game OVER!", 10))
		shouldGG = true;
	//CubeCraft
	else if (cmpExternMemEndWith(text, textLenght, cubecraftAutogg, 26))
		shouldGG = true;
	//Nethergame
	else if (cmpExternMemStartWith(text, textLenght, nethergameAutogg, 45))
		shouldGG = true;
	//Hyperland
	else if (cmpExternMemStartWith(text, textLenght, hyperlandAutogg, 50))
		shouldGG = true;
		
	/*	char byte[600] = { 0 };

	for (size_t i = 0; i < textLenght; i++) {
		int gamer = 0;
		gamer = (unsigned char)text[i];
		unsigned char moreGaming = gamer;
		gamer = 0;
		gamer = moreGaming;
		sprintf(byte + (i * 4), "%d, ", gamer);
	}

	*/
	/*if (!shouldGG) {
		Logf("%d  %s", textLenght, text);
		Logger::log(byte);
		return;

		for (size_t i = 0; i < 51; i++) {
			int gamer = 0;
			gamer = (unsigned char)hyperlandAutogg[i];
			unsigned char moreGaming = gamer;
			gamer = 0;
			gamer = moreGaming;
			sprintf(byte + (i * 4), "%d, ", gamer);
		}
		Logger::log(byte);
	}*/
	return false;
}

