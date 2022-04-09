#pragma once
#include "Module.h"
class EntityJesus : public IModule {
private:
	bool wasInWater = false;
	float upness = 0.01f;

public:
	EntityJesus();
	~EntityJesus();
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onLevelRender() override;
};