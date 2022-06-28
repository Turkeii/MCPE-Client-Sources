#include "../../../Utils/Target.h"
#include "ScufedEsp.h"

ScufedEsp::ScufedEsp() : IModule(0, Category::VISUAL, "See player models through walls!") {
	type.addEntry(EnumEntry("Model", 0));
	type.addEntry(EnumEntry("Wire", 1));
	type.addEntry(EnumEntry("Color", 2));
	registerEnumSetting("Type", &type, 0);
}

ScufedEsp::~ScufedEsp() {
}

const char* ScufedEsp::getModuleName() {
	return ("ScufedEsp");
}