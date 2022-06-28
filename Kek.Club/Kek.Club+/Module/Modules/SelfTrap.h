#pragma once
#include "Module.h"
class SelfTrap : public IModule {
public:
	SelfTrap();
	~SelfTrap();
	vec3_t pos;

	bool rotate = true;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable() override;
	virtual void onEnable() override;
};
