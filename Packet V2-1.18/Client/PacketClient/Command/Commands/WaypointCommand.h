#pragma once

#include "ICommand.h"
#include "../../Module/ModuleManager.h"
#include "../../Module/Modules/Visual/Waypoints.h"

class WaypointCommand : public IMCCommand {
public:
	virtual bool execute(std::vector<std::string>* args) override;
	WaypointCommand();
};
