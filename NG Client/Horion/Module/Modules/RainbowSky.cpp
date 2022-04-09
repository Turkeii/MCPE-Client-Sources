#include "RainbowSky.h"

float RainbowSky::red{0};
float RainbowSky::green{0};
float RainbowSky::blue{0};
bool RainbowSky::custom{false};

RainbowSky::RainbowSky() : IModule(0x0, Category::VISUAL, "Chages the colour of the sky") {
	registerFloatSetting("Red", &red, red, 0, 1);
	registerFloatSetting("Green", &green, green, 0, 1);
	registerFloatSetting("Blue", &blue, blue, 0, 1);
	registerBoolSetting("Rainbow", &custom, custom);
	registerFloatSetting("intensity", &intensity, intensity, 0.01f, 0.1f);
}

RainbowSky::~RainbowSky() {
}

const char* RainbowSky::getModuleName() {
	return ("CustomSky");
}