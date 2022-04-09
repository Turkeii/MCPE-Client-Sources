#pragma once
#include "ICommand.h"
#include "../../../Memory/Hooks.h"
class SeedCommand : public IMCCommand {
public:
	SeedCommand() : IMCCommand("seed", "Prints your seed", "") {
		registerAlias("getSeed");
	}
	~SeedCommand(){}

	bool execute(std::vector<std::string>* args) {
		std::string txt = "Seed: " + std::to_string(g_Data.getLocalPlayer()->getPointingStruct()->getSeed());
		g_Data.getLocalPlayer()->displayClientMessage(&TextHolder(txt));
		return true;
	}
};