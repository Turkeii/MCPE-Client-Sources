#pragma once
#include "Module.h"
class MinplexConfig : public IModule {
public:
	MinplexConfig();
	~MinplexConfig();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	void onEnable() override;
};
