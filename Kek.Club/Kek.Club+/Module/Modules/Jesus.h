#pragma once
#include "Module.h"
class Jesus :
	public IModule
{
private:
	bool wasInWater = false;
	bool isSneaking = false;

public:
	bool jesus1 = false;
	Jesus();
	~Jesus();
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual const char* getModName() override;
	virtual void onLevelRender() override;
};

