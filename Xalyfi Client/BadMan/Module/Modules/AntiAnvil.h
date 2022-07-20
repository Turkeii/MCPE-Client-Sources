#pragma once
#include "Module.h"

class AntiAnvil : public IModule {
private:
	int noclipTick = -1;
	float oldY = -1000.f;

public:
	AntiAnvil() : IModule(0x0, Category::PLAYER, "Prevents many anvil related things") {}
	~AntiAnvil() {}

	virtual const char* getModuleName() override {
		return "AntiAnvil";
	}

	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable() override;
};