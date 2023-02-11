#pragma once
#include "ICommand.h"
#include <sstream>

class ClientNameCommand : public IMCCommand {
public:
	virtual bool execute(std::vector<std::string>* args) override;
	ClientNameCommand();
};