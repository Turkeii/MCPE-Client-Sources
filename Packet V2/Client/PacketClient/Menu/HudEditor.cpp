#include "HudEditor.h"

#include <Windows.h>

#include "../../Utils/Json.hpp"
#include "../../Utils/Logger.h"

int timesRendered2 = 0;
bool isLeftClickDown2 = false;
bool isRightClickDown2 = false;
bool shouldToggleLeftClick2 = false;  // If true, toggle the focused module
bool shouldToggleRightClick2 = false;
bool resetStartPos2 = true;
bool initialized = false;
int scrollingDirection2 = 0;

/*void HudEditor::render() {
	static auto hudEditorMod = moduleMgr->getModule<HudEditorMod>();
	if (!moduleMgr->isInitialized())
		return;

	if (timesRendered2 < 10)
		timesRendered2++;

	// Fill Background
	DrawUtils::fillRectangle(vec4_t(0, 0, g_Data.getClientInstance()->getGuiData()->widthGame, g_Data.getClientInstance()->getGuiData()->heightGame), MC_Color(0, 0, 0), 0.3);

	shouldToggleLeftClick2 = false;
	shouldToggleRightClick2 = false;
	resetStartPos2 = false;

	DrawUtils::flush();
}

void HudEditor::init() { initialized = true; }

void HudEditor::onMouseClickUpdate(int key, bool isDown) {
	static auto hudEditorMod = moduleMgr->getModule<HudEditorMod>();
	if (hudEditorMod->isEnabled() && g_Data.isInGame()) {
		switch (key) {
		case 1:  // Left Click
			isLeftClickDown2 = isDown;
			if (isDown)
				shouldToggleLeftClick2 = true;
			break;
		case 2:  // Right Click
			isRightClickDown2 = isDown;
			if (isDown)
				shouldToggleRightClick2 = true;
			break;
		}
	}
}

void HudEditor::onWheelScroll(bool direction) {
	if (!direction)
		scrollingDirection2++;
	else
		scrollingDirection2--;
}

void HudEditor::onKeyUpdate(int key, bool isDown) {
	if (!initialized)
		return;
	static auto hudEditorMod = moduleMgr->getModule<HudEditorMod>();

	if (!isDown)
		return;

	if (!hudEditorMod->isEnabled()) {
		timesRendered2 = 0;
		return;
	}

	if (timesRendered2 < 10)
		return;
	timesRendered2 = 0;

	switch (key) {
	case VK_ESCAPE:
		hudEditorMod->setEnabled(false);
		return;
	default:
		if (key == hudEditorMod->getKeybind())
			hudEditorMod->setEnabled(false);
	}
}

/*using json = nlohmann::json;
void HudEditor::onLoadConfig(void* confVoid) {
	savedWindowSettings.clear();
	windowMap.clear();
	json* conf = reinterpret_cast<json*>(confVoid);
	if (conf->contains("HudEditor")) {
		auto obj = conf->at("HudEditor");
		if (obj.is_null())
			return;
		for (int i = 0; i <= (int)Category::CUSTOM; i++) {
			auto catName = HudEditor::catToName((Category)i);
			if (obj.contains(catName)) {
				auto value = obj.at(catName);
				if (value.is_null())
					continue;
				try {
					SavedWindowSettings windowSettings = {};
					windowSettings.name = catName;
					if (value.contains("pos")) {
						auto posVal = value.at("pos");
						if (!posVal.is_null() && posVal.contains("x") && posVal["x"].is_number_float() && posVal.contains("y") && posVal["y"].is_number_float()) {
							try {
								windowSettings.pos = {posVal["x"].get<float>(), posVal["y"].get<float>()};
							} catch (std::exception e) {
							}
						}
					}
					if (value.contains("isExtended")) {
						auto isExtVal = value.at("isExtended");
						if (!isExtVal.is_null() && isExtVal.is_boolean()) {
							try {
								windowSettings.isExtended = isExtVal.get<bool>();
							} catch (std::exception e) {
							}
						}
					}
					savedWindowSettings[Utils::getCrcHash(catName)] = windowSettings;
				} catch (std::exception e) {
					logF("Config Load Error (HudEditorMenu): %s", e.what());
				}
			}
		}
	}
}
void HudEditor::onSaveConfig(void* confVoid) {
	json* conf = reinterpret_cast<json*>(confVoid);
	// First update our map
	for (const auto& wind : windowMap) {
		savedWindowSettings[wind.first] = {wind.second->pos, wind.second->isExtended, wind.second->name};
	}

	// Save to json
	if (conf->contains("HudEditor"))
		conf->erase("HudEditor");

	json obj = {};

	for (const auto& wind : savedWindowSettings) {
		json subObj = {};
		subObj["pos"]["x"] = wind.second.pos.x;
		subObj["pos"]["y"] = wind.second.pos.y;
		subObj["isExtended"] = wind.second.isExtended;
		obj[wind.second.name] = subObj;
	}

	conf->emplace("HudEditor", obj);
}*/