#include "PotionAura.h"

PotionAura::PotionAura() : IModule('P', Category::COMBAT, "Attacks entities around you automatically") {
	registerFloatSetting("Range", &range, range, 2.f, 20.f);
	registerIntSetting("Delay", &delay, delay, 0, 20);
	registerBoolSetting("MobAura", &isMobAura, isMobAura);
	registerBoolSetting("AutoSlot", &autoweapon, autoweapon);
	registerBoolSetting("Bad Rotations", &rotations, rotations);
	registerBoolSetting("Sexy Rotations", &sexy, sexy);
	registerBoolSetting("Server Rotations", &silent, silent);
}

PotionAura::~PotionAura() {
}

const char* PotionAura::getModuleName() {
		return "PotionAura";
}

struct CompareTargetEnArray {
	bool operator()(C_Entity* lhs, C_Entity* rhs) {
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
	}
};

static std::vector<C_Entity*> targetLissst;
void finnddEntity(C_Entity* currentEntity, bool isRegularEntity) {
	std::sort(targetLissst.begin(), targetLissst.end(), CompareTargetEnArray());
	static auto PotionAuraMod = moduleMgr->getModule<PotionAura>();

	if (currentEntity == nullptr) return;
	if (currentEntity == g_Data.getLocalPlayer()) return; // Skip Local player
	if (!g_Data.getLocalPlayer()->canAttack(currentEntity, false)) return;
	if (!g_Data.getLocalPlayer()->isAlive()) return;
	if (!currentEntity->isAlive()) return;
	if (currentEntity->width <= 0.10f || currentEntity->height <= 0.10f) return; // Don't hit this pesky antibot on 2b2e.org
	if (PotionAuraMod->isMobAura) {
		if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 63) return;
		if (currentEntity->width <= 0.01f || currentEntity->height <= 0.01f) return; // Don't hit this pesky antibot on 2b2e.org
		if (currentEntity->getEntityTypeId() == 64) return;  // item
		if (currentEntity->getEntityTypeId() == 69) return; // xp
	} else {
		if (!Target::isValidTarget(currentEntity)) return;
	}

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
	if (dist < PotionAuraMod->range) {
		targetLissst.push_back(currentEntity);
	}
}

void PotionAura::findWeapon() {
	if (g_Data.isInGame()) {
		C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
		supplies->selectedHotbarSlot = 8;
	}
}

void PotionAura::onTick(C_GameMode* gm) {
	targetListA = targetLissst.empty();
	if (g_Data.isInGame()) {
		g_Data.forEachEntity(finnddEntity);
		if (autoweapon) findWeapon();
		if (!targetLissst.empty()) {
			Odelay++;
			if (Odelay >= delay) {
				if (isMulti) {
					for (auto& i : targetLissst) {
						if (!(i->damageTime > 1 && hurttime)) {
							auto inv = g_Data.getLocalPlayer()->getSupplies()->inventory;
							C_ItemStack* stack = inv->getItemStack(8);
							C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
							Utils::rightClick();
						}
					}
				} else {
					if (!(targetLissst[0]->damageTime > 1 && hurttime)) {
						auto inv = g_Data.getLocalPlayer()->getSupplies()->inventory;
						C_ItemStack* stack = inv->getItemStack(8);
						C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
						Utils::rightClick();
					}
				}
				Odelay = 0;
			}
			if (rotations) {
				C_LocalPlayer* player = g_Data.getLocalPlayer();
				vec2 angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetLissst[0]->getPos()).normAngles();
				player->bodyYaw = angle.y;
			}
		}
	}
}

void PotionAura::onLevelRender() {
	if (g_Data.getClientInstance()->isInGame()) {
		C_ItemStack* yot = new C_ItemStack(***ItemRegistry::lookUpByName(std::make_unique<uintptr_t>().get(), std::make_unique<uintptr_t>().get(), TextHolder("lingering_potion")), 1, 24);
		g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, nullptr, nullptr, yot, nullptr, 1, 507, 99999));
		auto inv = g_Data.getLocalPlayer()->getSupplies()->inventory;
		C_ItemStack* stack = inv->getItemStack(8);
		if (stack->count != 1) {
			inv->setItem(8, *yot);
		}
	}
	targetListA = targetLissst.empty();
	if (g_Data.isInGame()) {
		targetLissst.clear();
		g_Data.forEachEntity(finnddEntity);

		if (!targetLissst.empty()) {
			if (sexy) {
				joe = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetLissst[0]->getPos()).normAngles();
				C_LocalPlayer* player = g_Data.getLocalPlayer();
				vec2 angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetLissst[0]->getPos()).normAngles();
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

void PotionAura::onEnable() {
	targetLissst.clear();
	if (g_Data.isInGame()) {
		if (g_Data.getLocalPlayer() == nullptr)
			setEnabled(false);
	}
}
void PotionAura::onDisable() {
	targetLissst.clear();
}
void PotionAura::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
}

void PotionAura::onPostRender(C_MinecraftUIRenderContext* ctx) {
}

void PotionAura::onSendPacket(C_Packet* packet) {
	if (g_Data.isInGame()) {
		if (!g_Data.isInGame()) {
			auto hop = moduleMgr->getModule<Bhop>();
			hop->setEnabled(false);
		}
		targetListA = targetLissst.empty();
		targetLissst.clear();
		g_Data.forEachEntity(finnddEntity);
		std::sort(targetLissst.begin(), targetLissst.end(), CompareTargetEnArray());
		if (packet->isInstanceOf<C_MovePlayerPacket>() && g_Data.getLocalPlayer() != nullptr && silent) {
			if (!targetLissst.empty()) {
				auto* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
				vec2 angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetLissst[0]->getPos());
				movePacket->pitch = angle.x;
				movePacket->headYaw = angle.y;
				movePacket->yaw = angle.y;
			}
		}
	}
}