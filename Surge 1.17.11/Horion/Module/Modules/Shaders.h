#pragma once
#include "Module.h"
class Shaders : public IModule {
public:
	Shaders();
	~Shaders();
	virtual const char* getModuleName() override;
};
