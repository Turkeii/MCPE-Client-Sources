#pragma once
#include "Module.h"
class Theme : public IModule {
private:
public:
	Theme();
	~Theme();

	bool rainbow = false;
	bool outline = true;
	virtual const char* getModuleName() override;
	static float rFloat;
	static float bFloat;
	static float gFloat;
	static float rFloat2;
	static float bFloat2;
	static float gFloat2;
	static float rFloat3;
	static float bFloat3;
	static float gFloat3;
	static float rFloat4;
	static float bFloat4;
	static float gFloat4;
};