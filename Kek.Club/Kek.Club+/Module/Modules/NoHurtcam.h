#pragma once
#include "Module.h"

class NoHurtcam : public IModule {
public:
	NoHurtcam() : IModule(0, Category::VISUAL, "Disables visual hurt animation") {}
	~NoHurtcam(){};
	const char* getModuleName() override { return "NoHurtcam"; }
	virtual void onWorldTick(C_GameMode* gm) override { g_Data.getLocalPlayer()->cancelHurtAnimation(); }
};