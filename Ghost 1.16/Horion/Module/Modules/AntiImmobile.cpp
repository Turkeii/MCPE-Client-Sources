#include "AntiImmobile.h"

AntiImmobile::AntiImmobile() : IModule(0, Category::MISC, "Disables immobile flag set by some servers to prevent you from moving") {
	registerBoolSetting("600 Pound", &fat, fat);
}
AntiImmobile::~AntiImmobile() {
}

const char* AntiImmobile::getModuleName() {
	return "AntiImmobile";
}