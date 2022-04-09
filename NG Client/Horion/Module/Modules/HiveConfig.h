#pragma once
#include "Module.h"
class HiveConfig : public IModule {
public:
	HiveConfig();
	~HiveConfig();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	void onEnable() override;
};
