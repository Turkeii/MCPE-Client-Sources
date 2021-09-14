#pragma once
#include "Module.h"
class Emo : public IModule {
public:
	int amount = 1;
	Emo();
	~Emo();

private:
	virtual const char* getModuleName() override;
	virtual void onEnable() override;
	//void onTick(C_GameMode* gm);
};