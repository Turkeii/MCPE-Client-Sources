#include "ColorCustomizer.h"

int ColorCustomizer::rFloat{
};
int ColorCustomizer::gFloat{};
int ColorCustomizer::bFloat{};
float ColorCustomizer::opacity{1};

ColorCustomizer::ColorCustomizer() : IModule(0, Category::HUD, "Change the color of the UI.") {
	registerIntSetting("Red", &rFloat, rFloat, 0, 255);
	registerIntSetting("Green", &gFloat, gFloat, 0, 255);
	registerIntSetting("Blue", &bFloat, bFloat, 0, 255);
	registerBoolSetting("Chroma", &this->chroma, false);
	registerFloatSetting("Opacity", &opacity, opacity, 0.35, 1);
}

ColorCustomizer::~ColorCustomizer() {

}




const char* ColorCustomizer::getModuleName() {
	return ("ColorCustomizer");
}
