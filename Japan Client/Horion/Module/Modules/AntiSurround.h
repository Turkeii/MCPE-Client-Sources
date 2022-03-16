#pragma once
#include "Module.h"
class AntiSurround : public IModule {
private:
	bool findBlock();
	bool findBlock2();
	
public:
	bool autoswitch = false;
	bool spoof = false;
	bool multi = false;
	bool bypass = true;
	int range = 5;

	AntiSurround();
	~AntiSurround();

	virtual void onTick(C_GameMode* gm) override;
	virtual const char* getModuleName() override;
};
