#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class Spammer : public IModule {
public:
	int Odelay = 0;
	bool bypass = true;
	int delay = 2;
	int length = 8;
	std::string message = "NG Client On top ";
	inline std::string& getMessage() { return message; };
	inline int& getDelay() { return delay; };
	inline int& getLength() { return length; };
	inline bool& getBypass() { return bypass; };

	Spammer() : IModule(0x0, Category::WORLD, "Spams a message in a specified delay") {
		registerIntSetting("delay", &delay, delay, 0, 10);
		registerIntSetting("length", &length, length, 1, 60);
		registerBoolSetting("bypass", &bypass, bypass);
	};
	~Spammer(){};

	void onTick(C_GameMode* gm) {
		Odelay++;
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message + " | " + Utils::randomString(length)) : message);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			Odelay = 0;
		}
	}

	virtual const char* getModuleName() override {
		return "Spammer";
	}
};