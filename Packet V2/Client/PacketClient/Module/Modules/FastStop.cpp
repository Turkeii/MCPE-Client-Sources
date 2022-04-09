#include "../../Module/ModuleManager.h"

FastStop::FastStop() : IModule(0, Category::MOVEMENT, "Stops fast yes") {
}

FastStop::~FastStop() {
}

const char* FastStop::getModuleName() {
	return ("FastStop");
}

void FastStop::onMove(C_MoveInputHandler* input) {
	auto targetStrafe = moduleMgr->getModule<TargetStrafe>();
	auto player = g_Data.getLocalPlayer();
	vec2_t move = {input->forwardMovement, -input->sideMovement};
	bool pressed = move.magnitude() > 0.f;
	if (targetStrafe->isEnabled() && !targetStrafe->targetListEmpty)
		return;

	if (icey) {
		/*for (int i = 0; i < 40; i++) {
			if (counter == 8) {
				counter = 1;
			} else {
				counter++;
			}

			if (counter == 2) {
				flight true
			} else if (counter == 4) {
				flight false
			} else if (counter == 6) {
				longjump true
			} else if (counter == 8) {
				longjump false
			}
		}*/
	}
	if (!pressed && player->damageTime == 0) {
		player->velocity.x = 0;
		player->velocity.z = 0;
	}
} 