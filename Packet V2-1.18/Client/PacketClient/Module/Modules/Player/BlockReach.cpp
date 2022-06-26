#include "BlockReach.h"
#include "../pch.h"

BlockReach::BlockReach() : IModule(0, Category::PLAYER, "Allows you to place blocks further away") {
	registerIntSetting("Reach", &distance, distance, 7, 255);
}

const char* BlockReach::getModuleName() {
	return "BlockReach";
}