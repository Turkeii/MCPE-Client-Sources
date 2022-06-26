#pragma once
#include "ICommand.h"

class ToggleCommand : public IMCCommand {
public:
	virtual bool execute(std::vector<std::string>* args) override;
	ToggleCommand();
};
