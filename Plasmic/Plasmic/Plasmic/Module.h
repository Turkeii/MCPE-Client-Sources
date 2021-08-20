#pragma once
class Hook;
class Module;
class VisualModule;
class Command;
class Setting;



#include "../include/MinHook.h"
#include <fstream>


#include "../SDK/sdk.h"
#include "../Utils/RenderUtils.h"

#include "Manager.h"
#include "../Utils/Logger.h"





namespace Config {

	//definition is in module manager

	extern void save(const char* name);
	extern void load(const char* name);

}



struct ClickguiColor {
private:
	int8_t colorPreset = 0;
public:
	MC_Color color = MC_Color(1.f, 1.f, 1.f);
	float opacity = 1.f;
	bool isRGB = false;
	bool showAlpha = true;
	float rgbSpeed = 0.003f;
	float rgbBrightness = 1.f;

	static std::vector<ClickguiColor*> colors;




	//it will show alpha this last setting is not used
	ClickguiColor(float cr, float cg, float cb, float alpha = 1.f, bool ShowAlpha = true);


	MC_Color getColor();
	float* getTheColor();
	void setColor(float cr, float cg, float cb, float alpha = 1.f);
	void setRGB(bool newRGB, float newrgbSpeed = 0.001f);

	void lowerBrightness(float amount, bool isSpeed = false);
	void increaseBrightness(float amount, bool isSpeed = false);

	void scrollPreset(bool dirrection);
	void selectPreset(int8_t preset);
	static MC_Color getPreset(int8_t& preset, bool& isRGB);


	friend class Setting;
};



typedef void(*SettingChanged)(class Setting* s);



// v = value rn
//d = defalt value
//min = minimum
//max = maximum

class Setting {
	Setting(SettingType Type, const char* Name, const char* InternalName, void* CurrentValue, void* defaultValue, void* minValue, void* maxValue, bool showInClickGui, uintptr_t onSettingChange);

public:

	Setting(const Setting& os);

	SettingType type = SettingType::BOOL;

	const char* name;
	const char* internalName;
	bool showInClickgui = true;
	uintptr_t onChangeAddr;


	union {
		float* vfloat;
		int* vint;
		bool* vbool;
		uint16_t* vKeybind;
		Vec2* vvec2;
		ClickguiColor* vColor;
	};

	union {
		float dfloat;
		int dint;
		bool dbool;
		uint16_t dKeybind;
		Vec2 dvec2;
		ClickguiColor dColor;
	};

	union {
		float minfloat;
		int minint;
		Vec2 minvec2;
	};

	union {
		float maxfloat;
		int maxint;
		Vec2 maxvec2;
	};

	union {
		bool selected = false;
		uint8_t selectID;
	};

	void closeClickgui();
	void reset();

	void callOnChange();

	float getHeight();
	void getKeybindName(char* output);



	void serialize(std::ofstream& out);
	void deserialize(std::ifstream& in);

	friend void Config::save(const char* name);
	friend void Config::load(const char* name);
	friend class VisualModule;
	friend class Module;
	friend class clickGui;
};


namespace ModuleManager {
	extern void BlockModuleByName(const char* ModuleName);
}

class Module {
private:
	uint16_t moduleKey;
	bool enabled = false;
	bool isBlocked = false;
	std::vector<Setting> settings;


public:
	const char* name = nullptr;
	const char* shortDescription = nullptr;
	bool isToggle = true;

	Module(const char* ModuleName, uint16_t DefaultKey, const char* ShortDescription);
	Module(const char* ModuleName, const char* ShortDescription);

	virtual void onEnable();
	virtual void onDisable();
	virtual void onEject();
	virtual void onTick(Gamemode* gm);
	virtual void onRender();
	virtual void onKey(uint16_t key, bool isDown, bool& cancelPress);
	virtual void onMouse(MouseButton button, bool isDown, bool& cancelClick);

	void Enable();
	void Disable();
	bool isEnabled();
	void Toggle();


