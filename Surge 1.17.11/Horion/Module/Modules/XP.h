#pragma once
#include "Module.h"
class XP : public IModule {
public:
	int amount = 1;
	XP();
	~XP();

private:
	virtual const char* getModuleName() override;
	void onTick(C_GameMode* gm);
};