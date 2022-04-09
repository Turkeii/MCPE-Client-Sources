#pragma once
#include "Module.h"

class AutoTotem : public IModule {
private:
	int savedSlot;

public:
	AutoTotem();
	~AutoTotem();

	virtual const char* getModuleName() override;
	virtual void onLevelRender() override;
	virtual void onEnable();
	virtual void onDisable();
	virtual void onTick(C_GameMode* gm) override;
};
