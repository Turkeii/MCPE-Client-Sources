#include "Jesus.h"

Jesus::Jesus() : IModule(0, Category::MOVEMENT, "Walk over water, like Jesus") {
}

Jesus::~Jesus() {
}

const char* Jesus::getModuleName() {
	return "Jesus";
}

void Jesus::onTick(C_GameMode* gm) {
	if (gm->player->isSneaking()) return;

	if (gm->player->hasEnteredWater()) {
		gm->player->velocity.y = 0.01f;
		gm->player->onGround = false;
		wasInWater = false;
	} else if (gm->player->isInWater() || gm->player->isInLava()) {
		gm->player->velocity.y = 0.1f;
		gm->player->onGround = false;
		wasInWater = false;
	} else {
		if (wasInWater) {
			wasInWater = false;
			gm->player->velocity.x *= 1.2f;
			gm->player->velocity.x *= 1.2f;
		}
	}
}