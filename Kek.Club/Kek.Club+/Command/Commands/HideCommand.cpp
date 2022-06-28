#include "HideCommand.h"

HideCommand::HideCommand() : IMCCommand("hide", "hide the mod", "") {
}

HideCommand::~HideCommand() {
}

bool HideCommand::execute(std::vector<std::string>* args) {
	GameData::hide();
	if (GameData::shouldHide()) {
		clientMessageF("<%Kek.Club+%s> %sHidden.", GREEN, WHITE, GREEN);
	} else {
		clientMessageF("<%Kek.Club+%s> %sMod is now visible.", GREEN, WHITE, GREEN);
	}
	return true;
}
