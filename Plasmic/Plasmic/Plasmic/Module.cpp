#include "Module.h"


#pragma region ClickGuiColor

ClickguiColor::ClickguiColor(float cr, float cg, float cb, float alpha, bool ShowAlpha) {
	color = MC_Color(cr, cg, cb);
	opacity = alpha;
	showAlpha = ShowAlpha;
	colors.push_back(this);
}


MC_Color ClickguiColor::getColor() {
	return MC_Color(color.r / rgbBrightness, color.g / rgbBrightness, color.b / rgbBrightness);
}

float* ClickguiColor::getTheColor() {
	static float col[4];
	col[0] = color.r / rgbBrightness;
	col[1] = color.g / rgbBrightness;
	col[2] = color.b / rgbBrightness;
	return col;
}

void ClickguiColor::setColor(float cr, float cg, float cb, float alpha) {
	color = MC_Color(cr, cg, cb);
	alpha = alpha;
}
void ClickguiColor::setRGB(bool newRGB, float newrgbSpeed) {
	isRGB = newRGB;
	rgbSpeed = newrgbSpeed;
}


void ClickguiColor::lowerBrightness(float amount, bool isSpeed) {
	if (isRGB && isSpeed) {
		rgbSpeed -= 0.002f;
		//limitations
		if (rgbSpeed < 0.0008f)
			rgbSpeed = 0.0008f;
		else if (rgbSpeed > 0.01f)
			rgbSpeed = 0.01;
		return;
	}

	if (isRGB) {
		rgbBrightness += 0.25f;
		//KNOW YOUR LIMITS
		if (rgbBrightness < 1.f)
			rgbBrightness = 1.f;
		else if (rgbBrightness > 5.f)
			rgbBrightness = 5.f;
		return;
	}

	color.r /= amount;
	color.g /= amount;
	color.b /= amount;
}
void ClickguiColor::increaseBrightness(float amount, bool isSpeed) {
	if (isRGB && isSpeed) {
		rgbSpeed += 0.002f;
		//limitations
		if (rgbSpeed < 0.0008f)
			rgbSpeed = 0.0008f;
		else if (rgbSpeed > 0.01f)
			rgbSpeed = 0.01;
		return;
	}

	if (isRGB) {
		rgbBrightness -= 0.25f;
		//KNOW YOUR LIMITS
		if (rgbBrightness < 1.f)
			rgbBrightness = 1.f;
		else if (rgbBrightness > 5.f)
			rgbBrightness = 5.f;
		return;
	}

	color.r *= amount;
	color.g *= amount;
	color.b *= amount;
}

void ClickguiColor::scrollPreset(bool dirrection) {
	colorPreset += dirrection ? 1 : -1;
	color = ClickguiColor::getPreset(colorPreset, isRGB);
}


void ClickguiColor::selectPreset(int8_t preset) {
	color = ClickguiColor::getPreset(preset, isRGB);
	colorPreset = preset;
}



MC_Color ClickguiColor::getPreset(int8_t& preset, bool& isRGB) {
	if (preset < 0)
		preset = 16;
	if (preset > 16)
		preset = 0;
	if (preset != 16)
		isRGB = false;

	switch (preset) {
	case 0:
		return MC_Color(1.f, 1.f, 1.f);
		break;
	case 1:
		return MC_Color(1.f, 1.f, 0.f);
		break;
	case 2:
		return MC_Color(1.f, 0.4f, 0.003921f);
		break;
	case 3:
		return MC_Color(1.f, 0.f, 0.f);
		break;
	case 4:
		return MC_Color(1.f, 0.f, 0.607843f);
		break;
	case 5:
		return MC_Color(0.196078f, 0.f, 0.607843f);
		break;
	case 6:
		return MC_Color(0.0f, 0.0f, 0.803921f);
		break;
	case 7:
		return MC_Color(0.f, 0.6f, 0.996078f);
		break;
	case 8:
		return MC_Color(0.f, 0.670588f, 0.003921f);
		break;
	case 9:
		return MC_Color(0.f, 0.4f, 0.f);
		break;
	case 10:
		return MC_Color(0.407843f, 0.196078f, 0.f);
		break;
	case 11:
		return MC_Color(0.6f, 0.403921f, 0.2f);
		break;
	case 12:
		return MC_Color(0.733333f, 0.733333f, 0.733333f);
		break;
	case 13:
		return MC_Color(0.533333f, 0.533333f, 0.533333f);
		break;
	case 14:
		return MC_Color(0.262745f, 0.262745f, 0.262745f);
		break;
	case 15:
		return MC_Color(0.f, 0.f, 0.f);
		break;
	case 16:
		return MC_Color(0.f, 1.f, 1.f);
		isRGB = true;
		break;
	}
	return 0;
}
#pragma endregion



