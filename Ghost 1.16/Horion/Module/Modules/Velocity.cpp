#include "Velocity.h"

Velocity::Velocity() : IModule(0, Category::MOVEMENT, "No Knockback") {
}

Velocity::~Velocity() {
}

const char* Velocity::getModuleName() {
	return ("Velocity");
}

void Velocity::onTick(C_GameMode* gm) {
}