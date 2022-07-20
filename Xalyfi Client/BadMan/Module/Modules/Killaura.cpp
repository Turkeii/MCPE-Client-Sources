#include "Killaura.h"

Killaura::Killaura() : IModule('P', Category::COMBAT, "Attacks entities around you automatically") {
	registerEnumSetting("Rotations", &RotMode, 0);
	RotMode = SettingEnum(this)
				  .addEntry(EnumEntry("None", 0))
				  .addEntry(EnumEntry("Silent", 1))
				  .addEntry(EnumEntry("Client", 2));
	this->registerBoolSetting("MultiAura", &this->isMulti, this->isMulti);
	this->registerBoolSetting("MobAura", &this->isMobAura, this->isMobAura);
	this->registerFloatSetting("range", &this->range, this->range, 2.f, 20.f);
	this->registerIntSetting("delay", &this->delay, this->delay, 0, 20);
	this->registerBoolSetting("hurttime", &this->hurttime, this->hurttime);
	this->registerBoolSetting("AutoWeapon", &this->autoweapon, this->autoweapon);
	this->registerBoolSetting("Visualise Target", &this->VisTarget, this->VisTarget);
}

Killaura::~Killaura() {
}

const char* Killaura::getModuleName() {
	return ("Killaura");
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

	if (!currentEntity->isAlive())
		return;

	if (killauraMod->isMobAura) {
		if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 63) // this means target every mob a-part from the player!
			return;
		if (currentEntity->width <= 0.01f || currentEntity->height <= 0.01f)  // Don't hit this pesky antibot on 2b2e.org
			return;
		if (currentEntity->getEntityTypeId() == 64)  // item
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

void Killaura::onTick(C_GameMode* gm) {

	switch (RotMode.selected) {
	case 0:
		silent = false;
		noSilent = false;
		break;
	case 1:
		silent = true;
		noSilent = false;
		break;
	case 2:
		silent = false;
		noSilent = true;
		break;
	}

	//Loop through all our players and retrieve their information
	targetList.clear();

	g_Data.forEachEntity(findEntity);
	
	//cool shit ngl
	if (noSilent && !targetList.empty()) {
		vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos());
		gm->player->pitch = angle.x;
		gm->player->yaw = angle.y;
		gm->player->bodyYaw = angle.y;
		gm->player->yawUnused1 = angle.y;
	}

	Odelay++;
	if (!targetList.empty() && Odelay >= delay) {
		if (autoweapon) findWeapon();

		if (g_Data.getLocalPlayer()->velocity.squaredxzlen() < 0.01) {
			C_MovePlayerPacket p(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);  // make sure to update rotation if player is standing still
		}

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
}

void Killaura::onEnable() {
	if (g_Data.getLocalPlayer() == nullptr)
		this->setEnabled(false);
	timer5 = 0;
}

void Killaura::onSendPacket(C_Packet* packet) {
	if (packet->isInstanceOf<C_MovePlayerPacket>() && g_Data.getLocalPlayer() != nullptr && silent) {
		if (!targetList.empty()) {
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

	targetList.clear();

	g_Data.forEachEntity(findEntity);
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
