#include "InputHook.h"
using namespace ModuleManager;


typedef void(*_onKey)(uint16_t key, bool isDown);
_onKey oonKey;
#define EJECT_KEY 'L'
extern void Eject(HMODULE hm);



bool ctrlPushed = false;


void onKeyHook(uint16_t key, bool isDown) {
	bool Cancel = false;
	

	if (key == VK_CONTROL)
		ctrlPushed = isDown;
	//if (key == VK_MENU)
	//	altPushed = isDown;
	//if (key == VK_SHIFT)
	//	shiftPushed = isDown;

	if (key == EJECT_KEY && ctrlPushed == true) {
		HANDLE WarningGoByeBye = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Eject, mem::g_hModule, 0, 0);
		if (WarningGoByeBye != NULL)
			CloseHandle(WarningGoByeBye);
		return oonKey(key, isDown);
	}


	//ClickGui onKey
	if (isDown)
		if (game::clickGui != nullptr) 
			if ((game::clickGui->key == key || key == VK_INSERT) && game::clickGui->isEnabled() == false && game::minecraftGame->canMoveCamera)
				game::clickGui->Enable();
			else if (game::clickGui->isEnabled())
				game::clickGui->onKey(key, isDown, Cancel);

	
	//Module activation
	if (game::minecraftGame == NULL)
		return;
	if (game::minecraftGame->canMoveCamera) //only in game, not in the chat
		if (isDown == true) {
			for (uint16_t i = 0; moduleList.size() > i; i++)
				if (moduleList[i] != nullptr)
					if (moduleList[i]->moduleKey == key)
						moduleList[i]->Toggle();
		} else 
			for (uint16_t i = 0; moduleList.size() > i; i++)
				if (moduleList[i] != nullptr)
					if (moduleList[i]->moduleKey == key && !moduleList[i]->isToggle)
						moduleList[i]->Disable();
		
		
	for (uint16_t i = 0; moduleList.size() > i; i++) {
		if (moduleList[i] != nullptr)
			if (moduleList[i]->isEnabled())
				moduleList[i]->onKey(key, isDown, Cancel);
	}
	for (uint16_t i = 0; visualModuleList.size() > i; i++) {
		if (visualModuleList[i] != nullptr)
			if (visualModuleList[i]->isEnabled())
				visualModuleList[i]->onKey(key, isDown, Cancel);
	}

	if (!Cancel)
		return oonKey(key, isDown);
}

void KeyboardHook::init() {
	name = "KeyboardHook";

	uintptr_t hookAddress = mem::FindSignature("48 89 5C 24 ?? ?? 48 83 EC ?? 8B 05 ?? ?? ?? ?? 8B DA");
	if (hookAddress == NULL) {
		Logf("Unable to hook!\n Sig of %s is broken", name);
		return;
	}
	Logf("%s: %p", name, (void*)hookAddress);

	isInit = true;

	MH_CreateHook((LPVOID)hookAddress, (LPVOID)onKeyHook, (LPVOID*)&oonKey);
	MH_EnableHook((LPVOID)hookAddress);
}


typedef void(*_onMouse)(uintptr_t arg1, int8_t pressedButton, int8_t dirrection, int16_t mouseX, int16_t mouseY, int16_t idk1, int16_t idk2, char ok);
_onMouse oonMouse;
uint16_t leftclickCalc[10] = { 0 };
uint16_t rightclickCalc[10] = { 0 };


#ifdef _1_16_40
typedef __int64(*_oldOnMouse)(__int64 a1, struct Inputs* input, __int64 a3, __int64 a4);
_oldOnMouse ooldonMouse;
#endif