#pragma region Setting
// v = value rn
//d = defalt value
//min = minimum
//max = maximum


Setting::Setting(SettingType Type, const char* Name, const char* InternalName, void* CurrentValue, void* defaultValue, void* minValue, void* maxValue, bool showInClickGui, uintptr_t onSettingChange) {
	type = Type;
	name = Name;
	internalName = InternalName;
	showInClickgui = showInClickGui;

	switch (type) {
	case SettingType::BOOL:
		vbool = (bool*)CurrentValue;
		dbool = *(bool*)defaultValue;
		*vbool = *(bool*)defaultValue;
		break;
	case SettingType::INT:
		vint = (int*)CurrentValue;
		dint = *(int*)defaultValue;
		minint = *(int*)minValue;
		maxint = *(int*)maxValue;
		*vint = *(int*)defaultValue;
		break;
	case SettingType::FLOAT:
		vfloat = (float*)CurrentValue;
		dfloat = *(float*)defaultValue;
		minfloat = *(float*)minValue;
		maxfloat = *(float*)maxValue;
		*vfloat = *(float*)defaultValue;
		break;
	case SettingType::KEYBIND:
		vKeybind = (uint16_t*)CurrentValue;
		dKeybind = *(uint16_t*)defaultValue;
		*vKeybind = *(uint16_t*)defaultValue;
		break;
	case SettingType::VEC2:
		vvec2 = (Vec2*)CurrentValue;
		dvec2 = *(Vec2*)defaultValue;
		minvec2 = *(Vec2*)minValue;
		maxvec2 = *(Vec2*)maxValue;
		*vvec2 = *(Vec2*)defaultValue;
		break;
	case SettingType::COLOR:
		vColor = (ClickguiColor*)CurrentValue;
		dColor = *(ClickguiColor*)defaultValue;
		*vColor = *(ClickguiColor*)defaultValue;
		break;
	};

	onChangeAddr = onSettingChange;
}


Setting::Setting(const Setting& os) {
	memcpy(this, &os, sizeof(Setting));
}


void Setting::closeClickgui() { selected = false; }
void Setting::callOnChange() {
	if (onChangeAddr == NULL)
		return;
	SettingChanged gamer = (SettingChanged)onChangeAddr;
	gamer(this);
}

void Setting::reset() {
	switch (type) {
	case SettingType::BOOL:
		*vbool = dbool;
		return;
	case SettingType::INT:
		*vint = dint;
		return;
	case SettingType::FLOAT:
		*vfloat = dfloat;
		return;
	case SettingType::KEYBIND:
		*vKeybind = dKeybind;
		return;
	case SettingType::VEC2:
		*vvec2 = dvec2;
		return;
	case SettingType::COLOR:
		*vColor = dColor;
		return;
	}
}

float Setting::getHeight() {
	switch (type) {
	case SettingType::BOOL:
		return 11.f;
	case SettingType::INT:
		return 18.f;
	case SettingType::FLOAT:
		return 18.f;
	case SettingType::KEYBIND:
		return 11.f;
	case SettingType::VEC2:
		return 18.f;
	case SettingType::COLOR:
		return 11.f;
	}
	return 11.f;
}


