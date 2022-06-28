#include "ArrayList.h"

float ArrayList::opacity{0};
int ArrayList::rFloat{255};
int ArrayList::gFloat{255};
int ArrayList::bFloat{255};

ArrayList::ArrayList() : IModule(0x0, Category::HUD, "draws the array list on the right of your screen") {
	registerEnumSetting("Rainbow", &rainBow, 2);
	rainBow = SettingEnum(this)
				  .addEntry(EnumEntry("Custom Color", 0))
				  .addEntry(EnumEntry("Astolfo", 1))
				  .addEntry(EnumEntry("Rainbow", 2));
	registerEnumSetting("Rainbow Type", &rainBowDirection, 0);
	rainBowDirection = SettingEnum(this)
				  .addEntry(EnumEntry("Up", 0))
				  .addEntry(EnumEntry("Down", 1))
				  .addEntry(EnumEntry("Left", 2))
				  .addEntry(EnumEntry("Right", 3));
	registerBoolSetting("Outline", &outline, outline);
//	registerBoolSetting("WIP", &underline, underline);
	//registerBoolSetting("Surgev2", &surge, surge);
	registerBoolSetting("Top", &top, top);
	registerBoolSetting("Mode", &mode, mode);
	//registerBoolSetting("Keybinds", &keybinds, keybinds);
	//registerBoolSetting("Rainbow Sync", &sync, sync);
	registerFloatSetting("ArrayList Opacity", &opacity, opacity, 0.f, 1.f);
	registerFloatSetting("PrimaryRed", &r1, r1, 0.f, 255.f);
	registerFloatSetting("PrimaryGreen", &g1, g1, 0.f, 255.f);
	registerFloatSetting("PrimaryBlue", &b1, b1, 0.f, 255.f);
	registerFloatSetting("SecondaryRed", &r2, r2, 0.f, 255.f);
	registerFloatSetting("SecondaryGreen", &g2, g2, 0.f, 255.f);
	registerFloatSetting("SecondaryBlue", &b2, b2, 0.f, 255.f);
	registerFloatSetting("Wave Speed", &sped, sped, 0.f, 100.f);
	registerFloatSetting("Scale", &scale, scale, 0.5f, 1.5f);
}

ArrayList::~ArrayList() {
}

const char* ArrayList::getModuleName() {
	return ("Arraylist");
}