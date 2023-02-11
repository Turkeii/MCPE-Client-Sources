#pragma once
#include "ICommand.h"

class HelpCommand : public IMCCommand {
public:
	virtual bool execute(std::vector<std::string>* args) override;
	HelpCommand();
};
