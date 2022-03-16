#pragma once
#include "Module.h"

class AutoTotem : public IModule {
public:

	bool open = false;
	AutoTotem();
	~AutoTotem();

	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
