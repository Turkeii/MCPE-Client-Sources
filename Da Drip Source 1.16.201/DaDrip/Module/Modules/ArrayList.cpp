#include "ArrayList.h"
#include "../../DrawUtils.h"
#include "../../Scripting/ScriptManager.h"
#include "../../../Utils/Logger.h"

int ArrayList::rFloat{255};
int ArrayList::gFloat{255};
int ArrayList::bFloat{255};

ArrayList::ArrayList() : IModule(0x0, Category::HUD, "Shows a list of modules on your screen that are currently enabled") {
	registerBoolSetting("Rainbow", &this->rainbow, this->rainbow);
	registerBoolSetting("ClickToggle", &this->clickToggle, this->clickToggle);
	registerBoolSetting("Show Keybinds", &this->keybinds, this->keybinds);
	registerIntSetting("Red", &rFloat, rFloat, 0, 255);
	registerIntSetting("Green", &gFloat, gFloat, 0, 255);
	registerIntSetting("Blue", &bFloat, bFloat, 0, 255);
	registerFloatSetting("Scale", &this->scale, this->scale, 0.5f, 1.5f);
}

ArrayList::~ArrayList() {
}

const char* ArrayList::getModuleName() {
	return ("ArrayList");
}