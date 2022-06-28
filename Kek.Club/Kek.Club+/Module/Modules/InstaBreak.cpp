#include "InstaBreak.h"

InstaBreak::InstaBreak() : IModule(VK_NUMPAD4, Category::WORLD, "break shit fast idfk") {
}

InstaBreak::~InstaBreak() {
}

const char* InstaBreak::getModuleName() {
	return ("SpeedMine");
}
