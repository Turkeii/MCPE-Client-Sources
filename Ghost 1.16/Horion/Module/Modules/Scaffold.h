#pragma once
#include "Module.h"
class Scaffold : public IModule {
private:
	bool free = false;
	bool tower = false;
	bool time = false;
	bool spoof = false;
	bool staircaseMode = false;
	bool andromeda = false;
	bool rot = true;
	bool tryScaffold(vec3_t blockBelow);
	bool findBlock();
	float speed = 1.5f;
	float towerspeed = 1.5f;

public:
	Scaffold();
	~Scaffold();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	void onMove(C_MoveInputHandler* input);
	virtual void onDisable() override;
};
