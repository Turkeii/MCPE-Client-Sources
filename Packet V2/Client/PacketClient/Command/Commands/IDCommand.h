#pragma once
#include "ICommand.h"
class IDCommand : public IMCCommand {
public:
	IDCommand();
	~IDCommand();

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override;
};
