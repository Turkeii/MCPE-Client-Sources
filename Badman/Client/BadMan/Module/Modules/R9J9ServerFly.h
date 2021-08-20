#pragma once
#include "Module.h"
class R9J9ServerFly : public IModule {
private:
	std::vector<C_MovePlayerPacket*> MovePlayerPacketHolder;
    std::vector<PlayerAuthInputPacket*> PlayerAuthInputPacketHolder;
    int gameTick = 0;
    float YMod = 0;
	
public:
    R9J9ServerFly();
    ~R9J9ServerFly();

    bool Mineplex = false;
    bool Hive = false;
    bool HiveSafe = false;
    bool Lifeboat = true;
    bool Creative = false;
    float HiveSpeed = 0.2f;
    int HiveTimer = 25;
    float MineplexSpeed = 0.5f;
    bool Test = false;

    virtual const char* getModuleName() override;
    virtual void onTick(C_GameMode* gm) override;
    virtual void onDisable() override;

    inline std::vector<C_MovePlayerPacket*>* getMovePlayerPacketHolder() { return &MovePlayerPacketHolder; };
    inline std::vector<PlayerAuthInputPacket*>* getPlayerAuthInputPacketHolder() { return &PlayerAuthInputPacketHolder; };
};