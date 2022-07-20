#pragma once
#include <sstream>

#include "ICommand.h"

class ChatCommand : public IMCCommand {
public:
	ChatCommand();
	~ChatCommand();

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override;
};
