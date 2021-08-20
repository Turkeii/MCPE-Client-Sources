#pragma once
#include "Module.h"

class HudModule :
	public IModule
{
public:
	HudModule();
	~HudModule();

	bool arraylist = true;
	bool coordinates = false;
	bool keybinds = true;

	// Inherited via IModule
	virtual const char* getModuleName() override;
};