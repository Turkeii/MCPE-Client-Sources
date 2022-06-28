#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class AirJump : public IModule {
private:
	uint8_t* opcode = 0;

public:
	AirJump();
	~AirJump();

	virtual const char* getModuleName() override;
	virtual void onEnable() override;
	virtual void onDisable() override;
};
