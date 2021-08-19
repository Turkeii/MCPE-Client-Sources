#pragma once

#include <tuple>

#include "../../../Memory/GameData.h"
#include "../../FriendList/FriendList.h"
//#include "../../DrawUtils.h"
#include "../../../SDK/COption.h"
#include "../../../Utils/keys.h"

class IModule;

enum class Category {
	COMBAT = 0,
	VISUAL = 1,
	HUD = 7,
	MOVEMENT = 2,
	PLAYER = 3,
	WORLD = 4,
	MISC = 5,
	CUSTOM = 6
};

struct EnumEntry {
private:
	/*const */ std::string name;
	/*const */ unsigned char val;

public:
	/// <summary>Use this however you want</summary>
	void* ptr = nullptr;
	EnumEntry(const std::string _name, const unsigned char value);

	/*operator*/ EnumEntry(std::tuple<int, std::string> value);
	/*operator*/ EnumEntry(std::tuple<int, std::string, void*> value);
	std::string GetName();
	unsigned char GetValue();
};

struct AddResult;

class SettingEnum {
private:
	IModule* owner = nullptr;

public:
	std::vector<EnumEntry> Entrys;
	int selected = -1;

	SettingEnum(std::vector<EnumEntry> entr, IModule* mod = nullptr);
	SettingEnum(IModule* mod, std::vector<EnumEntry> entr);
	SettingEnum(IModule* mod = nullptr);
	//SettingEnum();
	SettingEnum& addEntry(EnumEntry entr);
	EnumEntry& GetEntry(int ind);
	EnumEntry& GetSelectedEntry();
	int GetCount();
};

enum class ValueType {
	FLOAT_T,   // A float setting with a slider.
	DOUBLE_T,  // A double setting with a slider.
	INT64_T,   // An int64 setting with a slider.
	INT_T,     // An int setting with a slider.
	BOOL_T,    // A bool setting with a checkbox. Click it to toggle.
	TEXT_T,    // A string setting. You can type text into it.
	ENUM_T,

	//BUTTON_T,        // A button that does something
	//COLOR_PICKER_T,  // A simple color picker menu
	KEYBIND_T,  // A keybind menu
				//MODE_T,          // A multiple choice setting that can rotate between different predefined values.

	SETTING_GROUP_T,       // An expandable setting group. Any settings may be added to it.
	BOOL_SETTING_GROUP_T,  // An expandable setting group combined with a bool setting.
	ENUM_SETTING_GROUP_T,  // An expandable setting group combined with a mode setting. Each mode has its own setting group.
};

struct SettingValue {
	union {
		float _float;
		double _double;
		__int64 int64;
		int _int;
		bool _bool;
		std::string* text;
		SettingEnum* Enum;
	};
};

struct SettingEntry;

class SettingGroup {
private:
public:
	bool isExpanded = false;

	std::vector<SettingEntry*> entries;
	SettingEntry* parent;

	SettingEntry* registerFloatSetting(std::string name, float* floatPtr, float defaultValue, float minValue, float maxValue);
	SettingEntry* registerIntSetting(std::string name, int* intpTr, int defaultValue, int minValue, int maxValue);

	SettingEntry* registerEnumSetting(std::string name, SettingEnum* intPtr, int defaultValue);
	SettingEntry* registerEnumSettingGroup(std::string name, SettingEnum* enumPtr, int defaultValue);

	SettingEntry* registerBoolSetting(std::string name, bool* boolPtr, bool defaultValue);

	SettingEntry* registerKeybindSetting(std::string name, int* intPtr, int defaultValue);

	void onSaveConfig(void* json);
	void onLoadConfig(void* json);

	SettingGroup(SettingEntry* _parent) : entries(), parent(_parent) {}
	SettingGroup() : entries(), parent(nullptr) {}
};

