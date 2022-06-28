#include "FastSwim.h"

FastSwim::FastSwim() : IModule(0x0, Category::MOVEMENT, "Swim fast") {
	registerFloatSetting("Water Horizontal", &waterHorizontal, 3.0f, 1.0f, 20.0f);
	registerFloatSetting("Water Vertical", &waterVertical, 3.0, 1.0, 20.0);
	registerFloatSetting("Lava Horizontal", &lavaHorizontal, 4.0, 1.0, 20.0);
	registerFloatSetting("Lava Vertical", &lavaVertical, 4.0, 1.0, 20.0);
}

FastSwim::~FastSwim() {
}

const char* FastSwim::getModuleName() {
	return "FastSwim";
}

void FastSwim::onMove(C_MoveInputHandler* input) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (player->isInLava() && !player->onGround) {
		player->velocity.z = (lavaHorizontal);
		player->velocity.x = (lavaHorizontal);
		player->velocity.y = (lavaVertical);
	} else if (player->isInWater() && !player->onGround) {
		player->velocity.z = (waterHorizontal);
		player->velocity.x = (waterHorizontal);
		player->velocity.y = (waterVertical);
	}
}