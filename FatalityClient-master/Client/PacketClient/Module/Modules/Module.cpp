#include "Module.h"
#include "../../../Utils/Json.hpp"
#include "../../../Utils/Logger.h"
#include <cstdarg>
#include "../../../Memory/Hooks.h"
#include <iomanip>
#include <chrono>
#include <string>
#include <Windows.h>
#include <Psapi.h>
#include <iostream>
#include <direct.h>
#include <conio.h>
#include <sstream>
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <string>
#include<TlHelp32.h>
#include <tchar.h> 
#include <vector>
#include <thread>
#include <wtsapi32.h>
#include <psapi.h>
#include <math.h>
#include <algorithm> 
#include <playsoundapi.h>
#include<windows.h>
#include <tchar.h>
#include <urlmon.h>
#include "pch.h"

using json = nlohmann::json;
using namespace std;

#pragma region EnumEntry
EnumEntry::EnumEntry(const string _name, const unsigned char value) {
	name = _name;
	val = value;
}

EnumEntry::EnumEntry(const char* _name, const unsigned char value) {
	name = _name;
	val = value;
}

string EnumEntry::GetName() {
	return name;
}

unsigned char EnumEntry::GetValue() {
	return val;
}

#pragma endregion
#pragma region SettingEnum
SettingEnum::SettingEnum(vector<EnumEntry>& entr, IModule* mod) {
	Entrys = entr;
	owner = mod;
	sort(Entrys.begin(), Entrys.end(), [](EnumEntry rhs, EnumEntry lhs) {
		return rhs.GetValue() < lhs.GetValue();
		});
}

SettingEnum::SettingEnum(IModule* mod) {
	owner = mod;
}

SettingEnum& SettingEnum::addEntry(EnumEntry entr) {
	auto etr = EnumEntry(entr);
	bool SameVal = false;
	for (auto it = this->Entrys.begin(); it != this->Entrys.end(); it++) {
		SameVal |= it->GetValue() == etr.GetValue();
	}
	if (!SameVal) {
		Entrys.push_back(etr);
		sort(Entrys.begin(), Entrys.end(), [](EnumEntry rhs, EnumEntry lhs) {
			return rhs.GetValue() < lhs.GetValue();
			});
	}
	return *this;
}

SettingEnum& SettingEnum::addEntry(const char* name, int value) {
	auto etr = EnumEntry(name, value);
	bool SameVal = false;
	for (auto it : Entrys)
		SameVal |= it.GetValue() == etr.GetValue();

	if (!SameVal) {
		Entrys.push_back(etr);
		sort(Entrys.begin(), Entrys.end(), [](EnumEntry rhs, EnumEntry lhs) {
			return rhs.GetValue() < lhs.GetValue();
			});
	}
	return *this;
}

EnumEntry& SettingEnum::GetEntry(int ind) {
	return Entrys.at(ind);
}

EnumEntry& SettingEnum::GetSelectedEntry() {
	return GetEntry(selected);
}

int SettingEnum::getSelectedValue() {
	return GetEntry(selected).GetValue();
}

int SettingEnum::GetCount() {
	return (int)Entrys.size();
}

int SettingEnum::SelectNextValue(bool back) {
	if (back)
		selected--;
	else
		selected++;

	if (Entrys.size() <= selected) {
		selected = 0;
		return selected;
	}
	else if (selected < 0) {
		selected = (int)Entrys.size() - 1;
		return selected;
	}
	return selected;
}
#pragma endregion

IModule::IModule(int key, Category c, const char* tooltip) {
	this->keybind = key;
	this->category = c;
	this->tooltip = tooltip;
	this->registerKeybindSetting(string("keybind"), &this->keybind, this->keybind, 0, 0xFF);
	this->registerBoolSetting(string("enabled"), &this->enabled, false);
	this->ModulePos = vec2_t(0.f, 0.f);
}

void IModule::registerFloatSetting(string name, float* floatPtr, float defaultValue, float minValue, float maxValue) {
#ifdef DEBUG
	if (minValue > maxValue)
		__debugbreak();  // Minimum value is bigger than maximum value
#endif

	SettingEntry* setting = new SettingEntry();
	setting->valueType = ValueType::FLOAT_T;

	setting->value = reinterpret_cast<SettingValue*>(floatPtr);

	// Default Value
	SettingValue* defaultVal = new SettingValue();
	defaultVal->_float = defaultValue;
	setting->defaultValue = defaultVal;

	// Min Value
	SettingValue* minVal = new SettingValue();
	minVal->_float = minValue;
	setting->minValue = minVal;

	// Max Value
	SettingValue* maxVal = new SettingValue();
	maxVal->_float = maxValue;
	setting->maxValue = maxVal;

	strcpy_s(setting->name, 19, name.c_str());  // Name

	settings.push_back(setting);  // Add to list
}

