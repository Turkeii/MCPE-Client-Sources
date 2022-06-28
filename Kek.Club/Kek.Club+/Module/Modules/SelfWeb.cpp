#include "../ModuleManager.h"
#include "SelfWeb.h"

SelfWeb::SelfWeb() : IModule(0, Category::WORLD, "Automatically places webs on you") {
	registerBoolSetting("Rotate", &center, center);
	registerBoolSetting("Center", &centerblock, centerblock);
	registerBoolSetting("Rotations", &rots, rots);
	registerBoolSetting("Silent", &spoof, spoof);
}

SelfWeb::~SelfWeb() {
}
const char* SelfWeb::getModuleName() {
	return ("SelfWeb");
}
bool SilentSwapSW(int Itemid) {
	__int64 id = *g_Data.getLocalPlayer()->getUniqueId();
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	for (int n = 0; n < 9; n++) {
		C_ItemStack* stack = inv->getItemStack(n);
		if (stack->item != nullptr) {
			if ((*stack->item)->itemId != 0) {
				if (stack->getItem()->itemId == Itemid) {
					C_MobEquipmentPacket a(id, *stack, n, n);
					g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);
					return true;
				}
			}
		}
	}
	return false;
}

bool isInInvSW(int Itemid) {
	__int64 id = *g_Data.getLocalPlayer()->getUniqueId();
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	for (int n = 0; n < 9; n++) {
		C_ItemStack* stack = inv->getItemStack(n);
		if (stack->item != nullptr) {
			if ((*stack->item)->itemId != 0) {
				if (stack->getItem()->itemId == Itemid) {
					return true;
				}
			}
		}
	}
	return false;
}
// made this fast so its a bit bad but yea add autodisable too
bool SelfWeb::isFlashMode() {
	return true;
}
	bool SelfWeb::Center() {
	g_Data.getLocalPlayer()->applyTurnDelta(&vec2_t((float)(rand() % (2 * -1 - 1) + (-1)), (float)(rand() % (2 * -1 - 1) + (-1))));
	return true;
}
	bool SelfWeb::CenterBlock() {
		vec3_t yR = vec3_t(floor(g_Data.getLocalPlayer()->getPos()->x), g_Data.getLocalPlayer()->getPos()->y, floor(g_Data.getLocalPlayer()->getPos()->z));
		yR.x += 0.5f;
		// yR.y += 2.3f;
		yR.z += 0.5f;
		g_Data.getLocalPlayer()->setPos(yR);
		return true;
	}
	bool SelfWeb::tryScaffold(vec3_t blockBelow) {
		C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();

		if (input == nullptr)
			return false;

		blockBelow = blockBelow.floor();

		C_Block* block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blockBelow));
		C_BlockLegacy* blockLegacy = (block->blockLegacy);
		if (blockLegacy->material->isReplaceable) {
			vec3_ti blok(blockBelow);

			// Find neighbour
			static std::vector<vec3_ti*> checklist;
			if (checklist.empty()) {
				checklist.push_back(new vec3_ti(0, -1, 0));
				checklist.push_back(new vec3_ti(0, 1, 0));
			}
			bool foundCandidate = false;
			int i = 0;
			for (auto current : checklist) {
				vec3_ti calc = blok.sub(*current);
				if (!((g_Data.getLocalPlayer()->region->getBlock(calc)->blockLegacy))->material->isReplaceable) {
					// Found a solid block to click
					foundCandidate = true;
					if (isInInvSW(30)) SilentSwapSW(30);
					C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
					bool idk = false;
					if (moduleMgr->getModule<Surround>()->playSound)
						g_Data.getLocalPlayer()->pointingStruct->playStringSound("block.itemframe.place", *g_Data.getLocalPlayer()->getPos(), 1.f, 1.f);
					g_Data.getCGameMode()->buildBlock(&blok, i, idk);
					if (g_Data.getLocalPlayer()->isAlive() && g_Data.getLocalPlayer()->getSelectedItemId() != 0 && supplies != nullptr && supplies->inventory != nullptr && supplies->selectedHotbarSlot != -1 && supplies->inventory->getItemStack(supplies->selectedHotbarSlot) != nullptr && supplies->inventory->getItemStack(supplies->selectedHotbarSlot)->getItem() != nullptr && supplies->inventory->getItemStack(supplies->selectedHotbarSlot)->item != nullptr && !supplies->inventory->getItemStack(supplies->selectedHotbarSlot)->getItem()->isWeapon() && !supplies->inventory->getItemStack(supplies->selectedHotbarSlot)->getItem()->isShooter()) {
						__int64 id = *g_Data.getLocalPlayer()->getUniqueId();
						C_ItemStack* stack = supplies->inventory->getItemStack(supplies->selectedHotbarSlot);
						C_MobEquipmentPacket a(id, *stack, supplies->selectedHotbarSlot, supplies->selectedHotbarSlot);
						g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);
					}
					return true;
				}
			}
			return false;
		}
	}
	void SelfWeb::onPreTick(C_GameMode* gm) {
	auto clickguiMods = moduleMgr->getModule<SelfWeb>();
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	if (g_Data.getLocalPlayer() == nullptr)
		return;
	if (!g_Data.canUseMoveKeys())
		return;

		for (int n = 0; n < 9; n++) {
			C_ItemStack* stack = g_Data.getLocalPlayer()->getSupplies()->inventory->getItemStack(n);
			if (stack->item != nullptr) {
				if (stack->getItem()->itemId == 30) {
					g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot = n;
				}
			}
		}


	int place = 1;

	vec3_t blockSide = g_Data.getLocalPlayer()->eyePos0;

	blockSide.y -= g_Data.getLocalPlayer()->height - 1;

	if (!tryScaffold(blockSide)) {
		blockSide.y -= 0;
		blockSide.x -= 0;
	}
}
void SelfWeb::onEnable() {}

void SelfWeb::onDisable() {
}
float timmmmer = 0.f;
void SelfWeb::onSendPacket(C_Packet* packet) {
	vec3_t* pos = g_Data.getLocalPlayer()->getPos();
	if (packet->isInstanceOf<C_MovePlayerPacket>()) {
		C_MovePlayerPacket* InputPacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
		if (timmmmer = 1) {
			InputPacket->Position.y = static_cast<float>(pos->y + 0.41999998688698);
		}
		if (timmmmer = 2) {
			InputPacket->Position.y = static_cast<float>(pos->y + 0.7531999805211997);
		}
		if (timmmmer = 3) {
			InputPacket->Position.y = static_cast<float>(pos->y + 1.00133597911214);
		}
		if (timmmmer = 4) {
			InputPacket->Position.y = static_cast<float>(pos->y + 1.16610926093821);
		}
		if (timmmmer = 5) {
			timmmmer = 0.f;
		}
	} else if (packet->isInstanceOf<C_MovePlayerPacket>()) {
		C_MovePlayerPacket* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
		movePacket->Position.y = static_cast<float>(pos->y - 1.16610926093821);
	}
}
void SelfWeb::onPlayerTick(C_Player* plr) {
	if (rots)
		plr->pitch = 90;
}