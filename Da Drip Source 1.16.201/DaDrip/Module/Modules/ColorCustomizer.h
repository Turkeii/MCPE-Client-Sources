#pragma once
#include "Module.h"
class ColorCustomizer : public IModule {
private:
	

public: 
	
	ColorCustomizer();
	~ColorCustomizer();

	virtual const char* getModuleName() override;
	static int rFloat;
	static int bFloat;
	static int gFloat;
	static float opacity;
	bool chroma = false;
};
