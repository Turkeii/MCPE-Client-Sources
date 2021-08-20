#include "DeathCoords.h"

DeathCoords::DeathCoords() : IModule(0, Category::PLAYER, "logs your last known position before you died") {
}

DeathCoords::~DeathCoords() {
}

const char* DeathCoords::getModuleName() {
	return ("DeathCoords");
}
void DeathCoords::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	int deathtim = player->getDeathTime();

	vec3_t* pos = g_Data.getLocalPlayer()->getPos();
	std::string coordsX = "X: " + std::to_string((int)floorf(pos->x));
	std::string coordsY = "Y: " + std::to_string((int)floorf(pos->y - 1.f));
	std::string coordsZ = "Z: " + std::to_string((int)floorf(pos->z));
	std::string coordsText = "%sDeath Pos%s : %s" + coordsX + " " + coordsY + " " + coordsZ;
	const char* coordsYEET = coordsText.c_str(); //took me 30 mins to figure this out

	if (deathtim == 1) {
		C_GuiData* guiData = g_Data.getClientInstance()->getGuiData();
		if (guiData != nullptr) {
			guiData->displayClientMessageF(coordsYEET, RED, WHITE, GOLD); //change the colours if you want, dunno the "perfect" combo
		}
	}
}
