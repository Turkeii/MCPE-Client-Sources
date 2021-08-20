#pragma once
#include "Module.h"
class CreativeFly : public IModule {
public:
	CreativeFly();
	~CreativeFly();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable() override;
};
