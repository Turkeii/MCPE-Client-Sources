#include "EjectCommand.h"
#include "pch.h"

EjectCommand::EjectCommand() : IMCCommand("eject", "Removes the cheat from the game.", "") {
	registerAlias("uninject");
}

bool EjectCommand::execute(std::vector<std::string>* args) {
	GameData::terminate();
	return true;
}
