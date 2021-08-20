#pragma once
#include "Module.h"
#include "../ModuleManager.h"
#include "../../../Utils/Target.h"


class Blink : public IModule {
private:
	std::vector<C_MovePlayerPacket*> MovePlayerPacketHolder;
	std::vector<PlayerAuthInputPacket*> PlayerAuthInputPacketHolder;

	std::vector<vec3_t> linePoints;
	vec3_t startPos;
	vec3_t startPosTop;

public:
	Blink();
	~Blink();

	vec2_t cameraRot = {0.f, 0.f};
	bool wasDisabled = false;

	// Inherited via IModule
	virtual void onTick(C_GameMode* gm) override;
	virtual const char* getModuleName() override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
	void onLevelRender() override;
	inline std::vector<C_MovePlayerPacket*>* getMovePlayerPacketHolder() { return &MovePlayerPacketHolder; };
	inline std::vector<PlayerAuthInputPacket*>* getPlayerAuthInputPacketHolder() { return &PlayerAuthInputPacketHolder; };
};
//ja