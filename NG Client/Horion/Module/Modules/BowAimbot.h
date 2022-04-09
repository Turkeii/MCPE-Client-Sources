#pragma once
#include "Module.h"
class BowAimbot : public IModule {
public:
	BowAimbot();
	~BowAimbot();

	bool silent = true;
	bool predict = false;
	bool visualize = false;
	vec2 angle;

	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual void onSendPacket(C_Packet* packet) override;
};
