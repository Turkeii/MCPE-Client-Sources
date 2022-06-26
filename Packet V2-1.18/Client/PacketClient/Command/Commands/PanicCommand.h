#pragma once
#include "ICommand.h"

class PanicCommand : public IMCCommand {
public:
	virtual bool execute(std::vector<std::string>* args) override;
	PanicCommand();
};
