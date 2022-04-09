#include "Notifications.h"

Notifications::Notifications() : IModule(0, Category::VISUAL, "Notifications") {
	registerBoolSetting("ShowToggle", &showToggle, showToggle);
	registerFloatSetting("Opacity", &opacity, opacity, 0.f, 1.f);
}

Notifications::~Notifications() {
}

const char* Notifications::getModuleName() {
	return ("Notifications");
}