#pragma once
#include "Module.h"
class ArrayList : public IModule {
public:
	ArrayList();
	~ArrayList();

	bool rainbowArrayList = false;
	bool bottom = false;
	bool keybinds = true;
	bool outline = false;
	bool underline = true;
	float scale = 1.f;
	static float opacity;

	// Inherited via IModule
	virtual const char* getModuleName() override;
};
