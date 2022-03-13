#include "Glide.h"

Glide::Glide() : IModule(0, Category::MOVEMENT, "Float down") {
	this->registerFloatSetting("value", &this->glideMod, this->glideMod, -2, 1);
}

Glide::~Glide() {
}

const char* Glide::getModuleName() {
	return ("Glide");
}

void Glide::onTick(C_GameMode* gm) {
	glideModEffective = glideMod;
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();

	if (g_Data.canUseMoveKeys()) {
		if (GameData::isKeyDown(*input->spaceBarKey))
			glideModEffective += 0.2f;
		if (GameData::isKeyDown(*input->sneakKey))
			glideModEffective -= 0.2f;
	}
	gm->player->velocity.y = glideModEffective;
}

const char* Glide::getRawModuleName() {
	return "Glide";
}
