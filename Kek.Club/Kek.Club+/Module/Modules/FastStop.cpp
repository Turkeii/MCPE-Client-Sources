#include "FastStop.h"
#include "../ModuleManager.h"
FastStop::FastStop() : IModule(0, Category::MOVEMENT, "Stops fast") {
}

FastStop::~FastStop() {
}

const char* FastStop::getModuleName() {
	return ("FastStop");
}

void FastStop::onMove(C_MoveInputHandler* input) {
	if (g_Data.getLocalPlayer() != nullptr && g_Data.getCGameMode() != nullptr && g_Data.getLocalPlayer()->isAlive() && !moduleMgr->getModule<FollowPath>()->isEnabled()) {
		bool pressed = input->forward || input->backward || input->right || input->left;
		C_LocalPlayer* player = g_Data.getLocalPlayer();

		vec3_t pos = *g_Data.getLocalPlayer()->getPos();

		if (!pressed) {
			player->velocity.x *= 0.1f;
			player->velocity.z *= 0.1f;
		}
	}
}