#pragma once
#include "Module.h"
class Teams : public IModule {
private:
	bool alliedCheck = false;
	bool colorCheck = false;
	bool ppCheck = true;

public:
	Teams();
	~Teams();

	bool isAlliedCheckEnabled() { return this->isEnabled() && alliedCheck; };
	bool isColorCheckEnabled() { return this->isEnabled() && colorCheck; };
	bool isPpCheckEnabled() { return this->isEnabled() && ppCheck; };

	// Inherited via IModule
	virtual const char* getModuleName() override;
};
