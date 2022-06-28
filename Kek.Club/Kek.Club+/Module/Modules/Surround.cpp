#include "Surround.h"
#include "../../DrawUtils.h"
#include "../ModuleManager.h"
vec3_t* center_block;
bool center;
bool blockSwap = false;
int obyslot = -1;
bool sound1 = false;
bool sound2 = false;
bool sound3 = false;
bool sound4 = false;
bool echests = false;
Surround::Surround() : IModule(0, Category::WORLD, "surround urself with obi and such") {
enum1 = SettingEnum(this)
.addEntry(EnumEntry("AntiCity", 1))
.addEntry(EnumEntry("Normal", 2));
registerEnumSetting("Mode", &enum1, 2);
rotations = SettingEnum(this)
.addEntry(EnumEntry("Off", rotations_off))
.addEntry(EnumEntry("Normal", rotation))
.addEntry(EnumEntry("Aurora", rotations_arora));
registerEnumSetting("Rotations", &rotations, rotations_off);
registerBoolSetting("Silent Swap", &silentSwitch, true);
registerBoolSetting("Auto Swap", &blockSwap, false);
registerBoolSetting("Center", &center, false);
registerBoolSetting("Jump Disable", &jumpDisable, false);
registerBoolSetting("Disable Complete", &disableOnComplete2, false);
registerBoolSetting("EChests", &echests, false);
registerBoolSetting("Sound", &playSound, false);
registerEnumSetting("Sound Type", &sound, 0);
sound = SettingEnum(this)
.addEntry(EnumEntry("Place", 0))
.addEntry(EnumEntry("Respawn", 1))
.addEntry(EnumEntry("Portal", 2))
.addEntry(EnumEntry("Level Up", 3));
registerIntSetting("Blocks Per Tick", &tick_for_place, 12, 1, 20);
registerBoolSetting("Render", &renderSurround, false);
registerEnumSetting("Render Mode", &render, 0);
render = SettingEnum(this)
.addEntry(EnumEntry("Outline", 0))
.addEntry(EnumEntry("Box", 1));
registerFloatSetting("Red", &rFloat, 0.f, 0.f, 255.f);
registerFloatSetting("Green", &gFloat, 255.f, 0.f, 255.f);
registerFloatSetting("Blue", &bFloat, 0.f, 0.f, 255.f);
registerFloatSetting("Line Width", &thickness, 1.f, 0.1f, 1.f);
registerFloatSetting("Alpha", &alpha, 1.f, 0.1f, 1.f);
}
// why hardcode silent swap -_- nrg - xello
Surround::~Surround() {
}

