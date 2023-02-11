#include "Velocity.h"
#include "../pch.h"

using namespace std;
Velocity::Velocity() : IModule(0, Category::MOVEMENT, "Modifies your velocity (knockback)") {
	registerFloatSetting("Linear", &x, x, 0.f, 5.f);
	registerFloatSetting("Height", &y, y, 0.f, 5.f);
}

const char* Velocity::getRawModuleName() {
	return "AntiVelocity";
}

const char* Velocity::getModuleName() {
	name = string("AntiVelocity") + string(GRAY) + string("");
	fullname = name + string("") + string("") + string("");
	return fullname.c_str();
}

void Velocity::onTick(C_GameMode* gm) {
}