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

void C_GameMode::useItem(C_ItemStack& stack) {
	using baseUseItem = void (*)(C_GameMode*, C_ItemStack&);
	static baseUseItem baseUseItemFunc = reinterpret_cast<baseUseItem>(FindSignature("48 89 5C 24 ? 48 89 74 24 ? 55 57 41 56 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 48 8B F2 48 8B F9 45 33 F6 4C 89 75 ? E8 ? ? ? ? 4C 8B 00 BA ? ? ? ? 48 8B C8 41 FF 50 ? 48 8B D8 48 89 44 24 ? 48 85 C0 74 ? 33 D2 41 B8 ? ? ? ? 48 8B C8 E8 ? ? ? ? 48 8B CB E8 ? ? ? ? EB ? 49 8B C6 48 89 45 ? 48 8B 5F"));

	return baseUseItemFunc(this, stack);
}
