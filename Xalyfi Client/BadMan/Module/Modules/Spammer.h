#pragma once
#include "Module.h"

class Spammer : public IModule {
public:
	int Odelay = 0;
	int delay = 2;
	int gamer = 0;

	bool custom = false;

	//Addon modes
	bool bypass = false;
	bool bypassv2 = false;
	bool hash = false;
	bool discord = false;

	std::string message = "Xalyfi on TOP";
	std::string message2 = "Use Xalyfi";
	std::string message3 = "You are kids use Xalyfi";
	std::string message4 = "Xalyfi is better";
	std::string message5 = "";
	std::string message6 = "";
	std::string message7 = "";
	std::string message8 = "";
	std::string message9 = "";
	std::string message10 = "";
	std::string message11 = "";
	std::string message12 = "";
	std::string message13 = "";
	std::string message14 = "";
	std::string message15 = "";
	std::string playerName = "";

	std::string customMessage = "";
	std::string customMessage2 = "Kids crying because of Xalyfi";
	std::string customMessagee3 = "You cannot hide from Xalyfi";
	std::string customMessage4 = "Horion users arent safe from Xalyfi";
	//custom message 2,3 and 4 are here just incase anyone wants more :D

	SettingEnum spamMode;
	SettingEnum extensionMode;

public:
	Spammer();
	~Spammer();

	inline std::string& getCustomMessage() { return customMessage; };
	inline std::string& getCustomMessage2() { return customMessage; };
	inline std::string& getCustomMessage3() { return customMessage; };
	inline std::string& getCustomMessage4() { return customMessage; };
	inline int& getDelay() { return delay; };
	inline bool& getBypass() { return bypass; };

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable();
};
