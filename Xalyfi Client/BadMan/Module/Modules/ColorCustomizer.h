#pragma once
#include "Module.h"
class ColorCustomizer : public IModule {
private:
public:
	ColorCustomizer();
	~ColorCustomizer();

	virtual const char* getModuleName() override;
	static float rFloat;
	static float bFloat;
	static float gFloat;
	static float opacity;
	bool chroma = false;
};
