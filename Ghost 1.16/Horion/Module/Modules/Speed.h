#pragma once
#include "Module.h"

class Speed : public IModule {
private:
	float origSpeed = 0;
	float speed = 1.0f;
	bool SpeedV2 = false;

public:
	Speed();
	~Speed();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onMove(C_MoveInputHandler* input) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
};
