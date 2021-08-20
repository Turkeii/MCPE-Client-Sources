#include "DamageCommand.h"

DamageCommand::DamageCommand() : IMCCommand("damage", "Damage yourself (relies on falldamage)", "<amount>")
{
	registerAlias("dmg");
}

DamageCommand::~DamageCommand()
{
}

bool DamageCommand::execute(std::vector<std::string>* args)
{
	assertTrue(g_Data.getClientInstance()->getLocalPlayer() != nullptr);
	float amount = assertFloat(args->at(1));

	if (moduleMgr->getModule<NoFall>()->isEnabled()) {
		moduleMgr->getModule<NoFall>()->setEnabled(false);
		g_Data.getLocalPlayer()->causeFallDamage(amount + 3.f);
		moduleMgr->getModule<NoFall>()->setEnabled(true);
	}
	else {
		g_Data.getLocalPlayer()->causeFallDamage(amount + 3.f);
	}
	return true;
}
