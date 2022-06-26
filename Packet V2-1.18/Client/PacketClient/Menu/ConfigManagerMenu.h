#pragma once

#include <vector>

#include "../../Utils/DrawUtils.h"
#include "../Module/ModuleManager.h"
#include "../../Utils/Json.hpp"

class ConfigManagerMenu {
public:
	static void onKeyUpdate(int key, bool isDown);
	static void render();
	static void init();
};