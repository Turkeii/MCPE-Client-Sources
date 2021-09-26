#pragma once
#include "Module.h"
class ThiccerScaffold : public IModule {
private:
	bool staircaseMode = false;
	bool timerBool = false;
	bool rot = true;
	int timer = 20;
	bool tryScaffold(vec3_t blockBelow);
	bool findBlock();

public:
	ThiccerScaffold();
	~ThiccerScaffold();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable() override;
};