#pragma once
#include "ICommand.h"

class ServerCommand : public IMCCommand {
public:
	virtual bool execute(std::vector<std::string>* args) override;
	ServerCommand();
};
