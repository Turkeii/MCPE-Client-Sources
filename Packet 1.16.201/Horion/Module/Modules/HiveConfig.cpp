#include "HiveConfig.h"

#include "../../Module/ModuleManager.h"

HiveConfig::HiveConfig() : IModule(0, Category::MISC, "Hive") {
	//registerBoolSetting("Auto Play", &this->autoPlay, this->autoPlay);
	registerBoolSetting("Cubecraft", &this->ccconfigMode, this->ccconfigMode);
	registerBoolSetting("Hive", &this->hiveconfigMode, this->hiveconfigMode);
}

const char* HiveConfig::getModuleName() {
	return "AutoConfig";
}

void HiveConfig::onTick(C_GameMode* gm) {
	if (ccconfigMode) {
		auto targetstrafeMod = moduleMgr->getModule<TargetStrafe>();
		auto flyMod = moduleMgr->getModule<Glide>();
		auto scaffoldMod = moduleMgr->getModule<Scaffold>();
		targetstrafeMod->speedMod = 0.39f;
		scaffoldMod->timer = 20.f;
		scaffoldMod->towerMode = false;
		flyMod->speed = 1.f;
		auto bhopMod = moduleMgr->getModule<Bhop>();
		bhopMod->speed = 0.39f;
		bhopMod->timer = 21.f;
		auto antibotMod = moduleMgr->getModule<AntiBot>();
		antibotMod->setEnabled(true);
		antibotMod->hitboxCheck = true;
		antibotMod->nameCheck = false;
		antibotMod->invisibleCheck = true;
		antibotMod->entityIdCheck = true;
		antibotMod->otherCheck = true;
		antibotMod->extraCheck = false;
	}
	if (hiveconfigMode) {
		auto killauraMod = moduleMgr->getModule<Killaura>();
		killauraMod->distanceCheck = true;
		killauraMod->silent = false;
		killauraMod->isMulti = true;
		killauraMod->cock = false;
		killauraMod->rot = true;
		killauraMod->isMobAura = false;
		killauraMod->hurttime = false;
		killauraMod->range = 4.2566f;
		killauraMod->delay = 2.f;
		auto targetstrafeMod = moduleMgr->getModule<TargetStrafe>();
		targetstrafeMod->speedMod = 0.445f;
		auto bhopMod = moduleMgr->getModule<Bhop>();
		bhopMod->speed = 0.445f;
		auto antibotMod = moduleMgr->getModule<AntiBot>();
		antibotMod->setEnabled(true);
		antibotMod->hitboxCheck = true;
		antibotMod->nameCheck = false;
		antibotMod->invisibleCheck = true;
		antibotMod->entityIdCheck = true;
		antibotMod->otherCheck = true;
		antibotMod->extraCheck = false;
	}
	if (autoPlay) {
		if (strcmp(g_Data.getRakNetInstance()->serverIp.getText(), "geo.hivebedrock.network") == 0) {
			g_Data.getGuiData()->displayClientMessageF("Sending you to the next game");
		}
	}
}

void HiveConfig::onEnable() {
	if (ccconfigMode) {
		auto stepMod = moduleMgr->getModule<Step>();
		if (stepMod->isEnabled()) {
			stepMod->setEnabled(false);
		}
	}
}

void HiveConfig::onDisable() {
}