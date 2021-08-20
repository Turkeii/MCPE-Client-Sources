#pragma once
#include "Module.h"

class NoHitbox : public IModule
{
public:
	NoHitbox();
	~NoHitbox();

	virtual const char* getModuleName() override;

	virtual void onEnable() override;
	virtual void onDisable() override;

	float width, height;
};
