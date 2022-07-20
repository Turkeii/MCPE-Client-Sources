#pragma once
#include "Module.h"

class Speed : public IModule {
private:
	//default value
	float origSpeed = 0;
	float speed = 0.28f;
	bool SpeedV2 = true;

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
