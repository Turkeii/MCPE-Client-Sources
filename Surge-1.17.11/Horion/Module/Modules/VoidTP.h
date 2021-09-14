#pragma once
#include "Module.h"
class Twerk : public IModule {
public:
	int amount = 1;
	Twerk();
	~Twerk();

private:

	virtual const char* getModuleName() override;
	virtual void onEnable() override;
	//void onTick(C_GameMode* gm);
};