#include "ToggleSounds.h"
#include "../pch.h"

using namespace std;
ToggleSounds::ToggleSounds() : IModule(0, Category::OTHER, "Plays a sound when you toggle a module") {
	registerEnumSetting("Sound", &sound, 0);
	sound.addEntry("Click", 0);
	sound.addEntry("Piston", 1);
	sound.addEntry("Sigma", 2);
	registerFloatSetting("Volume", &volume, volume, 0.05f, 1.f);
}

const char* ToggleSounds::getRawModuleName() {
	return "ToggleSounds";
}

const char* ToggleSounds::getModuleName() {
	if (sound.getSelectedValue() == 0) name = string("ToggleSounds ") + string(GRAY) + string("Click");
	if (sound.getSelectedValue() == 1) name = string("ToggleSounds ") + string(GRAY) + string("Piston");
	if (sound.getSelectedValue() == 2) name = string("ToggleSounds ") + string(GRAY) + string("Sigma");
	return name.c_str();
}