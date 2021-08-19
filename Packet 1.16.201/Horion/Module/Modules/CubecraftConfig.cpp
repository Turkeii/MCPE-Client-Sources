#include "../../Module/ModuleManager.h"
#include "CubecraftConfig.h"

CubecraftConfig::CubecraftConfig() : IModule(0, Category::MISC, "Cubecraft Config") {
}

const char* CubecraftConfig::getModuleName() {
	return "CubeCraft";
}

void CubecraftConfig::onTick(C_GameMode* gm) {  //Module settings
	auto antibotMod = moduleMgr->getModule<AntiBot>();
	antibotMod->setEnabled(true);
	antibotMod->hitboxCheck = true;
	antibotMod->nameCheck = false;
	antibotMod->invisibleCheck = true;
	antibotMod->entityIdCheck = true;
	antibotMod->otherCheck = true;
	antibotMod->extraCheck = false;
}

void CubecraftConfig::onEnable() {  //Enable/Disable Modules
	auto killauraMod = moduleMgr->getModule<Killaura>();
	killauraMod->distanceCheck = false;
	killauraMod->silent = true;
	killauraMod->isMulti = true;
	killauraMod->isMobAura = false;
	killauraMod->hurttime = false;
	killauraMod->range = 8.f;
	killauraMod->delay = 0.f;
	auto bhopMod = moduleMgr->getModule<Bhop>();
	bhopMod->speed = 0.55f;
	auto nofallMod = moduleMgr->getModule<NoFall>();
	nofallMod->motionMode = true;
	auto autoplayMod = moduleMgr->getModule<AutoPlay>();
	autoplayMod->hiveMode = false;
}