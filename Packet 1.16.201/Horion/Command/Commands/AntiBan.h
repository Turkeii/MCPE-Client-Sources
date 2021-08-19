#pragma once
#include "ICommand.h"
class AntiBan : public IMCCommand {
public:
	AntiBan();
	~AntiBan();

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override;
};