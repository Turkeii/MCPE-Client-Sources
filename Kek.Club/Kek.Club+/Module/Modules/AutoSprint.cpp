#include "AutoSprint.h"

AutoSprint::AutoSprint() : IModule(0, Category::MOVEMENT, "ZOOOOOOOOM") {
	registerEnumSetting("Mode", &SprintMode, 0);
	SprintMode = SettingEnum(this)
				   .addEntry(EnumEntry("Vanilla", 0))
				   .addEntry(EnumEntry("Rage", 1));
}
AutoSprint::~AutoSprint() {
}

const char* AutoSprint::getModuleName() {
	return ("AutoSprint");
}
const char* AutoSprint::getModName() {
	if (alldirections) {
		return " [Rage]";
	} else {
		return " [Vanilla]";
	}
}
void AutoSprint::onTick(C_GameMode* gm) {
	switch (SprintMode.selected) {
	default:
		alldirections = false;
		break;
	case 1:
		alldirections = true;
		break;
	}
	if (!gm->player->isSprinting() && gm->player->velocity.magnitudexz() > 0.01f) {
		C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
		if (alldirections || GameData::isKeyDown(*input->forwardKey))
			gm->player->setSprinting(true);
	}
}