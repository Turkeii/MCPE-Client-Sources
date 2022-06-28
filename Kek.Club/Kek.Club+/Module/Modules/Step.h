#pragma once
#include "Module.h"
class Step : public IModule {
private:
	float height = 2.f;

public:
	Step();
	~Step();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onMove(C_MoveInputHandler* input) override;
	virtual void onDisable() override;
};
