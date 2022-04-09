#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class Notifications : public IModule {
private:
public:
	bool showToggle = true;
	float opacity = 0.6;

	Notifications();
	~Notifications();

	SettingEnum mode = this;

	// Inherited via IModule
	virtual const char* getModuleName() override;
};