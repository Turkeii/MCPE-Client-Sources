#pragma once
#include <sstream>

#include "ICommand.h"

class SpammerCommand : public IMCCommand {
public:
	SpammerCommand();
	~SpammerCommand();

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override;
};