#include "Notifications.h"
#include "../pch.h"

Notifications::Notifications() : IModule(0, Category::VISUAL, "Displays notifications") {
	registerBoolSetting("ShowToggle", &showToggle, showToggle);
	registerIntSetting("Opacity", &opacity, opacity, 0, 255);
	shouldHide = true;
}

const char* Notifications::getModuleName() {
	return ("Notifications");
}