#pragma once
#include "ICommand.h"
#include <map>

class UnbindCommand : public IMCCommand {
public:
	virtual bool execute(std::vector<std::string>* args) override;
	UnbindCommand();
};
