#pragma once
#include "Module.h"
class TestModule : public IModule {
private:
	int delay = 0;
	int tickTimeout = 0;
	std::vector<AABB> bufferedChestList;
	std::mutex listLock;

public:
	float float1 = 0;
	int int1 = 0;
	bool onlyjump = true;
	SettingEnum enum1;
	TestModule();
	~TestModule();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual void onTick(C_GameMode* gm) override;
};
