#pragma once
#include "ICommand.h"
#include <sstream>

class SpammerCommand : public IMCCommand {
public:
	virtual bool execute(std::vector<std::string>* args) override;
	SpammerCommand();
};