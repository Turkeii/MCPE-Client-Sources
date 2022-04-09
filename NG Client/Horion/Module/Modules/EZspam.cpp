#include "../../Module/ModuleManager.h"
#include "EZspam.h"

//Private this; Made by eKowz
EZspam::EZspam() : IModule(0x0, Category::SERVER, "Spams with no silent mute: use both sliders at 10") {

			registerEnumSetting("Mode", &mode, 0);
			mode = SettingEnum(this)
		   .addEntry(EnumEntry("AutoEZ: Toxic", 0))
		   .addEntry(EnumEntry("AutoEZ: Lag", 1))
		   .addEntry(EnumEntry("AutoEZ: Spam", 2));

	registerIntSetting("EnabledLength", &onLength, onLength, 1, 30);
	registerIntSetting("DisabledLength", &offLength, offLength, 1, 30);
}

const char* EZspam::getModuleName() {
	return "EZspam";
}

void EZspam::onEnable() {
	timer1 = 0;
	timer2 = 0;
}

bool EZspam::isFlashMode() {
		return false;
}

void EZspam::onTick(C_GameMode* gm) {
	auto autoEZ = moduleMgr->getModule<AutoEZ>();
	auto autoEZv2 = moduleMgr->getModule<AutoEZv2>();
	auto autoEZv3 = moduleMgr->getModule<AutoEZv3>();
	if (!blinkBool1) {
		timer1++;
		if (timer1 >= offLength) {
			blinkBool1 = true;
			if (mode.selected == 0) {
				if (autoEZ->isEnabled()) autoEZ->setEnabled(false);
			}
			if (mode.selected == 1) {
				if (autoEZv2->isEnabled()) autoEZv2->setEnabled(false);
			}
			if (mode.selected == 2) {
				if (autoEZv3->isEnabled()) autoEZv3->setEnabled(false);
			}
			timer1 = 0;
		}
	} else {
		timer2++;
		if (timer2 >= onLength) {
			blinkBool1 = false;
			if (mode.selected == 0) {
				if (!autoEZ->isEnabled()) autoEZ->setEnabled(true);
			}
			if (mode.selected == 1) {
				if (!autoEZv2->isEnabled()) autoEZv2->setEnabled(true);
			}
			if (mode.selected == 2) {
				if (!autoEZv3->isEnabled()) autoEZv3->setEnabled(true);
			}
			timer2 = 0;
		}
	}
}

void EZspam::onMove(C_MoveInputHandler* input) {
}

void EZspam::onDisable() {
	auto autoEZ = moduleMgr->getModule<AutoEZ>();
	auto autoEZv2 = moduleMgr->getModule<AutoEZv2>();
	auto autoEZv3 = moduleMgr->getModule<AutoEZv3>();
	if (autoEZ->isEnabled()) autoEZ->setEnabled(false);
	if (autoEZv2->isEnabled()) autoEZv2->setEnabled(false);
	if (autoEZv3->isEnabled()) autoEZv3->setEnabled(false);
	timer1 = 0;
	timer2 = 0;
}

void EZspam::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
}
