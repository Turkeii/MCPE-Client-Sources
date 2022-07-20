#include "Theme.h"
#include "../../../Utils/Utils.h"

float Theme::rFloat{0.f};
float Theme::gFloat{1.f};
float Theme::bFloat{1.f};

Theme::Theme() : IModule(0x0, Category::GUI, "Change IRO/color") {
	registerEnumSetting("Fonts", &TheRealFonts, 0);
	TheRealFonts = SettingEnum(this)
						 .addEntry(EnumEntry("Noto Sans", 0))
						 .addEntry(EnumEntry("Mojangles", 1));

	registerFloatSetting("Red", &rFloat, 0.f, 0.f, 1.f);
	registerFloatSetting("Green", &gFloat, 1.f, 0.f, 1.f);
	registerFloatSetting("Blue", &bFloat, 1.f, 0.f, 1.f);
	registerBoolSetting("Outline", &this->outline, this->outline);
}

Theme::~Theme() {
}	

const char* Theme::getModuleName() {
	return ("Color");
}