void IModule::registerIntSetting(string name, int* intPtr, int defaultValue, int minValue, int maxValue) {
#ifdef DEBUG
	if (minValue > maxValue)
		__debugbreak();  // Minimum value is bigger than maximum value
#endif

	SettingEntry* setting = new SettingEntry();
	setting->valueType = ValueType::INT_T;
	setting->value = reinterpret_cast<SettingValue*>(intPtr);  // Actual Value

	// Default Value
	SettingValue* defaultVal = new SettingValue();
	defaultVal->_int = defaultValue;
	setting->defaultValue = defaultVal;

	// Min Value
	SettingValue* minVal = new SettingValue();
	minVal->_int = minValue;
	setting->minValue = minVal;

	// Max Value
	SettingValue* maxVal = new SettingValue();
	maxVal->_int = maxValue;
	setting->maxValue = maxVal;

	// Name
	strcpy_s(setting->name, 19, name.c_str());

	settings.push_back(setting);  // Add to list
}

void IModule::registerMinMaxSetting(string name, int* intPtr, int defaultValue, int minValue, int maxValue) {
#ifdef DEBUG
	if (minValue > maxValue)
		__debugbreak();  // Minimum value is bigger than maximum value
#endif

	SettingEntry* setting = new SettingEntry();
	setting->valueType = ValueType::INT_T;
	setting->value = reinterpret_cast<SettingValue*>(intPtr);  // Actual Value

	// Default Value
	SettingValue* defaultVal = new SettingValue();
	defaultVal->_int = defaultValue;
	setting->defaultValue = defaultVal;

	// Min Value
	SettingValue* minVal = new SettingValue();
	minVal->_int = minValue;
	setting->minValue = minVal;

	// Max Value
	SettingValue* maxVal = new SettingValue();
	maxVal->_int = maxValue;
	setting->maxValue = maxVal;

	// Name
	strcpy_s(setting->name, 19, name.c_str());

	settings.push_back(setting);  // Add to list
}

void IModule::registerKeybindSetting(string name, int* intPtr, int defaultValue, int minValue, int maxValue) {
#ifdef DEBUG
	if (minValue > maxValue)
		__debugbreak();  // Minimum value is bigger than maximum value
#endif

	SettingEntry* setting = new SettingEntry();
	setting->valueType = ValueType::KEYBIND_T;
	setting->value = reinterpret_cast<SettingValue*>(intPtr);  // Actual Value

	// Default Value
	SettingValue* defaultVal = new SettingValue();
	defaultVal->_keybind = defaultValue;
	setting->defaultValue = defaultVal;

	// Min Value
	SettingValue* minVal = new SettingValue();
	minVal->_keybind = minValue;
	setting->minValue = minVal;

	// Max Value
	SettingValue* maxVal = new SettingValue();
	maxVal->_keybind = maxValue;
	setting->maxValue = maxVal;

	// Name
	strcpy_s(setting->name, 19, name.c_str());

	settings.push_back(setting);  // Add to list
}

void IModule::registerEnumSetting(string name, SettingEnum* ptr, int defaultValue) {
	SettingEntry* setting = new SettingEntry();
	setting->valueType = ValueType::ENUM_T;
	if (defaultValue < 0 || defaultValue >= ptr->GetCount())
		defaultValue = 0;

	// Actual Value
	setting->value = reinterpret_cast<SettingValue*>(&ptr->selected);
	setting->value->_int = defaultValue;

	// Default Value
	SettingValue* defaultVal = new SettingValue();
	defaultVal->_int = defaultValue;
	setting->defaultValue = defaultVal;

	// Min Value (is Extended)
	SettingValue* minVal = new SettingValue();
	minVal->_bool = false;
	setting->minValue = minVal;

	// Enum data
	setting->extraData = ptr;

	strcpy_s(setting->name, 19, name.c_str());
	settings.push_back(setting);
}
void IModule::registerEnumSetting(const char* name, SettingEnum* ptr, int defaultValue) {
	SettingEntry* setting = new SettingEntry();
	setting->valueType = ValueType::ENUM_T;
	if (defaultValue < 0 || defaultValue >= ptr->GetCount())
		defaultValue = 0;

	// Actual Value
	setting->value = reinterpret_cast<SettingValue*>(&ptr->selected);
	setting->value->_int = defaultValue;

	// Default Value
	SettingValue* defaultVal = new SettingValue();
	defaultVal->_int = defaultValue;
	setting->defaultValue = defaultVal;

	// Min Value (is Extended)
	SettingValue* minVal = new SettingValue();
	minVal->_bool = false;
	setting->minValue = minVal;

	// Enum data
	setting->extraData = ptr;

	strcpy_s(setting->name, 19, name);
	settings.push_back(setting);
}

