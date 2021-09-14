#include "InsideAura.h"

InsideTP::InsideTP() : IModule(0x0, Category::COMBAT, "Tp's U To The Nearest Player/Mob") {
	this->registerBoolSetting("MobAura", &this->isMobAura, this->isMobAura);
	this->registerBoolSetting("UnlimitedRange", &this->unlim, this->unlim);
	this->registerBoolSetting("Bypass", &this->pushm, this->pushm);
	this->registerFloatSetting("Range", &this->range, this->range, 0.5f, 20.f);
	this->registerIntSetting("Delay", &this->delay, this->delay, 0, 20);
	this->registerBoolSetting("Silent Rotations", &this->silent, this->silent);
	this->registerBoolSetting("Killaura", &this->Kill, this->Kill);
	this->registerBoolSetting("MobAura 4 Killaura", &this->Killmob, this->Killmob);
}

InsideTP::~InsideTP() {
}

const char* InsideTP::getModuleName() {
	return ("InsideAura");
}

static std::vector<C_Entity*> targetList;

void findEntity1(C_Entity* currentEntity, bool isRegularEntity) {
	static auto insideMod = moduleMgr->getModule<InsideTP>();

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

	if (insideMod->isMobAura) {
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

void InsideTP::onTick(C_GameMode* gm) {
	auto Kill = moduleMgr->getModule<Killaura>();
	//Loop through all our players and retrieve their information
	targetList.clear();

	g_Data.forEachEntity(findEntity1);

	Odelay++;
	if (!targetList.empty() && Odelay >= delay) {
		vec3_t pos = *targetList[0]->getPos();
		if (this->Kill) {
			Kill->setEnabled(true);
		}

		if (!pushm) {
			//if (g_Data.getLocalPlayer()->velocity.squaredxzlen() < 0.01) {
			C_MovePlayerPacket p(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
			//}
			C_LocalPlayer* player = g_Data.getLocalPlayer();
			player->setPos(pos);
		} else {
			float dist2 = gm->player->getPos()->dist(pos);
			g_Data.getLocalPlayer()->lerpTo(pos, vec2_t(1, 1), (int)fmax((int)dist2 * 0.1, 1));
		}
		Odelay = 0;
	}
}

void InsideTP::onEnable() {
	if (g_Data.getLocalPlayer() == nullptr)
		this->setEnabled(false);
}

void InsideTP::onSendPacket(C_Packet* packet) {
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

void InsideTP::onDisable() {
	auto Kill = moduleMgr->getModule<Killaura>();
	if (this->Kill) {
		Kill->setEnabled(false);
	}
}