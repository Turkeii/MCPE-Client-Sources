#include "AltTheme.h"
#include "../../../Utils/Utils.h"

float AltTheme::rFloat{0.8};
float AltTheme::gFloat{0.74};
float AltTheme::bFloat{1.f};

AltTheme::AltTheme() : IModule(0, Category::GUI, "Change the color of alt UI Elements.") {

	registerFloatSetting("Red", &rFloat, 0.8f, 0.f, 1.f);
	registerFloatSetting("Green", &gFloat, 0.74f, 0.f, 1.f);
	registerFloatSetting("Blue", &bFloat, 1.f, 0.f, 1.f);
}

AltTheme::~AltTheme() {
}

const char* AltTheme::getModuleName() {
	return ("AltTheme");
}