void IModule::registerBoolSetting(string name, bool* boolPtr, bool defaultValue) {
	SettingEntry* setting = new SettingEntry();
	setting->valueType = ValueType::BOOL_T;

	setting->value = reinterpret_cast<SettingValue*>(boolPtr);  // Actual value

	SettingValue* defaultVal = new SettingValue();  // Default Value
	defaultVal->_bool = defaultValue;
	setting->defaultValue = defaultVal;

	strcpy_s(setting->name, 19, name.c_str());  // Name

	settings.push_back(setting);  // Add to list
}

IModule::~IModule() {
	for (auto it = this->settings.begin(); it != this->settings.end(); it++) {
		delete* it;
	}
	this->settings.clear();
}

const char* IModule::getModuleName() {
	return "Module";
}

const char* IModule::getRawModuleName() {
	return getModuleName();
}

int IModule::getKeybind() {
	return this->keybind;
}

void IModule::setKeybind(int key) {
	this->keybind = key;
}

bool IModule::allowAutoStart() {
	return true;
}

void IModule::onPlayerTick(C_Player*) {
}

void IModule::onWorldTick(C_GameMode*) {
}

void IModule::onTick(C_GameMode*) {
}

void IModule::onKeyUpdate(int key, bool isDown) {
	if (key == getKeybind()) {
		if (isHoldMode())
			setEnabled(isDown);
		else if (isDown)
			toggle();
	}
}

void IModule::onEnable() {
}

void IModule::onDisable() {
}

void IModule::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
}

void IModule::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
}

void IModule::onSendPacket(C_Packet*) {
}

void IModule::onLoadConfig(void* confVoid) {
	json* conf = reinterpret_cast<json*>(confVoid);
	if (conf->contains(this->getRawModuleName())) {
		auto obj = conf->at(this->getRawModuleName());
		if (obj.is_null())
			return;
		for (auto it = this->settings.begin(); it != this->settings.end(); ++it) {
			SettingEntry* sett = *it;
			if (obj.contains(sett->name)) {
				auto value = obj.at(sett->name);
				if (value.is_null())
					continue;
				try {
					switch (sett->valueType) {
					case ValueType::FLOAT_T:
						sett->value->_float = value.get<float>();
						break;
					case ValueType::DOUBLE_T:
						sett->value->_double = value.get<double>();
						break;
					case ValueType::INT64_T:
						sett->value->int64 = value.get<__int64>();
						break;
					case ValueType::INT_T:
						sett->value->_int = value.get<int>();
						break;
					case ValueType::BOOL_T:
						sett->value->_bool = value.get<bool>();
						break;
					case ValueType::TEXT_T:
						sett->value->text = new string(value.get<string>());
						break;
					case ValueType::ENUM_T:
						try {
							sett->value->_int = value.get<int>();
						}
						catch (const exception& e) {
							logF("Config Load Error(Enum) (%s): %s ", this->getRawModuleName(), e.what());
						}
						break;
					}
					sett->makeSureTheValueIsAGoodBoiAndTheUserHasntScrewedWithIt();
					continue;
				}
				catch (exception e) {
					logF("Config Load Error (%s): %s", this->getRawModuleName(), e.what());
				}
			}
		}
		if (this->enabled)
			this->onEnable();
	}
}

