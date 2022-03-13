#include "ESP.h"

#include "../../../Utils/Target.h"

ESP::ESP() : IModule(0x0, Category::VISUAL, "Makes it easier to find entities around you") {
	//this->registerBoolSetting("rainbow", &this->doRainbow, this->doRainbow);
	this->registerBoolSetting("MobEsp", &this->isMobEsp, this->isMobEsp);
	this->registerBoolSetting("2d", &this->is2d, this->is2d);
}

ESP::~ESP() {
}

const char* ESP::getModuleName() {
	return ("ESP");
}
/*
static std::vector<C_Entity*> targetList;

void findEntity111(C_Entity* currentEntity111, bool isRegularEntity) {
	static auto killauraMod = moduleMgr->getModule<ESP>();

	if (currentEntity111 == nullptr)
		return;

	if (currentEntity111 == g_Data.getLocalPlayer())  // Skip Local player
		return;

	if (!g_Data.getLocalPlayer()->canAttack(currentEntity111, false))
		return;

	if (!g_Data.getLocalPlayer()->isAlive())
		return;

	if (!currentEntity111->isAlive())
		return;

	if (currentEntity111->getEntityTypeId() == 69)  // XP
		return;

	if (killauraMod->isMobEsp) {
		if (currentEntity111->getNameTag()->getTextLength() <= 1 && currentEntity111->getEntityTypeId() == 63)
			return;
		if (currentEntity111->width <= 0.01f || currentEntity111->height <= 0.01f)  // Don't hit this pesky antibot on 2b2e.org
			return;
		if (currentEntity111->getEntityTypeId() == 64)  // item
			return;
		if (currentEntity111->getEntityTypeId() == 80)  // Arrows
			return;
		if (currentEntity111->getEntityTypeId() == 51)  // NPC
			return;
	} else {
		if (!Target::isValidTarget(currentEntity111))
			return;
	}

	float dist = (*currentEntity111->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < killauraMod->range) {
		targetList.push_back(currentEntity111);
	}
}

void ESP::onTick(C_GameMode* gm) {
	//Loop through all our players and retrieve their information
	targetList.clear();

	g_Data.forEachEntity(findEntity111);

	Odelay++;
	if (!targetList.empty() && Odelay >= delay) {
		// Attack all entitys in targetList
		if (isMulti) {
			for (auto& i : targetList) {
				if (!(i->damageTime > 1 && hurttime)) {
					//g_Data.getLocalPlayer()->swing();
					//g_Data.getCGameMode()->attack(i);
					timer5 + 10;
				} else {
					timer5 = 0;
				}
			}
		} else {
			if (!(targetList[0]->damageTime > 1 && hurttime)) {
				//g_Data.getLocalPlayer()->swing();
				//g_Data.getCGameMode()->attack(targetList[0]);
				timer5++;
			} else {
				timer5 = 0;
			}
		}
		Odelay = 0;
	}
}

void ESP::onEnable() {
	timer5 = 0;
}

float t1 = 0;
void ESP::onLevelRender() {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	targetList.clear();

	g_Data.forEachEntity(findEntity111);
	if (!targetList.empty() && g_Data.isInGame()) {
		t1++;
		DrawUtils::setColor(1.f, 1.f, 1.f, 1.f);

		vec3_t permutations[37];
		for (int i = 0; i < 37; i++) {
			permutations[i] = {sinf((i * 10.f) / (180 / PI)), 0.f, cosf((i * 10.f) / (180 / PI))};
		}

		const float coolAnim = 0.9f + 0.9f * sin((t1 / 60) * PI * 2);

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
}*/

static float rcolors[4];

void doRenderStuff(C_Entity* ent, bool isRegularEntitie) {
	static auto espMod = moduleMgr->getModule<ESP>();
	
	C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
	if (ent == localPlayer)
		return;
	if (ent->timeSinceDeath > 0)
		return;
	static auto noFriendsModule = moduleMgr->getModule<NoFriends>();
	if (!noFriendsModule->isEnabled() && FriendList::findPlayer(ent->getNameTag()->getText())) {
		DrawUtils::setColor(0.1f, 0.9f, 0.1f, (float)fmax(0.1f, (float)fmin(1.f, 15 / (ent->damageTime + 1))));
	} else if (Target::isValidTarget(ent)) {
		if (!(ent->damageTime > 1)) {
			DrawUtils::setColor(0.f, 1.f, 0.f, (float)fmax(0.1f, (float)fmin(1.f, 15 / (ent->damageTime + 1))));
		} else {
			DrawUtils::setColor(1.f, 0.f, 0.f, (float)fmax(0.1f, (float)fmin(1.f, 15 / (ent->damageTime + 1))));
		}
			} else if (espMod->isMobEsp) {
		if (ent->getNameTag()->getTextLength() <= 1 && ent->getEntityTypeId() == 63)
			return;

		if (ent->isInvisible())
			return;

		if (!localPlayer->canAttack(ent, false))
			return;

		if (!(ent->damageTime > 1)) {
			DrawUtils::setColor(0.f, 1.f, 0.f, (float)fmax(0.1f, (float)fmin(1.f, 15 / (ent->damageTime + 1))));
		} else {
			DrawUtils::setColor(1.f, 0.f, 0.f, (float)fmax(0.1f, (float)fmin(1.f, 15 / (ent->damageTime + 1))));
		}
	} else
		return;
	if (espMod->is2d)
		DrawUtils::draw2D(ent, (float)fmax(0.4f, 1 / (float)fmax(1, localPlayer->getPos()->dist(*ent->getPos()) * 3.f)));
	else 
		DrawUtils::drawEntityBox(ent, (float)fmax(0.2f, 1 / (float)fmax(1, localPlayer->getPos()->dist(*ent->getPos()))));
	
	
}

void ESP::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();

	if (localPlayer != nullptr && GameData::canUseMoveKeys()) {
		// Rainbow colors
		{
			if (rcolors[3] < 1) {
				rcolors[0] = 0.2f;
				rcolors[1] = 0.2f;
				rcolors[2] = 1.f;
				rcolors[3] = 1;
			}

			Utils::ApplyRainbow(rcolors, 0.0015f);
		}

		g_Data.forEachEntity(doRenderStuff);
	}
}
