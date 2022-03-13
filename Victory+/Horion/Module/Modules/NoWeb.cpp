#include "NoWeb.h"

NoWeb::NoWeb() : IModule(0, Category::MOVEMENT, "Ignore cobwebs slowdown") {
	//this->registerFloatSetting("Speed", &this->speed, this->speed, 0, 10);
	//this->registerFloatSetting("YSpeed", &this->y, this->y, 0, 10);
}

NoWeb ::~NoWeb() {
}

const char* NoWeb::getModuleName() {
	return ("NoSpiderWeb");
}

void NoWeb::onTick(C_GameMode* gm) {
	gm->player->slowdownFactor = {speed, y, speed};
	//gm->player->web = 0.f;
}
