#pragma once
#include <sstream>

#include "ICommand.h"

class IRCCommand : public IMCCommand {
public:
	bool toggled = false;

	virtual bool execute(std::vector<std::string>* args) override;
	virtual void sendToServer(std::string name, std::string message);
	IRCCommand();
};