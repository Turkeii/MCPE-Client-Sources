#pragma once
#include "Module.h"
class CubeCraftFly : public IModule {
private:
	float glideMod = 0.0f;
	float glideModEffective = 0;

public:
	CubeCraftFly();
	~CubeCraftFly();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual const char* getRawModuleName() override;
	virtual void onDisable() override;
};
