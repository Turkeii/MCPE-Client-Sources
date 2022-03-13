#include "TestModule.h"

TestModule::TestModule() : IModule(0, Category::MISC, "For testing purposes") {
	registerBoolSetting("GreenText", &this->bool1, true);
}

TestModule::~TestModule() {
}

const char* TestModule::getModuleName() {
	return "TestModule";
}