#pragma warning(push)
#pragma warning(disable : 26444)
void IModule::onSaveConfig(void* confVoid) {
	json* conf = reinterpret_cast<json*>(confVoid);
	string modName = getRawModuleName();
	if (conf->contains(modName.c_str()))
		conf->erase(modName.c_str());

	json obj = {};
	//auto obj = conf->at(modName);
	for (auto sett : this->settings) {
		switch (sett->valueType) {
		case ValueType::FLOAT_T:
			obj.emplace(sett->name, sett->value->_float);
			break;
		case ValueType::DOUBLE_T:
			obj.emplace(sett->name, sett->value->_double);
			break;
		case ValueType::INT64_T:
			obj.emplace(sett->name, sett->value->int64);
			break;
		case ValueType::INT_T:
			obj.emplace(sett->name, sett->value->_int);
			break;
		case ValueType::BOOL_T:
			obj.emplace(sett->name, sett->value->_bool);
			break;
		case ValueType::TEXT_T:
			obj.emplace(sett->name, *sett->value->text);
			break;
		case ValueType::ENUM_T:
			obj.emplace(sett->name, sett->value->_int);
			break;
		}
	}
	conf->emplace(modName.c_str(), obj);
}

#pragma warning(pop)

void IModule::onLoadSettings(void* confVoid) {
	json* conf = reinterpret_cast<json*>(confVoid);
	if (conf->contains(this->getRawModuleName())) {
		auto obj = conf->at(this->getRawModuleName());
		if (obj.is_null())
			return;
		for (auto it = this->settings.begin(); it != this->settings.end(); ++it) {
			SettingEntry* sett = *it;
			if (obj.contains(sett->name)) {
				auto value = obj.at(sett->name);
				if (value.is_null())
					continue;
				try {
					switch (sett->valueType) {
					case ValueType::KEYBIND_T:
						sett->value->_keybind = value.get<int>();
						break;
					}
					sett->makeSureTheKeyValueIsAGoodBoiAndTheUserHasntScrewedWithIt();
					continue;
				}
				catch (exception e) {
					logF("Keybind Load Error (%s): %s", this->getRawModuleName(), e.what());
				}
			}
			if (obj.contains("Hidden")) {
				auto value = obj.at("Hidden");
				if (value.is_null())
					continue;
				shouldHide = value.get<bool>();
			}
		}

		for (vector<string>::iterator it = g_friend.List.begin(); it != g_friend.List.end(); ++it) {
			if (conf->contains("Friends")) {
				auto friends = conf->at("Friends");//e
				if (!friends.is_null()) {
					auto value = friends.at(it->data());
					string name = value.get < string >();
					name = Utils::sanitize(name);
					name = name.substr(0, name.find('\n'));
					if(!FriendList::findPlayer(name))
					FriendList::addPlayerToList(name);
				}
			}
		}
		if (this->enabled)
			this->onEnable();
	}
}

#pragma warning(push)
#pragma warning(disable : 26444)
void IModule::onSaveSettings(void* confVoid) {
	json* conf = reinterpret_cast<json*>(confVoid);
	string modName = getRawModuleName();
	if (conf->contains(modName.c_str()))
		conf->erase(modName.c_str());

	json obj = {};
	//auto obj = conf->at(modName);
	for (auto sett : this->settings) {
		obj.emplace("Hidden", this->shouldHide);
		switch (sett->valueType) {
		case ValueType::KEYBIND_T:
			obj.emplace(sett->name, sett->value->_keybind);
			break;
		}
	}
	json Friends = {};
	for (vector<string>::iterator it = g_friend.List.begin(); it != g_friend.List.end(); ++it)
		Friends.emplace(it->data(), (int)it->length());

	conf->emplace(modName.c_str(), obj);
	conf->emplace("Friends", Friends);
}

#pragma warning(pop)

bool IModule::isHoldMode() {
	return false;
}

