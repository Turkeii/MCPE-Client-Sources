#include "NoPaintingCrash.h"

NoPaintingCrash::NoPaintingCrash() : IModule(0, Category::VISUAL, "Fix Painting crash when using mob spawner !") {
}

NoPaintingCrash::~NoPaintingCrash() {
}

const char* NoPaintingCrash::getModuleName() {
	return ("NoPaintingCrash");
}