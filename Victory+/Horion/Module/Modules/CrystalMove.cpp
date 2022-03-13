#include "CrystalMove.h"

CrystalMove::CrystalMove() : IModule('U', Category::COMBAT, "Move Crystal") {
	registerIntSetting("Range", &this->range, this->range, 1, 10);
	registerIntSetting("Crystal range", &this->cRange, this->cRange, 1, 15);
	registerIntSetting("Place range", &this->eRange, this->eRange, 1, 5);
	registerIntSetting("Player range", &this->pRange, this->pRange, 1, 10);
}
CrystalMove::~CrystalMove() {
}
const char* CrystalMove::getModuleName() {
	return ("CrystalMove");
}

static std::vector<C_Entity*> targetList;

void CrystalMove::onEnable() {
	targetList.clear();
}

bool findEntityCMove(C_Entity* curEnt, bool isRegularEntity) {
	if (curEnt == nullptr) return false;
	if (curEnt == g_Data.getLocalPlayer()) return false;  // Skip Local player
	if (!curEnt->isAlive()) return false;
	if (!g_Data.getLocalPlayer()->isAlive()) return false;
	if (curEnt->getEntityTypeId() == 71) return false;  // endcrystal
	if (curEnt->getEntityTypeId() == 66) return false;  // falling block
	if (curEnt->getEntityTypeId() == 64) return false;  // item
	if (curEnt->getEntityTypeId() == 69) return false;  // xp orb
	if (!Target::isValidTarget(curEnt)) return false;

	float dist = (*curEnt->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
	if (dist <= moduleMgr->getModule<CrystalMove>()->pRange) {
		targetList.push_back(curEnt);
		return true;
	}
	return false;
}

void CrystalMove::onTick(C_GameMode* gm) {
	if (supplies == nullptr)
		supplies = g_Data.getLocalPlayer()->getSupplies();
	if (inv == nullptr)
		inv = supplies->inventory;
	targetList.clear();
	g_Data.forEachEntity(findEntityCMove);
		g_Data.forEachEntity([](C_Entity* ent, bool b) {
			if (targetList.empty()) return;
			int id = ent->getEntityTypeId();
			int range = moduleMgr->getModule<CrystalMove>()->range;
			C_MovePlayerPacket p(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
			if (id == 71 && g_Data.getLocalPlayer()->getPos()->dist(*ent->getPos()) <= range) {
				vec3_t pos = *targetList[0]->getPos();
				pos.y -= 1.3;
				ent->setPos(pos);
			}
		});  //*/
	}