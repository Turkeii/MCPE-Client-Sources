#include "NoSlowDown.h"

#include <Windows.h>

#include "../../../Utils/Logger.h"
#include "../../../Utils/Utils.h"
NoSlowDown::NoSlowDown() : IModule(0, Category::MOVEMENT, "Don't get slowed down when blocking or eating") {
	registerEnumSetting("Mode", &noSlow, 0);
	noSlow = SettingEnum(this)
				 .addEntry(EnumEntry("Normal", 0))
				 .addEntry(EnumEntry("Spoof", 1));
	// registerBoolSetting("GuiMove", &this->guiMove, this->guiMove);
	registerBoolSetting("NoWeb", &this->noWeb, this->noWeb);
	registerBoolSetting("silentSneak", &this->silentSneak, this->silentSneak);
	registerBoolSetting("AntiImmobile", &this->antii, this->antii);
}

NoSlowDown::~NoSlowDown() {
}

const char* NoSlowDown::getModuleName() {
	return ("NoSlow");
}
const char* NoSlowDown::getModName() {
	if (noSlow.selected == 0) {
		return " [Vanilla]";
	} else {
		return " [Spoof]";
	}
}
void NoSlowDown::onMove(C_MoveInputHandler* input) {
	if (spoof)
		auto player = g_Data.getLocalPlayer();
	if (spoof)
		if ((GameData::isRightClickDown()) && GameData::canUseMoveKeys()) {
			if (spoof)
				input->forwardMovement *= 10;
			input->sideMovement *= 10;
		}
}
void NoSlowDown::onEnable() {
	if (opcode == 0 || opcode1 == 0 || opcode2 == 0 || opcode3 == 0) {
		opcode = reinterpret_cast<uint8_t*>(FindSignature("F3 0F 11 46 0C F3 0F 10 05"));
		opcode1 = reinterpret_cast<uint8_t*>(FindSignature("F3 0F 11 46 0C 41 C7"));
		opcode2 = reinterpret_cast<uint8_t*>(FindSignature("F3 0F 11 46 08 F3 0F 10 46 0C F3 0F 59 05 11"));
		opcode3 = reinterpret_cast<uint8_t*>(FindSignature("F3 0F 11 46 08 F3 0F 10 46 0C F3 0F 59 05 87"));
	}

	DWORD oldProtect = 0;
	if (!VirtualProtect(opcode, 5, PAGE_EXECUTE_READWRITE, &oldProtect)) {
#ifdef _DEBUG
		logF("couldnt unprotect memory send help");
		__debugbreak();
#endif
	} else {
		opcode[0] = 0x90;
		opcode[1] = 0x90;
		opcode[2] = 0x90;
		opcode[3] = 0x90;
		opcode[4] = 0x90;
		VirtualProtect(opcode, 5, oldProtect, &oldProtect);
	}

	if (!VirtualProtect(opcode1, 5, PAGE_EXECUTE_READWRITE, &oldProtect)) {
#ifdef _DEBUG
		logF("couldnt unprotect memory send help");
		__debugbreak();
#endif
	} else {
		opcode1[0] = 0x90;
		opcode1[1] = 0x90;
		opcode1[2] = 0x90;
		opcode1[3] = 0x90;
		opcode1[4] = 0x90;
		VirtualProtect(opcode1, 5, oldProtect, &oldProtect);
	}
	// left right 1
	if (!VirtualProtect(opcode2, 5, PAGE_EXECUTE_READWRITE, &oldProtect)) {
#ifdef _DEBUG
		logF("couldnt unprotect memory send help");
		__debugbreak();
#endif
	} else {
		opcode2[0] = 0x90;
		opcode2[1] = 0x90;
		opcode2[2] = 0x90;
		opcode2[3] = 0x90;
		opcode2[4] = 0x90;
		VirtualProtect(opcode2, 5, oldProtect, &oldProtect);
	}
	// left right 2
	if (!VirtualProtect(opcode3, 5, PAGE_EXECUTE_READWRITE, &oldProtect)) {
#ifdef _DEBUG
		logF("couldnt unprotect memory send help");
		__debugbreak();
#endif
	} else {
		opcode3[0] = 0x90;
		opcode3[1] = 0x90;
		opcode3[2] = 0x90;
		opcode3[3] = 0x90;
		opcode3[4] = 0x90;
		VirtualProtect(opcode3, 5, oldProtect, &oldProtect);
	}
}

