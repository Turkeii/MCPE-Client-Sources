#pragma once
#include "ICommand.h"

class ShowCommand : public IMCCommand {
public:
	virtual bool execute(std::vector<std::string>* args) override;
	ShowCommand();
};