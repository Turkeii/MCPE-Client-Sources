#include "AutoRespawn.h"

AutoRespawn::AutoRespawn() : IModule(0, Category::MISC, "Respawns you when you die") {
	registerBoolSetting("DeathPos", &deathpos, deathpos);
}

AutoRespawn::~AutoRespawn() {
}

const char* AutoRespawn::getModuleName() {
	return "AutoRespawn";
}
void* targetAddress;

void AutoRespawn::onEnable() {
	if (targetAddress == nullptr)
		targetAddress = (void*)(FindSignature("40 88 BB ? ? ? ? 40 84 FF"));
	Utils::nopBytes((unsigned char*)((uintptr_t)targetAddress), 7);
}

void AutoRespawn::onDisable() {
	unsigned char* patch = (unsigned char*)"\x40\x88\xBB\x98\x0A\x00\x00";
	Utils::patchBytes((unsigned char*)((uintptr_t)targetAddress), patch, 7);
}
void AutoRespawn::onTick(C_GameMode* gm) {
	if (deathpos) {
		auto player = g_Data.getLocalPlayer();
		if (player == nullptr) return;

		int deathtimer = player->getDeathTime();

		vec3_t* pos = g_Data.getLocalPlayer()->getPos();
		std::string X = "X: " + std::to_string((int)floorf(pos->x));
		std::string Y = "Y: " + std::to_string((int)floorf(pos->y - 1.f));
		std::string Z = "Z: " + std::to_string((int)floorf(pos->z));
		std::string All = "[%sKek.Club+%s] | %s" + X + " " + Y + " " + Z;
		const char* all = All.c_str();

		if (deathtimer == 1) {
			C_GuiData* guiData = g_Data.getClientInstance()->getGuiData();
			if (guiData != nullptr) {
				guiData->displayClientMessageF(all, GREEN, WHITE, GRAY);
			}
		}
	}
}
//boo