#include "EditionFaker.h"

EditionFaker::EditionFaker() : IModule(0, Category::MISC, "Fakes your edition") {
	registerIntSetting("Edition", &edition, edition, 0, 11);
	registerBoolSetting("Random Edition", &this->RandomEdition, this->RandomEdition);
}

EditionFaker::~EditionFaker() {
}

int min = 0;
int max = 11;

int EditionFaker::getFakedEditon() {
	// static const char* gameEditons[] = { "Unknown", "Android", "iOS", "macOS", "FireOS", "GearVR", "HoloLens", "Windows 10 (PC)", "Windows", "Dedicated", "Orbis", "NX" };

	if (RandomEdition && turn == 0) {
		int jim = (int)(rand() % ((max - min) + min));
		turn = 1;
		return jim;
	} else {
		return edition;
	}
}

void EditionFaker::onDisable() {
	turn == 0;
}

const char* EditionFaker::getModuleName() {
	return ("EditionFaker");
}