	void addBoolSetting(const char* visualName, const char* InternalName, bool defaultValue, bool* currValue, bool showInClickgui = true, uintptr_t onSettingChange = 0);
	void addIntSetting(const char* visualName, const char* InternalName, int defaultValue, int* currValue, int min, int max, bool showInClickgui = true, uintptr_t onSettingChange = 0);
	void addFloatSetting(const char* visualName, const char* InternalName, float defaultValue, float* currValue, float min, float max, bool showInClickgui = true, uintptr_t onSettingChange = 0);
	void addKeybindSetting(const char* visualName, const char* InternalName, uint16_t defaultValue, uint16_t* currValue, bool showInClickgui = true, uintptr_t onSettingChange = 0);
	void addVec2Setting(const char* visualName, const char* InternalName, Vec2 defaultValue, Vec2* currValue, Vec2 min, Vec2 max, bool showInClickgui = true, uintptr_t onSettingChange = 0);
	void addColorSetting(const char* visualName, const char* InternalName, ClickguiColor defaultValue, ClickguiColor* currValue, bool showInClickgui = true, uintptr_t onSettingChange = 0);
	


	friend void BlockModules();
	friend void ModuleManager::BlockModuleByName(const char* ModuleName);
	friend void Config::save(const char* name);
	friend void Config::load(const char* name);
	friend void onKeyHook(uint16_t key, bool isDown);
	friend class ClickGui;
};



class VisualModule {
private:
	bool isDragging = false;

	bool enabled = false;
	std::vector<Setting> settings;

public:
	Vec2 pos;
	Vec2 size;

	const char* name = nullptr;
	const char* shortDescription = nullptr;

	VisualModule(const char* ModuleName, Vec2 Position, Vec2 Size, const char* ShortDescription);

	virtual void onEnable();
	virtual void onDisable();
	virtual void onRender();
	virtual void onEject();
	virtual void onTick(Gamemode* gm);
	virtual void onKey(uint16_t key, bool isDown, bool& cancelPress);
	virtual void onMouse(MouseButton button, bool isDown, bool& cancelClick);


	void addBoolSetting(const char* visualName, const char* InternalName, bool defaultValue, bool* currValue, bool showInClickgui = true, uintptr_t onSettingChange = 0);
	void addIntSetting(const char* visualName, const char* InternalName, int defaultValue, int* currValue, int min, int max, bool showInClickgui = true, uintptr_t onSettingChange = 0);
	void addFloatSetting(const char* visualName, const char* InternalName, float defaultValue, float* currValue, float min, float max, bool showInClickgui = true, uintptr_t onSettingChange = 0);
	void addKeybindSetting(const char* visualName, const char* InternalName, uint16_t defaultValue, uint16_t* currValue, bool showInClickgui = true, uintptr_t onSettingChange = 0);
	void addVec2Setting(const char* visualName, const char* InternalName, Vec2 defaultValue, Vec2* currValue, Vec2 min, Vec2 max, bool showInClickgui = true, uintptr_t onSettingChange = 0);
	void addColorSetting(const char* visualName, const char* InternalName, ClickguiColor defaultValue, ClickguiColor* currValue, bool showInClickgui = true, uintptr_t onSettingChange = 0);



	void Enable();
	void Disable();
	bool isEnabled();
	void Toggle();

	friend void Config::save(const char* name);
	friend void Config::load(const char* name);
	friend class ClickGui;
};


class Hook {
public:
	uintptr_t hookAddress = 0;

	bool isInit = false;
	const char* name = nullptr;

	virtual void init();


	void Enable();
	void Disable();
};



class Command {

public:
	const char* command = "DefaultCommandName.... oops";
	const char* helpMessage = "Default help message.... oops";
	size_t commandLenght = 0;
	bool showInHelp = true;

	Command(const char* Name, const char* HelpMessage, bool showInHelp = true);

	virtual void init();
	virtual void execute(const char* args);
};