#include "ShieldBreak.h"

ShieldBreak::ShieldBreak() : IModule('P', Category::COMBAT, "Break the shield fast") {
	this->registerFloatSetting("range", &this->range, this->range, 2.f, 20.f);
}

ShieldBreak::~ShieldBreak() {
}

const char* ShieldBreak::getModuleName() {
	return ("ShieldBreaker");
}

static std::vector<C_Entity*> targetListsb;

void findEntitysb(C_Entity* currentEntity, bool isRegularEntity) {
	static auto ShieldBreakMod = moduleMgr->getModule<ShieldBreak>();

	if (currentEntity == nullptr)
		return;

	if (currentEntity == g_Data.getLocalPlayer())  // Skip Local player
		return;

	if (!g_Data.getLocalPlayer()->canAttack(currentEntity, false))
		return;

	if (!g_Data.getLocalPlayer()->isAlive())
		return;

	if (!currentEntity->isAlive())
		return;

	if (currentEntity->getEntityTypeId() == 69)  // XP
		return;
{
		if (!Target::isValidTarget(currentEntity))
			return;
	}

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < ShieldBreakMod->range) {
		targetListsb.push_back(currentEntity);
	}
}

void ShieldBreak::onTick(C_GameMode* gm) {
	//Loop through all our players and retrieve their information
	targetListsb.clear();

	g_Data.forEachEntity(findEntitysb);

	Odelay++;
	if (!targetListsb.empty() && Odelay >= delay) {

		if (g_Data.getLocalPlayer()->velocity.squaredxzlen() < 0.01) {
			C_MovePlayerPacket p(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);  // make sure to update rotation if player is standing still
		}

		// Attack all entitys in targetList
			if (!(targetListsb[0]->damageTime > 1)) {
				g_Data.getCGameMode()->attack(targetListsb[0]);
				g_Data.getCGameMode()->attack(targetListsb[0]);
				g_Data.getCGameMode()->attack(targetListsb[0]);
				g_Data.getCGameMode()->attack(targetListsb[0]);
				g_Data.getCGameMode()->attack(targetListsb[0]);
				g_Data.getCGameMode()->attack(targetListsb[0]);
				g_Data.getCGameMode()->attack(targetListsb[0]);
				g_Data.getCGameMode()->attack(targetListsb[0]);
				g_Data.getCGameMode()->attack(targetListsb[0]);
				g_Data.getCGameMode()->attack(targetListsb[0]);
				g_Data.getCGameMode()->attack(targetListsb[0]);
				g_Data.getCGameMode()->attack(targetListsb[0]);
				g_Data.getCGameMode()->attack(targetListsb[0]);
				g_Data.getCGameMode()->attack(targetListsb[0]);
				g_Data.getCGameMode()->attack(targetListsb[0]);
				g_Data.getCGameMode()->attack(targetListsb[0]);
				g_Data.getCGameMode()->attack(targetListsb[0]);
				g_Data.getCGameMode()->attack(targetListsb[0]);
				g_Data.getCGameMode()->attack(targetListsb[0]);
				g_Data.getCGameMode()->attack(targetListsb[0]);
				g_Data.getCGameMode()->attack(targetListsb[0]);
				g_Data.getCGameMode()->attack(targetListsb[0]);
				g_Data.getCGameMode()->attack(targetListsb[0]);
				g_Data.getCGameMode()->attack(targetListsb[0]);
				g_Data.getCGameMode()->attack(targetListsb[0]);
				g_Data.getCGameMode()->attack(targetListsb[0]);
				g_Data.getCGameMode()->attack(targetListsb[0]);
				g_Data.getCGameMode()->attack(targetListsb[0]);
				g_Data.getCGameMode()->attack(targetListsb[0]);
				g_Data.getCGameMode()->attack(targetListsb[0]);
				g_Data.getLocalPlayer()->swing();
			}
		Odelay = 0;
	}
}

void ShieldBreak::onEnable() {
	if (g_Data.getLocalPlayer() == nullptr)
		this->setEnabled(false);
}