#include "TimeChanger.h"

TimeChanger::TimeChanger() : IModule(0, Category::VISUAL, "Changes the client-sided time.") {
	registerFloatSetting("Value", &modifier, modifier, 0.1f, 1.f);
}

TimeChanger::~TimeChanger() {
}

const char* TimeChanger::getRawModuleName() {
	return "TimeChanger";
}

const char* TimeChanger::getModuleName() {
	if (modifier <= 0.24 || modifier >= 0.77) {
		name = std::string("TimeChanger ") + std::string(GRAY) + std::string("Day");
		return name.c_str();
	}
	if (modifier >= 0.24 || modifier <= 0.77) {
		name = std::string("TimeChanger ") + std::string(GRAY) + std::string("Night");
		return name.c_str();
	}
}