#pragma once
#include "ICommand.h"
class DamageCommand : public IMCCommand {
public:
	DamageCommand() : IMCCommand("damage", "Damage yourself (relies on attacking yourself)", "<hi>") {
		registerAlias("dmg");
	}
	~DamageCommand(){}

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override {
		g_Data.getCGameMode()->attack(g_Data.getLocalPlayer());
		return true;
	}
};