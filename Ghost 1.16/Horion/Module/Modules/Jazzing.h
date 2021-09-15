#pragma once
#include "Module.h"

class Jazzing : public IModule {
public:
	Jazzing();
	~Jazzing();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onEnable() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable() override;
};