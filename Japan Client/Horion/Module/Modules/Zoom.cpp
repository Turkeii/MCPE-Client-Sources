#include "Zoom.h"

Zoom::Zoom() : IModule('C', Category::VISUAL, "Zoom in or out!") {
	registerFloatSetting("Strength", &strength, strength, -100.f, 100.f);
	registerBoolSetting("Smooth", &smooth, smooth);
}

Zoom::~Zoom() {
}

bool Zoom::isFlashMode() {
	return true;
}

const char* Zoom::getModuleName() {
	return ("Zoom");
}

void Zoom::onEnable() {
	zooming = true;
}

void Zoom::onDisable() {
	target = g_Data.fov;
}