extern volatile bool GMH_WaitForRightclick;
#ifndef _1_16_40
void onMouseHook(uintptr_t arg1, int8_t pressedButton, int8_t dirrection, int16_t mouseX, int16_t mouseY, int16_t idk1, int16_t idk2, char ok) {
#else
bool onMouseHook(int8_t pressedButton, int8_t dirrection) {
#endif // !_1_16_40
	bool Cancel = false;
	
	MouseButton button = (MouseButton)(int)pressedButton;
	bool isdown;

	switch (pressedButton) {
	case 0:
#ifdef _1_16_40
		return false;
#else
			return oonMouse(arg1, pressedButton, dirrection, mouseX, mouseY, idk1, idk2, ok);
#endif
	case 1:
		button = MouseButton::LEFT;
		isdown = dirrection == 1;
		break;
	case 2:
		button = MouseButton::RIGHT;
		isdown = dirrection == 1;
		break;
	case 3:
		button = MouseButton::MIDDLE;
		isdown = dirrection == 1;
		break;
	case 4:
		button = MouseButton::SCROLL;
		isdown = dirrection < 0;
		break;
	}

	if (game::clickGui != nullptr)
		if (game::clickGui->isEnabled())
			game::clickGui->onMouse(button, isdown, Cancel);

	//cps calc
	if (button == MouseButton::LEFT)
		if (isdown)
			for (uint8_t i = 0; i < 10; i++)
				leftclickCalc[i]++;
	if (button == MouseButton::RIGHT)
		if (isdown)
			for (uint8_t i = 0; i < 10; i++)
				rightclickCalc[i]++;


	for (uint16_t i = 0; moduleList.size() > i; i++) {
		if (moduleList[i] != nullptr)
			if (moduleList[i]->isEnabled())
				moduleList[i]->onMouse(button, isdown, Cancel);
	}
	for (uint16_t i = 0; visualModuleList.size() > i; i++) {
		if (visualModuleList[i] != nullptr)
			if (visualModuleList[i]->isEnabled())
				visualModuleList[i]->onMouse(button, isdown, Cancel);
	}


	GMH_WaitForRightclick = true;
#ifndef _1_16_40
	if (!Cancel)
		return oonMouse(arg1, pressedButton, dirrection, mouseX, mouseY, idk1, idk2, ok);
#else
	return Cancel;
#endif
}

#ifdef _1_16_40
struct Inputs {
private:
	char pad_0000[72]; //0x0000
public:
	int8_t scrollDirrection; //0x0048
private:
	char pad_0049[3]; //0x0049
public:
	int8_t button; //0x004C
private:
	char pad_004D[11]; //0x004D
public:
	int8_t inputButton; //0x0058
private:
	//char pad_0059[20]; //0x0059
}; //Size: 0x0144

bool moveInputInit = false;
Inputs moveInput;

__int64 oldMouseHook(__int64 a1, Inputs* input, __int64 a3, __int64 a4) {
	bool Cancel = false;


	switch (input->inputButton) {
	case 0:
		if (input->scrollDirrection == 0) {
			memcpy(&moveInput, input, sizeof(input));
			moveInputInit = true;
			break;
		}
		Cancel = onMouseHook(4, input->scrollDirrection);
		break;
	case 1:
		Cancel = onMouseHook(1, true);
		break;
	case 2:
		Cancel = onMouseHook(1, false);
		break;
	case 3:
		Cancel = onMouseHook(2, true);
		break;
	case 4:
		Cancel = onMouseHook(2, false);
		break;
	case 5:
		Cancel = onMouseHook(3, true);
		break;
	case 6:
		Cancel = onMouseHook(3, false);
		break;
	}

	if (Cancel && moveInputInit) {
		memcpy(input, &moveInput, sizeof(Inputs));
	}


	return ooldonMouse(a1, input, a3, a4);
}
#endif


void MouseHook::init() {
	name = "MouseHook";
#ifndef _1_16_40
	uintptr_t hookAddress = mem::FindSignature("48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 57 41 54 41 55 41 56 41 57 48 83 EC 60 44 0F B7 BC 24 ?? ?? ?? ?? 48 8B D9 44 0F B7 A4 24");
#else
	uintptr_t hookAddress = mem::FindSignatureInModule("Windows.UI.dll", "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 F9 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 45 EF 48 8B 85 ?? ?? ?? ?? 4D 8B F0 4C 8B 65 6F");
#endif

	if (hookAddress == NULL) {
		Logf("Unable to hook!\n Sig of %s is broken", name);
		return;
	}
	Logf("%s: %p", name, (void*)hookAddress);

	isInit = true;

#ifndef _1_16_40
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)onMouseHook, (LPVOID*)&oonMouse);
#else
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)oldMouseHook, (LPVOID*)&ooldonMouse);
#endif // !_1_16_40
}