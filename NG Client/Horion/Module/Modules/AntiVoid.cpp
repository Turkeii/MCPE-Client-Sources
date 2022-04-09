#include "AntiVoid.h"
bool voidcheck = false;
AntiVoid::AntiVoid() : IModule(0x0, Category::MOVEMENT, "Automatically teleports you back up if you fall down more than X blocks") {
	registerBoolSetting("VoidCheck", &voidcheck, voidcheck);
	registerEnumSetting("Mode", &mode, 0);
	mode = SettingEnum(this)
			   .addEntry(EnumEntry("Teleport", 0))
			   .addEntry(EnumEntry("Bounce", 1));
	registerIntSetting("distance", &distance, distance, 1, 20);
}

AntiVoid::~AntiVoid() {
}

const char* AntiVoid::getModuleName() {
		return "AntiVoid";
}

bool checkVoid() {
	auto Avoid = moduleMgr->getModule<AntiVoid>();
	if (voidcheck) {
		C_LocalPlayer* player = g_Data.getLocalPlayer();
		vec3 blockBelow = player->eyePos0;
		blockBelow.y -= player->height;
		blockBelow.y -= Avoid->distance;
		vec3 bb = vec3(blockBelow.x, blockBelow.y, blockBelow.z);
		for (int i = (int)(blockBelow.y); i > -62; i--) {
			if (player->region->getBlock(bb)->blockLegacy->material->isSolid || player->region->getBlock(bb)->blockLegacy->material->isLiquid) {
				return false;
			}
			bb.y -= 1.f;
		}
		return true;
	} else
		return true;
}

void AntiVoid::onTick(C_GameMode* gm) {
	C_LocalPlayer* player = g_Data.getLocalPlayer();
	vec3 blockBelow = g_Data.getLocalPlayer()->eyePos0;  // Block below the player
	blockBelow.y -= g_Data.getLocalPlayer()->height;
	blockBelow.y -= 0.5f;

	if (player->region->getBlock(blockBelow)->blockLegacy->material->isSolid && player->onGround) {
		orgipos = *player->getPos();
	}
	if (player->fallDistance >= distance && checkVoid()) {
		if (mode.selected == 0) {
			g_Data.getClientInstance()->getMoveTurnInput()->clearMovementState();
			player->setPos(orgipos);
			static auto hopMod = moduleMgr->getModule<Bhop>();
			static auto speedMod = moduleMgr->getModule<Speed>();
			static auto partner = moduleMgr->getModule<Partner>();
			static auto Fight = moduleMgr->getModule<FightBot>();
			hopMod->setEnabled(false);
			Fight->setEnabled(false);
			speedMod->setEnabled(false);
			//if (partner->Partnered.selected == 0)
				//g_Data.getGuiData()->displayClientMessageF("[%sAntiVoid%s] %sDisabled Speed, Fightbot, Bhop, and disabled move keys%s", BLUE, WHITE, BLUE, WHITE, configMgr, WHITE);
			//else
				//g_Data.getGuiData()->displayClientMessageF("[%sAntiVoid%s] %sDisabled Speed, Fightbot, Bhop, and disabled move keys%s", LIGHT_PURPLE, WHITE, LIGHT_PURPLE, WHITE, configMgr, WHITE);
		}
		if (mode.selected == 1) {
			float dist = gm->player->getPos()->dist(orgipos);
			g_Data.getLocalPlayer()->lerpMotion(vec3(0, 1, 0));
		}
	}
}