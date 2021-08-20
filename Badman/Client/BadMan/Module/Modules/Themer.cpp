#include "Theme.h"
#include "../../../Utils/Utils.h"

float Theme::rFloat{1.f};
float Theme::gFloat{0.f};
float Theme::bFloat{0.f};

Theme::Theme() : IModule(0, Category::GUI, "Change the color of UI Elements.") {
	registerEnumSetting("Fonts", &TheRealFonts, 0);
	TheRealFonts = SettingEnum(this)
						 .addEntry(EnumEntry("Noto Sans", 0))
						 .addEntry(EnumEntry("Mojangles", 1));

	registerFloatSetting("Red", &rFloat, rFloat, 0.f, 1.f);
	registerFloatSetting("Green", &gFloat, gFloat, 0.f, 1.f);
	registerFloatSetting("Blue", &bFloat, bFloat, 0.f, 1.f);
	registerBoolSetting("Rainbow", &this->rainbow, this->rainbow);
	registerBoolSetting("Outline", &this->outline, this->outline);
}

Theme::~Theme() {
}

const char* Theme::getModuleName() {
	return ("Theme");
}