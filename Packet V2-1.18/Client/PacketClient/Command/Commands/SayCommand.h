#pragma once
#include "ICommand.h"
#include <sstream>

class SayCommand : public IMCCommand {
public:
	virtual bool execute(std::vector<std::string>* args) override;
	SayCommand();
};
