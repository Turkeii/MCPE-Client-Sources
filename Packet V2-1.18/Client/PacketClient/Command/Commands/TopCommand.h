#pragma once
#include "ICommand.h"

class TopCommand : public IMCCommand {
public:
	virtual bool execute(std::vector<std::string>* args) override;
	TopCommand();
};