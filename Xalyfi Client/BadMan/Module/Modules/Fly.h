#pragma once
#include "Module.h"

class Fly : public IModule {
	private: float speed = 0.325f;
	float upanddown = 0.6f;
		float glideMod = -0.00f;
	float glideModEffective = 0;
		bool superMan = false;
	int fastSpeed = 100;

	public:
	Fly();
	~Fly();

	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onMove(C_MoveInputHandler* input) override;
};
