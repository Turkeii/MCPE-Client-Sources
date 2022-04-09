#include "surround.h"

#include "../../DrawUtils.h"
#include "../ModuleManager.h"

Surround::Surround() : IModule(0x0, Category::WORLD, "Surrounds you in obsidian for less damage") {
	enum1 = SettingEnum(this)
				.addEntry(EnumEntry("AntiCity", 1))
				.addEntry(EnumEntry("Normal", 2));
	registerEnumSetting("Mode", &enum1, 2);
	registerBoolSetting("Spoof", &silentSwitch, false);
	registerBoolSetting("Render", &renderSurround, true);
	registerBoolSetting("Disable Complete", &disableOnComplete2, true);
}

Surround::~Surround() {
}

const char* Surround::getModuleName() {
	return "Surround";
}

bool SilentSwap(int Itemid) {
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
	C_MobEquipmentPacket a(id, *g_Data.getLocalPlayer()->getSelectedItem(), supplies->selectedHotbarSlot, supplies->selectedHotbarSlot);
	g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);
	return false;
}

bool isInInv(int Itemid) {
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

bool SurroundCheck(vec3 blockBelow) {
	blockBelow = blockBelow.floor();

	C_Block* block = g_Data.getLocalPlayer()->region->getBlock(vec3i(blockBelow));
	C_BlockLegacy* blockLegacy = (block->blockLegacy);
	if (blockLegacy->material->isReplaceable) {
		vec3i blok(blockBelow);

		// Find neighbour
		static std::vector<vec3i*> checklist;
		if (checklist.empty()) {
			checklist.push_back(new vec3i(0, -1, 0));
			checklist.push_back(new vec3i(0, 1, 0));

			checklist.push_back(new vec3i(0, 0, -1));
			checklist.push_back(new vec3i(0, 0, 1));

			checklist.push_back(new vec3i(-1, 0, 0));
			checklist.push_back(new vec3i(1, 0, 0));
		}

		bool foundCandidate = false;
		int i = 0;
		for (auto current : checklist) {
			vec3i calc = blok.sub(*current);
			bool Y = ((g_Data.getLocalPlayer()->region->getBlock(calc)->blockLegacy))->material->isReplaceable;
			if (!((g_Data.getLocalPlayer()->region->getBlock(calc)->blockLegacy))->material->isReplaceable) {
				// Found a solid block to click
				foundCandidate = true;
				blok = calc;
				break;
			}
			i++;
		}
		if (foundCandidate) {
			if(isInInv(49)) SilentSwap(49);
			g_Data.getCGameMode()->buildBlock(&blok, i);
			return true;
		}
	}
	return false;
}

void Surround::onTick(C_GameMode* gm) {
	if (g_Data.getLocalPlayer() == nullptr) return;

	auto selectedItem = g_Data.getLocalPlayer()->getSelectedItem();
	if (!isInInv(49)) {
		setEnabled(false);
		return;
	}

	if (surrArr.empty()) {
		doReset = true;
	} else {
		doReset = false;
	}
	if (doReset == true) {
		surrArr.clear();

		if (enum1.selected == 1)
			for (auto surroundBlock : regularBlocks) {
				auto playerPosition = g_Data.getLocalPlayer()->getPos();
				auto flooredPos = playerPosition->floor();
				flooredPos.y -= 1.f;
				auto mathsBlockPos = flooredPos.add(surroundBlock);

				if (g_Data.getLocalPlayer()->region->getBlock(mathsBlockPos)->toLegacy()->blockId == 0)
					surrArr.push_back(surroundBlock);
			}
		if (enum1.selected == 0)
			for (auto surroundBlock : antiCityBlocks) {
				auto playerPosition = g_Data.getLocalPlayer()->getPos();
				auto flooredPos = playerPosition->floor();
				flooredPos.y -= 1.f;
				auto mathsBlockPos = flooredPos.add(surroundBlock);

				if (g_Data.getLocalPlayer()->region->getBlock(mathsBlockPos)->toLegacy()->blockId == 0)
					surrArr.push_back(surroundBlock);
			}
	}

	vec3 yR = vec3(floor(g_Data.getLocalPlayer()->getPos()->x), g_Data.getLocalPlayer()->getPos()->y, floor(g_Data.getLocalPlayer()->getPos()->z));
	yR.x += 0.5f;
	yR.z += 0.5f;
	g_Data.getLocalPlayer()->setPos(yR);

	for (auto surroundBlock : surrArr) {
		auto playerPosition = g_Data.getLocalPlayer()->getPos();
		auto flooredPos = playerPosition->floor();
		flooredPos.y -= 1.f;
		auto mathsBlockPos = flooredPos.add(surroundBlock);

		SurroundCheck(mathsBlockPos);
		surrArr.erase(surrArr.begin());
		break;
	}
	if (surrArr.empty() && disableOnComplete2) setEnabled(false);
}

void Surround::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	if (g_Data.getLocalPlayer() == nullptr) return;

	if (renderSurround) {
		if (enum1.selected == 1) {
			for (auto surroundBlock : regularBlocks) {
				DrawUtils::setColor(1.f, 0.f, 1.f, 1.f);

				auto playerPosition = g_Data.getLocalPlayer()->getPos();

				auto flooredPos = playerPosition->floor();
				flooredPos.y -= 1.f;

				auto mathsBlockPos = flooredPos.add(surroundBlock);

				auto vec1 = vec3(1.f, 0.2f, 1.f);

				if (g_Data.getLocalPlayer()->region->getBlock(mathsBlockPos)->toLegacy()->blockId == 0)
					DrawUtils::drawBox(mathsBlockPos, mathsBlockPos.add(vec1), 1.f, true);
			}

		} else if (enum1.selected == 0) {
			for (auto surroundBlock : antiCityBlocks) {
				DrawUtils::setColor(1.f, 0.f, 1.f, 1.f);

				auto playerPosition = g_Data.getLocalPlayer()->getPos();

				auto flooredPos = playerPosition->floor();
				flooredPos.y -= 1.f;

				auto mathsBlockPos = flooredPos.add(surroundBlock);

				auto vec1 = vec3(1.f, 0.2f, 1.f);

				if (g_Data.getLocalPlayer()->region->getBlock(mathsBlockPos)->toLegacy()->blockId == 0)
					DrawUtils::drawBox(mathsBlockPos, mathsBlockPos.add(vec1), 1.f, true);
			}

		} else {
			for (auto surroundBlock : regularBlocks) {
				DrawUtils::setColor(1.f, 1.f, 0.f, 1.f);

				auto playerPosition = g_Data.getLocalPlayer()->getPos();

				auto flooredPos = playerPosition->floor();
				flooredPos.y -= 1.f;

				auto mathsBlockPos = flooredPos.add(surroundBlock);

				auto vec1 = vec3(1.f, 0.2f, 1.f);

				if (g_Data.getLocalPlayer()->region->getBlock(mathsBlockPos)->toLegacy()->blockId == 0)
					DrawUtils::drawBox(mathsBlockPos, mathsBlockPos.add(vec1), 1.f, true);
			}
		}
	}
}