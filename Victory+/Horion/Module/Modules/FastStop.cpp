#include "FastStop.h"

FastStop::FastStop() : IModule(0, Category::MOVEMENT, "Stoping fast!!") {
	//registerBoolSetting("GroundCheck", &this->hitboxCheck, this->hitboxCheck);
}

FastStop::~FastStop() {
}

const char* FastStop::getModuleName() {
	return ("FastStop");
}

void FastStop::onMove(C_MoveInputHandler* input) {
	bool pressed = input->forward || input->backward || input->right || input->left;
	C_LocalPlayer* player = g_Data.getLocalPlayer();

	vec3_t pos = *g_Data.getLocalPlayer()->getPos();


	if (!pressed) {
		player->velocity.x *= 0.1f;
		player->velocity.z *= 0.1f;
	}
}