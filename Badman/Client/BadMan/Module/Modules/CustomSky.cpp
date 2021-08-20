#include "CustomSky.h"

float CustomSky::red{0};
float CustomSky::green{0};
float CustomSky::blue{0};
bool CustomSky::custom{false};


CustomSky::CustomSky() : IModule(0, Category::VISUAL, "Chages the colour of the sky") {
	registerFloatSetting("Red", &red, red, 0, 1);
	registerFloatSetting("Green", &green, green, 0, 1);
	registerFloatSetting("Blue", &blue, blue, 0, 1);
	registerBoolSetting("Rainbow", &custom, custom);
	registerFloatSetting("intensity", &this->intensity, this->intensity, 0.01f, 0.1f);
}

CustomSky::~CustomSky() {
}

const char* CustomSky::getModuleName() {
	return ("CustomSky");
}
