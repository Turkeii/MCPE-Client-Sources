#pragma once
#include "Module.h"
class Zoom : public IModule {
public:
	Zoom();
	~Zoom();

	bool smooth = true;
	bool zooming = false;
	float strength = 65.f;
	float target = 65.f;
	float modifier = 65.f;

	// Inherited via IModule
	virtual bool isFlashMode() override;
	virtual const char* getModuleName() override;
	virtual void onEnable() override;
	virtual void onDisable() override;
};
