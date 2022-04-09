#pragma once

#include <map>
#include <vector>

#include "../../Memory/GameData.h"
#include "../DrawUtils.h"
#include "../GuiUtils.h"
#include "../Module/ModuleManager.h"

struct ClickModule {
	bool isExtended = false;
};

struct ClickWindow {
	ClickWindow() {
		pos.x = 0;
		pos.y = 0;

		size.x = 20;
		size.y = 20;
	}
	vec2 pos;
	vec2 size;

	vec4 selectableSurface = vec4(pos.x, pos.y, pos.x + size.x, pos.y + size.y);

	bool isExtended = true;
	bool isInAnimation = false;
	float animation = 0;
	const char* name;
	std::map<unsigned int, std::shared_ptr<ClickModule> > moduleMap;

	int yOffset = 0;
};

class ClickGui {
private:
	inline static std::shared_ptr<ClickWindow> getWindow(const char* id);
	inline static std::shared_ptr<ClickModule> getClickModule(std::shared_ptr<ClickWindow> window, const char* id);

	static void renderLabel(const char* text);
	static void renderTooltip(std::string* text);

	static void renderCategory(Category category);
	inline static void getModuleListByCategory(Category category, std::vector<std::shared_ptr<IModule> >* modList);

	inline static const char* catToName(Category cat) {
		const char* categoryName;

		// Get Category Name
		{
			switch (cat) {
			case Category::COMBAT:
				categoryName = "Combat";
				break;
			case Category::VISUAL:
				categoryName = "Visual";
				break;
			case Category::MOVEMENT:
				categoryName = "Movement";
				break;
			case Category::PLAYER:
				categoryName = "Player";
				break;
			case Category::WORLD:
				categoryName = "World";
				break;
			case Category::GUI:
				categoryName = "Customize";
				break;
			case Category::FLYS:
				categoryName = "Flys";
				break;
			case Category::SERVER:
				categoryName = "Server";
				break;
			case Category::CONFIG:
				categoryName = "Configs";
				break;
			case Category::ENTITY:
				categoryName = "Entity";
				break;
			case Category::PARTNER:
				categoryName = "Partner";
				break;
			}
		}
		return categoryName;
	}

public:
	static void init();
	static void render();
	static void onKeyUpdate(int key, bool isDown);
	static void onMouseClickUpdate(int key, bool isDown);
	static void onWheelScroll(bool direction);  // true = up, false = down
	static void onLoadConfig(void* confVoid);
	static void onSaveConfig(void* confVoid);
};