#pragma once
#include "ICommand.h"
class IDCommand : public IMCCommand {
public:
	virtual bool execute(std::vector<std::string>* args) override;
	IDCommand();
};
