#pragma once
#include <sstream>

#include "ICommand.h"

class ClientNameCommand : public IMCCommand {
public:
	ClientNameCommand();
	~ClientNameCommand();

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override;
};