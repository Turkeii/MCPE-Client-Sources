#pragma once
#include "Module.h"
class Background : public IModule {
private:
public:
	Background();
	~Background();

	virtual const char* getModuleName() override;
	static float opacity;
	static float rFloat;
	static float bFloat;
	static float gFloat;
	
};