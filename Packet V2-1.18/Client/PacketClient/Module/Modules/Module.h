#pragma once
#include "../../../Memory/GameData.h"
#include "../../Notifications/NotificationManager.h"
#include "../../FriendList/FriendList.h"
#include "../../../Utils/TimerUtil.h"
#include "../../../Utils/MoveUtil.h"
#include "../../../Utils/keys.h"
//#include "../../DrawUtils.h"

class IModule;

enum class Category {
	COMBAT = 0,
	VISUAL = 1,
	MOVEMENT = 2,
	PLAYER = 3,
	EXPLOIT = 4,
	OTHER = 5,
	UNUSED = 6,
	CUSTOM = 7
};

enum class HudEditorCategory {
	// HudModule
	POSITION = 0,
	SPEED = 1,
	FPS = 2,
	ARMORHUD = 3,
	// Other Modules
	WATERMARK = 4,
	ARRAYLIST = 5,
	RELEASE = 6,
	TARGETHUD = 7,
	// Scaffold
	BLOCKCOUNT = 8
};

struct EnumEntry {
private:
	std::string name;
	unsigned char val;

public:
	void* ptr = nullptr;
	EnumEntry(const std::string _name, const unsigned char value);
	EnumEntry(const char* _name, const unsigned char value);
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

	SettingEnum(std::vector<EnumEntry>& entr, IModule* mod = nullptr);
	SettingEnum(IModule* mod = nullptr);
	//SettingEnum();
	SettingEnum& addEntry(EnumEntry entr);
	SettingEnum& addEntry(const char* name, int value);
	EnumEntry& GetEntry(int ind);
	EnumEntry& GetSelectedEntry();
	int GetCount();
	int getSelectedValue();
	int SelectNextValue(bool back = false);
};

enum class ValueType {
	FLOAT_T,
	DOUBLE_T,
	INT64_T,
	INT_T,
	KEYBIND_T,
	BOOL_T,
	TEXT_T,
	ENUM_T
};

struct SettingValue {
	union {
		float _float;
		double _double;
		__int64 int64;
		int _int;
		int _keybind;
		bool _bool;
		std::string* text;
		SettingEnum* Enum;
	};
};

struct SettingEntry {
	char name[0x20] = "";
	ValueType valueType;
	SettingValue* value = nullptr;
	SettingValue* defaultValue = nullptr;
	SettingValue* minValue = nullptr;
	SettingValue* maxValue = nullptr;
	void* extraData; // Only used by enum for now

	// ClickGui Data
	bool isDragging = false;  // This is incredibly hacky and i wanted to avoid this as much as possible but i want to get this clickgui done

	void makeSureTheValueIsAGoodBoiAndTheUserHasntScrewedWithIt();
	void makeSureTheKeyValueIsAGoodBoiAndTheUserHasntScrewedWithIt();
};

class IModule {
public:
	bool shouldHide = false;
	bool enabled = false;
	int keybind = 0x0;
	bool extended = false;
	float length = 0;
	vec2_t ModulePos;
private:
	Category category;
	const char* tooltip;

	std::vector<SettingEntry*> settings;

protected:
	IModule(int key, Category c, const char* tooltip);

	void registerFloatSetting(std::string name, float* floatPtr, float defaultValue, float minValue, float maxValue);
	void registerIntSetting(std::string name, int* intpTr, int defaultValue, int minValue, int maxValue);
	void registerMinMaxSetting(std::string name, int* intpTr, int defaultValue, int minValue, int maxValue);
	void registerKeybindSetting(std::string name, int* intpTr, int defaultValue, int minValue, int maxValue);
	void registerEnumSetting(std::string name, SettingEnum* intPtr, int defaultValue);
	void registerEnumSetting(const char* name, SettingEnum* intPtr, int defaultValue);
	void registerBoolSetting(std::string name, bool* boolPtr, bool defaultValue);

	void clientMessageF(const char* fmt, ...);

public:
	virtual ~IModule();

	const Category getCategory() { return category; };

	inline vec2_t* getPos() { return &ModulePos; };

	inline std::vector<SettingEntry*>* getSettings() { return &settings; };

	virtual const char* getModuleName() = 0;
	virtual const char* getRawModuleName();
	virtual int getKeybind();
	virtual void setKeybind(int key);
	virtual bool allowAutoStart();
	virtual void onPlayerTick(C_Player*);
	virtual void onWorldTick(C_GameMode*);
	virtual void onTick(C_GameMode*);
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
	virtual void onLoadSettings(void* conf);
	virtual void onSaveSettings(void* conf);
	virtual bool isHoldMode();
	virtual void setEnabled(bool enabled);
	virtual void toggle();
	virtual bool isEnabled();
	virtual void onSendPacket(C_Packet*);
	virtual bool callWhenDisabled();
	const char* getTooltip();
};