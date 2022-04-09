#include "BlockReach.h"

BlockReach::BlockReach() : IModule(0, Category::PLAYER, "Gach.") {
}

BlockReach::~BlockReach() {
}

const char* BlockReach::getModuleName() {
	return "BlockReach";
}

void BlockReach::onTick(C_GameMode* gm) {
}