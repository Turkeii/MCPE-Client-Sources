#pragma once
#include "Module.h"
class SpawnTP : public IModule {
public:
	SpawnTP() : IModule(0, Category::EXPLOIT, "Teleport to your spawnpoint") {
	}
	~SpawnTP(){};

	// module broke idk why

	virtual const char* getModuleName() override { return "SpawnTP"; }

	void onTick(C_GameMode* gm) override {
		auto player = g_Data.getLocalPlayer();
		if (g_Data.getLocalPlayer() != nullptr) player->setSleeping(true);
		auto box = g_Data.addNotification("SpawnTP:", "Teleported!");
		box->duration = 15;
		setEnabled(false);
	}

	void onDisable() override {
		auto player = g_Data.getLocalPlayer();
		if (g_Data.getLocalPlayer() != nullptr) player->setSleeping(false);
	}
};