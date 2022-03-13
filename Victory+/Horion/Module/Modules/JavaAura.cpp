#include "JavaAura.h"

JavaAura::JavaAura() : IModule(0x0, Category::JAVA, "Killaura best java delay | Developed : KaeruClinet") {
	//this->registerBoolSetting("MultiAura", &this->isMulti, this->isMulti);
	//this->registerBoolSetting("Rot", &this->rot, this->rot);
	this->registerBoolSetting("MobAura", &this->isMobAura, this->isMobAura);
	this->registerFloatSetting("range", &this->range, this->range, 2.f, 20.f);
	//this->registerIntSetting("delay", &this->delay, this->delay, 0, 20);
	//this->registerBoolSetting("hurttime", &this->hurttime, this->hurttime);
}

JavaAura::~JavaAura() {
}

const char* JavaAura::getModuleName() {
	return ("JavaKill");
}

const char* JavaAura::getRawModuleName() {
	return "JavaKill";
}

static std::vector<C_Entity*> targetList;

void findEntityJK(C_Entity* currentEntityJK, bool isRegularEntityJK) {
	static auto JavaAuraMod = moduleMgr->getModule<JavaAura>();

	if (currentEntityJK == nullptr)
		return;

	if (currentEntityJK == g_Data.getLocalPlayer())  // Skip Local player
		return;

	if (!g_Data.getLocalPlayer()->canAttack(currentEntityJK, false))
		return;

	if (!g_Data.getLocalPlayer()->isAlive())
		return;

	if (!currentEntityJK->isAlive())
		return;

	if (currentEntityJK->getEntityTypeId() == 69)  // XP
		return;

	if (JavaAuraMod->isMobAura) {
		if (currentEntityJK->getNameTag()->getTextLength() <= 1 && currentEntityJK->getEntityTypeId() == 63)
			return;
		if (currentEntityJK->width <= 0.01f || currentEntityJK->height <= 0.01f)  // Don't hit this pesky antibot on 2b2e.org
			return;
		if (currentEntityJK->getEntityTypeId() == 64)  // item
			return;
		if (currentEntityJK->getEntityTypeId() == 80)  // Arrows
			return;
		if (currentEntityJK->getEntityTypeId() == 51)  // NPC
			return;
	} else {
		if (!Target::isValidTarget(currentEntityJK))
			return;
	}

	float dist = (*currentEntityJK->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < JavaAuraMod->range) {
		targetList.push_back(currentEntityJK);
	}
}

void JavaAura::onTick(C_GameMode* gm) {
	//Loop through all our players and retrieve their information
	targetList.clear();

	g_Data.forEachEntity(findEntityJK);

	Odelay++;
	if (!targetList.empty() && Odelay >= delay) {
		// Attack all entitys in targetList
		if (isMulti) {
			for (auto& i : targetList) {
				if (!(i->damageTime > 1 && hurttime)) {
					g_Data.getLocalPlayer()->swing();
					g_Data.getCGameMode()->attack(i);
				}
			}
		} else {
			if (!(targetList[0]->damageTime > 1 && hurttime)) {
				g_Data.getLocalPlayer()->swing();
				g_Data.getCGameMode()->attack(targetList[0]);
			}
		}
		Odelay = 0;
	}

	for (auto& i : targetList) {
		if (rot && !targetList.empty()) {
			vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*i->getPos());
			auto weewee = g_Data.getLocalPlayer();
			weewee->setRot(angle);
		}

		if (rot && !targetList.empty()) {
			vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*i->getPos());
			auto weewee = g_Data.getLocalPlayer();
			gm->player->pitch = angle.x;
			gm->player->yaw = angle.y;
			gm->player->bodyYaw = angle.x;
			gm->player->yawUnused1 = angle.y;
		}
	}
}

void JavaAura::onEnable() {
	if (g_Data.getLocalPlayer() == nullptr)
		this->setEnabled(false);
}