const char* Surround::getModuleName() {
	return "Surround";
}

		vec3_t getCenter(double posX, double posY, double posZ) {
	vec3_t xyz = vec3_t(floor(g_Data.getLocalPlayer()->getPos()->x), g_Data.getLocalPlayer()->getPos()->y, floor(g_Data.getLocalPlayer()->getPos()->z));
	xyz.x += 0.5f;
	xyz.z += 0.5f;
	g_Data.getLocalPlayer()->setPos(xyz);
	return vec3_t(xyz.x, xyz.y, xyz.z);
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

bool SurroundCheck(vec3_t blockBelow) {
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
				if (((std::string)((g_Data.getLocalPlayer()->region->getBlock(calc)->blockLegacy))->name.getText()).find("anvil") == std::string::npos && ((std::string)((g_Data.getLocalPlayer()->region->getBlock(calc)->blockLegacy))->name.getText()).find("chest") == std::string::npos)
					// Found a solid block to click
					foundCandidate = true;
				blok = calc;
				break;
			}
			i++;
		}
		if (foundCandidate) {
			if (echests) {
				if (isInInv(130)) SilentSwap(130);
			} else
			if (isInInv(49)) SilentSwap(49);
			C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
			bool idk = false;
			if (moduleMgr->getModule<Surround>()->playSound) 
				if (sound1) {
					g_Data.getLocalPlayer()->pointingStruct->playStringSound("block.itemframe.place", *g_Data.getLocalPlayer()->getPos(), 1.f, 1.f);
				}
				if (sound2) {
				g_Data.getLocalPlayer()->pointingStruct->playStringSound("respawn_anchor.ambient", *g_Data.getLocalPlayer()->getPos(), 1.f, 1.f);
				}
				if (sound3) {
				g_Data.getLocalPlayer()->pointingStruct->playStringSound("block.end_portal_frame.fill", *g_Data.getLocalPlayer()->getPos(), 1.f, 1.f);
				} 
				if (sound4) {
					g_Data.getLocalPlayer()->pointingStruct->playStringSound("random.levelup", *g_Data.getLocalPlayer()->getPos(), 1.f, 1.f);
				} // dont yell at me for coding this bad haha fuck you
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

void Surround::onMove(C_MoveInputHandler* hand) {
	if (g_Data.getLocalPlayer() == nullptr) return;

	if (jumpDisable && hand->isJumping) setEnabled(false);
}

void Surround::onEnable() {
	if (blockSwap) {
		auto inv = g_Data.getLocalPlayer()->getSupplies()->inventory;
		for (int i = 0; i < 9; i++) {
			C_ItemStack* stack = inv->getItemStack(i);
			if (stack->item != nullptr) {
				if (stack->getItem()->itemId == 49, 130) {
							g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot = i;
							return;
						}
				}
			}
		}
	if (g_Data.getLocalPlayer() != nullptr) {
		y_level = (int)round(g_Data.getLocalPlayer()->getPos()->y);

		center_block = &getCenter(g_Data.getLocalPlayer()->getPos()->x, g_Data.getLocalPlayer()->getPos()->y, g_Data.getLocalPlayer()->getPos()->z);
		vec3_t moveVec;

		if (center) {
			moveVec.x = 0.5;
			moveVec.z = 0.5;
		}
	}
}
void Surround::onLevelRender() {
	switch (sound.selected) {
	case 0:
		sound1 = true;
		sound2 = false;
		sound3 = false;
		sound4 = false;
		break;
	case 1:
		sound1 = false;
		sound2 = true;
		sound3 = false;
		sound4 = false;
		break;
	case 2:
		sound1 = false;
		sound2 = false;
		sound3 = true;
		sound4 = false;
		break;
	case 3:
		sound1 = false;
		sound2 = false;
		sound3 = false;
		sound4 = true;
		break;
	}
	if (g_Data.getLocalPlayer() == nullptr) return;

	auto selectedItem = g_Data.getLocalPlayer()->getSelectedItem();
	if (echests) {
		(!isInInv(130));
	} else
	if (!isInInv(49)) {
		setEnabled(false);
		return;
	}

	if (rotations.GetSelectedEntry().GetValue() == rotations_arora) {
		if (moduleMgr->getModule<Disabler>()->Server.selected != 0)
			moduleMgr->getModule<Disabler>()->Server.selected = 0;
		if (!moduleMgr->getModule<Disabler>()->isEnabled())
			moduleMgr->getModule<Disabler>()->setEnabled(true);
	}
	int blocks_placed = 0;

	while (blocks_placed < tick_for_place) {
		if (offset_step >= (regularBlocks.size())) {
			offset_step = 0;
			break;
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
		offset_step++;
	}

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
				DrawUtils::setColor(Surround::rFloat, Surround::gFloat, Surround::bFloat, Surround::alpha);

				auto playerPosition = g_Data.getLocalPlayer()->getPos();

				auto flooredPos = playerPosition->floor();
				flooredPos.y -= 1.f;

				auto mathsBlockPos = flooredPos.add(surroundBlock);

				auto vec1 = vec3_t(1.f, 0.2f, 1.f);

				if (g_Data.getLocalPlayer()->region->getBlock(mathsBlockPos)->toLegacy()->blockId == 0)

					if (render.selected == 0) {
						DrawUtils::drawBox(mathsBlockPos, mathsBlockPos.add(vec1), Surround::thickness, true);
					}
				if (render.selected == 1) {
					DrawUtils::drawBox(mathsBlockPos, mathsBlockPos.add(1, 1, 1), Surround::thickness, true);
				}
			}

		} else if (enum1.selected == 0) {
			for (auto surroundBlock : antiCityBlocks) {
				DrawUtils::setColor(Surround::rFloat, Surround::gFloat, Surround::bFloat, Surround::alpha);

				auto playerPosition = g_Data.getLocalPlayer()->getPos();

				auto flooredPos = playerPosition->floor();
				flooredPos.y -= 1.f;

				auto mathsBlockPos = flooredPos.add(surroundBlock);

				auto vec1 = vec3_t(1.f, 0.1f, 1.f);

				if (g_Data.getLocalPlayer()->region->getBlock(mathsBlockPos)->toLegacy()->blockId == 0)
					if (render.selected == 1) {
						DrawUtils::drawBox(mathsBlockPos, mathsBlockPos.add(vec1), Surround::thickness, true);
					}
				if (render.selected == 0) {
					DrawUtils::drawBox(mathsBlockPos, mathsBlockPos.add(1, 1, 1), Surround::thickness, true);
				}
			}

		} else {
			for (auto surroundBlock : regularBlocks) {
				DrawUtils::setColor(Surround::rFloat, Surround::gFloat, Surround::bFloat, Surround::alpha);

				auto playerPosition = g_Data.getLocalPlayer()->getPos();

				auto flooredPos = playerPosition->floor();
				flooredPos.y -= 1.f;

				auto mathsBlockPos = flooredPos.add(surroundBlock);

				auto vec1 = vec3_t(1.f, 0.2f, 1.f);

				if (g_Data.getLocalPlayer()->region->getBlock(mathsBlockPos)->toLegacy()->blockId == 0)
					if (render.selected == 0) {
						DrawUtils::drawBox(mathsBlockPos, mathsBlockPos.add(vec1), Surround::thickness, true);
					}
				if (render.selected == 1) {
					DrawUtils::drawBox(mathsBlockPos, mathsBlockPos.add(1, 1, 1), Surround::thickness, true);
				}
			}
		}
	}
}

void Surround::onPlayerTick(C_Player* plr) {
}