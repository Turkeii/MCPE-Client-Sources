#include "SettingManager.h"

#include <windows.storage.h>
#include <wrl.h>
#include "../../Utils/Logger.h"

using namespace ABI::Windows::Storage;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

std::wstring SettingManager::GetRoamingFolderPath() {
	std::string SettingsFolder = (getenv("AppData") + (std::string)"\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\PacketClient\\");
	return Utils::stringToWstring(SettingsFolder);
}

SettingManager::SettingManager() {
	this->roamingFolder = GetRoamingFolderPath();
}

SettingManager::~SettingManager() {
}

void SettingManager::loadSettings(std::string name, bool create) {
	size_t allocSize = name.size() + roamingFolder.size() + 20;  // std::wstring::size() can be wierd so lets make sure this actually fits
	char* fullPath = new char[allocSize];
	sprintf_s(fullPath, allocSize, "%S\\%s.txt", roamingFolder.c_str(), name.c_str());

	const bool SettingsExists = std::filesystem::exists(fullPath);
	if (SettingsExists || create) {
		if (name != currentSettings)
			saveSettings();  // Save old Settings

		currentSettings = name;
		if (SettingsExists) {
			std::ifstream confFile(fullPath, std::ifstream::binary);
			json conf;
			try {
				currentSettingsObj.clear();
				confFile >> currentSettingsObj;
			}
			catch (json::parse_error& e) {
				logF("Settings Load Exception!: %s", e.what());
			}
			currentSettingsObj["from"] = "PacketClient";
		}

		if (SettingsExists)
			moduleMgr->onLoadSettings(&currentSettingsObj);

		if (create)
			saveSettings();

		if (g_Data.getLocalPlayer() != nullptr) {
			g_Data.getGuiData()->displayClientMessageF("[Packet] %sSuccessfully %s %s%s%s!", GREEN, !SettingsExists ? "created" : "loaded", GRAY, name.c_str(), GREEN);
		}
	}

	delete[] fullPath;
}

void SettingManager::saveSettings() {
	logF("Saving Settings %s", currentSettings.c_str());
	size_t allocSize = currentSettings.size() + roamingFolder.size() + 20;  // std::wstring::size() can be wierd so lets make sure this actually fits
	char* fullPath = new char[allocSize];
	sprintf_s(fullPath, allocSize, "%S\\%s.txt", roamingFolder.c_str(), currentSettings.c_str());

	moduleMgr->onSaveSettings(&currentSettingsObj);

	std::ofstream o(fullPath, std::ifstream::binary);

	o << std::setw(4) << currentSettingsObj << std::endl;
	o.flush();
	o.close();

	delete[] fullPath;
}

void SettingManager::init() {
	logF("Initializing Settings");
	loadSettings(currentSettings, true);
}

SettingManager* SettingMgr = new SettingManager();
