#pragma once
#include "ICommand.h"
#include <map>

class setoffhandCommand : public IMCCommand {
public:
	virtual bool execute(std::vector<std::string>* args) override;
	setoffhandCommand();
};
