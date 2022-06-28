#include "Notifications.h"

Notifications::Notifications() : IModule(0, Category::HUD, "Gives Notifications For Disabling/Enabling Modules") {
	//registerEnumSetting("Types", &notification, 1);
	notification = SettingEnum(this)
					   .addEntry(EnumEntry("Java", 1))
					   .addEntry(EnumEntry("Time", 2))
					   .addEntry(EnumEntry("Box", 3));
}

Notifications::~Notifications() {
}

const char* Notifications::getModuleName() {
	return ("Notifications");
}
void Notifications::onTick(C_GameMode* gm) {
	switch (notification.selected) {
	default:
		java = true;
		time = false;
		box = false;
		break;
	case 1:
		java = false;
		time = true;
		box = false;
		break;
	case 2:
		java = false;
		time = false;
		box = true;
		break;
	}
}