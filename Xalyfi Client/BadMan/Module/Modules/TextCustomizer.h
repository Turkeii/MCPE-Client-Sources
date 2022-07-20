#pragma once
#include "Module.h"
class TextCustomizer : public IModule {
private:
public:
	TextCustomizer();
	~TextCustomizer();

	virtual const char* getModuleName() override;
	static float rFloat;
	static float bFloat;
	static float gFloat;
	static bool chroma;
};
