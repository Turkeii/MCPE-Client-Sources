#pragma once
#include "Module.h"
class LongJump : public IModule {
public:
	float jumpPower = 1.21f;
	float speed = 0.325f;
	bool Blinc = true;
	float freq = 5.f;
	int nigger = 1;
	LongJump();
	~LongJump();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onDisable() override;
	virtual void onMove(C_MoveInputHandler* input) override;
};
