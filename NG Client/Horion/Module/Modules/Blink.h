#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class Blink : public IModule {
public:
	std::vector<C_MovePlayerPacket*> MovePlayerPacketHolder;
	std::vector<PlayerAuthInputPacket*> PlayerAuthInputPacketHolder;
	inline std::vector<C_MovePlayerPacket*>* getMovePlayerPacketHolder() { return &MovePlayerPacketHolder; };
	inline std::vector<PlayerAuthInputPacket*>* getPlayerAuthInputPacketHolder() { return &PlayerAuthInputPacketHolder; };

	Blink() : IModule(0x0, Category::PLAYER, "Stops you from sending packets and then sends them in a bunch"){

	};
	~Blink(){
		if (!g_Data.canUseMoveKeys()) return;
		getMovePlayerPacketHolder()->clear();
		getPlayerAuthInputPacketHolder()->clear();
	};

	bool isFlashMode() {
		return true;
	}

	virtual const char* getModuleName() override {
		return "Blink";
	}
};