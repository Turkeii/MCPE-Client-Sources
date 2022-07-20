#pragma once
#include "Module.h"

class NoClip : public IModule {
		private: 
			float speed = 0.325f;
	float upanddown = 0.6f;
		float glideMod = -0.00f;
	float glideModEffective = 0;
		vec3_t oldPos;
	bool NoPacket = false;

	public:
	NoClip();
	~NoClip();

	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onMove(C_MoveInputHandler* input) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
};
