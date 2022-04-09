#pragma once
#include "Module.h"
class Scaffold : public IModule {
private:
	bool foundBlock = false;
	bool switchMode = true;
	bool extendOut = true;
	bool staircase = true;
	bool airplace = false;
	bool sprint = true;
	bool spoof = false;
	int prevSlot = 0;
	int expand = 1;

	bool tryScaffold(vec3_t blockBelow);
	bool selectBlock();
	vec3_t initialPos;

	int yLock = -1;

public:
	std::vector<vec3_t> blockBelow2;
	bool foundCandidate2 = false;
	bool isHoldingSpace = false;
	bool isSneaking = false;
	bool isOnHive = false;
	bool rotations = true;
	bool tower = false;
	bool lockY = false;
	bool useRot = true;
	vec4_t scaffoldRot;
	int timer = 20;
	int tCounter = 1;

	// useRot
	bool forward = false;
	bool left = false;
	bool right = false;
	bool backwards = false;

	Scaffold();
	~Scaffold();

	std::string name = ("Scaffold");

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual const char* getRawModuleName() override;
	virtual void onSendPacket(C_Packet* packet) override;
	virtual void onMove(C_MoveInputHandler* input) override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;

	std::vector<C_MovePlayerPacket> movePacket1;
	std::vector<PlayerAuthInputPacket> authPacket1;
	std::vector<C_MovePlayerPacket*> MovePlayerPacketHolder;
	std::vector<PlayerAuthInputPacket*> PlayerAuthInputPacketHolder;
	inline std::vector<C_MovePlayerPacket*>* getMovePlayerPacketHolder() { return &MovePlayerPacketHolder; };
	inline std::vector<PlayerAuthInputPacket*>* getPlayerAuthInputPacketHolder() { return &PlayerAuthInputPacketHolder; };
};