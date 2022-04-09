#include "Module.h"

#include <Psapi.h>
#include <TlHelp32.h>
#include <Windows.h>
#include <conio.h>
#include <direct.h>
#include <math.h>
#include <playsoundapi.h>
#include <psapi.h>
#include <stdio.h>
#include <string.h>
#include <tchar.h>
#include <urlmon.h>
#include <windows.h>
#include <windows.h>
#include <wtsapi32.h>

#include <algorithm>
#include <chrono>
#include <cstdarg>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "../../../Memory/Hooks.h"
#include "../../../Utils/Json.hpp"
#include "../../../Utils/Logger.h"

using json = nlohmann::json;

#pragma region EnumEntry
EnumEntry::EnumEntry(const std::string _name, const unsigned char value) {
	name = _name;
	val = value;
}
EnumEntry::EnumEntry(const char* _name, const unsigned char value) {
	name = _name;
	val = value;
}
std::string EnumEntry::GetName() {
	return name;
}
unsigned char EnumEntry::GetValue() {
	return val;
}
#pragma endregion
#pragma region SettingEnum
SettingEnum::SettingEnum(std::vector<EnumEntry>& entr, IModule* mod) {
	Entrys = entr;
	owner = mod;
	std::sort(Entrys.begin(), Entrys.end(), [](EnumEntry rhs, EnumEntry lhs) {
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
		std::sort(Entrys.begin(), Entrys.end(), [](EnumEntry rhs, EnumEntry lhs) {
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
		std::sort(Entrys.begin(), Entrys.end(), [](EnumEntry rhs, EnumEntry lhs) {
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
	} else if (selected < 0) {
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
	this->registerIntSetting(std::string("keybind"), &this->keybind, this->keybind, 0, 0xFF);
	this->registerBoolSetting(std::string("enabled"), &this->enabled, false);
	this->ModulePos = vec2(0.f, 0.f);
}
void IModule::registerFloatSetting(std::string name, float* floatPtr, float defaultValue, float minValue, float maxValue) {
#ifdef DEBUG
	if (minValue > maxValue)
		__debugbreak();  // Minimum value is bigger than maximum value
#endif

	SettingEntry* setting = new SettingEntry();
	setting->valueType = ValueType::FLOAT;

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

void IModule::registerSpace(std::string name) {
	SettingEntry* setting = new SettingEntry();
	setting->valueType = ValueType::SPACE;
	strcpy_s(setting->name, 19, name.c_str());  // Name

	settings.push_back(setting);  // Add to list
}

void IModule::registerIntSetting(std::string name, int* intPtr, int defaultValue, int minValue, int maxValue) {
#ifdef DEBUG
	if (minValue > maxValue)
		__debugbreak();  // Minimum value is bigger than maximum value
#endif

	SettingEntry* setting = new SettingEntry();
	setting->valueType = ValueType::INT;
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

void IModule::registerEnumSetting(std::string name, SettingEnum* ptr, int defaultValue) {
	SettingEntry* setting = new SettingEntry();
	setting->valueType = ValueType::ENUM;
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
	setting->valueType = ValueType::ENUM;
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

void IModule::registerBoolSetting(std::string name, bool* boolPtr, bool defaultValue) {
	SettingEntry* setting = new SettingEntry();
	setting->valueType = ValueType::BOOL;

	setting->value = reinterpret_cast<SettingValue*>(boolPtr);  // Actual value

	SettingValue* defaultVal = new SettingValue();  // Default Value
	defaultVal->_bool = defaultValue;
	setting->defaultValue = defaultVal;

	strcpy_s(setting->name, 19, name.c_str());  // Name

	settings.push_back(setting);  // Add to list
}

IModule::~IModule() {
	for (auto it = this->settings.begin(); it != this->settings.end(); it++) {
		delete *it;
	}
	this->settings.clear();
}

const char* IModule::getModuleName() {
	return "Module";
}

const char* IModule::getRawModuleName() {
	return getModuleName();
}

int IModule::getKey() {
	return this->keybind;
}

void IModule::setKey(int key) {
	this->keybind = key;
}

bool IModule::allowAutoStart() {
	return true;
}
void IModule::onPreTick(C_GameMode*) {
}
void IModule::onPlayerTick(C_Player*) {
}

void IModule::onWorldTick(C_GameMode*) {
}

void IModule::onTick(C_GameMode*) {
}

void IModule::onKeyUpdate(int key, bool isDown) {
	if (key == getKey()) {
		if (isFlashMode())
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
					case ValueType::FLOAT:
						sett->value->_float = value.get<float>();
						break;
					case ValueType::DOUBLE:
						sett->value->_double = value.get<double>();
						break;
					case ValueType::INT64:
						sett->value->int64 = value.get<__int64>();
						break;
					case ValueType::INT:
					case ValueType::KEY:
						sett->value->_int = value.get<int>();
						break;
					case ValueType::BOOL:
						sett->value->_bool = value.get<bool>();
						break;
					case ValueType::TEXT:
						sett->value->text = new std::string(value.get<std::string>());
						break;
					case ValueType::ENUM:
						try {
							sett->value->_int = value.get<int>();
						} catch (const std::exception& e) {
							logF("Config Load Error(Enum) (%s): %s ", this->getRawModuleName(), e.what());
						}
						break;
					}
					sett->makeSureTheValueIsAGoodBoiAndTheUserHasntScrewedWithIt();
					continue;
				} catch (std::exception e) {
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
	std::string modName = getRawModuleName();
	if (conf->contains(modName.c_str()))
		conf->erase(modName.c_str());

	json obj = {};
	// auto obj = conf->at(modName);
	for (auto sett : this->settings) {
		switch (sett->valueType) {
		case ValueType::FLOAT:
			obj.emplace(sett->name, sett->value->_float);
			break;
		case ValueType::DOUBLE:
			obj.emplace(sett->name, sett->value->_double);
			break;
		case ValueType::INT64:
			obj.emplace(sett->name, sett->value->int64);
			break;
		case ValueType::INT:
		case ValueType::KEY:
		case ValueType::ENUM:
			obj.emplace(sett->name, sett->value->_int);
			break;
		case ValueType::BOOL:
			obj.emplace(sett->name, sett->value->_bool);
			break;
		case ValueType::TEXT:
			obj.emplace(sett->name, *sett->value->text);
			break;
		}
	}

	conf->emplace(modName.c_str(), obj);
}

#pragma warning(pop)

bool IModule::isFlashMode() {
	return false;
}

void IModule::setEnabled(bool enabled) {
	if (this->enabled != enabled) {
		this->enabled = enabled;
#ifndef _DEBUG
		if (!isFlashMode())
#endif
			logF("%s %s", enabled ? "Enabled" : "Disabled", this->getModuleName());

		// Toggle Notifications

		static auto AntiBotMod = moduleMgr->getModule<AntiBot>();
		static auto ToggleSound = moduleMgr->getModule<ToggleSounds>();
		static auto Logmsg = moduleMgr->getModule<Notifications>();
		bool shouldShow = true;

		if (Logmsg->isEnabled()) {
			g_Data.getClientInstance()->getGuiData()->displayClientMessageF("[%sNG+%s] %s%s %s%s%s", DARK_PURPLE, WHITE, GRAY, enabled ? "Enabled" : "Disabled", BOLD, WHITE, this->getModuleName());
		}
		if (enabled) {
			this->onEnable();
			if (ToggleSound->isEnabled() && !((GameData::isKeyDown('L') && GameData::isKeyDown(VK_CONTROL)) || GameData::shouldTerminate()) && g_Data.isInGame() && g_Data.getLocalPlayer() != nullptr && !isFlashMode())
				Utils::systemPlay("CustomEnable.wav");
		} else {
			this->onDisable();
			if (ToggleSound->isEnabled() && !((GameData::isKeyDown('L') && GameData::isKeyDown(VK_CONTROL)) || GameData::shouldTerminate()) && g_Data.isInGame() && g_Data.getLocalPlayer() != nullptr && !isFlashMode())
				Utils::systemPlay("CustomDisable.wav");
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
	case ValueType::ENUM:
		value->_int = std::max(0, std::min(reinterpret_cast<SettingEnum*>(extraData)->GetCount() - 1, value->_int));
		break;
	case ValueType::BOOL:
		break;
	case ValueType::INT64:
		value->int64 = std::max(minValue->int64, std::min(maxValue->int64, value->int64));
		break;
	case ValueType::DOUBLE:
		value->_double = std::max(minValue->_double, std::min(maxValue->_double, value->_double));
		break;
	case ValueType::FLOAT:
		value->_float = std::max(minValue->_float, std::min(maxValue->_float, value->_float));
		break;
	case ValueType::INT:
		value->_int = std::max(minValue->_int, std::min(maxValue->_int, value->_int));
		break;
	case ValueType::TEXT:
		// break;
	default:
		logF("unrecognized value %i", valueType);
		break;
	}
}