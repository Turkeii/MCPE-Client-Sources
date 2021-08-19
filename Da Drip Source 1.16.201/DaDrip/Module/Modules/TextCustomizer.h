#pragma once
#include "Module.h"
class TextCustomizer : public IModule {
private:


public:

	TextCustomizer();
	~TextCustomizer();

	virtual const char* getModuleName() override;
	static int rFloat;
	static int bFloat;
	static int gFloat;
	static bool chroma;
};
