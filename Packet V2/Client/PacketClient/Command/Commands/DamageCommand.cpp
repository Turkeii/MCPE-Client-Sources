#include "DamageCommand.h"

#include "../../Module/ModuleManager.h"

DamageCommand::DamageCommand() : IMCCommand("damage", "Damage yourself (relies on falldamage)", "<amount>") {
	registerAlias("dmg");
}

DamageCommand::~DamageCommand() {
}