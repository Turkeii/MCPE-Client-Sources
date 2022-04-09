#include "AntiImmobile.h"

AntiImmobile::AntiImmobile() : IModule(0, Category::EXPLOIT, "Disables immobile flag set by hive servers to prevent you from moving") {
}
AntiImmobile::~AntiImmobile() {
}

const char* AntiImmobile::getModuleName() {
	return "AntiImmobile";
}