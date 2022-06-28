#pragma once
#include "Module.h"
class ArrayList : public IModule {
public:
	SettingEnum rainBow;
	SettingEnum rainBowDirection;

	ArrayList();
	~ArrayList();

	bool rainbowArrayList = false;
	bool bottom = true;
	bool keybinds = false;
	bool outline = false;
	bool sync = false;
	bool surge = false;
	bool underline = false;
	bool top = false;
	bool mode = true;
	float scale = 1.f;
	static float opacity;
	static int rFloat;
	static int bFloat;
	static int gFloat;

	float r1 = 255.f;
	float g1 = 255.f;
	float b1 = 255.f;

	float r2 = 32.f;
	float g2 = 32.f;
	float b2 = 32.f;

	float sped = 75.f;

	// Inherited via IModule
	virtual const char* getModuleName() override;
};
