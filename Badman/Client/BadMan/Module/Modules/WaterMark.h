#pragma once
#include "Module.h"
class WaterMark : public IModule {
public:
	WaterMark();
	~WaterMark();

	// Inherited via IModule
	virtual const char* getModuleName() override;
};
