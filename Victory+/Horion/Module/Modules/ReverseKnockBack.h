#pragma once

#include "Module.h"

class ReverseKnockBack : public IModule {
public:

	ReverseKnockBack();
	~ReverseKnockBack();

	// Inherited via IModule
	virtual const char* getModuleName() override;
};
