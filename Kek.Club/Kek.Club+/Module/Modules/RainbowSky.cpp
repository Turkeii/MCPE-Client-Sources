#include "RainbowSky.h"
int RainbowSky::rFloat{255};
int RainbowSky::gFloat{255};
int RainbowSky::bFloat{255};
RainbowSky::RainbowSky() : IModule(0, Category::VISUAL, "Changes the sky's colors!") {
	registerIntSetting("Red", &rFloat, rFloat, 0, 255);
	registerIntSetting("Green", &gFloat, gFloat, 0, 255);
	registerIntSetting("Blue", &bFloat, bFloat, 0, 255);
	registerBoolSetting("Rainbow", &rainbow, rainbow);
}

RainbowSky::~RainbowSky() {
}

const char* RainbowSky::getModuleName() {
	return ("CustomSky");
}
