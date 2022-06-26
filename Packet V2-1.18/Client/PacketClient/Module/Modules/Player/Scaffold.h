#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class Scaffold : public IModule {
private:
	bool shouldSwing = false;
	bool foundBlock = false;
	bool blockCount = true;
	float animPitch = 0.f;
	float animBack = 0.f;
	float animYaw = 0.f;
	int towerTimer = 20;
	float random = 1.5f;
	bool sprint = true;
	bool lockY = false;
	bool spoof = false;
	int yLock = -1;
	int timer = 20;
	int range = 4;
	int slot = 0;
	vec3_t blockBelowY;

	bool sneaking = false;
	bool jumping = false;

	bool findBlocks(C_ItemStack* itemStack);
	bool isUsefulBlock(C_ItemStack* itemStack);
	bool buildBlock(vec3_t blockBelow);
	bool predictBlock(vec3_t blockBelow);
	bool isBlockReplacable(vec3_t blockPos);
	bool selectBlock();

	// Positions
	vec3_t calcPos = vec3_t{0, 0, 0};
	vec3_t initialPos;
	vec3_t blockPos;
	vec3_t backPos;

public:
	float currExtend = 0.f;
	bool swing = true;
	float scY = 20.f;
	float scX = 10.f;
	float extend = 1;

	std::string name = ("Scaffold");
	SettingEnum rotations = this;
	SettingEnum downwards = this;
	SettingEnum tower = this;

	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual void onMove(C_MoveInputHandler* input) override;
	virtual void onSendPacket(C_Packet* packet) override;
	virtual void onPlayerTick(C_Player* plr) override;
	virtual const char* getRawModuleName() override;
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable() override;
	virtual void onEnable() override;
	Scaffold();
};