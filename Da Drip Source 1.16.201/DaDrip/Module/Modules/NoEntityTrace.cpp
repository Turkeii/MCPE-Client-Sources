
#include "../../../Utils/Logger.h"
#include "../../DrawUtils.h"
#include "NoEntityTrace.h"

NoEntityTrace::NoEntityTrace() : IModule(0, Category::PLAYER, "Lets you place and break behind players and mobs") {
	//this->registerBoolSetting("AllMobs", &this->allMobs, this->allMobs);
	this->registerBoolSetting("No Weapon", &this->noWeapon, this->noWeapon);
}

NoEntityTrace::~NoEntityTrace() {
}

const char* NoEntityTrace::getModuleName() {
	return ("NoEntityTrace");
}

static std::vector<C_Entity*> playerList2;

void findEntityButCooler(C_Entity* currentEntity, bool isRegularEntity) {
	static auto noEntityTraceMod = moduleMgr->getModule<NoEntityTrace>();
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

	if (noEntityTraceMod->allMobs) {
		if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 63)
			return;
		if (currentEntity->width <= 0.01f || currentEntity->height <= 0.01f)  // Don't hit this pesky antibot on 2b2e.org
			return;
		if (currentEntity->getEntityTypeId() == 64)  // item
			return;
		if (currentEntity->getEntityTypeId() == 69)  // xp_orb
			return;
		if (currentEntity->getEntityTypeId() == 80)  // arrow
			return;
	} else {
		//if (!Target::isValidTarget(currentEntity))

		if (currentEntity->getEntityTypeId() != 63)

			return;
	}

	//float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	playerList2.push_back(currentEntity);
}

void NoEntityTrace::onEnable() {
	if (g_Data.getLocalPlayer() == nullptr) return;
}

void NoEntityTrace::onDisable() {
	if (g_Data.getLocalPlayer() == nullptr) return;

	if (!playerList2.empty()) {
		for (auto& i : playerList2) {
			i->height = 1.8f;
			i->width = 0.6f;
		}
	}
}

void NoEntityTrace::onTick(C_GameMode* gm) {
	C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
	static auto autoTrapMod = moduleMgr->getModule<AutoTrap>();
	static auto autoAnvilMod = moduleMgr->getModule<AutoAnvil>();
	static auto crystalMod = moduleMgr->getModule<CrystalAuraWTA>();
	if (g_Data.getLocalPlayer() == nullptr) return;

	playerList2.clear();

	g_Data.forEachEntity(findEntityButCooler);

	if (!playerList2.empty()) {
		for (auto& i : playerList2) {
			i->height = 0.f;
			i->width = 0.f;
		}
	}
	auto selectedItemId = localPlayer->getSelectedItemId();
	if (noWeapon && playerList2.empty() && selectedItemId == 308 || selectedItemId == 307 || selectedItemId == 312 || selectedItemId == 316 || selectedItemId == 322 || selectedItemId == 592 || selectedItemId == 536 /*swords*/
		|| selectedItemId == 311 || selectedItemId == 315 || selectedItemId == 319 || selectedItemId == 325 || selectedItemId == 298 || selectedItemId == 595 /*axes*/) {

		for (auto& i : playerList2) {
			i->height = 1.8f;
			i->width = 0.6f;
		}
	}

	if (playerList2.empty() && autoTrapMod->isEnabled() || autoAnvilMod->isEnabled() || crystalMod->isEnabled()) {
		for (auto& i : playerList2) {
			i->height = 1.8f;
			i->width = 0.6f;
		}
	}	
	
}