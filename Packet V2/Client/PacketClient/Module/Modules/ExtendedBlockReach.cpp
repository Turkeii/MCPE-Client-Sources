#include "ExtendedBlockReach.h"

ExtendedBlockReach::ExtendedBlockReach() : IModule(0, Category::MISC, "Exteneded reach for placing/breaking blocks") {
	this->registerFloatSetting(std::string("reach"), &this->blockReach, this->blockReach, 50, 500);
}

ExtendedBlockReach::~ExtendedBlockReach() {
}

const char* ExtendedBlockReach::getModuleName() {
	return ("ExtendedBlockReach");
}
