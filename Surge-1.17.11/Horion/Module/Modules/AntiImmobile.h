#pragma once
#include "Module.h"

class AntiImmobile : public IModule {
public:
	bool fat = false;
	AntiImmobile();
	~AntiImmobile();

	const char* getModuleName() override;
};
