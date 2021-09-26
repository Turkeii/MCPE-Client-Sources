#include "SuperSaiyan.h"

SuperSaiyan::SuperSaiyan() : IModule(0x0, Category::MISC, "Fukin Insane") {
}

SuperSaiyan::~SuperSaiyan() {
}

const char* SuperSaiyan::getModuleName() {
	return ("SuperSaiyan");
}

void SuperSaiyan::onLevelRender() {
auto player = g_Data.getLocalPlayer();
	player->animateHurt();
	player->yawUnused1 = 360;
	player->bodyYaw = 360;
	player->pitch = 360;
}