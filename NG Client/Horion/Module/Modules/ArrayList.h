#pragma once
#include "../../DrawUtils.h"
#include "Module.h"
class ArrayList : public IModule {
public:
	bool enabled = true;
	bool different = false;
	bool bar = false;
	bool underbar = false;
	bool ice = false;
	bool rgb = true;
	bool bottom = false;
	bool rgbtext = true;
	float opacity = true;
	static float rcolor;
	static float bcolor;
	static float gcolor;
	float scale = 0.75f;

	ArrayList();
	~ArrayList();

	// Inherited via IModule
	virtual const char* getModuleName() override;
};


#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class ArrayList : public IModule {
public:
	bool enabled = true;
	bool different = false;
	bool bar = false;
	bool underbar = false;
	bool ice = false;
	bool rgb = true;
	bool bottom = false;
	bool rgbtext = true;
	float opacity = true;
	static float rcolor;
	static float bcolor;
	static float gcolor;
	float scale = 0.75f;

	float ArrayList::rcolor{0.f};
	float ArrayList::gcolor{0.f};
	float ArrayList::bcolor{0.f};

	ArrayList() : IModule(0x0, Category::GUI, "ArrayList") {
		registerBoolSetting("Icy Arraylist", &ice, ice);
		registerBoolSetting("RGB", &rgb, rgb);
		registerBoolSetting("Surge Client Colors", &different, different);
		registerBoolSetting("Side Bar", &bar, bar);
		registerBoolSetting("Bottom Bar", &underbar, underbar);
		registerBoolSetting("Bottom Right", &bottom, bottom);
		registerFloatSetting("Scale", &scale, scale, 0.5f, 1.5f);
		registerFloatSetting("ArrayList Opacity", &opacity, opacity, 0.0f, 1.f);
		registerFloatSetting("Red", &rcolor, rcolor, 0.f, 1.f);
		registerFloatSetting("Blue", &gcolor, gcolor, 0.f, 1.f);
		registerFloatSetting("Green", &bcolor, bcolor, 0.f, 1.f);
	};
	~ArrayList(){};

	virtual const char* getModuleName() override {
		return "ArrayList";
	}
};