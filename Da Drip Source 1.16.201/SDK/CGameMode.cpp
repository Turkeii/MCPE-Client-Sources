#include "CGameMode.h"

#include "../Memory/GameData.h"

void C_GameMode::survivalDestroyBlockHack(vec3_ti const &block, int face, bool &isDestroyedOut, bool isFirst) {
	auto p = this->player;
	p->swing();
	if (isFirst)
		this->startDestroyBlock(block, face, isDestroyedOut);
	else {
		*reinterpret_cast<bool *>(reinterpret_cast<__int64>(p) + 0x1c5a) = 1;
		this->continueDestroyBlock(block, face, isDestroyedOut);
	}

	p->startDestroying();

	// prevents regular code from aborting block-break
	*reinterpret_cast<bool *>(reinterpret_cast<__int64>(p) + 0x1c5a) = 0;

	C_PlayerActionPacket action;
	action.action = 18;
	action.blockPosition = vec3_ti(block.x, block.y, block.z);
	action.face = face;
	action.entityRuntimeId = p->entityRuntimeId;
	g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&action);
}

/*   
returns what mob type an entity is.

0 = other
1 = player
2 = Monster
3 = Animal
4 = Item
//5 = Projectile



*/

int C_GameMode::getMobType(C_Entity *entToCheck) {
	int checkID = entToCheck->getEntityTypeId();

	//if (passiveIds.)

	if (entToCheck == nullptr)
		return 0;

	if (entToCheck->getEntityTypeId() == 63)  //player
		return 1;

	if (entToCheck->getEntityTypeId() == 64)  //item
		return 4;

	if (std::find(hostileIds.begin(), hostileIds.end(), checkID) != hostileIds.end()) return 2;

	if (std::find(otherIds.begin(), otherIds.end(), checkID) != otherIds.end()) return 0;

	if (std::find(passiveIds.begin(), passiveIds.end(), checkID) != passiveIds.end()) return 3;

	return 0;
}
