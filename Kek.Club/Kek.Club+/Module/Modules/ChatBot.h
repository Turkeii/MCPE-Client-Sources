#pragma once
#include "Module.h"

class ChatBot : public IModule {
private:
	int delay = 1;
	int length = 5;
	bool bypass = false;
	int messageTimer = 0;
	int messageIndex = 0;

public:
	const char* kekList[13] = {"Kek runs u", "Kek.club+ best cpvp", "Bypassing your server :yawn:", "Kek.club+ believes this server is 2 ez", "sit down nn", "Begone nn", "Kek.club+ always on top!", "Kek.Club+ :sunglasses:", "Kek.Club+ is the best anarchy utility mod out there lmfao", "Kek.Club+ has the coolest ChatBot, maybe that's what I'm using?!", "Kek.Club+ is Untouchable", "Why use any other client?","Kek.club+ crashes your server"};
	const char* toxicList[15] = {"You are complete dog", "You aren't worthy of life", "Jake Paul is better at cpvp than you", "stay losing nn", "Kek.Club+ winning all day", "i win again :yawn:", "hush mode shitter", "uninstall or swat", "hush mode shitter", "keep fighting nn", "hang yourself incel", "*monkey noises*", "smh cringe newfags get blocked", "bow down doggie", "i am so much better than you LOLZ"};
	const char* fadedList[11] = {"Fadeaway Best PvP", "Fadeaway best bypasses!", "Hive's Anti-Cheat is Non-Existent", "Use FadedTool to remove all your Alias'!", "FadedTool is the #1 tool to Spoof your DID, MCID, and CID :sunglasses:", "Fadeaway had the fastest HiveFly at one point...", "Sipping Fadeaway on a daily", "Fadeaway has a secret insta eat/gap method, very few people know about it", "Fadeaway has the most bypassing capability out of any client!"};

	SettingEnum messageMode;

	ChatBot();
	~ChatBot();

	const char* getModuleName() override;
	virtual void onEnable() override;
	virtual void onTick(C_GameMode* gm) override;
};
