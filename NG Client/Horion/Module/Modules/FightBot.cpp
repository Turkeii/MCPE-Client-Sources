#include "FightBot.h"

FightBot::FightBot() : IModule(0x0, Category::COMBAT, "Attacks entities around you automatically") {
	registerIntSetting("TargetRange", &targ, targ, 50, 500);
	registerFloatSetting("HitRange", &range, range, 2.f, 20.f);
	registerIntSetting("delay", &delay, delay, 0, 20);
	registerBoolSetting("MultiAura", &isMulti, isMulti);
	registerBoolSetting("MobAura", &isMobAura, isMobAura);
	registerBoolSetting("hurttime", &hurttime, hurttime);
	registerBoolSetting("AutoWeapon", &autoweapon, autoweapon);
	registerBoolSetting("Silent Rotations", &silent, silent);
	registerBoolSetting("NoSwing", &noSwing, noSwing);
}

FightBot::~FightBot() {
}

const char* FightBot::getModuleName() {
		return "FightBot";
}

struct CompareTargetEnArray {
	bool operator()(C_Entity* lhs, C_Entity* rhs) {
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
	}
};

static std::vector<C_Entity*> targetList;
void findadEntity(C_Entity* currentEntity, bool isRegularEntity) {
	std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
	static auto FightBotMod = moduleMgr->getModule<FightBot>();

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

	if (currentEntity->width <= 0.1f || currentEntity->height <= 0.1f)  // Don't hit this pesky antibot on 2b2e.org
		return;

	if (FightBotMod->isMobAura) {
		if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 63)
			return;
		if (currentEntity->width <= 0.01f || currentEntity->height <= 0.01f)  // Don't hit this pesky antibot on 2b2e.org
			return;
		if (currentEntity->getEntityTypeId() == 64)  // item
			return;
		if (currentEntity->getEntityTypeId() == 69)  // xp
			return;
	} else {
		if (!Target::isValidTarget(currentEntity))
			return;
	}

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
	if (dist < FightBotMod->targ) {
		targetList.push_back(currentEntity);
	}
}

void FightBot::findWeapon() {
	if (g_Data.isInGame()) {
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
}

void FightBot::onTick(C_GameMode* gm) {
	std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
	targetListA = targetList.empty();
	if (g_Data.isInGame()) {
		g_Data.forEachEntity(findadEntity);
		g_Data.getClientInstance()->getMoveTurnInput()->forward = true;
		g_Data.getClientInstance()->getLocalPlayer()->setSprinting(true);
		if (autoweapon) findWeapon();
		if (!targetList.empty()) {
			Odelay++;
			if (Odelay >= delay) {
				if (isMulti) {
					for (auto& i : targetList) {
						float dist = (*i->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
						if (!(i->damageTime > 1 && hurttime) && dist < range) {
							if (!noSwing)
								g_Data.getLocalPlayer()->swing();
							g_Data.getCGameMode()->attack(i);
						}
					}
				} else {
					float dist = (*targetList[0]->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
					if (!(targetList[0]->damageTime > 1 && hurttime) && dist < range) {
						if (!noSwing)
							g_Data.getLocalPlayer()->swing();
						g_Data.getCGameMode()->attack(targetList[0]);
					}
				}
				Odelay = 0;
			}
		}
	}
}

void FightBot::onLevelRender() {
	std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
	targetListA = targetList.empty();
	if (g_Data.isInGame()) {
		targetList.clear();
		g_Data.forEachEntity(findadEntity);

		if (!targetList.empty()) {
			if (sexy) {
				joe = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos()).normAngles();
				C_LocalPlayer* player = g_Data.getLocalPlayer();
				vec2 angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos()).normAngles();
				player->bodyYaw = angle.x;
				player->bodyYaw = angle.y;
			}
			int prevSlot;
			if (autoweapon) {
				auto supplies = g_Data.getLocalPlayer()->getSupplies();
				prevSlot = supplies->selectedHotbarSlot;
				auto FinishSelect = true;
				auto inv = supplies->inventory;
				for (int n = 0; n < 9; n++) {
					C_ItemStack* stack = inv->getItemStack(n);
					if (stack->item != nullptr) {
						if (stack->getItem()->isWeapon()) {
							if (prevSlot != n)
								supplies->selectedHotbarSlot = n;
							return;
						}
					}
				}
			}
		}
	}
	if (!g_Data.isInGame())
		setEnabled(false);
}

void FightBot::onEnable() {
	std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
	targetList.clear();
	if (g_Data.isInGame()) {
		if (g_Data.getLocalPlayer() == nullptr)
			setEnabled(false);
	}
}
void FightBot::onDisable() {
	targetList.clear();
	g_Data.getClientInstance()->getMoveTurnInput()->forward = false;
	g_Data.getClientInstance()->getLocalPlayer()->setSprinting(false);
	g_Data.getClientInstance()->getMoveTurnInput()->clearMovementState();
}

void FightBot::onSendPacket(C_Packet* packet) {
	if (g_Data.isInGame()) {
		if (!g_Data.isInGame()) {
			auto hop = moduleMgr->getModule<Bhop>();
			hop->setEnabled(false);
		}
		targetListA = targetList.empty();
		targetList.clear();
		g_Data.forEachEntity(findadEntity);
		std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
		if (packet->isInstanceOf<C_MovePlayerPacket>() && g_Data.getLocalPlayer() != nullptr && silent) {
			if (!targetList.empty()) {
				auto* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
				vec2 angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos());
				movePacket->pitch = angle.x;
				movePacket->headYaw = angle.y;
				movePacket->yaw = angle.y;
			}
		}
	}
}