struct SettingEntry {
	char name[0x20] = "";
	ValueType valueType;
	SettingValue* value = nullptr;
	SettingValue* defaultValue = nullptr;
	SettingValue* minValue = nullptr;
	SettingValue* maxValue = nullptr;
	void* extraData;

	int nestValue = 0;

	std::vector<SettingGroup*> groups;

	// ClickGui Data
	bool isDragging = false;  // This is incredibly hacky and i wanted to avoid this as much as possible but i want to get this clickgui done

	void makeSureTheValueIsAGoodBoiAndTheUserHasntScrewedWithIt();

	SettingEntry* addSettingGroup(int _enum, SettingGroup* group);
	SettingEntry* addSettingGroup(SettingGroup* group);

	std::vector<SettingEntry*> getAllExtendedSettings() {
		std::vector<SettingEntry*> vec;
		if (groups.empty())
			return vec;

		if (valueType == ValueType::ENUM_SETTING_GROUP_T) {
			int i = value->_int;

			if (groups[i] == nullptr)
				return vec;

			if (!groups[i]->isExpanded)
				return vec;

			for (auto it : groups[i]->entries) {
				vec.push_back(it);
				auto vec2 = it->getAllExtendedSettings();

				vec.reserve(vec.size() + vec2.size());
				vec.insert(vec.end(), vec2.begin(), vec2.end());
			}
		} else if (groups[0] != nullptr) {
			if (!groups[0]->isExpanded)
				return vec;

			for (auto it : groups[0]->entries) {
				vec.push_back(it);
				auto vec2 = it->getAllExtendedSettings();

				vec.reserve(vec.size() + vec2.size());
				vec.insert(vec.end(), vec2.begin(), vec2.end());
			}
		}

		return vec;
	};
};

class IModule {
private:
	bool enabled = false;
	int keybind = 0x0;
	bool extended = false;
	vec2_t ModulePos;
	bool visible = true;

private:
	Category category;
	const char* tooltip;

	std::vector<SettingEntry*> settings;

protected:
	IModule(int key, Category c, const char* tooltip);

	void registerFloatSetting(std::string name, float* floatPtr, float defaultValue, float minValue, float maxValue);
	SettingEntry* registerIntSetting(std::string name, int* intpTr, int defaultValue, int minValue, int maxValue);
	void registerEnumSetting(std::string name, SettingEnum* intPtr, int defaultValue);
	SettingEntry* registerEnumSettingGroup(std::string name, SettingEnum* enumPtr, int defaultValue);
	void registerBoolSetting(std::string name, bool* boolPtr, bool defaultValue);

	SettingEntry* registerKeybindSetting(std::string name, int* intPtr, int defaultValue);

	void clientMessageF(const char* fmt, ...);

public:
	virtual ~IModule();

	const Category getCategory() { return category; };

	inline vec2_t* getPos() { return &ModulePos; };

	inline std::vector<SettingEntry*>* getSettings() { return &settings; };
	inline bool isVisibleInArrayList() { return visible; };

	virtual const char* getModuleName() = 0;
	virtual const char* getRawModuleName();
	virtual int getKeybind();
	virtual void setKeybind(int key);
	virtual bool allowAutoStart();

	virtual void onTick(C_GameMode*);
	virtual void onPreTick(C_GameMode*);
	virtual void onKeyUpdate(int key, bool isDown);
	virtual void onEnable();
	virtual void onDisable();
	virtual void onAttack(C_Entity*);
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx);
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx);
	virtual void onLevelRender();
	virtual void onMove(C_MoveInputHandler*);
	virtual void onLoadConfig(void* conf);
	virtual void onSaveConfig(void* conf);
	virtual bool isFlashMode();
	virtual void setEnabled(bool enabled);
	virtual void toggle();
	virtual bool isEnabled();
	virtual void onSendPacket(C_Packet*);
	virtual bool callWhenDisabled();
	virtual void onOptionsTick(C_Option** optionList);
	const char* getTooltip();
};
