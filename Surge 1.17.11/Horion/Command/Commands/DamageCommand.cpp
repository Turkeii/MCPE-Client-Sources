#include "DamageCommand.h"

#include "../../Module/ModuleManager.h"

DamageCommand::DamageCommand() : IMCCommand("damage", "Damage yourself", "Helped By Intop") {
	registerAlias("dmg");
}

DamageCommand::~DamageCommand() {
}
static std::vector<C_Entity*> targetMyself;

void findMyself(C_Entity* currentEntity, bool isRegularEntity) {

	if (currentEntity == nullptr)
		return;
	if (currentEntity != g_Data.getLocalPlayer())
		return;
	targetMyself.push_back(currentEntity);
}

bool DamageCommand::execute(std::vector<std::string>* args) {
	targetMyself.clear();
	g_Data.forEachEntity(findMyself);

	if (!targetMyself.empty()) {
		g_Data.getCGameMode()->attack(targetMyself[0]);
	}
	return true;
}
