#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include <filesystem>
#include <fstream>
#include <string>
#pragma comment(lib, "runtimeobject")

#include "../../Utils/Json.hpp"
#include "../Command/CommandMgr.h"
#include "../Module/ModuleManager.h"

using json = nlohmann::json;

class SettingManager {
private:
	std::wstring roamingFolder;
	static std::wstring GetRoamingFolderPath();
	json currentSettingsObj;

public:
	SettingManager();
	~SettingManager();

	std::string currentSettings = "Settings";

	void loadSettings(std::string name, bool create);
	void saveSettings();
	void init();
};

extern SettingManager* SettingMgr;
