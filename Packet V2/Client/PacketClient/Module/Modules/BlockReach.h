#pragma once
#include "Module.h"
class BlockReach : public IModule {
public:
	BlockReach();
	~BlockReach();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};