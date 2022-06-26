#pragma once
#include "ICommand.h"
#include <sstream>

class NameSpoofCommand : public IMCCommand {
public:
	virtual bool execute(std::vector<std::string>* args) override;
	NameSpoofCommand();
};
