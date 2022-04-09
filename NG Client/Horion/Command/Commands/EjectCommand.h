#pragma once
#include "ICommand.h"
class EjectCommand : public IMCCommand {
public:
	EjectCommand() : IMCCommand("uninject", "Removes the cheat from the game.", "") {
		registerAlias("uninject");
	}
	~EjectCommand(){};

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override {
		GameData::terminate();
		return true;
	}
};