#pragma once

#include "Module.h"

class ViewModel : public IModule {
public:
	ViewModel();
	virtual const char* getModuleName();
};