#pragma once

#include "../../Memory/GameData.h"
#include "Commands/CommandBlockExploitCommand.h"
#include "Commands/ClientNameCommand.h"
#include "Commands/FriendListCommand.h"
#include "Commands/NameSpoofCommand.h"
#include "Commands/SetprefixCommand.h"
#include "Commands/GameModeCommand.h"
#include "Commands/TeleportCommand.h"
#include "Commands/PlayerTPCommand.h"
#include "Commands/SpammerCommand.h"
#include "Commands/EnchantCommand.h"
#include "Commands/ModulesCommand.h"
#include "Commands/CoordsCommand.h"
#include "Commands/DamageCommand.h"
#include "Commands/ServerCommand.h"
#include "Commands/ToggleCommand.h"
#include "Commands/UnbindCommand.h"
#include "Commands/ConfigCommand.h"
#include "Commands/EjectCommand.h"
#include "Commands/PanicCommand.h"
#include "Commands/VClipCommand.h"
#include "Commands/BindCommand.h"
#include "Commands/DupeCommand.h"
#include "Commands/GiveCommand.h"
#include "Commands/HelpCommand.h"
#include "Commands/HideCommand.h"
#include "Commands/ShowCommand.h"
#include "Commands/PathCommand.h"
#include "Commands/IRCCommand.h"
#include "Commands/SayCommand.h"
#include "Commands/TopCommand.h"
#include "Commands/NbtCommand.h"
#include "Commands/KitCommand.h"
#include "Commands/IDCommand.h"
#include "Commands/ICommand.h"

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