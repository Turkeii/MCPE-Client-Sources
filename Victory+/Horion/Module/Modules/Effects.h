#pragma once
#include "Module.h"
class teste : public IModule {
private:
	bool Invisible = false;
	bool Fire = false;
	bool Freeze = false;

public:
	teste();
	~teste();

	virtual const char* getModuleName() override;
	//virtual void onEnable() override;
	virtual void onTick(C_GameMode* gm) override;
};