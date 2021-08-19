#include "TimeChanger.h"

TimeChanger::TimeChanger() : IModule(0, Category::VISUAL, "Changes the client-sided time.") {
	registerFloatSetting("Value", &this->modifier, this->modifier, 0.1f, 1.f);
}

TimeChanger::~TimeChanger() {
}

const char* TimeChanger::getModuleName() {
	return "TimeChanger";
}
