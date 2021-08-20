#pragma once
#include "../Module.h"


class ToggleSprintSneak : public Module {
public:
	
	bool isTop = false;

	bool isSprint = true;
	bool isSneak = false;
	bool lastOne = false;
	bool alwaysSprint = false;

	uint8_t toggled = false;
	uint8_t sneaktoggled = false;
	uint16_t sprintKey = VK_CONTROL;
	uint16_t sneakKey = VK_SHIFT;

	ToggleSprintSneak() : Module("Toggle Sprint/Sneak", 0, mltext("Allows you to sprint without holding your key.", "Permet de courrir sans tenir votre touche.")) {
		addBoolSetting(mltext("At the top of the screen", "Indicateur en haut"), "isTop", isTop, &isTop);
		addKeybindSetting(mltext("Sprint key", "Touche pour courrir"), "sprintKey", sprintKey, &sprintKey);
		addKeybindSetting(mltext("Sneak key", "Touche pour s'accroupir"), "sneakKey", sneakKey, &sneakKey);
		addBoolSetting(mltext("Enable Toggle Sprint", "Activer Togglesprint"), "ToggleSprint", isSprint, &isSprint);
		addBoolSetting(mltext("Enable Toggle Sneak", "Activer Toggle Sneak"), "ToggleSneak", isSneak, &isSneak);
		addBoolSetting(mltext("Always Sprint", "Toujours courrir"), "alwaysSprint", alwaysSprint, &alwaysSprint);
	}

	virtual void onRender() override;
	virtual void onKey(uint16_t key, bool isDown, bool& cancel) override;

	virtual void onDisable() override;
};