void Setting::getKeybindName(char* output) {

	switch (*vKeybind) {
	case 0:
		memcpy(output, "none", 5);
		break;
	case VK_SPACE:
		memcpy(output, "space", 6);
		break;
	case VK_MENU:
		memcpy(output, "ALT", 4);
		break;
	case VK_CONTROL:
		memcpy(output, "CTRL", 5);
		break;
	case VK_TAB:
		memcpy(output, "TAB", 4);
		break;
	case VK_INSERT:
		memcpy(output, "insert", 7);
		break;
	case VK_DELETE:
		memcpy(output, "DEL", 4);
		break;
	case VK_BACK:
		memcpy(output, "bkspac", 7);
		break;
	case VK_PRIOR:
		memcpy(output, "pgup", 5);
		break;
	case VK_NEXT:
		memcpy(output, "pgDown", 7);
		break;
	case VK_HOME:
		memcpy(output, "HOME", 5);
		break;
	case VK_END:
		memcpy(output, "END", 4);
		break;
	case VK_LSHIFT:
		memcpy(output, "SHIFT", 6);
		break;
	case VK_SHIFT:
		memcpy(output, "SHIFT", 6);
		break;
	case VK_PAUSE:
		memcpy(output, "pause", 5);
		break;
	case VK_SCROLL:
		memcpy(output, "scrLOK", 7);
		break;
	case VK_PRINT:
		memcpy(output, "prtscr", 7);
		break;
	case VK_F1:
		memcpy(output, "F1", 3);
		break;
	case VK_F2:
		memcpy(output, "F2", 3);
		break;
	case VK_F3:
		memcpy(output, "F3", 3);
		break;
	case VK_F4:
		memcpy(output, "F4", 3);
		break;
	case VK_F5:
		memcpy(output, "F5", 3);
		break;
	case VK_F6:
		memcpy(output, "F6", 3);
		break;
	case VK_F7:
		memcpy(output, "F7", 3);
		break;
	case VK_F8:
		memcpy(output, "F8", 3);
		break;
	case VK_F9:
		memcpy(output, "F9", 3);
		break;
	case VK_F10:
		memcpy(output, "F10", 4);
		break;
	case VK_F11:
		memcpy(output, "F11", 4);
		break;
	case VK_F12:
		memcpy(output, "F12", 4);
		break;
	case VK_UP:
		output[0] = '^';
		output[1] = 0;
		break;
	case VK_LEFT:
		output[0] = '<';
		output[1] = 0;
		break;
	case VK_DOWN:
		output[0] = 'v';
		output[1] = 0;
		break;
	case VK_RIGHT:
		output[0] = '>';
		output[1] = 0;
		break;
	default:
		char keyText = MapVirtualKeyA(*vKeybind, MAPVK_VK_TO_CHAR);
		output[0] = keyText;
		output[1] = 0;
	};

}



void Setting::serialize(std::ofstream& out) {
	out << internalName << ' ';

	switch (type) {
	case SettingType::BOOL:
		out << '1' << ' ' << *vbool << '\n';
		break;
	case SettingType::INT:
		out << '2' << ' ' << *vint << '\n';
		break;
	case SettingType::FLOAT:
		out << '3' << ' ' << *vfloat << '\n';
		break;
	case SettingType::KEYBIND:
		out << '4' << ' ' << *vKeybind << '\n';
		break;
	case SettingType::VEC2:
		out << '5' << ' ' << vvec2->x << ' ' << vvec2->y << '\n';
		break;
	case SettingType::COLOR:
		out << '6' << ' ' << vColor->color.r << ' ' << vColor->color.g << ' ' << vColor->color.b << ' ' << vColor->opacity << ' ';
		out << vColor->colorPreset << ' ' << vColor->isRGB << ' ' << vColor->showAlpha << ' ' << vColor->rgbSpeed << ' ' << vColor->rgbBrightness << '\n';
		break;
	};

}
void Setting::deserialize(std::ifstream& in) {
	int16_t tos = 0;// type of settings
	in >> tos;


	switch (tos) {
	case 1:
		in >> *vbool;
		type = SettingType::BOOL;
		break;
	case 2:
		in >> *vint;
		type = SettingType::INT;
		break;
	case 3:
		in >> *vfloat;
		type = SettingType::FLOAT;
		break;
	case 4:
		in >> *vKeybind;
		type = SettingType::KEYBIND;
		break;
	case 5:
		in >> vvec2->x >> vvec2->y;
		type = SettingType::VEC2;
		break;
	case 6:
		bool nooWhyAmISavingShowAlphaImSoDumbWTF = true;
		in >> vColor->color.r >> vColor->color.g >> vColor->color.b >> vColor->opacity;
		in >> vColor->colorPreset >> vColor->isRGB >> nooWhyAmISavingShowAlphaImSoDumbWTF >> vColor->rgbSpeed >> vColor->rgbBrightness;
		type = SettingType::COLOR;
		break;
	};

	callOnChange();
}
#pragma endregion



