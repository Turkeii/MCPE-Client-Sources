#pragma once
#include "Module.h"

class ArrayList : public IModule {
public:
	ArrayList();
	~ArrayList();
	bool clickToggle = true;
	bool keybinds = true;
	bool rainbow = false;

	//bool editHud = false;
	float scale = 1.f;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	static int rFloat;
	static int bFloat;
	static int gFloat;
};