#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class Notifications : public IModule {
public:
	float positionX, positionY = 0;
	bool showToggle = true;
	int opacity = 150;

	SettingEnum mode = this;

	virtual const char* getModuleName() override;
	Notifications();
};