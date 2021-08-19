#include "EditionFaker.h"

EditionFaker::EditionFaker() : IModule(0, Category::MISC, "Fakes your device to android") {
}

EditionFaker::~EditionFaker() {
}

int EditionFaker::getFakedEditon() {
	static const char* gameEditons[] = {"Android"};

	return 1;  // Android
}

const char* EditionFaker::getModuleName() {
	return ("EditionFaker");
}
