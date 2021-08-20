#include "EditionFaker.h"

EditionFaker::EditionFaker() : IModule(0x0, Category::MISC, "Fakes your device to IOS") {
}

EditionFaker::~EditionFaker() {
}

int EditionFaker::getFakedEditon() {
	// static const char* gameEditons[] = { "Unknown - 0", "Android - 1", "iOS - 2", "macOS - 3", "FireOS - 4", "GearVR - 5", "HoloLens - 6", "Windows 10 (PC) - 7", "Windows - 8", "Dedicated - 9", "Orbis - 10", "NX - 11" };

	return 2;  // IOS
}

const char* EditionFaker::getModuleName() {
	return ("EditionFaker");
}
