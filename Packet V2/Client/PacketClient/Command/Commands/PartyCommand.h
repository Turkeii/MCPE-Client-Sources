#pragma once
#include "ICommand.h"
class PartyCommand : public IMCCommand {
public:
	PartyCommand();
	~PartyCommand();

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override;
};