#include "GUI.h"

#include "../ModuleManager.h"

float GUI::rcolor{0.f};
float GUI::gcolor{0.f};
float GUI::bcolor{0.f};

GUI::GUI() : IModule(0x0, Category::GUI, "ArrayList") {
	registerBoolSetting("Modes", &modes, modes);
	registerBoolSetting("Arraylist RGB", &rgb, rgb);
	registerBoolSetting("Flux Bar", &Fluxbar, Fluxbar);
	registerBoolSetting("under Bar", &underbar, underbar);
	registerBoolSetting("Side Bar", &bar, bar);
	registerBoolSetting("Icy", &ice, ice);
	registerBoolSetting("Bottom Right", &bottom, bottom);
	registerBoolSetting("ClickToggle", &clickToggle, clickToggle);
	registerBoolSetting("Keybinds", &keybinds, keybinds);

	registerEnumSetting("Mode", &mode, 0);
	mode.addEntry(EnumEntry("Badman RGB", 0));
	mode.addEntry(EnumEntry("Surge", 1));
	mode.addEntry(EnumEntry("Horion", 2));
	mode.addEntry(EnumEntry("Surge V2", 3));
	mode.addEntry(EnumEntry("Fadeaway", 4));
	mode.addEntry(EnumEntry("NG", 5));
	mode.addEntry(EnumEntry("Weather", 6));
	mode.addEntry(EnumEntry("Cool RGB", 7));
	mode.addEntry(EnumEntry("Badman", 8));
	//mode.addEntry(EnumEntry("Packet", 9));

	registerFloatSetting("Red", &rcolor, rcolor, 0.f, 1.f);
	registerFloatSetting("Blue", &gcolor, gcolor, 0.f, 1.f);
	registerFloatSetting("Green", &bcolor, bcolor, 0.f, 1.f);
	registerFloatSetting("ArrayList Opacity", &opacity, opacity, 0.0f, 1.f);
}

GUI::~GUI() {
}

const char* GUI::getModuleName() {
	// Badman RGB
	if (mode.getSelectedValue() == 0) std::string("Arraylist ") + std::string("[Badman RGB]");

	// Surge
	if (mode.getSelectedValue() == 1) std::string("Arraylist ") + std::string("[Surge]");

	// Horion
	if (mode.getSelectedValue() == 3) std::string("Arraylist ") + std::string("[Horion]");

	// Surge V2
	if (mode.getSelectedValue() == 3) std::string("Arraylist ") + std::string("[Surge V2]");
	
	// Fadeaway
	if (mode.getSelectedValue() == 3) std::string("Arraylist ") + std::string("[Fadeaway]");
	
	// NG
	if (mode.getSelectedValue() == 3) std::string("Arraylist ") + std::string("[NG]");
	
	// Weather
    if (mode.getSelectedValue() == 3) std::string("Arraylist ") + std::string("[Weather]");

	// Cool RGB
	if (mode.getSelectedValue() == 3) std::string("Arraylist ") + std::string("[Cool RGB]");
	
	// Badman
	if (mode.getSelectedValue() == 3) std::string("Arraylist ") + std::string("Badman");
	return name.c_str();
}