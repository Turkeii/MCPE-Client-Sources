#include "Regen.h"
#include "../../../../SDK/CAttribute.h"
#include "../pch.h"

using namespace std;
Regen::Regen() : IModule(0, Category::COMBAT, "Regenerates your health") {
	registerEnumSetting("Mode", &mode, 0);
	mode.addEntry("Vanilla", 0);
	mode.addEntry("Hive", 1);
	registerFloatSetting("Range", &range, range, 1, 7);
	registerIntSetting("Delay", &delay, delay, 0, 20);
	registerBoolSetting("Swing", &swing, swing);
}

const char* Regen::getRawModuleName() {
	return "Heal";
}

const char* Regen::getModuleName() {
	if (mode.getSelectedValue() == 0) name = string("Heal");
	if (mode.getSelectedValue() == 1) name = string("Heal");
	return name.c_str();
}

bool Regen::selectPickaxe() {
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	auto prevSlot = supplies->selectedHotbarSlot;

	for (int n = 0; n < 36; n++) {
		C_ItemStack* stack = inv->getItemStack(n);
		if (stack->item != nullptr) {
			if (stack->getItem()->isPickaxe()) {
				if (prevSlot != n)
					supplies->selectedHotbarSlot = n;
				return true;
			}
		}
	}
	return false;
}

void Regen::onEnable() {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	slot = supplies->selectedHotbarSlot;
}

void Regen::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr || moduleMgr->getModule<Scaffold>()->isEnabled()) return;
	tick++;

	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	auto timerUtil = new TimerUtil();
	static vector<vec3_ti> blocks;

	if (tick == delay) tick = 0;
	if (g_Data.canUseMoveKeys()) {
		switch (mode.getSelectedValue()) {
		case 0: // Vanilla
			// nothing lol
			break;
		case 1: // Hive
			if (blocks.empty()) {
				for (int x = -range; x <= range; x++) {
					for (int z = -range; z <= range; z++) {
						for (int y = -range; y <= range; y++) {
							blocks.push_back(vec3_ti(x, y, z));
						}
					}
				}
				// https://www.mathsisfun.com/geometry/pythagoras-3d.html sort = a12 + a22 + √(x2 + y2 + z2) + an2 √(a12 + a22 + √(x2 + y2 + z2) + an2) / 4.f
				sort(blocks.begin(), blocks.end(), [](vec3_ti start, vec3_ti end) {
					return sqrtf((start.x * start.x) + (start.y * start.y) + (start.z * start.z)) < sqrtf((end.x * end.x) + (end.y * end.y) + (end.z * end.z));
				});
			}

			for (const vec3_ti& offset : blocks) {
				blockPos = gm->player->getPos()->add(offset.toVector3());
				destroy = false;

				string name = gm->player->region->getBlock(blockPos)->toLegacy()->name.getText();
				if (name == "lit_redstone_ore" || name == "redstone_ore" /* && attribute->getCurrentHealth() < 10*/)
					destroy = true;

				int aids = delay - 1;
				if (destroy && tick >= aids) {
					slot = supplies->selectedHotbarSlot;
					static bool restored = false;
					if (!selectPickaxe()) {
						if (!restored) restored = true;
						else {
							//auto warning = g_Data.addNotification("Regen", "No Pickaxe Found"); warning->duration = 3;
							setEnabled(false);
						}
						return;
					}
					restored = false;

					bool isDestroyed = false;
					gm->startDestroyBlock(blockPos, 1, isDestroyed);
					gm->destroyBlock(&blockPos, 0); hasDestroyed = true;
					supplies->selectedHotbarSlot = slot;
					if (!swing) player->swing();
					return;
				}

				if (hasDestroyed) { hasDestroyed = false; blocksBroke += 1; }
				if (blocksBroke > 5) blocksBroke = 0;
			}
			break;
		}
	}
}

void Regen::onPlayerTick(C_Player* plr) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
}

void Regen::onSendPacket(C_Packet* packet) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (packet->isInstanceOf<C_MovePlayerPacket>()) {
		auto* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);

		switch (mode.getSelectedValue()) {
		case 1: // Hive
			if (destroy) {
				vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(vec3_t(blockPos.x, blockPos.y, blockPos.z));
				movePacket->headYaw = angle.y;
				movePacket->yaw = angle.y;
				movePacket->pitch = angle.x;
			}
			break;
		}
	}
}

void Regen::onDisable() {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	blocksBroke = 0;
	destroy = false;
	tick = 0;
}
