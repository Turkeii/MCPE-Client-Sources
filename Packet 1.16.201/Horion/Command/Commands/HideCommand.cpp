#include "HideCommand.h"

HideCommand::HideCommand() : IMCCommand("hide", "hide the mod", "") {
}

HideCommand::~HideCommand() {
}

bool HideCommand::execute(std::vector<std::string>* args) {
	GameData::hide();
	if (GameData::shouldHide()) {
		clientMessageF("[%sPacket%s] %sHidden.", GRAY, WHITE, GREEN);
	} else {
		clientMessageF("[%sPacket%s] %sClient is now visible.", GRAY, WHITE, GREEN);
	}
	return true;
}