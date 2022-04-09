#pragma once

#include "../../Memory/GameData.h"
#include "Commands/BindCommand.h"
#include "Commands/CBEPCommand.h"
#include "Commands/CommandBlockExploitCommand.h"
#include "Commands/ConfigCommand.h"
#include "Commands/CoordsCommand.h"
#include "Commands/Credits.h"
#include "Commands/DamageCommand.h"
#include "Commands/DupeCommand.h"
#include "Commands/EjectCommand.h"
#include "Commands/EmoteCommand.h"
#include "Commands/EnchantCommand.h"
#include "Commands/FriendListCommand.h"
#include "Commands/GiveCommand.h"
#include "Commands/GMCommand.h"
#include "Commands/GodmodeCommand.h"
#include "Commands/HelpCommand.h"
#include "Commands/HideCommand.h"
#include "Commands/ICommand.h"
#include "Commands/KitCommand.h"
#include "Commands/ModulesCommand.h"
#include "Commands/NameSpoofCommand.h"
#include "Commands/NbtCommand.h"
#include "Commands/PanicCommand.h"
#include "Commands/PathCommand.h"
#include "Commands/PlayerTeleportCommand.h"
#include "Commands/RelativeTeleportCommand.h"
#include "Commands/SeedCommand.h"
#include "Commands/ServerCommand.h"
#include "Commands/setoffhandCommand.h"
#include "Commands/SetprefixCommand.h"
#include "Commands/SpammerCommand.h"
#include "Commands/TeleportCommand.h"
#include "Commands/TestCommand.h"
#include "Commands/ToggleCommand.h"
#include "Commands/TopCommand.h"
#include "Commands/UnbindCommand.h"
#include "Commands/WaypointCommand.h"

#ifdef _DEBUG
#endif

#include <algorithm>
#include <string>
#include <vector>

class CommandMgr {
private:
	GameData* gameData;
	std::vector<IMCCommand*> commandList;

public:
	CommandMgr(GameData* gm);
	~CommandMgr();

	char prefix = '.';

	void initCommands();
	void disable();
	std::vector<IMCCommand*>* getCommandList();

	void execute(char* message);
};

extern CommandMgr* cmdMgr;
