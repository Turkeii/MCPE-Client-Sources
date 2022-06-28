#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class Disabler : public IModule {
public:
	SettingEnum Server;
	Disabler() : IModule(0x0, Category::MISC, "Disable Anticheat Lul") {
		Server = SettingEnum(this)
					   .addEntry(EnumEntry("Aurora", 0))
					   .addEntry(EnumEntry("CubeCraft", 1));
		registerEnumSetting("Server", &Server, 0);

	};
	~Disabler(){};

	virtual const char* getModuleName() override {
		return "Disabler";
	}
	const char* Disabler::getModName() {
		if (Server.selected == 0)
			return " [Aurora]";
		if (Server.selected == 1)
			return " [CubeCraft]";
	}
	virtual void onPlayerTick(C_Player* plr);
	virtual void onSendPacket(C_Packet* packet);
};