void NoSlowDown::onDisable() {
	if (opcode == 0 || opcode1 == 0) {
		opcode = reinterpret_cast<uint8_t*>(FindSignature("F3 0F 11 46 0C F3 0F 10 05"));
		opcode1 = reinterpret_cast<uint8_t*>(FindSignature("F3 0F 11 46 0C 41 C7"));
		opcode2 = reinterpret_cast<uint8_t*>(FindSignature("F3 0F 11 46 08 F3 0F 10 46 0C F3 0F 59 05 11"));
		opcode3 = reinterpret_cast<uint8_t*>(FindSignature("F3 0F 11 46 08 F3 0F 10 46 0C F3 0F 59 05 87"));
	}

	DWORD oldProtect = 0;
	if (!VirtualProtect(opcode, 5, PAGE_EXECUTE_READWRITE, &oldProtect)) {
#ifdef _DEBUG
		logF("couldnt unprotect memory send help");
		__debugbreak();
#endif
	} else {
		opcode[0] = 0xF3;
		opcode[1] = 0x0F;
		opcode[2] = 0x11;
		opcode[3] = 0x46;
		opcode[4] = 0x0C;
		// opcode[5] = {0xF3; 0x0F, 0x11, 0x46, 0x0C};
		VirtualProtect(opcode, 5, oldProtect, &oldProtect);
	};

	if (!VirtualProtect(opcode1, 5, PAGE_EXECUTE_READWRITE, &oldProtect)) {
#ifdef _DEBUG
		logF("couldnt unprotect memory send help");
		__debugbreak();
#endif
	} else {
		opcode1[0] = 0xF3;
		opcode1[1] = 0x0F;
		opcode1[2] = 0x11;

		opcode1[3] = 0x46;

		opcode1[4] = 0x0C;
		// opcode[5] = {0xF3; 0x0F, 0x11, 0x46, 0x0C};
		VirtualProtect(opcode1, 5, oldProtect, &oldProtect);
	};

	if (!VirtualProtect(opcode2, 5, PAGE_EXECUTE_READWRITE, &oldProtect)) {
#ifdef _DEBUG
		logF("couldnt unprotect memory send help");
		__debugbreak();
#endif
	} else {
		// F3 0F 11 46 08 F3 0F 10 46 0C F3 0F 59 05 11
		opcode2[0] = 0xF3;
		opcode2[1] = 0x0F;
		opcode2[2] = 0x11;
		opcode2[3] = 0x46;
		opcode2[4] = 0x08;
		// opcode[5] = {0xF3; 0x0F, 0x11, 0x46, 0x0C};
		VirtualProtect(opcode2, 5, oldProtect, &oldProtect);
	};
	if (!VirtualProtect(opcode3, 5, PAGE_EXECUTE_READWRITE, &oldProtect)) {
#ifdef _DEBUG
		logF("couldnt unprotect memory send help");
		__debugbreak();
#endif

	} else {
		// F3 0F 11 46 08 F3 0F 10 46 0C F3 0F 59 05 87
		opcode3[0] = 0xF3;
		opcode3[1] = 0x0F;
		opcode3[2] = 0x11;
		opcode3[3] = 0x46;
		opcode3[4] = 0x08;
		// opcode[5] = {0xF3; 0x0F, 0x11, 0x46, 0x0C};
		VirtualProtect(opcode, 5, oldProtect, &oldProtect);
	};
}
void NoSlowDown::onTick(C_GameMode* gm) {
	switch (noSlow.selected) {
	default:
		spoof = false;
		break;
	case 1:
		spoof = true;
		break;
	}
	if (noWeb)
		gm->player->slowdownFactor = {0, 0, 0};
	if (silentSneak) {
		if (sneakopcode == 0) {
			sneakopcode = reinterpret_cast<uint8_t*>(FindSignature("80 7B 48 00 74 2E 48 8B 07 48 8B CF"));
		}
		DWORD oldProtect = 0;
		if (!VirtualProtect(sneakopcode, 5, PAGE_EXECUTE_READWRITE, &oldProtect)) {
		} else {
			sneakopcode[0] = 0x90;
			sneakopcode[1] = 0x90;
			sneakopcode[2] = 0x90;
			sneakopcode[3] = 0x90;
			VirtualProtect(sneakopcode, 5, oldProtect, &oldProtect);
		}
	} else if (noWeb == false) {
		DWORD oldProtect = 0;
		if (!VirtualProtect(sneakopcode, 5, PAGE_EXECUTE_READWRITE, &oldProtect)) {
		} else {
			sneakopcode[0] = 0x80;
			sneakopcode[1] = 0x7B;
			sneakopcode[2] = 0x48;
			sneakopcode[3] = 0x00;
			VirtualProtect(sneakopcode, 5, oldProtect, &oldProtect);
		}
	}
}
