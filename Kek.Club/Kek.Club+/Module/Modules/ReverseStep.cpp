#include "ReverseStep.h"
float pullSpeed = -1.f;
ReverseStep::ReverseStep() : IModule(0x0, Category::MOVEMENT, "Screams stuff in chinese and TP's you down") {
	registerFloatSetting("PullSpeed", &pullSpeed, -1.f, -2.f, -1.f);
}

ReverseStep::~ReverseStep() {
}

const char* ReverseStep::getModuleName() {
	return ("ReverseStep");
}

void ReverseStep::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (gm->player->onGround && !gm->player->isInWater()) {
		gm->player->velocity.y = pullSpeed;
	}
}