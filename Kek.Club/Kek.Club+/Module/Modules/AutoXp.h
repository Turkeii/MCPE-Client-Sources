#pragma once
#include "Module.h"
class AutoXP : public IModule {
private:
	bool hasClicked = false;

public:
	bool rots = false;
	bool instant = false;
	AutoXP();
	~AutoXP();
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onPlayerTick(C_Player* plr) override;
};