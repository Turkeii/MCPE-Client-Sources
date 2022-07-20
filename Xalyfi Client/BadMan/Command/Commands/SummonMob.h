#pragma once
#include "ICommand.h"

class SummonMob : public IMCCommand {
public:
	SummonMob();
	~SummonMob();

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override;
};
