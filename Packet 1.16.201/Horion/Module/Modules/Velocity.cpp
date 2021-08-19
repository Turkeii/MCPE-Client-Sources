#include "Velocity.h"

Velocity::Velocity() : IModule(0, Category::MOVEMENT, "AntiKB Module") {
	//this->registerFloatSetting("Linear Modifier", &this->xModifier, this->xModifier, 0.f, 1.f);
	//this->registerFloatSetting("Height Modifier", &this->yModifier, this->yModifier, 0.f, 1.f);
}

Velocity::~Velocity() {
}

const char* Velocity::getModuleName() {
	return ("Velocity");
}

void Velocity::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (gm->player->damageTime >= 1 && gm->player->onGround) {
		gm->player->velocity.y = -1.f;
		gm->player->velocity.x = 0;
		gm->player->velocity.z = 0;
	}
}