#pragma once
#include "Module.h"
class AltTheme : public IModule {
private:
public:
	AltTheme();
	~AltTheme();

	virtual const char* getModuleName() override;
	static float rFloat;
	static float bFloat;
	static float gFloat;
	
};