#pragma once
#include "Module.h"
class TestModule : public IModule {
public:
	bool bool1 = true;

	TestModule();
	~TestModule();

	// Inherited via IModule
	virtual const char* getModuleName() override;
};
