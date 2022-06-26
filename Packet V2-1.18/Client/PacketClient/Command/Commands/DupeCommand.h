#pragma once
#include "ICommand.h"

class DupeCommand : public IMCCommand {
public:
	virtual bool execute(std::vector<std::string>* args) override;
	DupeCommand();
};
