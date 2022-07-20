#pragma once
#include "ICommand.h"

class IDinfoCommand : public IMCCommand {
public:
	IDinfoCommand();
	~IDinfoCommand();

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override;
};