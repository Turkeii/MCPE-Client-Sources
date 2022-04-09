#include "HideCommand.h"

HideCommand::HideCommand() : IMCCommand("hide", "hide the mod", "") {
}

HideCommand::~HideCommand() {
}

bool HideCommand::execute(std::vector<std::string>* args) {
	GameData::hide();
	if (GameData::shouldHide()) {
		clientMessageF("[Packet] %sHidden.", GREEN);
	} else {
		clientMessageF("[Packet] %sClient is now visible.", GREEN);
	}
	return true;
}