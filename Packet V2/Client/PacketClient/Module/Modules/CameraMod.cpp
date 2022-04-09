#include "CameraMod.h"

CameraMod::CameraMod() : IModule(0, Category::VISUAL, "DeiDeeDeiDerrtDord") {
	this->registerBoolSetting("NoHurtcam", &this->nohurtMode, this->nohurtMode);
	this->registerBoolSetting("Fullbright", &this->fullbright, this->fullbright);
	this->registerIntSetting("FBAmount", &this->fbAmount, this->fbAmount, -25, 25);
}

const char* CameraMod::getModuleName() {
	return "Camera";
}

float originalGamma = -1;

void CameraMod::onTick(C_GameMode* gm) {
	if (fullbright) {
		if (gammaPtr != nullptr && *gammaPtr != 10)
			*gammaPtr = 10;
	}
}

void CameraMod::onEnable() {
	if (fullbright) {
		if (gammaPtr != nullptr) {
			originalGamma = *gammaPtr;
			*gammaPtr = 10;
		}
	}
}

void CameraMod::onDisable() {
	if (fullbright) {
		if (gammaPtr != nullptr) {
			if (originalGamma >= 0 && originalGamma <= 1)
				*gammaPtr = originalGamma;
			else
				*gammaPtr = 0.5f;
		}
	}
}