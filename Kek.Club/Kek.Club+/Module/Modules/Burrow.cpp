#include "Burrow.h"

#include "../ModuleManager.h"

Burrow::Burrow() : IModule(0, Category::WORLD, "Burrow Into Blocks") {
	enum1 = SettingEnum(this)
				.addEntry(EnumEntry("Obsidian", 1))
				.addEntry(EnumEntry("EndChest", 2))
				.addEntry(EnumEntry("All", 3));
	registerEnumSetting("Mode", &enum1, 2);
	this->registerBoolSetting("Rotate", &this->center, this->center);
}

Burrow::~Burrow() {
}
const char* Burrow::getModName() {
	if (enum1.selected == 1) {
		return " [Obsidian]";
	} else {
		return " [Enderchest]";
	}
}
const char* Burrow::getModuleName() {
	return ("Burrow");
}

bool Burrow::isFlashMode() {
	return false;
}

bool Burrow::Center() {
	g_Data.getLocalPlayer()->applyTurnDelta(&vec2_t((float)(rand() % (2 * -1 - 1) + (-1)), (float)(rand() % (2 * -1 - 1) + (-1))));
	return true;
}

bool Burrow::tryScaffold(vec3_t blockBelow) {
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

			checklist.push_back(new vec3_ti(0, 0, -1));
			checklist.push_back(new vec3_ti(0, 0, 1));

			checklist.push_back(new vec3_ti(-1, 0, 0));
			checklist.push_back(new vec3_ti(1, 0, 0));
		}
		bool foundCandidate = false;
		int i = 0;
		for (auto current : checklist) {
			vec3_ti calc = blok.sub(*current);
			if (!((g_Data.getLocalPlayer()->region->getBlock(calc)->blockLegacy))->material->isReplaceable) {
				// Found a solid block to click
				foundCandidate = true;
				blok = calc;
				break;
			}
			i++;
		}

		if (center) Center();
		bool idk = false;
		g_Data.getCGameMode()->buildBlock(&blok, i, idk);

		return true;
	}
	return false;
}

void Burrow::onTick(C_GameMode* gm) {
	auto clickguiMods = moduleMgr->getModule<Burrow>();
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	if (g_Data.getLocalPlayer() == nullptr)
		return;
	if (!g_Data.canUseMoveKeys())
		return;

	if (enum1.selected == 1) {
		for (int n = 0; n < 9; n++) {
			C_ItemStack* stack = g_Data.getLocalPlayer()->getSupplies()->inventory->getItemStack(n);
			if (stack->item != nullptr) {
				if (stack->getItem()->itemId == 130) {
					g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot = n;
				}
			}
		}
	}
	if (enum1.selected == 0) {
		for (int n = 0; n < 9; n++) {
			C_ItemStack* stack = g_Data.getLocalPlayer()->getSupplies()->inventory->getItemStack(n);
			if (stack->item != nullptr) {
				if (stack->getItem()->itemId == 49) {
					g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot = n;
				}
			}
		}
	}

	if (enum1.selected == 2) {
		C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
		C_Inventory* inv = supplies->inventory;
		for (int n = 0; n < 9; n++) {
			C_ItemStack* stack = inv->getItemStack(n);
			if (stack->item != nullptr) {
				if (stack->getItem()->isBlock()) {
					supplies->selectedHotbarSlot = n;
				}
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
void Burrow::onEnable() {}

void Burrow::onDisable() {
}

float timer = 0.f;

void Burrow::onSendPacket(C_Packet* packet) {
	vec3_t* pos = g_Data.getLocalPlayer()->getPos();
	if (packet->isInstanceOf<C_MovePlayerPacket>()) {
		C_MovePlayerPacket* InputPacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
		if (timer = 1) {
			InputPacket->Position.y = static_cast<float>(pos->y + 0.41999998688698);
		}
		if (timer = 2) {
			InputPacket->Position.y = static_cast<float>(pos->y + 0.7531999805211997);
		}
		if (timer = 3) {
			InputPacket->Position.y = static_cast<float>(pos->y + 1.00133597911214);
		}
		if (timer = 4) {
			InputPacket->Position.y = static_cast<float>(pos->y + 1.16610926093821);
		}
		if (timer = 5) {
			timer = 0.f;
		}
	} else if (packet->isInstanceOf<C_MovePlayerPacket>()) {
		C_MovePlayerPacket* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
		movePacket->Position.y = static_cast<float>(pos->y - 1.16610926093821);
	}
}