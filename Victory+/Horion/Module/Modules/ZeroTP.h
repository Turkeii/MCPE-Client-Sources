#pragma once
#include "Module.h"

class ZeroTP : public IModule {
//private:
public:
	ZeroTP();
	~ZeroTP();

	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
