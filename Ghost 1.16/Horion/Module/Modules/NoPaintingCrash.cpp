#include "NoPaintingCrash.h"

NoPaintingCrash::NoPaintingCrash() : IModule(0, Category::MISC, "Fix Painting crash when using mob spawner ! Not sure if it works!") {
}

NoPaintingCrash::~NoPaintingCrash() {
}

const char* NoPaintingCrash::getModuleName() {
	return ("NoPaintingCrash");
}