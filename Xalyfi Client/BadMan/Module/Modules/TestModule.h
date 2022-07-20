#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class TestModule : public IModule {
public:
	bool greentext = true;
	bool custom = true;
	std::string message = " | Xalyfi";

	TestModule();
	~TestModule();

	// Inherited via IModule
	inline std::string& getMessage() { return message; };
	virtual const char* getModuleName() override;
};
