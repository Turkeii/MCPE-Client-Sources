#include "Theme.h"
#include "../../../Utils/Utils.h"

float Theme::rFloat{1.f};
float Theme::gFloat{1.f};
float Theme::bFloat{1.f};
float Theme::rFloat2{0.5f};
float Theme::gFloat2{0.5f};
float Theme::bFloat2{0.5f};
float Theme::rFloat3{0.f};
float Theme::gFloat3{0.f};
float Theme::bFloat3{0.f};
float Theme::rFloat4{0.f};
float Theme::gFloat4{0.f};
float Theme::bFloat4{0.f};

Theme::Theme() : IModule(0, Category::GUI, "Change the color of UI Elements.") {
	registerFloatSetting("Red", &rFloat, rFloat, 0.f, 1.f);
	registerFloatSetting("Green", &gFloat, gFloat, 0.f, 1.f);
	registerFloatSetting("Blue", &bFloat, bFloat, 0.f, 1.f);
	registerFloatSetting("ModeRed", &rFloat2, rFloat2, 0.f, 1.f);
	registerFloatSetting("ModeGreen", &gFloat2, gFloat2, 0.f, 1.f);
	registerFloatSetting("ModeBlue", &bFloat2, bFloat2, 0.f, 1.f);
	registerFloatSetting("ShadowRed", &rFloat3, rFloat3, 0.f, 1.f);
	registerFloatSetting("ShadowGreen", &gFloat3, gFloat3, 0.f, 1.f);
	registerFloatSetting("ShadowBlue", &bFloat3, bFloat3, 0.f, 1.f);
	registerFloatSetting("ModeShadowRed", &rFloat4, rFloat4, 0.f, 1.f);
	registerFloatSetting("ModeShadowGreen", &gFloat4, gFloat4, 0.f, 1.f);
	registerFloatSetting("ModeShadowBlue", &bFloat4, bFloat4, 0.f, 1.f);
}

Theme::~Theme() {
}

const char* Theme::getModuleName() {
	return ("Theme");
}