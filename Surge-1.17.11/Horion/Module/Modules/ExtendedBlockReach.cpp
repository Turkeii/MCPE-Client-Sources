#include "ExtendedBlockReach.h"

ExtendedBlockReach::ExtendedBlockReach() : IModule(0, Category::PLAYER, "Exteneded reach for placing/breaking blocks") {
	this->registerFloatSetting(std::string("Reach"), &this->blockReach, this->blockReach, 7, 200);
}

ExtendedBlockReach::~ExtendedBlockReach() {
}

const char* ExtendedBlockReach::getModuleName() {
	return ("ExtendedBlockReach");
}
