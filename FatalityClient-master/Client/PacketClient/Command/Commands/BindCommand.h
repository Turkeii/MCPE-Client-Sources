#pragma once
#include "ICommand.h"
#include <map>

class BindCommand : public IMCCommand {
public:
	virtual bool execute(std::vector<std::string>* args) override;
	BindCommand();
};
