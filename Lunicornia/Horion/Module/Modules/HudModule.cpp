#include "HudModule.h"

HudModule::HudModule() : IModule(0x0, Category::VISUAL, "")
{
	registerBoolSetting("ArrayList", &this->arraylist, this->arraylist);
	registerBoolSetting("Coordinates", &this->coordinates, this->coordinates);
	registerBoolSetting("Show Keybinds", &this->keybinds, this->keybinds);

	this->enabled = true;
}

HudModule::~HudModule()
{
}

const char* HudModule::getModuleName()
{
	return ("HUD");
}