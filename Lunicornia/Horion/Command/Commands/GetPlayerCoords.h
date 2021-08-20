#pragma once
#include "ICommand.h"

class GetPlayerCoords :
	public IMCCommand
{
public:
	GetPlayerCoords();
	~GetPlayerCoords();

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override;
};

