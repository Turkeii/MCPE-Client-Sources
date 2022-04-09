#pragma once
#include "Module.h"
class FreeTP : public IModule {
private:
	bool speedWasEnabled = false;
	float speed = 1.f;

public:
	FreeTP();
	~FreeTP();

	// Inherited via IModule
	virtual void onEnable() override;
	virtual void onMove(C_MoveInputHandler* input) override;
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable() override;
};