void IModule::setEnabled(bool enabled) {
	if (this->enabled != enabled) {
		this->enabled = enabled;

		// Toggle Notifications
		static auto configMenu = moduleMgr->getModule<ConfigManagerMod>();
		static auto notifications = moduleMgr->getModule<Notifications>();
		static auto interfaceMod = moduleMgr->getModule<Interface>();
		static auto clickGUI = moduleMgr->getModule<ClickGUIMod>();
		static auto antiBotMod = moduleMgr->getModule<AntiBot>();
		static auto autoPlay = moduleMgr->getModule<AutoPlay>();
		static auto path = moduleMgr->getModule<FollowPath>();
		bool shouldShow = true;

		string screenName(g_Hooks.currentScreenName);
		auto player = g_Data.getLocalPlayer();
		if (player == nullptr ||
			clickGUI->isEnabled() || configMenu->isEnabled() ||
			path->isEnabled() || autoPlay->isEnabled() || isHoldMode() || strcmp(screenName.c_str(), "start_screen") == 0)
			shouldShow = false;

		if (notifications->showToggle && shouldShow && !((GameData::isKeyDown('L') && GameData::isKeyDown(VK_CONTROL)) || GameData::shouldTerminate())) {
			auto state = enabled ? " Enabled" : " Disabled";
			//auto notification = g_Data.addNotification("Notification:", string(string(state) + " " + this->getRawModuleName())); notification->duration = 3.f;
		}

		if (enabled) {
			this->onEnable();
			static auto toggleSounds = moduleMgr->getModule<ToggleSounds>();
			if (toggleSounds->isEnabled() && g_Data.getLocalPlayer() != nullptr && !((GameData::isKeyDown('L') && GameData::isKeyDown(VK_CONTROL)) || GameData::shouldTerminate())) {
				PointingStruct* level = g_Data.getLocalPlayer()->pointingStruct;

				switch (toggleSounds->sound.getSelectedValue()) {
				case 0: // Click
					level->playSound("random.click", *player->getPos(), toggleSounds->volume, 0.6); // 0.6
					break;
				case 1: // Piston
					level->playSound("tile.piston.out", *player->getPos(), toggleSounds->volume, 1);
					break;
				case 2: // Sigma
					Utils::systemPlay("Sigma_Enable.wav");
					break;
				}
			}
		}
		else {
			this->onDisable();
			static auto toggleSounds = moduleMgr->getModule<ToggleSounds>();
			if (toggleSounds->isEnabled() && g_Data.getLocalPlayer() != nullptr && !((GameData::isKeyDown('L') && GameData::isKeyDown(VK_CONTROL)) || GameData::shouldTerminate())) {
				PointingStruct* level = g_Data.getLocalPlayer()->pointingStruct;

				switch (toggleSounds->sound.getSelectedValue()) {
				case 0: // Click
					level->playSound("random.click", *player->getPos(), toggleSounds->volume, 0.5); // 0.6
					break;
				case 1: // Piston
					level->playSound("tile.piston.out", *player->getPos(), toggleSounds->volume, 1);
					break;
				case 2: // Sigma
					Utils::systemPlay("Sigma_Disable.wav");
					break;
				}
			}
		}
	}
}

void IModule::toggle() {
	setEnabled(!this->enabled);
}

bool IModule::isEnabled() {
	return this->enabled;
}

const char* IModule::getTooltip() {
	return this->tooltip;
}
void IModule::onAttack(C_Entity*) {
}
bool IModule::callWhenDisabled() {
	return false;
}
void IModule::onMove(C_MoveInputHandler*) {
}
void IModule::onLevelRender() {
}
void IModule::clientMessageF(const char* fmt, ...) {
	va_list arg;
	va_start(arg, fmt);

	char message[300];
	vsprintf_s(message, 300, fmt, arg);

	GameData::log("%s", message);

	va_end(arg);
}

void SettingEntry::makeSureTheValueIsAGoodBoiAndTheUserHasntScrewedWithIt() {
	switch (valueType) {
	case ValueType::ENUM_T:
		value->_int = max(0, min(reinterpret_cast<SettingEnum*>(extraData)->GetCount() - 1, value->_int));
		break;
	case ValueType::BOOL_T:
		break;
	case ValueType::INT64_T:
		value->int64 = max(minValue->int64, min(maxValue->int64, value->int64));
		break; 
	case ValueType::INT_T:
		value->_int = max(minValue->_int, min(maxValue->_int, value->_int));
		break;
	case ValueType::DOUBLE_T:
		value->_double = max(minValue->_double, min(maxValue->_double, value->_double));
		break;
	case ValueType::FLOAT_T:
		value->_float = max(minValue->_float, min(maxValue->_float, value->_float));
		break;
	case ValueType::TEXT_T:
		//break;
	default:
		logF("unrecognized value %i", valueType);
		break;
	}
}

void SettingEntry::makeSureTheKeyValueIsAGoodBoiAndTheUserHasntScrewedWithIt() {
	switch (valueType) {
	case ValueType::KEYBIND_T:
		value->_keybind = max(minValue->_keybind, min(maxValue->_keybind, value->_keybind));
		break;
	default:
		logF("unrecognized value %i", valueType);
		break;
	}
}