#pragma once
#include "Module.h"
class Scaffold : public IModule {
private:
	int slot = false;
	bool airplace = false;
	bool autoselect = true;
	bool entityscaff = false;
	bool predict = true;
	bool staircaseMode = false;
	bool tryScaffold(vec3_t blockBelow);
	bool findBlock();

public:
	Scaffold();
	~Scaffold();
	bool spoof = false;
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable() override;
};