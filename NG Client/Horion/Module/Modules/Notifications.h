#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class Notifications : public IModule {
public:
	SettingEnum mode = this;
	bool showToggle = true;
	float opacity = 0.50;

	Notifications() : IModule(0x0, Category::GUI, "Shows Enabled/Disabled Modules"){
		registerEnumSetting("Mode", &mode, 0);
		mode.addEntry(EnumEntry("Chat", 0));
		mode.addEntry(EnumEntry("Notifications", 1));

		registerBoolSetting("ShowToggle", &showToggle, showToggle);
		registerFloatSetting("Opacity", &opacity, opacity, 0.f, 1.f);
	};
	~Notifications(){};

	virtual const char* getModuleName() override { 
	return "Notifications"; 
	}
};
