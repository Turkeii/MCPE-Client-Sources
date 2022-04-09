#pragma once

#include <map>
#include <vector>

#include "../../Memory/GameData.h"
#include "../DrawUtils.h"
#include "../GuiUtils.h"
#include "../Module/ModuleManager.h"

struct HudWindow {
	HudWindow() {
		pos.x = 0;
		pos.y = 0;

		size.x = 30;
		size.y = 30;
	}
	vec2_t pos;
	vec2_t size;
};

class HudEditor {
public:
	static void init();
	static void render();
	static void onKeyUpdate(int key, bool isDown);
	static void onMouseClickUpdate(int key, bool isDown);
	static void onWheelScroll(bool direction);  // true = up, false = down
	//static void onLoadConfig(void* confVoid);
	//static void onSaveConfig(void* confVoid);
};
