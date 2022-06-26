#pragma once
#include "ICommand.h"
class ModulesCommand : public IMCCommand {
public:
	virtual bool execute(std::vector<std::string>* args) override;
	ModulesCommand();
};
