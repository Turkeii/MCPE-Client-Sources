#pragma once
#include "Module.h"
class Xray : public IModule {
public:
	Xray();
	~Xray();
	bool debris = false;
	bool diamonds = false;
	bool emeralds = false;
	bool iron = false;
	bool gold = false;
	bool coal = false;
	bool redstone = false;
	bool lapis = false;
	bool other = false;
	// Inherited via IModule
	virtual const char* getModuleName() override;
};
