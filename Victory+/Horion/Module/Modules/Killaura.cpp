#include "Killaura.h"

Killaura::Killaura() : IModule('P', Category::COMBAT, "Attacks entities around you automatically") {
	this->registerBoolSetting("MultiAura", &this->isMulti, this->isMulti);
	this->registerBoolSetting("Rotation", &this->rot, this->rot);
	this->registerBoolSetting("MobAura", &this->isMobAura, this->isMobAura);
	this->registerFloatSetting("range", &this->range, this->range, 2.f, 20.f);
	this->registerIntSetting("delay", &this->delay, this->delay, 0, 20);
	//this->registerBoolSetting("hurttime", &this->hurttime, this->hurttime);

}

Killaura::~Killaura() {
}

const char* Killaura::getModName() {
	if (isMulti) {
		return ("Multi");
	} else {
		return ("witch");
	}
}
const char* Killaura::getModuleName() {
	return ("KillAura");
}

const char* Killaura::getRawModuleName() {
	return "Killaura";
}

static std::vector<C_Entity*> targetList;

void findEntity(C_Entity* currentEntity, bool isRegularEntity) {
	static auto killauraMod = moduleMgr->getModule<Killaura>();

	if (currentEntity == nullptr)
		return;
	
	if (currentEntity == g_Data.getLocalPlayer())  // Skip Local player
		return;

	if (!g_Data.getLocalPlayer()->canAttack(currentEntity, false))
		return;

	if (!g_Data.getLocalPlayer()->isAlive())
		return;

	if(!currentEntity->isAlive())
		return;

	if (currentEntity->getEntityTypeId() == 69)  // XP
		return;

	if (killauraMod->isMobAura) {
		if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 63)
			return;
		if(currentEntity->width <= 0.01f || currentEntity->height <= 0.01f) // Don't hit this pesky antibot on 2b2e.org
			return;
		if(currentEntity->getEntityTypeId() == 64) // item
			return;
		if (currentEntity->getEntityTypeId() == 80)  // Arrows
			return;
		if (currentEntity->getEntityTypeId() == 51) // NPC
			return;
	} else {
		if (!Target::isValidTarget(currentEntity))
			return;
	}

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < killauraMod->range) {
		targetList.push_back(currentEntity);
	}
}



void Killaura::onTick(C_GameMode* gm) {
	//Loop through all our players and retrieve their information
	targetList.clear();

	g_Data.forEachEntity(findEntity);

	Odelay++;
	if (!targetList.empty() && Odelay >= delay) {
		// Attack all entitys in targetList
		if (isMulti) {
			for (auto& i : targetList) {
				if (!(i->damageTime > 1 && hurttime)) {
					g_Data.getLocalPlayer()->swing();
					g_Data.getCGameMode()->attack(i);
					timer5++;
				} else {
					timer5 = 0;
				}
			}
		} else {
			if (!(targetList[0]->damageTime > 1 && hurttime)) {
				g_Data.getLocalPlayer()->swing();
				g_Data.getCGameMode()->attack(targetList[0]);
				timer5++;
			} else {
				timer5 = 0;
			}
		}
		Odelay = 0;
	}

	for (auto& i : targetList) {
		if (rot && !targetList.empty()) {
			vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*i->getPos());
			auto weewee = g_Data.getLocalPlayer();
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);
			weewee->setRot(angle);

		}

		if (rot && !targetList.empty()) {
			timer++;
			vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*i->getPos());
			auto weewee = g_Data.getLocalPlayer();
				gm->player->pitch = angle.x;
				gm->player->yaw = angle.y;
				gm->player->bodyYaw = angle.x;
				gm->player->yawUnused1 = angle.y;
				gm->player->yawUnused2 = angle.y;
				//gm->player->oldBodyYaw = angle.y;
				//gm->player->yaw = angle.x;
				timer = 0;
			}
		}
	}


void Killaura::onEnable() {
		auto Server = g_Data.getRakNetInstance();
		if (Server == nullptr) return;

		if (Server->serverIp.getText() == "69.195.128.107") {
			clientMessageF("[%Kaeru Vxint%] %Testing is in 2b2e???", DARK_PURPLE, WHITE, GREEN);
		}
	if (g_Data.getLocalPlayer() == nullptr)
		this->setEnabled(false);
	timer5 = 0;
}

float t = 0;
void Killaura::onLevelRender() {

	// Rainbow colors
	static float rcolors[4];

	{
		if (rcolors[3] < 1) {
			rcolors[0] = 0.2f;
			rcolors[1] = 0.2f;
			rcolors[2] = 1.f;
			rcolors[3] = 1;
		}

		Utils::ApplyRainbow(rcolors, 0.015f);
	}

	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	targetList.clear();

	g_Data.forEachEntity(findEntity);
	if (!targetList.empty() && g_Data.isInGame()) {
		t++;
		DrawUtils::setColor(rcolors[0], rcolors[1], rcolors[2], 1.f);

		vec3_t permutations[37];
		for (int i = 0; i < 37; i++) {
			permutations[i] = {sinf((i * 10.f) / (180 / PI)), 0.f, cosf((i * 10.f) / (180 / PI))};
		}

		const float coolAnim = 0.9f + 0.9f * sin((t / 60) * PI * 2);

		vec3_t* start;
		vec3_t* end;

		if (!(targetList[0]->damageTime > 1 && hurttime)) {
			start = targetList[0]->getPosOld();
			end = targetList[0]->getPos();
		}

		auto te = DrawUtils::getLerpTime();
		vec3_t pos = start->lerp(end, te);

		auto yPos = pos.y;
		yPos -= 1.62f;
		yPos += coolAnim;

		std::vector<vec3_t> posList;
		posList.reserve(36);
		for (auto& perm : permutations) {
			vec3_t curPos(pos.x, yPos, pos.z);
			posList.push_back(curPos.add(perm));
		}

		DrawUtils::drawLinestrip3d(posList);
	}
}
