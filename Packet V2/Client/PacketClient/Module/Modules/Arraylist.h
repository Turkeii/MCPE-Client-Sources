#pragma once
#include "Module.h"

class ArrayList : public IModule {
public:
	ArrayList();
	~ArrayList();

	bool modes = true;
	bool arraylist = true;
	bool arraylistBackground = true;
	float bgOp = 0.6;
	bool clickToggle = false;
	bool keybinds = false;
	bool alwaysShow = false;

	float scale = 1.f;

			SettingEnum mode = this;

	// Inherited via IModule
	virtual const char* getModuleName() override;
};