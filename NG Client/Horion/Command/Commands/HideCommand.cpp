#include "HideCommand.h"
#include "../../Module/ModuleManager.h"

HideCommand::HideCommand() : IMCCommand("hide", "hide the mod", "") {
}

HideCommand::~HideCommand() {
}

bool HideCommand::execute(std::vector<std::string>* args) {
	static auto partner = moduleMgr->getModule<Partner>();
	GameData::hide();
	if (GameData::shouldHide()) {
		if (partner->Partnered.selected == 0)
		clientMessageF("[%sSurge%s] %sHidden.", GOLD, WHITE, BLUE);
		else
			clientMessageF("[%sNG%s] %sHidden.", GOLD, WHITE, LIGHT_PURPLE);
	} else {
		if (partner->Partnered.selected == 0)
		clientMessageF("[%sSurge%s] %sMod is now visible.", GOLD, WHITE, BLUE);
		else
		clientMessageF("[%sNG%s] %sMod is now visible.", GOLD, WHITE, LIGHT_PURPLE);
	}
	return true;
}
