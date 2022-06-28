#include "Killaura.h"
#include "../../../SDK/CAttribute.h"
bool distanceSort = false;
bool healthSort = false;
bool hold = false;
Killaura::Killaura() : IModule('P', Category::COMBAT, "To able hit enemies in a range") {
	registerEnumSetting("Rotations", &RotMode, 0);
	RotMode = SettingEnum(this)
				  .addEntry(EnumEntry("None", 0))
				  .addEntry(EnumEntry("Silent", 1))
				  .addEntry(EnumEntry("Full", 2))
				  .addEntry(EnumEntry("Client", 3));
	registerEnumSetting("Hit Type", &HitMode, 0);
	HitMode = SettingEnum(this)
				  .addEntry(EnumEntry("Multi", 0))
				  .addEntry(EnumEntry("Single", 1));
	registerEnumSetting("Priority", &priority, 0);
	priority = SettingEnum(this)
				   .addEntry(EnumEntry("None", 0))
				   .addEntry(EnumEntry("Distance", 1))
				  .addEntry(EnumEntry("Health", 2))
				  .addEntry(EnumEntry("Smart", 3));
	registerFloatSetting("Range", &range, range, 2.f, 20.f);
	registerIntSetting("Intervals", &delay, delay, 0, 20);
	registerBoolSetting("Hurttime", &hurttime, hurttime);
	registerBoolSetting("Auto Weapon", &autoweapon, autoweapon);
	registerBoolSetting("Target Mobs", &isMobAura, isMobAura);
	//registerBoolSetting("Health Sort", &healthSort, healthSort);
	//registerBoolSetting("Distance Sort", &distanceSort, distanceSort);
	registerBoolSetting("Target ESP", &VisTarget, VisTarget);
	registerBoolSetting("NoSwing", &noSwing, noSwing);
	//registerBoolSetting("Hold", &hold, hold);
	registerBoolSetting("Health Check", &healthcheck1, healthcheck1);
	registerFloatSetting("Min Health", &healthcheck, healthcheck, 1.f, 32.f);
}

Killaura::~Killaura() {
}
const char* Killaura::getModName() {
	if (multi) {
		return " [Multi]";
	} else {
		return " [Switch]";
	}
}
const char* Killaura::getModuleName() {
	return ("Aura");
}

//Sort by distance
struct CompareTargetDist {
	bool operator()(C_Entity* lhs, C_Entity* rhs) {
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
	}
};

//Sort By health
struct CompareTargetHealth {
	bool operator()(C_Entity* lhs, C_Entity* rhs) {
		return (lhs->getHealth()) < (rhs->getHealth());
	}
};

static std::vector<C_Entity*> targetList;

void findEntity(C_Entity* currentEntity, bool isRegularEntity) {
	static auto killauraMod = moduleMgr->getModule<Killaura>();

	if (currentEntity == nullptr)
		return;

	if (currentEntity == g_Data.getLocalPlayer())
		return;

	if (!g_Data.getLocalPlayer()->canAttack(currentEntity, false))
		return;

	if (!g_Data.getLocalPlayer()->isAlive())
		return;

	if (!currentEntity->isAlive())
		return;

	if (currentEntity->getEntityTypeId() == 69)  // XP
		return;

	if (currentEntity->getEntityTypeId() == 80)  // Arrows
		return;
	if (currentEntity->getEntityTypeId() == 71)  // crystal
		return;
	if (currentEntity->getEntityTypeId() == 64)  // item
		return;

	if (killauraMod->isMobAura) {
		if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 63)
			return;
		if (currentEntity->width <= 0.01f || currentEntity->height <= 0.01f)  // Don't hit this pesky antibot on 2b2e.org
			return;
		if (currentEntity->getEntityTypeId() == 64)  // item
			return;

	} else {
		if (!Target::isValidTarget(currentEntity))
			return;

		if (currentEntity->getEntityTypeId() == 1677999)  // Villager
			return;

		if (currentEntity->getEntityTypeId() == 51)  // NPC
			return;
	}

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < killauraMod->range) {
		targetList.push_back(currentEntity);
	}
}

void Killaura::findWeapon() {
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	float damage = 0;
	int slot = supplies->selectedHotbarSlot;
	for (int n = 0; n < 9; n++) {
		C_ItemStack* stack = inv->getItemStack(n);
		if (stack->item != nullptr) {
			float currentDamage = stack->getAttackingDamageWithEnchants();
			if (currentDamage > damage) {
				damage = currentDamage;
				slot = n;
			}
		}
	}
	supplies->selectedHotbarSlot = slot;
}

