#pragma once
#include <vector>
#include "../../../Utils/HMath.h"
#include "../ModuleManager.h"
#include "Module.h"
#include "../../DrawUtils.h"
class AutoBuild : public IModule {
public:
	vec3i startBuildPos;
	std::vector<vec3i> schematic;
	std::vector<vec3i> currentSchematic;
	bool autoBuildAirPlace = false;
	int ogAutoBuildSlot = 0;
	bool setAutoBuildSlot = false;
	int noMultiRenderSoLessLag = 0;
	int Odelay = 0;

	AutoBuild() : IModule(0x0, Category::WORLD, "Automaticly builds a shlong"){
		registerBoolSetting("AirPlace", &autoBuildAirPlace, autoBuildAirPlace);
	};
	~AutoBuild(){};

	virtual const char* getModuleName() override {
		return "AutoBuild";
	}

	void onEnable() {
		setAutoBuildSlot = false;
		if (schematic.empty()) {
			// Balls
			for (int s = -1; s <= 1; s += 2) {
				for (int y = 0; y <= 4; y += 4) {
					for (int x = 2; x <= 4; x++) {
						for (int z = -1; z <= 1; z++) {
							schematic.push_back(vec3i(x * s, y, z));
						}
					}
				}
				for (int y = 1; y < 4; y++) {
					schematic.push_back(vec3i(5 * s, y, 0));
					schematic.push_back(vec3i(5 * s, y, 1));
					schematic.push_back(vec3i(5 * s, y, -1));
					schematic.push_back(vec3i(4 * s, y, 1));
					schematic.push_back(vec3i(4 * s, y, -1));
					schematic.push_back(vec3i(4 * s, y, 2));
					schematic.push_back(vec3i(4 * s, y, -2));
					schematic.push_back(vec3i(3 * s, y, 2));
					schematic.push_back(vec3i(3 * s, y, -2));
					schematic.push_back(vec3i(2 * s, y, 1));
					schematic.push_back(vec3i(2 * s, y, -1));
					schematic.push_back(vec3i(2 * s, y, 2));
					schematic.push_back(vec3i(2 * s, y, -2));
					schematic.push_back(vec3i(1 * s, y, 0));
					schematic.push_back(vec3i(1 * s, y, 1));
					schematic.push_back(vec3i(1 * s, y, -1));
				}
			}
			// Shaft
			schematic.push_back(vec3i(1, 4, 0));
			schematic.push_back(vec3i(0, 4, 0));
			schematic.push_back(vec3i(-1, 4, 0));
			schematic.push_back(vec3i(0, 4, 1));
			schematic.push_back(vec3i(0, 4, -1));
			for (int y = 5; y < 16; y++) {
				schematic.push_back(vec3i(1, y, 0));
				schematic.push_back(vec3i(-1, y, 0));
				schematic.push_back(vec3i(0, y, 1));
				schematic.push_back(vec3i(0, y, -1));
			}
			schematic.push_back(vec3i(-2, 14, 0));
			schematic.push_back(vec3i(-1, 14, 1));
			schematic.push_back(vec3i(-1, 14, -1));
			schematic.push_back(vec3i(0, 14, 2));
			schematic.push_back(vec3i(0, 14, -2));
			schematic.push_back(vec3i(1, 14, 1));
			schematic.push_back(vec3i(1, 14, -1));
			schematic.push_back(vec3i(2, 14, 0));
			schematic.push_back(vec3i(0, 15, 0));
			schematic.push_back(vec3i(0, 16, 0));
		}
		C_LocalPlayer* Player = g_Data.getLocalPlayer();
		if (Player != nullptr) {
			vec3 myPos = Player->getPos()->sub(0, 1, 0);
			startBuildPos = vec3i(floorf(myPos.x), floorf(myPos.y), floorf(myPos.z));
			currentSchematic.clear();
			for (vec3i p : schematic) {
				currentSchematic.push_back(startBuildPos.add(p));
			}
			setAutoBuildSlot = true;
			ogAutoBuildSlot = Player->getSupplies()->selectedHotbarSlot;
		} else {
			setEnabled(false);
		}
	}

	void onDisable() {
		C_LocalPlayer* Player = g_Data.getLocalPlayer();
		if (Player != nullptr) {
			if (setAutoBuildSlot == true) {
				Player->getSupplies()->selectedHotbarSlot = ogAutoBuildSlot;
			}
		}
	}