#pragma region Module

Module::Module(const char* ModuleName, uint16_t DefaultKey, const char* ShortDescription) {
	name = ModuleName;
	shortDescription = ShortDescription;

	moduleKey = DefaultKey;
	addKeybindSetting(mltext("Key", "Touche"), "Key", DefaultKey, &moduleKey, true);
}
Module::Module(const char* ModuleName, const char* ShortDescription) {
	name = ModuleName;
	shortDescription = ShortDescription;
}

	void Module::onEnable() {}
	void Module::onDisable() {}
	void Module::onEject() {}
	void Module::onTick(Gamemode* gm) {}
	void Module::onRender() {}
	void Module::onKey(uint16_t key, bool isDown, bool& cancelPress) {}
	void Module::onMouse(MouseButton button, bool isDown, bool& cancelClick) {}

	void Module::Enable() {
		if (isBlocked) {
			if (enabled)
				Disable();
			ClickGui::sendNotificationf(mltext("You cannot use %s on this server.", "Vous ne pouvez pas utiliser %s sur ce serveur."), name);
		} else {
			enabled = true; onEnable();
		}
	}
void Module::Disable() { enabled = false; onDisable(); }
bool Module::isEnabled() { return enabled; }
void Module::Toggle() { if (enabled == true) { Disable(); } else { Enable(); } }


void Module::addBoolSetting(const char* visualName, const char* InternalName, bool defaultValue, bool* currValue, bool showInClickgui, uintptr_t onSettingChange ) {
	Setting useless(SettingType::BOOL, visualName, InternalName, (void*)currValue, (void*)&defaultValue, (void*)nullptr, (void*)nullptr, showInClickgui, onSettingChange);
	settings.push_back(useless);
}
void Module::addIntSetting(const char* visualName, const char* InternalName, int defaultValue, int* currValue, int min, int max, bool showInClickgui, uintptr_t onSettingChange) {
	Setting useless(SettingType::INT, visualName, InternalName, (void*)currValue, (void*)&defaultValue, (void*)&min, (void*)&max, showInClickgui, onSettingChange);
	settings.push_back(useless);
}
void Module::addFloatSetting(const char* visualName, const char* InternalName, float defaultValue, float* currValue, float min, float max, bool showInClickgui, uintptr_t onSettingChange) {
	Setting useless(SettingType::FLOAT, visualName, InternalName, (void*)currValue, (void*)&defaultValue, (void*)&min, (void*)&max, showInClickgui, onSettingChange);
	settings.push_back(useless);
}
void Module::addKeybindSetting(const char* visualName, const char* InternalName, uint16_t defaultValue, uint16_t* currValue, bool showInClickgui, uintptr_t onSettingChange) {
	Setting useless(SettingType::KEYBIND, visualName, InternalName, (void*)currValue, (void*)&defaultValue, (void*)nullptr, (void*)nullptr, showInClickgui, onSettingChange);
	settings.push_back(useless);
}
void Module::addVec2Setting(const char* visualName, const char* InternalName, Vec2 defaultValue, Vec2* currValue, Vec2 min, Vec2 max, bool showInClickgui, uintptr_t onSettingChange) {
	Setting useless(SettingType::VEC2, visualName, InternalName, (void*)currValue, (void*)&defaultValue, (void*)&min, (void*)&max, showInClickgui, onSettingChange);
	settings.push_back(useless);
}
void Module::addColorSetting(const char* visualName, const char* InternalName, ClickguiColor defaultValue, ClickguiColor* currValue, bool showInClickgui, uintptr_t onSettingChange) {
	Setting useless(SettingType::COLOR, visualName, InternalName, (void*)currValue, (void*)&defaultValue, (void*)nullptr, (void*)nullptr, showInClickgui, onSettingChange);
	settings.push_back(useless);
}
#pragma endregion



#pragma region VisualModule

