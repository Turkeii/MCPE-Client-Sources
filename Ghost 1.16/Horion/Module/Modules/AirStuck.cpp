#include "AirStuck.h"

AirStuck::AirStuck() : IModule(0, Category::MOVEMENT, "Become stuck") {
}

AirStuck::~AirStuck() {
}

const char* AirStuck::getModuleName() {
	return ("AirStuck");
}

void AirStuck::onTick(C_GameMode* gm) {
}