#pragma once
#include "ICommand.h"
class OutlineCommand : public IMCCommand {
public:
	OutlineCommand();
	~OutlineCommand();

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override;
};