VisualModule::VisualModule(const char* ModuleName, Vec2 Position, Vec2 Size, const char* ShortDescription) {
	name = ModuleName;
	shortDescription = ShortDescription;

	pos = Position;
	size = Size;

	addVec2Setting("Position", "pos", pos, &pos, Vec2(0.f, 0.f), Vec2(10000.f, 10000.f), false);
	addVec2Setting("Size", "size", size, &size, Vec2(0.f, 0.f), Vec2(10000.f, 10000.f), false);
}

void VisualModule::onEnable() {}
void VisualModule::onDisable() {}
void VisualModule::onRender() {}
void VisualModule::onEject() {}
void VisualModule::onTick(Gamemode* gm) {}
void VisualModule::onKey(uint16_t key, bool isDown, bool& cancelPress) {}
void VisualModule::onMouse(MouseButton button, bool isDown, bool& cancelClick) {}


void VisualModule::addBoolSetting(const char* visualName, const char* InternalName, bool defaultValue, bool* currValue, bool showInClickgui, uintptr_t onSettingChange) {
	Setting useless(SettingType::BOOL, visualName, InternalName, (void*)currValue, (void*)&defaultValue, (void*)nullptr, (void*)nullptr, showInClickgui, onSettingChange);
	settings.push_back(useless);
}
void VisualModule::addIntSetting(const char* visualName, const char* InternalName, int defaultValue, int* currValue, int min, int max, bool showInClickgui, uintptr_t onSettingChange) {
	Setting useless(SettingType::INT, visualName, InternalName, (void*)currValue, (void*)&defaultValue, (void*)&min, (void*)&max, showInClickgui, onSettingChange);
	settings.push_back(useless);
}
void VisualModule::addFloatSetting(const char* visualName, const char* InternalName, float defaultValue, float* currValue, float min, float max, bool showInClickgui, uintptr_t onSettingChange) {
	Setting useless(SettingType::FLOAT, visualName, InternalName, (void*)currValue, (void*)&defaultValue, (void*)&min, (void*)&max, showInClickgui, onSettingChange);
	settings.push_back(useless);
}
void VisualModule::addKeybindSetting(const char* visualName, const char* InternalName, uint16_t defaultValue, uint16_t* currValue, bool showInClickgui, uintptr_t onSettingChange) {
	Setting useless(SettingType::KEYBIND, visualName, InternalName, (void*)currValue, (void*)&defaultValue, (void*)nullptr, (void*)nullptr, showInClickgui, onSettingChange);
	settings.push_back(useless);
}
void VisualModule::addVec2Setting(const char* visualName, const char* InternalName, Vec2 defaultValue, Vec2* currValue, Vec2 min, Vec2 max, bool showInClickgui, uintptr_t onSettingChange) {
	Setting useless(SettingType::VEC2, visualName, InternalName, (void*)currValue, (void*)&defaultValue, (void*)&min, (void*)&max, showInClickgui, onSettingChange);
	settings.push_back(useless);
}
void VisualModule::addColorSetting(const char* visualName, const char* InternalName, ClickguiColor defaultValue, ClickguiColor* currValue, bool showInClickgui, uintptr_t onSettingChange) {
	Setting useless(SettingType::COLOR, visualName, InternalName, (void*)currValue, (void*)&defaultValue, (void*)nullptr, (void*)nullptr, showInClickgui, onSettingChange);
	settings.push_back(useless);
}



void VisualModule::Enable() { enabled = true; onEnable(); }
void VisualModule::Disable() { enabled = false; onDisable(); }
bool VisualModule::isEnabled() { return enabled; }
void VisualModule::Toggle() { if (enabled == true) { enabled = false; onDisable(); } else { enabled = true; onEnable(); } }

#pragma endregion



void Hook::init() {};
void Hook::Enable() {
	if (isInit)
		MH_EnableHook((void*)hookAddress);
}
void Hook::Disable() {
	if (isInit)
		MH_DisableHook((void*)hookAddress);
}




Command::Command(const char* Name, const char* HelpMessage, bool ShowInHelp) {
		command = Name;
		helpMessage = HelpMessage;
		commandLenght = strlen(Name);
		showInHelp = ShowInHelp;
	}

	void Command::init() {}
	void Command::execute(const char* args) {}
