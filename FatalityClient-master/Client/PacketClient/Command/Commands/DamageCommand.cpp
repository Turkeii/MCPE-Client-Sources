#include "DamageCommand.h"
#include "../../Module/ModuleManager.h"
#include "pch.h"

DamageCommand::DamageCommand() : IMCCommand("damage", "Damage yourself (relies on falldamage)", "<amount>") {
	registerAlias("dmg");
}