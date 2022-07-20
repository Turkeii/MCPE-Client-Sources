#include "TestModule.h"

TestModule::TestModule() : IModule(0, Category::MISC, "For Chat purposes Xalyfi") {
	registerBoolSetting("GreenText", &this->greentext, true);
}

TestModule::~TestModule() {
}

const char* TestModule::getModuleName() {
	return "Chat+";
}