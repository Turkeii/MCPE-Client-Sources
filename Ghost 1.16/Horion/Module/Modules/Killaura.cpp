#include "Killaura.h"

Killaura::Killaura() : IModule('P', Category::COMBAT, "Attacks entities around you automatically") {
	this->registerBoolSetting("MultiAura", &this->isMulti, this->isMulti);
	this->registerBoolSetting("MobAura", &this->isMobAura, this->isMobAura);
	this->registerFloatSetting("range", &this->range, this->range, 2.f, 5.f);
	this->registerIntSetting("delay", &this->delay, this->delay, 0, 20);
	this->registerBoolSetting("hurttime", &this->hurttime, this->hurttime);
	this->registerBoolSetting("AutoWeapon", &this->autoweapon, this->autoweapon);
	this->registerBoolSetting("Yeet", &this->yeet, this->yeet);
	this->registerBoolSetting("Head Rotations", &this->head, this->head);
	this->registerBoolSetting("Body Rotations", &this->body, this->body);
	this->registerBoolSetting("Extra Rotations", &this->extra, this->extra);
	//this->registerBoolSetting("Client Side Crit", &this->crit, this->crit);
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
		if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 63)
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
	//Loop through all our players and retrieve their information
	targetList.clear();

	g_Data.forEachEntity(findEntity);

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
				}
			}
		} else {
			if (!(targetList[0]->damageTime > 1 && hurttime)) {
				g_Data.getLocalPlayer()->swing();
				g_Data.getCGameMode()->attack(targetList[0]);
			}
		}
		Odelay = 0;
		if (this->head) {
			for (int i = 0; i < 40; i++) {
			vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos());
			auto player = g_Data.getLocalPlayer();
				player->pitch = angle.x;
				player->pitch = angle.y;
			}
			if (this->body) {
				for (int i = 0; i < 40; i++) {
					vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos());
					auto player = g_Data.getLocalPlayer();
					player->bodyYaw = angle.x;
					player->bodyYaw = angle.x;
				}
				if (this->extra) {
					for (int i = 0; i < 40; i++) {
						vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos());
						auto player = g_Data.getLocalPlayer();
						player->yaw = angle.x;
						player->yaw2 = angle.x;
						player->pitch2 = angle.x;
					}
					if (this->yeet) {
						gm->player->velocity;
						5;

						/* if (this->full) {
					vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos());
					auto player = g_Data.getLocalPlayer();
					player->yaw = angle.x;
					player->yaw2 = angle.x;
				    player->oldBodyYaw = angle.x;
					player->yawUnused1 = angle.x;
					player->yawUnused2 = angle.x; */
					}
				}
			}
		}
	}
}

void Killaura::onEnable() {
	if (g_Data.getLocalPlayer() == nullptr)
		this->setEnabled(false);
}

void Killaura::onSendPacket(C_Packet* packet) {
	if (packet->isInstanceOf<C_MovePlayerPacket>()) {
		if (!targetList.empty()) {
			auto* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
			vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos());
			auto player = g_Data.getLocalPlayer();
		}
	}
}