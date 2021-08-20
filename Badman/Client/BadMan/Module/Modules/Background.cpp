#include "Background.h"
#include "../../../Utils/Utils.h"


float Background::opacity{1};
float Background::rFloat{0.f};
float Background::gFloat{0.f};
float Background::bFloat{0.f};

Background::Background() : IModule(0, Category::GUI, "Change the color of Background Elements.") {

	registerFloatSetting("Red", &rFloat, rFloat, 0.f, 1.f);
	registerFloatSetting("Green", &gFloat, gFloat, 0.f, 1.f);
	registerFloatSetting("Blue", &bFloat, bFloat, 0.f, 1.f);
	registerFloatSetting("ClickGUI Opacity", &opacity, opacity, 0.f, 1.f);
}

Background::~Background() {
}

const char* Background::getModuleName() {
	return ("Background");
}