#include "HideCommand.h"

HideCommand::HideCommand() : IMCCommand("hide", "hide the mod", "") {
}

HideCommand::~HideCommand() {
}

bool HideCommand::execute(std::vector<std::string>* args) {
	GameData::hide();
	if (GameData::shouldHide()) {
		clientMessageF("[%sKaeru Vxint%s] %sHidden.", DARK_PURPLE, WHITE, GREEN);
	} else {
		clientMessageF("[%sKaeru Vxint%s] %sMod is now visible.", DARK_PURPLE, WHITE, GREEN);
	}
	return true;
}
