#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class EditionFaker : public IModule {
private:
	int edition = 0;
	SettingEnum Edition;

public:
	EditionFaker() : IModule(0x0, Category::SERVER, "Unknown" /*, Android, iOS, macOS, FireOS, GearVR, HoloLens, Windows 10(PC), Windows, Dedicated, Orbis, NX */) {
		//registerIntSetting("Edition", &edition, edition, 1, 13);
		registerEnumSetting("Edition", &Edition, 13);
		Edition = SettingEnum(this)
					  .addEntry(EnumEntry("Android", 1))
					  .addEntry(EnumEntry("IOS", 2))
					  .addEntry(EnumEntry("Kindle Fire", 4))
					  .addEntry(EnumEntry("Wondows", 7))
					  .addEntry(EnumEntry("PS4", 11))
					  .addEntry(EnumEntry("Switch", 12))
					  .addEntry(EnumEntry("XBOX", 13))
		;
		/* 
		1 Android
		2 IOS
		4 Kindle Fire
		7 Wondows
		10 PC
		11 PS4
		12 Switch
		13 XBOX*/
		
	};
	~EditionFaker(){};

	int EditionFaker::getFakedEditon() {
		return edition;
	}

	virtual const char* getModuleName() override {
		return "EditionFaker";
	}
};