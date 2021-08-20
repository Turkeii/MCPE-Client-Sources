#pragma once
#include "Module.h"

class NoClip : public IModule {
public:
	NoClip();
	~NoClip();

	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable() override;
};
