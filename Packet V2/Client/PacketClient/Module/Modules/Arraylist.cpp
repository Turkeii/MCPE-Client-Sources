#include "ArrayList.h"

#include "../../DrawUtils.h"

ArrayList::ArrayList() : IModule(0, Category::VISUAL, "Displays ArrayList") {
	registerEnumSetting("Mode", &mode, 0);
	mode.addEntry("Outline", 0);
	mode.addEntry("Split", 1);
	mode.addEntry("Bar", 2);
	//mode.addEntry("Old", 3);
	mode.addEntry("None", 4);
	registerBoolSetting("Modes", &modes, modes);
	registerFloatSetting("Opacity", &bgOp, bgOp, 0.f, 1.f);
}

ArrayList::~ArrayList() {
}

const char* ArrayList::getModuleName() {
	return ("ArrayList");
}