void Killaura::onPlayerTick(C_Player* plr) {
	if (g_Data.getLocalPlayer() == plr) {
		if (g_Data.isInGame() && g_Data.getLocalPlayer() != nullptr && !targetList.empty()) {
			if (distanceSort)
				std::sort(targetList.begin(), targetList.end(), CompareTargetDist());
			//if (healthSort)
				//std::sort(targetList.begin(), targetList.end(), CompareTargetHealth());
			targetListA = targetList.empty();
			targetList.clear();

			g_Data.forEachEntity(findEntity);

			// cool shit ngl
			if (noSilent && !targetList.empty()) {
				vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos());
				plr->pitch = angle.x;
				plr->yaw = angle.y;
				plr->bodyYaw = angle.y;
				plr->yawUnused1 = angle.y;
			} else if (Client && !targetList.empty()) {
				vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos());
				plr->bodyYaw = angle.y;
				plr->yawUnused1 = angle.y;
				plr->pitch = angle.x;
			}
		}
	}
}

void Killaura::onTick(C_GameMode* gm) {
	switch (RotMode.selected) {
	case 0:
		silent = false;
		noSilent = false;
		Client = false;
		break;
	case 1:
		silent = true;
		noSilent = false;
		Client = false;
		break;
	case 2:
		silent = false;
		noSilent = true;
		Client = false;
		break;
	case 3:
		silent = true;
		noSilent = false;
		Client = true;
		break;
	}
	switch (HitMode.selected) {
	case 0:
		multi = true;
		break;
	case 1:
		multi = false;
		break;
	}
	switch (priority.selected) {
	case 0:
		healthSort = false;
		distanceSort = false;
		break;
	case 1:
		healthSort = false;
		distanceSort = true;
		break;
	case 2:
		healthSort = true;
		distanceSort = false;
		break;
	case 3:
		healthSort = true;
		distanceSort = true;
		break;
	}
	if (healthcheck1) {
		auto player = g_Data.getLocalPlayer();
		if (player->getHealth() == healthcheck) return;
	}

	// Loop through all our players and retrieve their information
	targetListA = targetList.empty();
	targetList.clear();

	g_Data.forEachEntity(findEntity);
	if (distanceSort)
		std::sort(targetList.begin(), targetList.end(), CompareTargetDist());
	if (healthSort)
		std::sort(targetList.begin(), targetList.end(), CompareTargetHealth());
	Odelay++;
	if (!targetList.empty() && Odelay >= delay) {
		if (autoweapon) findWeapon();

		if (g_Data.getLocalPlayer()->velocity.squaredxzlen() < 0.01) {
			C_MovePlayerPacket p(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);  // make sure to update rotation if player is standing still
		}

		// Attack all entitys in targetList
		switch (HitMode.selected) {
		case 0:
			for (auto& i : targetList)
			//if ((GameData::isLeftClickDown() || !hold) && GameData::canUseMoveKeys()) 
					if (!(i->damageTime > 1 && hurttime)) {
						g_Data.getLocalPlayer()->swing();
						g_Data.getCGameMode()->attack(i);
						if (noSwing)
							return;
						timer5++;
					} else {
						timer5 = 0;
					}
				case 1:
				//	if ((GameData::isLeftClickDown() || !hold) && GameData::canUseMoveKeys()) 
						if (!(targetList[0]->damageTime > 1 && hurttime)) {
							g_Data.getLocalPlayer()->swing();
							g_Data.getCGameMode()->attack(targetList[0]);
							if (noSwing)
								return;
							timer5++;
						} else {
							timer5 = 0;
						}
					}
					Odelay = 0;
				}
		}
	void Killaura::onEnable() {
	if (g_Data.getLocalPlayer() == nullptr)
		setEnabled(false);
	timer5 = 0;
}

void Killaura::onSendPacket(C_Packet* packet) {
	if (packet->isInstanceOf<C_MovePlayerPacket>() && g_Data.getLocalPlayer() != nullptr && silent) {
		if (!targetList.empty()) {
			if (distanceSort)
				std::sort(targetList.begin(), targetList.end(), CompareTargetDist());
			if (healthSort)
				std::sort(targetList.begin(), targetList.end(), CompareTargetHealth());
			auto* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
			vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos());
			movePacket->pitch = angle.x;
			movePacket->headYaw = angle.y;
			movePacket->yaw = angle.y;
		}
	}
}

float t = 0;
void Killaura::onLevelRender() {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	targetListA = targetList.empty();
	targetList.clear();

	g_Data.forEachEntity(findEntity);
	if (distanceSort)
		std::sort(targetList.begin(), targetList.end(), CompareTargetDist());
	if (healthSort)
		std::sort(targetList.begin(), targetList.end(), CompareTargetHealth());
	if (!targetList.empty() && VisTarget && g_Data.isInGame()) {
		t++;
		DrawUtils::setColor(1.f, 1.f, 1.f, 1.f);

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