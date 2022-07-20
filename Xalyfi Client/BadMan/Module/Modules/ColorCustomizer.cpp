#include "ColorCustomizer.h"
#include "Background.h"
//#include "Background.h"

float ColorCustomizer::rFloat {Background::rFloat};
float ColorCustomizer::gFloat{Background::gFloat};
float ColorCustomizer::bFloat{Background::bFloat};
float ColorCustomizer::opacity = 1.f;

ColorCustomizer::ColorCustomizer() : IModule(0, Category::GUI, "Change the color of the UI.") {
	registerFloatSetting("Red", &rFloat, rFloat, 0, 255);
	registerFloatSetting("Green", &gFloat, gFloat, 0, 255);
	registerFloatSetting("Blue", &bFloat, bFloat, 0, 255);
//registerBoolSetting("Chroma", &this->chroma, false);
	registerFloatSetting("Opacity", &opacity, opacity, 0.35, 1);
}

ColorCustomizer::~ColorCustomizer() {
}

const char* ColorCustomizer::getModuleName() {
	return ("ClickGuiColor");
}
