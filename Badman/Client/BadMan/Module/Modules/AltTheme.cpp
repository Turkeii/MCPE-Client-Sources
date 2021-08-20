#include "AltTheme.h"
#include "../../../Utils/Utils.h"

float AltTheme::rFloat{1.f};
float AltTheme::gFloat{1.f};
float AltTheme::bFloat{1.f};

AltTheme::AltTheme() : IModule(0, Category::GUI, "Change the color of alt UI Elements.") {

	registerFloatSetting("Red", &rFloat, rFloat, 0.f, 1.f);
	registerFloatSetting("Green", &gFloat, gFloat, 0.f, 1.f);
	registerFloatSetting("Blue", &bFloat, bFloat, 0.f, 1.f);
}

AltTheme::~AltTheme() {
}

const char* AltTheme::getModuleName() {
	return ("AltTheme");
}