#pragma once
#include "ICommand.h"
class GMCommand : public IMCCommand {
public:
	GMCommand();
	~GMCommand();

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override;
};