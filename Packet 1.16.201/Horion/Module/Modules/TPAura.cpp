#include "TPAura.h"

TPAura::TPAura() : IModule(0, Category::COMBAT, "Description") {
	this->registerIntSetting("TP Delay", &this->delay, this->delay, 0, 5);
}

const char* TPAura::getModuleName() {
	return "TPAura";
}