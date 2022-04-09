#pragma once
#include "Module.h"

class AutoTotem : public IModule {
private:
	bool force = false;

public:
	AutoTotem();
	~AutoTotem();

	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};