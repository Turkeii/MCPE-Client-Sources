#include "CubeCraftFly.h"

CubeCraftFly::CubeCraftFly() : IModule(0, Category::MOVEMENT, "Bypassing fly for Cubecraft") {
	this->glideMod = 0.00f;
}

CubeCraftFly::~CubeCraftFly() {
}

const char* CubeCraftFly::getModuleName() {
	if (isEnabled()) {
		static char modName[30];  //Hello world! Goodbye im commiting suiicide. 
		sprintf_s(modName, 30, "CubeCraftFly", glideModEffective);
		return modName;
	} else
		return ("CubeCraftFly");
}

void CubeCraftFly::onTick(C_GameMode* gm) {
	glideModEffective = glideMod;
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();

	if (g_Data.canUseMoveKeys()) {
		if (GameData::isKeyDown(*input->spaceBarKey))
			glideModEffective += 0.0f;
		if (GameData::isKeyDown(*input->sneakKey))
			glideModEffective -= 0.0f;
	}
	gm->player->velocity.y = glideModEffective;

	//timer code
	*g_Data.getClientInstance()->minecraft->timer = static_cast<float>(120);

}
void CubeCraftFly::onDisable() {
	*g_Data.getClientInstance()->minecraft->timer = 20.f;
}

const char* CubeCraftFly::getRawModuleName() {
	return "CubeCraftFly";
}

