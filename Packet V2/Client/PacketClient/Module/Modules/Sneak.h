#pragma once
#include "Module.h"
class Sneak : public IModule {
private:
public:
	bool doSilent = false;
	Sneak();
	~Sneak();

	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable() override;
	virtual void onEnable() override;
};