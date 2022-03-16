#include "TPAura.h"

TPAura::TPAura() : IModule(0x0, Category::COMBAT, "TP like fuck so you dont get hit") {
	this->registerBoolSetting("MobAura", &this->isMobAura, this->isMobAura);
	this->registerBoolSetting("MultiAura", &this->isMulti, this->isMulti);
	this->registerBoolSetting("Lerp", &this->lerp, this->lerp);
	this->registerBoolSetting("UnlimitedRange", &this->unlim, this->unlim);
	this->registerFloatSetting("range", &this->range, this->range, 0.5f, 20.f);
	this->registerIntSetting("TP delay", &this->delay, this->delay, 0, 20);
	this->registerIntSetting("Attack delay", &this->delay1, this->delay1, 0, 20);
	this->registerBoolSetting("AutoWeapon", &this->autoweapon, this->autoweapon);
	this->registerBoolSetting("Silent Rotations", &this->silent, this->silent);
}

TPAura::~TPAura() {
}

const char* TPAura::getModuleName() {
	return ("TPAura");
}

static std::vector<C_Entity*> targetList;

void findEntity0(C_Entity* currentEntity, bool isRegularEntity) {
	static auto TPMod = moduleMgr->getModule<TPAura>();

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

	if (TPMod->isMobAura) {
		if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 63)
			return;
		if(currentEntity->width <= 0.01f || currentEntity->height <= 0.01f) // Don't hit this pesky antibot on 2b2e.org
			return;
		if(currentEntity->getEntityTypeId() == 64) // item
			return;
	} else {
		if (!Target::isValidTarget(currentEntity))
			return;
	}

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
	if (!TPMod->unlim) {
		if (dist < TPMod->range) {
			targetList.push_back(currentEntity);
		}
	} else {
		if (dist < TPMod->unlimRange) {
			targetList.push_back(currentEntity);
		}
	}
}

void TPAura::findWeapon() {
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

void TPAura::onTick(C_GameMode* gm) {

	//Loop through all our players and retrieve their information
	targetList.clear();

	g_Data.forEachEntity(findEntity0);

	Odelay++;
	if (!targetList.empty() && Odelay >= delay) {
		vec3_t pos = *targetList[0]->getPos();
		if (turn == 3) {
			pos.y += 2;
			pos.x += -1.f;
			pos.z += 1.f;
			turn = 0;
		} else if (turn == 2) {
			pos.y += 2.f;
			pos.x += -1.f;
			pos.z += -1.f;
			turn = 3;
		} else if (turn == 1) {
			pos.y += 2.f;
			pos.x += 1.f;
			pos.z += -1.f;
			turn = 2;
		} else if (turn == 0) {
			pos.y += 2.f;
			pos.x += 1.f;
			pos.z += 1.f;
			turn = 1;
		}
		if (autoweapon) findWeapon();
			//if (g_Data.getLocalPlayer()->velocity.squaredxzlen() < 0.01) {
			C_MovePlayerPacket p(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
			//}
			C_LocalPlayer* player = g_Data.getLocalPlayer();
			if (!lerp) {
				player->setPos(pos);
			} else {
				float dist2 = gm->player->getPos()->dist(pos);
				//player->lerpMotion(pos);
				//player->lerpTo(pos, vec2_t(1, 1), (int)fmax((int)dist2 * 0.1, 1));
				player->lerpMotion(pos);
			}
		Odelay = 0;
	}

		delay2++;
		g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = false;
		if (!targetList.empty() && delay2 >= delay1) {

			if (isMulti) {
				for (auto& i : targetList) {
						g_Data.getLocalPlayer()->swing();
						g_Data.getCGameMode()->attack(i);
				}
			} else {
					g_Data.getLocalPlayer()->swing();
					g_Data.getCGameMode()->attack(targetList[0]);
			}
			delay2 = 0;
		}
}

void TPAura::onEnable() {
	if (g_Data.getLocalPlayer() == nullptr)
		this->setEnabled(false);
}

void TPAura::onSendPacket(C_Packet* packet) {
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
