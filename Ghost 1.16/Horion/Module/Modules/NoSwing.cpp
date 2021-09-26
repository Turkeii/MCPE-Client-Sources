#include "NoSwing.h"

NoSwing::NoSwing() : IModule(0, Category::PLAYER, "BROKEN") {
}

NoSwing::~NoSwing() {
}

const char* NoSwing::getModuleName() {
	return ("NoSwing");
}