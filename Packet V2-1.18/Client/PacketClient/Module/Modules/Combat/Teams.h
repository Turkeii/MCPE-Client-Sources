#pragma once
#include "../Module.h"

class Teams : public IModule {
private:
	bool alliedCheck = false;
	bool colorCheck = true;

public:
	Teams();

	bool isAlliedCheckEnabled() { return this->isEnabled() && alliedCheck; };
	bool isColorCheckEnabled() { return this->isEnabled() && colorCheck; };

	virtual const char* getModuleName();
};
