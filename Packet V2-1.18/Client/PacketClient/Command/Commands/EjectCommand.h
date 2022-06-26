#pragma once
#include "ICommand.h"
class EjectCommand : public IMCCommand {
public:
	virtual bool execute(std::vector<std::string>* args) override;
	EjectCommand();
};
