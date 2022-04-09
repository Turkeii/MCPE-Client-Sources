#include "InsideAura.h"

InsideAura::InsideAura() : IModule(0x0, Category::COMBAT, "TP Into The Closest Entity") {
	registerBoolSetting("MobAura", &isMobAura, isMobAura);
	registerBoolSetting("UnlimitedRange", &unlim, unlim);
	registerBoolSetting("PushMode", &pushm, pushm);
	registerBoolSetting("Sex Mode", &sex, sex);
	registerFloatSetting("range", &range, range, 0.5f, 20.f);
	registerIntSetting("delay", &delay, delay, 0, 20);
	registerBoolSetting("hurttime", &hurttime, hurttime);
	registerBoolSetting("AutoWeapon", &autoweapon, autoweapon);
}

InsideAura::~InsideAura() {
}

const char* InsideAura::getModuleName() {
	return ("InsideAura");
}

static std::vector<C_Entity*> targetList;

void findEntity1(C_Entity* currentEntity, bool isRegularEntity) {
	static auto insideMod = moduleMgr->getModule<InsideAura>();

	if (currentEntity == nullptr) return;
	if (currentEntity == g_Data.getLocalPlayer()) return; // Skip Local player
	if (!g_Data.getLocalPlayer()->canAttack(currentEntity, false)) return;
	if (!g_Data.getLocalPlayer()->isAlive()) return;
	if (!currentEntity->isAlive()) return;

	if (insideMod->isMobAura) {
		if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 63) return;
		if (currentEntity->width <= 0.01f || currentEntity->height <= 0.01f) return;  // Don't hit this pesky antibot on 2b2e.org
		if (currentEntity->getEntityTypeId() == 64) return;  // item
	} else {
		if (!Target::isValidTarget(currentEntity)) return;
	}

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
	if (!insideMod->unlim) {
		if (dist < insideMod->range) {
			targetList.push_back(currentEntity);
		}
	} else {
		if (dist < insideMod->unlimRange) {
			targetList.push_back(currentEntity);
		}
	}
}

void InsideAura::findWeapon() {
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

void InsideAura::onTick(C_GameMode* gm) {
	// Loop through all our players and retrieve their information
	targetList.clear();

	g_Data.forEachEntity(findEntity1);

	Odelay++;
	if (!targetList.empty() && Odelay >= delay) {
		vec3 pos = *targetList[0]->getPos();
		if (autoweapon) findWeapon();
		if (!pushm) {
			C_MovePlayerPacket p(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
			C_LocalPlayer* player = g_Data.getLocalPlayer();
			player->setPos(pos);
		} else {
			float dist2 = gm->player->getPos()->dist(pos);
			g_Data.getLocalPlayer()->lerpTo(pos, vec2(1, 1), (int)fmax((int)dist2 * 0.1, 1));
		}
		Odelay = 0;
	}

	if (sex) {
		delay2++;
		g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = false;
		if (delay2 >= delay1) {
			g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = true;
			delay2 = 0;
		}
		if (delay1 <= 1) {
			delay1 = 2;
		}
	}
}

void InsideAura::onEnable() {
	if (g_Data.getLocalPlayer() == nullptr)
		setEnabled(false);
}