	void onLevelRender() {
		C_LocalPlayer* Player = g_Data.getLocalPlayer();
		if (Player != nullptr) {
			vec3 myPos = *Player->getPos();
			C_PlayerInventoryProxy* supplies = Player->getSupplies();
			C_Inventory* inv = supplies->inventory;
			C_ItemStack* handItem = inv->getItemStack(supplies->selectedHotbarSlot);
			if (handItem == nullptr || handItem->item == nullptr || !handItem->getItem()->isBlock() || !isUsefulBlock(handItem)) {
				for (int i = 0; i < 9; i++) {
					C_ItemStack* currentItemStack = inv->getItemStack(i);
					if (currentItemStack != nullptr && currentItemStack->item != nullptr) {
						if (currentItemStack->getItem()->isBlock()) {
							if (isUsefulBlock(currentItemStack)) {
								supplies->selectedHotbarSlot = i;
								break;
							}
						}
					}
				}
			}
			for (int i = 0; i < currentSchematic.size(); i++) {
				vec3i buildPos = currentSchematic.at(i);
				if (Player->getPos()->dist(vec3(buildPos.x + 0.5f, buildPos.y + 0.5f, buildPos.z + 0.5f)) <= 4.5f) {
					C_Block* block = Player->region->getBlock(buildPos);
					C_BlockLegacy* blockLegacy = block->toLegacy();

					if (blockLegacy->material->isReplaceable) {
						vec3i blok(buildPos);
						vec3i blockPosition(buildPos);
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
						if (autoBuildAirPlace == 1) {
							foundCandidate = true;
						} else {
							for (auto current : checklist) {
								vec3i calc = blok.sub(*current);
								bool Y = ((Player->region->getBlock(calc)->blockLegacy))->material->isReplaceable;
								if (!((Player->region->getBlock(calc)->blockLegacy))->material->isReplaceable) {
									// Found a solid block to click
									foundCandidate = true;
									blok = calc;
									break;
								}
								i++;
							}
						}
						if (foundCandidate) {
							vec3i beforethingy = vec3i(blok.x, blok.y, blok.z);
							vec3i* thingy = &beforethingy;
							g_Data.getCGameMode()->buildBlock(thingy, i);
							break;
						}
					} else {
						currentSchematic.erase(currentSchematic.begin() + i--);
					}
				}
				if (currentSchematic.empty()) {
					g_Data.getGuiData()->displayClientMessageF("%sFinished building!", GREEN);
					setEnabled(false);
				}
			}
		}
	}

	void onPreRender(C_MinecraftUIRenderContext* renderCtx) {
		if (noMultiRenderSoLessLag == 0)
			noMultiRenderSoLessLag = 2;
		else {
			noMultiRenderSoLessLag--;
			return;
		}
		C_LocalPlayer* Player = g_Data.getLocalPlayer();
		if (Player != nullptr) {
			Odelay++;
			if (Odelay < 180) {  // to stop lag
				vec2 res = g_Data.getGuiData()->windowSizeReal;
				vec3 camPos = g_Data.getClientInstance()->levelRenderer->getOrigin();
				vec3 myPos = *Player->getPos();
				for (vec3i p : currentSchematic) {
					vec3 bp(p.x, p.y, p.z);
					if (myPos.dist(bp.add(0.5f, 0.5f, 0.5f)) <= 4.5f)
						DrawUtils::setColor(10.f / 255.f, 255.f / 255.f, 10.f / 255.f, 1.f);
					else
						DrawUtils::setColor(85.f / 255.f, 150.f / 255.f, 85.f / 255.f, 1.f);
					DrawUtils::drawBox(bp, bp.add(1.f, 1.f, 1.f), 0.35f, true);
				}
				DrawUtils::setColor(0.f, 1.f, 0.f, 1.f);
				Odelay = 0;
			}
		}
	}

	bool isUsefulBlock(C_ItemStack* itemStack) {
		std::vector<std::string> uselessSubstrings = {"_button", "chest", "vine", "pressure_plate", "fence", "_wall", "_stairs", "_table", "furnace", "trapdoor", "command_block", "torch", "boombox"};
		std::vector<std::string> uselessNames = {"cake", "ladder", "tnt", "lever", "loom", "scaffolding", "web", "carpet", "sand", "gravel", "dragon_egg", "anvil"};
		std::string itemName = itemStack->getItem()->name.getText();
		for (auto substring : uselessSubstrings) {
			if (itemName.find(substring) != std::string::npos) {
				return 0;
			}
		}
		for (auto name : uselessNames) {
			if (itemName == name) {
				return 0;
			}
		}
		return 1;
	}

};
