#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class Chat : public IModule {
public:
	bool greentext = true;
	bool custom = true;
	std::string message = " | JapanClient";

	Chat();
	~Chat();

	// Inherited via IModule
	inline std::string& getMessage() { return message; };
	virtual const char* getModuleName() override;
};
#pragma once
