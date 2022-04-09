#pragma once
#include "ICommand.h"

class CBEPCommand : public IMCCommand {
public:
	CBEPCommand();
	~CBEPCommand();

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override;
};
