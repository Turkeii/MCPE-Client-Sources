#include "CustomSky.h"
#include "../pch.h"

CustomSky::CustomSky() : IModule(0, Category::VISUAL, "Customize the skys color") {
	registerBoolSetting("Rainbow", &rainbow, rainbow);
	registerFloatSetting("Red", &red, red, 0.f, 1.f);
	registerFloatSetting("Green", &green, green, 0.f, 1.f);
	registerFloatSetting("Blue", &blue, blue, 0.f, 1.f);
}

const char* CustomSky::getModuleName() {
	return "CustomSky";
}