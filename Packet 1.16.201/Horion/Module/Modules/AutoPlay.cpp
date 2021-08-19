#include "AutoPlay.h"

AutoPlay::AutoPlay() : IModule(0, Category::MISC, "Description") {
	this->registerBoolSetting("Hive", &this->hiveMode, this->hiveMode);
}

const char* AutoPlay::getModuleName() {
	return "AutoPlay";
}