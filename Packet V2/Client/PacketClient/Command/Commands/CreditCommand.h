#pragma once
#include "ICommand.h"
class CreditCommand : public IMCCommand {
public:
	CreditCommand();
	~CreditCommand();

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override;
};