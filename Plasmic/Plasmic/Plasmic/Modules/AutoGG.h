#pragma once
#include "../Module.h"
#include <ctime>




class AutoGG : public Module {
public:
	long long lastGG = 0;
	bool shouldGG = false;

	bool antiGG = false;
	bool antiToxic = false;

	bool capitalLetters = false;
	AutoGG() : Module("AutoGG", 0, mltext("Send gg in the chat at the end of a match\nworks on: Hive, Cubecraft, Nether Games and Hyperland", "Envoie gg dans le chat a la fin d'une partie\nFonctionne sur The Hive, Cubecraft, Nether Games, Hyperland")) {
		//addBoolSetting("shouldGG (DEBUG)", "shouldGG", shouldGG, &shouldGG);

		addBoolSetting(mltext("GG instead of gg", "gg en majuscule (GG)"), "capitalLetters", capitalLetters, &capitalLetters);
		addBoolSetting("Anti GG", "antiGG", antiGG, &antiGG);
		addBoolSetting("Anti ez/L", "antiToxic", antiToxic, &antiToxic);
	}


	void DoGG();
	virtual void onTick(Gamemode* gm) override;

	bool onChat(const char* message);

};

