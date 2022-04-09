#include "InfiniteAura.h"

InfiniteAura::InfiniteAura() : IModule(0x0, Category::COMBAT, "Killaura with infinite reach") {
	registerBoolSetting("Multiaura", &isMulti, isMulti);
	registerBoolSetting("Hive", &hivee, hivee);  //funni bypaz
	registerBoolSetting("MobAura", &isMobAura, isMobAura);
	registerBoolSetting("SetPacketPos", &packetfukery, packetfukery);  //"this is so god dang smart" -Intop 2021
	registerBoolSetting("Sexy Rotations", &sex, sex);
	registerFloatSetting("range", &range, range, 3, 500);
	registerIntSetting("delay", &delay, delay, 0, 30);
}

InfiniteAura::~InfiniteAura() {
	this->getMovePlayerPacketHolder()->clear();
	this->getPlayerAuthInputPacketHolder()->clear();
}

const char* InfiniteAura::getModuleName() {
	return ("InfiniteAura");
}

struct CompareTargetEnArray {
	bool operator()(C_Entity* lhs, C_Entity* rhs) {
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
	}
};

static std::vector<C_Entity*> targetList0;

void findEntities(C_Entity* currentEntity, bool isRegularEntitie) {
	static auto InfiniteAuraMod = moduleMgr->getModule<InfiniteAura>();

	if (currentEntity == g_Data.getLocalPlayer()) return;  // Skip Local player
	if (currentEntity == 0) return;
	if (currentEntity->timeSinceDeath > 0 || currentEntity->damageTime >= 7) return;
	if (FriendList::findPlayer(currentEntity->getNameTag()->getText())) return;//Skip Friend
	if (InfiniteAuraMod->isMobAura) {
	if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 63) return;
	if (currentEntity->width <= 0.01f || currentEntity->height <= 0.01f) return;//Don't hit this pesky antibot on 2b2e.org
	if (currentEntity->getEntityTypeId() == 64) return;//item
	} else {
	if (!Target::isValidTarget(currentEntity)) return;
	}

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < InfiniteAuraMod->range) {
		targetList0.push_back(currentEntity);
	}
}

void InfiniteAura::onEnable() {
	counter = 0;
	Odelay = 0;
}

void InfiniteAura::onTick(C_GameMode* gm) {
	if (g_Data.getClientInstance()->isInGame()) {
		targetList0.clear();
		g_Data.forEachEntity(findEntities);

		if (!targetList0.empty()) {
			targetListC = targetList0.empty();
			std::sort(targetList0.begin(), targetList0.end(), CompareTargetEnArray());
			Odelay++;

			if (targetList0.size() > 0 && Odelay >= delay) {
				g_Data.getLocalPlayer()->swingArm();

				float calcYaw = (gm->player->yaw + 90) * (PI / 180);
				float calcPitch = (gm->player->pitch) * -(PI / 180);

				float teleportX = cos(calcYaw) * cos(calcPitch) * 3.5f;
				float teleportZ = sin(calcYaw) * cos(calcPitch) * 3.5f;
				C_MovePlayerPacket teleportPacket;

				// Attack all entitys in targetList
				if (hivee) {
					if (isMulti) {
						for (int i = 0; i < targetList0.size(); i++) {
							vec3 pos = *targetList0[i]->getPos();
							teleportPacket = C_MovePlayerPacket(g_Data.getLocalPlayer(), vec3(pos.x - teleportX, pos.y, pos.z - teleportZ));
							g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&teleportPacket);
							g_Data.getCGameMode()->attack(targetList0[i]);
						}
					} else {
						vec3 pos = *targetList0[0]->getPos();
						teleportPacket = C_MovePlayerPacket(g_Data.getLocalPlayer(), vec3(pos.x, pos.y, pos.z));
						g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&teleportPacket);
						g_Data.getCGameMode()->attack(targetList0[0]);
					}
				} else {
					if (strcmp(g_Data.getRakNetInstance()->serverIp.getText(), "mco.cubecraft.net") == 0) {
						vec3 pos = *g_Data.getLocalPlayer()->getPos();

						C_MovePlayerPacket movePlayerPacket(g_Data.getLocalPlayer(), pos);
						g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&movePlayerPacket);

						pos.y += 0.35f;

						movePlayerPacket = C_MovePlayerPacket(g_Data.getLocalPlayer(), pos);
						g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&movePlayerPacket);
					}
					if (isMulti) {
						for (int i = 0; i < targetList0.size(); i++) {
							vec3 pos = *targetList0[i]->getPos();
							teleportPacket = C_MovePlayerPacket(g_Data.getLocalPlayer(), vec3(pos.x - teleportX, pos.y, pos.z - teleportZ));
							g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&teleportPacket);
							g_Data.getCGameMode()->attack(targetList0[i]);
							teleportPacket = C_MovePlayerPacket(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
							g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&teleportPacket);
						}
					} else {
						vec3 pos = *targetList0[0]->getPos();
						teleportPacket = C_MovePlayerPacket(g_Data.getLocalPlayer(), vec3(pos.x - teleportX, pos.y, pos.z - teleportZ));
						g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&teleportPacket);
						g_Data.getCGameMode()->attack(targetList0[0]);
						teleportPacket = C_MovePlayerPacket(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
						g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&teleportPacket);
					}
				}
				amogus = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList0[0]->getPos());
				Odelay = 0;
			}
		}
		if (counter == 30) {
			counter = 0;
		} else {
			counter++;
		}
		if (!g_Data.isInGame())
			setEnabled(false);
	}
}

void InfiniteAura::onSendPacket(C_Packet* packet) {  //this is big brain time
	if (packetfukery) {
		targetList0.clear();
		g_Data.forEachEntity(findEntities);

		if (!targetList0.empty()) {
			if (Odelay >= delay) {
				vec3 la = *targetList0[0]->getPos();
				if (packet->isInstanceOf<PlayerAuthInputPacket>()) {
					PlayerAuthInputPacket* InputPacket = reinterpret_cast<PlayerAuthInputPacket*>(packet);
					InputPacket->pos = la;
				} else if (packet->isInstanceOf<C_MovePlayerPacket>()) {
					C_MovePlayerPacket* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
					movePacket->Position = la;
				}
			}
		}
	}
}

void InfiniteAura::onDisable() {
	targetList0.clear();
	counter = 0;
	Odelay = 0;
}