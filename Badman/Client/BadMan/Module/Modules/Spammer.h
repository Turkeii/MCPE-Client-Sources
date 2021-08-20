#pragma once
#include "Module.h"

class Spammer : public IModule {
private:
	int Odelay = 0;
	int delay = 2;
	int gamer = 0;

	bool custom = false;

	//Addon modes
	bool bypass = false;
	bool bypassv2 = false;
	bool hash = false;
	bool discord = false;

	std::string message = "You cant beat BadMan";
	std::string message2 = "Kids crying because of BadMan";
	std::string message3 = "You cannot hide from BadMan";
	std::string message4 = "Other clients arent safe from BadMan";
	std::string playerName = "";

	std::string customMessage = "BadMan is the best anarchy utility mod on minecraft bedrock!";
	std::string customMessage2 = "Kids crying because of BadMan";
	std::string customMessagee3 = "You cannot hide from BadMan";
	std::string customMessage4 = "Horion users arent safe from BadMan";
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
