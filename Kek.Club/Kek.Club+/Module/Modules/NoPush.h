#pragma once
#include "Module.h"
class NoPush : public IModule {
public:
	NoPush();
	~NoPush();
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onEnable() override;
	virtual void onDisable() override;
};
