#pragma once
#include "Module.h"
class Freecam : public IModule {
private:
	vec3_t oldPos;
	int counter = 1;
	float speed2 = 0.000f;
	float speed = 1.f;
	bool enabled = true;

public:
	Freecam();
	~Freecam();

	// Inherited via IModule
	virtual void onMove(C_MoveInputHandler* input) override;
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
	virtual bool isFlashMode() override;
	virtual void onDisable() override;
};