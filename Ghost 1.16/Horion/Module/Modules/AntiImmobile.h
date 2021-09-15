#pragma once
#include "Module.h"

class AntiImmobile : public IModule {
private:
	bool fat = true;
public:
	AntiImmobile();
	~AntiImmobile();

	const char* getModuleName() override;
};
