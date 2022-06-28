#include "AutoCrystal.h"
#include <tuple>
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"

// Sort by distance
struct CompareTargetDist {
	bool operator()(C_Entity* lhs, C_Entity* rhs) {
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
	}
};

const char* AutoCrystal::getModName() {
	switch (dmgEnum.selected) {
	case dmg_java:
		return " [Java]";
		break;
	case dmg_2b2e:
		return " [2b2e]";
		break;
	case dmg_nukkit:
		return " [Nukkit]";
		break;
	case dmg_vanilla:
		return " [Vanilla]";
		break;
	}
}
bool SilentSwapCA(int Itemid) {
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

bool isInInvCA(int Itemid) {
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
void AutoCrystal::onPreTick(C_GameMode* gm) {
	if (g_Data.getLocalPlayer() != nullptr) {
		if (renderTimer > 0)
			renderTimer--;

		renderCrystal = (renderTimer > 0);

		packetSent = false;
		isPlayerAuthInput = false;
		rotate = false;

		if (switchCooldown > 0)
			return;

		if (ReturnOnEat)
			if (g_Data.getLocalPlayer()->getSupplies()->inventory->getItemStack(g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot)->getItem()->isFood() && g_Data.isRightClickDown()) return;

		if (!g_Data.getLocalPlayer()->isAlive())
			return;
		if (stopOnInv) {
			if (!GameData::canUseMoveKeys())  // TODO: Find out if 2b2e.org kicks you for placing in inventory
				return;
		} else {
			if (!GameData::canUseMoveKeys())  // TODO: Find out if 2b2e.org kicks you for placing in inventory
				false;
		}
		if (stopOnClick) {
			if (!GameData::isLeftClickDown())
				bool shouldPlace = true;

			return;
		} else {
			if (!GameData::isLeftClickDown())
				false;
		}
		if (!GameData::isRightClickDown() && rightClick) {
			if (previousSlot != -1) {
				g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot = previousSlot;
			}
			previousSlot = -1;
			return;
		}

		if (!autoPlace)
			disableAutoplace = true;
		if(silentSwitch)
			disableAutoplace = false;

		static int oBDelay = 0;
		static int oPDelay = 0;

		bool placed = false;

		vec3_t playerPos = *g_Data.getLocalPlayer()->getPos();

		std::vector<C_Entity*> targetList;
		std::vector<C_Entity*> allEnts;

		if (oPDelay >= placeDelay && !disableAutoplace) {
			oPDelay = 0;

			g_Data.forEachEntity([&](C_Entity* ent, bool isNormal) {
				if (!ent->isAlive())
					return;

				if (ent->getPos()->dist(*g_Data.getLocalPlayer()->getPos()) > 12.f + placeRange)
					return;

				if (ent == g_Data.getLocalPlayer()) {
					allEnts.push_back(ent);
					return;
				}

				if (!Target::isValidTarget(ent))
					return;
				allEnts.push_back(ent);
				targetList.push_back(ent);
			});

			//Sorts their distance
			std::sort(targetList.begin(), targetList.end(), CompareTargetDist());

			if (!targetList.empty()) {
				if (silentSwitch) {
					if (switchCooldown > 0)
						return;
					placed = doPlace(targetList, allEnts, g_Data.getCGameMode());
				}
				if (findCrystal() && autoSelect) {
					if (switchCooldown > 0)
						return;

					placed = doPlace(targetList, allEnts, g_Data.getCGameMode());

					if (rotations.GetSelectedEntry().GetValue() == rotations_antikick && placeDelay == breakDelay) {
						// Allow AutoDestroy to work if we are going to take priority over it again
						disableAutoplace = true;
					}
				}
			} else if (!rightClick && !flash) {
				if (previousSlot != -1) {
					g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot = previousSlot;
					previousSlot = -1;
				}
			}
		} else if (oPDelay >= placeDelay && disableAutoplace) {
			oPDelay = 0;
			disableAutoplace = false;
		} else {
			oPDelay++;
		}

		if (oBDelay >= breakDelay) {
			oBDelay = 0;

			std::vector<C_Entity*> crystalList;
			g_Data.forEachEntity([&](C_Entity* ent, bool isNormal) {
				if (ent->getEntityTypeId() != 71)  // Crystals only
					return;

				if (!ent->isAlive())
					return;
				if (g_Data.getLocalPlayer()->getHealth() <= minHealth)
					return;
				if (suicide) {
					minHealth = 0.f;
					maxSelfDmg = 32.f;
				}
				if (ent->getPos()->dist(*g_Data.getLocalPlayer()->getPos()) > hitRange)
					return;

				if (destroyEnum.GetSelectedEntry().GetValue() == destroy_check) {
					if (ent->getPos()->dist(*g_Data.getLocalPlayer()->getPos()) < minBreak)
						return;
					float dmg = computeExplosionDamage(ent, g_Data.getLocalPlayer(), g_Data.getLocalPlayer()->region, dmgEnum.GetSelectedEntry().GetValue());

					if (dmg >= (float)maxSelfDmg)
						return;

					if (targetList.empty())
						return;

					bool enoughTargets = false;
					bool enoughDmg = false;

					for (auto i : targetList) {
						if (i->getPos()->dist(*ent->getPos()) < 12.f) {
							enoughTargets = true;
						}

						if (computeExplosionDamage(ent, i, g_Data.getLocalPlayer()->region, dmgEnum.GetSelectedEntry().GetValue())) {
							enoughDmg = true;
						}
					}

					if (!enoughTargets && !enoughDmg)
						return;
				}

				if (botCheck) {
					float offX = ent->getPos()->sub(ent->getPos()->floor()).x;
					float offZ = ent->getPos()->sub(ent->getPos()->floor()).z;
					if (offX != 0.5f || offZ != 0.5f)
						return;
				}
				crystalList.push_back(ent);
			});
			// Sorts their distance
			std::sort(crystalList.begin(), crystalList.end(), CompareTargetDist());
			doDestroy(crystalList, g_Data.getCGameMode(), placed);
		} else {
			oBDelay++;
		}
	}
}
float animYaw = 0.f;

void AutoCrystal::onTick(C_GameMode* gm) {
	if (gm == nullptr || g_Data.getLocalPlayer() == nullptr)
		return;

	//g_Data.getLocalPlayer()->pointingStruct->rayHitType = 1;
	// Utils::nopBytes((unsigned char*)HiveBypass69, 3);
	// Utils::patchBytes((unsigned char*)HiveBypass692, (unsigned char*)"\xC7\x40\x18\x00\x00\x00\x00", 7);
	if (rotations.GetSelectedEntry().GetValue() == rotations_arora) {
		if (moduleMgr->getModule<Disabler>()->Server.selected != 0)
		moduleMgr->getModule<Disabler>()->Server.selected = 0;
		if (!moduleMgr->getModule<Disabler>()->isEnabled())
		moduleMgr->getModule<Disabler>()->setEnabled(true);
	}
	if (!toBreak.empty() && rotations.GetSelectedEntry().GetValue() == rotations_normal) {
		vec2_t targetRot2 = g_Data.getLocalPlayer()->getPos()->CalcAngle(*toBreak[0]->getPos()).normAngles();

		if (animYaw > targetRot2.y)
			animYaw -= ((animYaw - targetRot2.y) / 2);
		else if (animYaw < targetRot2.y)
			animYaw += ((targetRot2.y - animYaw) / 2);

		breakRot = {targetRot2.x, animYaw};
	}

	if (switchCooldown > 0)
		switchCooldown--;

	int rotationMode = rotations.GetSelectedEntry().GetValue();

	if (rotate && !packetSent && !isPlayerAuthInput && rotationMode == rotations_antikick) {
		C_MovePlayerPacket pkt(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&pkt);

		rotate = false;
		packetSent = false;
	}

	if ((!toBreak.empty() || !toPlace.empty()) && !moduleMgr->getModule<NoSwing>()->isEnabled())
		g_Data.getLocalPlayer()->swing();

	// The preTick code did the funny for us so we can just blindly use the toPlace and toBreak stuff
	for (auto it = toPlace.begin(); it != toPlace.end(); ++it) {
		__int64 id = *g_Data.getLocalPlayer()->getUniqueId();
		C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
		if (silentSwitch && isInInvCA(637)) SilentSwapCA(637);
		g_Data.getCGameMode()->buildBlock(it._Ptr, 0, false);
		if (g_Data.getLocalPlayer()->isAlive() && g_Data.getLocalPlayer()->getSelectedItemId() != 0 && supplies != nullptr && supplies->inventory != nullptr && supplies->selectedHotbarSlot != -1 && supplies->inventory->getItemStack(supplies->selectedHotbarSlot) != nullptr && supplies->inventory->getItemStack(supplies->selectedHotbarSlot)->getItem() != nullptr && supplies->inventory->getItemStack(supplies->selectedHotbarSlot)->item != nullptr && !supplies->inventory->getItemStack(supplies->selectedHotbarSlot)->getItem()->isWeapon() && !supplies->inventory->getItemStack(supplies->selectedHotbarSlot)->getItem()->isShooter() && silentSwitch) {
			C_ItemStack* stack = supplies->inventory->getItemStack(supplies->selectedHotbarSlot);
			C_MobEquipmentPacket a(id, *stack, supplies->selectedHotbarSlot, supplies->selectedHotbarSlot);
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);
		}
		renderTimer = 10;
	}

	toPlace.clear();

	std::vector<C_Entity*> swap;

	g_Data.forEachEntity([&](C_Entity* ent, bool isNormal) {
		for (auto i : toBreak) {
			if (ent == i)
				swap.push_back(i);
		}
	});
	// Sorts their distance
	std::sort(swap.begin(), swap.end(), CompareTargetDist());
	toBreak = swap;  // Fix crash

	for (auto i : toBreak) {
		if (rotationMode == rotations_antikick) {
			C_MovePlayerPacket pkt(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());

			vec2_t calcAngle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*i->getPos());

			pkt.pitch = calcAngle.x;
			pkt.yaw = calcAngle.y;
			pkt.headYaw = calcAngle.y;

			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&pkt);
		}
		g_Data.getCGameMode()->attack(i);
		if (noSwing)
			return;
	}

	toBreak.clear();
}

void AutoCrystal::onPlayerTick(C_Player* plr) {
}

void AutoCrystal::onSendPacket(C_Packet* pkt) {
	int rotationMode = rotations.GetSelectedEntry().GetValue();
	if (rotationMode != rotations_arora) {
		if (pkt->isInstanceOf<PlayerAuthInputPacket>()) {
			isPlayerAuthInput = true;

			if (rotate) {
				PlayerAuthInputPacket* packet = (PlayerAuthInputPacket*)pkt;

				packet->pitch = rotateTarget.x;
				packet->yaw = rotateTarget.y;
				packet->yawUnused = rotateTarget.y;
			}
		}
		if (pkt->isInstanceOf<C_MovePlayerPacket>()) {
			packetSent = true;

			if (rotate) {
				auto* packet = (C_MovePlayerPacket*)pkt;

				packet->pitch = rotateTarget.x;
				packet->yaw = rotateTarget.y;
				packet->headYaw = rotateTarget.y;
			}
		}
	}
}

void AutoCrystal::onPreRender(C_MinecraftUIRenderContext* ctx) {
	if (!g_Data.isInGame()) {
		previousSlot = -1;
		if (flash)
			setEnabled(false);
	} else if (renderPlaced && GameData::canUseMoveKeys()) {
		if (renderCrystal) {
			DrawUtils::setColor(AutoCrystal::rFloat, AutoCrystal::gFloat, AutoCrystal::bFloat, 1.f);
			DrawUtils::drawBox(latestCrystal.pos.toVec3t(), latestCrystal.pos.add(1, 1, 1).toVec3t(), 1.f, true);
			if (renderdmg && renderCrystal) {
				vec2_t textPos = DrawUtils::worldToScreen(latestCrystal.pos.toVec3t().add(0.5f, 0.5f, 0.5f));
				std::string text = std::to_string((int)latestCrystal.enemyDmg);
				textPos.x -= DrawUtils::getTextWidth(&text, 0.8f) / 2.f;
				textPos.y -= DrawUtils::getFontHeight(0.8f) / 2.f;

				DrawUtils::drawText(textPos, &text, MC_Color(1.f, 1.f, 1.f), 0.8f);
			}
		}
	}
}
void AutoCrystal::onEnable() {
	if (flash && g_Data.getCGameMode() != nullptr) {
		findCrystal();
	}
	if (autoSelect) {
		// if (Osdelay >= sdelay) {
		auto inv = g_Data.getLocalPlayer()->getSupplies()->inventory;
		for (int i = 0; i < 9; i++) {
			C_ItemStack* stack = inv->getItemStack(i);
				if (stack->item != nullptr) {
					if (stack->getItem()->itemId == 637) {
						g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot = i;
						return;
					}
				}
			}
		}
		// g_Data.getClientInstance()->getGuiData()->displayClientMessageF("<%sKek.Club+%s> we %sgaming", GREEN, WHITE, DARK_GREEN);
	}

void AutoCrystal::onDisable() {
	// g_Data.getClientInstance()->getGuiData()->displayClientMessageF("<%sKek.Club+%s> we aint %sgaming %sno more", GREEN, WHITE, RED, RESET);
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	__int64 id = *g_Data.getLocalPlayer()->getUniqueId();
	if (silentSwitch) {
		if (g_Data.getLocalPlayer()->isAlive() && g_Data.getLocalPlayer()->getSelectedItemId() != 0 && supplies != nullptr && supplies->inventory != nullptr && supplies->selectedHotbarSlot != -1 && supplies->inventory->getItemStack(supplies->selectedHotbarSlot) != nullptr && supplies->inventory->getItemStack(supplies->selectedHotbarSlot)->getItem() != nullptr && supplies->inventory->getItemStack(supplies->selectedHotbarSlot)->item != nullptr && !supplies->inventory->getItemStack(supplies->selectedHotbarSlot)->getItem()->isWeapon() && silentSwitch) {
			C_ItemStack* stack = supplies->inventory->getItemStack(supplies->selectedHotbarSlot);
			C_MobEquipmentPacket a(id, *stack, supplies->selectedHotbarSlot, supplies->selectedHotbarSlot);
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);
		}
	}
	if (previousSlot != -1 && g_Data.getLocalPlayer() != nullptr)
		g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot = previousSlot;
	previousSlot = -1;

	// Utils::patchBytes((unsigned char*)HiveBypass69, (unsigned char*)"\x89\x41\x18", 3);
	// Utils::patchBytes((unsigned char*)HiveBypass692, (unsigned char*)"\xC7\x40\x18\x03\x00\x00\x00", 7);
	if (ReturnOnGapple) {
		auto inv = g_Data.getLocalPlayer()->getSupplies()->inventory;
		for (int i = 0; i < 9; i++) {
			C_ItemStack* stack = inv->getItemStack(i);
			if (stack->item != nullptr) {
				if (stack->getItem()->itemId == 259) {
					g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot = i;
					return;
				}
			}
		}
	}
}

bool AutoCrystal::isTooFar(vec2_t left, vec2_t right) {
	return right.sub(left).magnitude() >= 12.f;
}

void AutoCrystal::doDestroy(std::vector<C_Entity*> crystalList, C_GameMode* gm, bool didPlace) {
	if (crystalList.empty())
		return;

	vec3_t playerPos = *gm->player->getPos();
	vec2_t playerRot = gm->player->viewAngles;

	switch (rotations.GetSelectedEntry().GetValue()) {
	case rotations_off:
	case rotations_normal: {
		toBreak = crystalList;
	} break;
	case rotations_antikick: {
		if (rotate) {
			for (auto i : crystalList) {
				vec2_t targetAngle = playerPos.CalcAngle(*i->getPos());
				if (!isTooFar(rotateTarget, targetAngle)) {
					toBreak.push_back(i);
				}
			}
			break;
		}
		if (didPlace) {
			for (auto i : crystalList) {
				vec2_t targetAngle = playerPos.CalcAngle(*i->getPos());
				if (!isTooFar(playerRot, targetAngle)) {
					toBreak.push_back(i);
				}
			}
			break;
		}

		// Find the best crystal
		struct CrystalCompareStruct {
			vec3_t playerPos;
			vec2_t playerRot;
			std::vector<C_Entity*>* vec;

			CrystalCompareStruct(vec3_t pPos, vec2_t pRot, std::vector<C_Entity*>* v) : playerPos(pPos), playerRot(pRot), vec(v) {}

			bool operator()(C_Entity* left, C_Entity* right) {
				vec2_t leftAngle = playerPos.CalcAngle(*left->getPos());
				vec2_t rightAngle = playerPos.CalcAngle(*right->getPos());

				std::vector<C_Entity*> leftEnts;  // Crystals we can hit if we rotate to left
				std::vector<C_Entity*> rightEnts;

				for (auto i : *vec) {
					vec2_t tgtRot = playerPos.CalcAngle(*i->getPos());

					if (!AutoCrystal::isTooFar(leftAngle, tgtRot))
						leftEnts.push_back(i);

					if (!AutoCrystal::isTooFar(rightAngle, tgtRot))
						rightEnts.push_back(i);
				}

				return leftEnts.size() > rightEnts.size();
			}
		};

		std::sort(crystalList.begin(), crystalList.end(), CrystalCompareStruct(playerPos, playerRot, &crystalList));

		C_Entity* gamerCrystal = crystalList[0];
		vec2_t angle = playerPos.CalcAngle(*gamerCrystal->getPos());

		for (auto i : crystalList) {
			vec2_t ang = playerPos.CalcAngle(*i->getPos());

			if (!isTooFar(ang, angle))
				toBreak.push_back(i);
		}

		rotate = true;
		rotateTarget = angle;
	} break;
	case rotations_arora: {
		toBreak = crystalList;
	} break;
	}
}

bool AutoCrystal::doPlace(std::vector<C_Entity*> targetList, std::vector<C_Entity*> allEnts, C_GameMode* gm) {
	struct CrystalStruct {
		vec3_ti blockPos;
		vec3_t entPos;
		float selfDamage;
		float enemyDmgAvg;
		float maxDamage;
	};

	if (targetList.empty() && NoTargetDisable) this->setEnabled(false);

	std::vector<CrystalStruct> candidates;

	vec3_t playerPos = *gm->player->getPos();

	int rangeInt = (int)ceilf(placeRange);

	int dmgMode = dmgEnum.GetSelectedEntry().GetValue();

	static std::vector<vec3_ti> blocks;

	if (blocks.empty()) {
		for (int x = -rangeInt; x <= rangeInt; x++) {
			for (int y = -rangeInt; y <= rangeInt; y++) {
				for (int z = -rangeInt; z <= rangeInt; z++) {
					if (y <= -64 || y >= 319)
						continue;
					blocks.push_back(vec3_ti(x, y, z));
				}
			}
		}
		// https://www.mathsisfun.com/geometry/pythagoras-3d.html sort = a12 + a22 + √(x2 + y2 + z2) + an2 √(a12 + a22 + √(x2 + y2 + z2) + an2) / 4.f
		std::sort(blocks.begin(), blocks.end(), [](vec3_ti start, vec3_ti end) {
			return sqrtf((start.x * start.x) + (start.y * start.y) + (start.z * start.z)) < sqrtf((end.x * end.x) + (end.y * end.y) + (end.z * end.z));
		});
	}

	for (const vec3_ti& offset : blocks) {
		vec3_ti blockPos = g_Data.getLocalPlayer()->getPos()->add(offset.toVec3t());
		vec3_t center = blockPos.toVec3t().add(0.5f, 0.5f, 0.5f);

		if (center.dist(playerPos) > placeRange || center.add(0.f, 1.f, 0.f).dist(playerPos) > hitRange)  // Make sure we can place AND destroy
			continue;

		if (center.add(0.f, 1.f, 0.f).dist(playerPos) < minPlace)
			continue;

		// We want to make sure we can place here before doing an expensive string compare
		if (gm->player->region->getBlock(blockPos.add(0, 1, 0))->blockLegacy->blockId != 0)
			continue;

		if (gm->player->region->getBlock(blockPos.add(0, 2, 0))->blockLegacy->blockId != 0 && dmgMode != dmg_nukkit /* Nukkit lets us do this but 2b2e and vanilla does not */)
			continue;

		auto name = gm->player->region->getBlock(blockPos)->blockLegacy->name.getText();

		if (strcmp(name, "obsidian") != 0 && strcmp(name, "bedrock") != 0)
			continue;

		// Time for an even more expensive calculation
		AABB aabb(
			blockPos.add(0, 1, 0).toVec3t(),
			blockPos.add(0, 1, 0).toVec3t().add(1.f, dmgMode == dmg_nukkit ? 1.f : 2.f, 1.f));
		bool valid = true;
		for (auto ent : allEnts) {
			if (aabb.intersects(ent->aabb)) {
				valid = false;
				break;
			}
		}
		if (!valid)
			continue;

		valid = false;
		bool closeEnough = true;  // TODO

		// Enemy damage
		float enemyDmgAvg = 0.f;
		float maxDamage = 0.f;
		{
			int count = 0;  // How many enemies where damaged
			for (auto i : targetList) {
				float dmg = computeExplosionDamage(center.add(0.f, 1.f, 0.f), i, gm->player->region, dmgMode);

				if (dmg >= (float)minDamage) {
					maxDamage = fmaxf(maxDamage, dmg);
					enemyDmgAvg += dmg;
					count++;
				}
				if (dmg >= (float)minDamage)
					valid = true;
			}

			if (count != 0 && enemyDmgAvg > 0.f)
				enemyDmgAvg /= (float)count;
		}

		float selfDmg = computeExplosionDamage(center.add(0.f, 1.f, 0.f), gm->player, gm->player->region, dmgMode);

		if (!gm->player->region->rayTraceBlocks(center.add(0.f, 1.f, 0.f), playerPos, gm->player)) {
			if (center.dist(playerPos) > wallRange)
				continue;
			if (center.add(0.f, 1.f, 0.f).dist(playerPos) > wallRange)
				continue;
		}

		CrystalStruct crystal{};

		crystal.blockPos = blockPos;
		crystal.entPos = center.add(0.f, 1.f, 0.f);
		crystal.enemyDmgAvg = enemyDmgAvg;
		crystal.selfDamage = selfDmg;
		crystal.maxDamage = maxDamage;

		if (crystal.selfDamage >= crystal.enemyDmgAvg)
			continue;

		candidates.push_back(crystal);
	}

	if (candidates.empty())
		return false;

	struct CrystalCompareStruct {
		bool operator()(CrystalStruct& left, CrystalStruct& right) {
			return (left.enemyDmgAvg) > (right.enemyDmgAvg);
		}
	};

	std::sort(candidates.begin(), candidates.end(), CrystalCompareStruct());

	vec3_ti bestPos = candidates[0].blockPos;
	vec2_t targetRot = playerPos.CalcAngle(bestPos.toVec3t().add(0.f, 1.f, 0.f)).normAngles();

	if (animYaw > targetRot.y)
		animYaw -= ((animYaw - targetRot.y) / 2);
	else if (animYaw < targetRot.y)
		animYaw += ((targetRot.y - animYaw) / 2);

	placeRot = {targetRot.x, animYaw};

	int rotationMode = rotations.GetSelectedEntry().GetValue();

	if (rotationMode == rotations_normal) {
		C_MovePlayerPacket pkt(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
		pkt.pitch = targetRot.x;
		pkt.yaw = animYaw;
		pkt.headYaw = animYaw;

		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&pkt);
	}

	if (isTooFar(gm->player->viewAngles, targetRot) && rotations.GetSelectedEntry().GetValue() == rotations_antikick) {
		rotate = true;
		rotateTarget = targetRot;
	}

	CrystalRenderHolder crystal{};

	crystal.enemyDmg = candidates[0].maxDamage;  // TODO
	crystal.playerDmg = 0.f;
	crystal.pos = bestPos;

	latestCrystal = crystal;
	renderCrystal = true;
	toPlace.push_back(bestPos);

	return true;
}

bool AutoCrystal::findCrystal() {
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();

	int prevSlot = supplies->selectedHotbarSlot;
	if (silentSwitch)
		return true;
	auto funny = supplies->inventory->getItemStack(prevSlot);
	if (funny->item != nullptr) {
		if (strcmp(funny->getItem()->tileName.getText(), "item.end_crystal") == 0)  // Try blocking that nukkit
			return true;
		else if (!autoSelect)
			return false;
	} else if (!autoSelect) {
		return false;
	}

	for (auto i = 0; i < 9; i++) {
		C_ItemStack* item = supplies->inventory->getItemStack(i);

		if (item->item != nullptr) {
			if (strcmp(item->getItem()->tileName.getText(), "item.end_crystal") == 0) {
				supplies->selectedHotbarSlot = i;
				switchCooldown = 3;
				previousSlot = prevSlot;
				return true;
			}
		}
	}

	return false;
}

float AutoCrystal::computeExplosionDamage(vec3_t crystalPos, C_Entity* target, C_BlockSource* reg, int mode) {
	float explosionRadius = 12.f;  // 6 * 2

	vec3_t pos = *target->getPos();

	float dist = pos.dist(crystalPos) / explosionRadius;

	if (dist <= 1.f) {
		float exposure;
		float impact;
		int damage;
		using getSeenPercent_t = float(__fastcall*)(C_BlockSource*, vec3_t const&, AABB const&);
		static getSeenPercent_t getSeenPercent = reinterpret_cast<getSeenPercent_t>(FindSignature("40 53 55 41 56 48 81 ec ? ? ? ? 48 8b 05 ? ? ? ? 48 33 c4 48 89 84 24"));
		exposure = getSeenPercent(reg, crystalPos, target->aabb);
		impact = (1 - dist) * exposure;
		damage = (int)((impact * impact * 3.5f + impact * 0.5f * 7.f) * explosionRadius + 1.f);

		float finalDamage = (float)damage;

		int armorPoints = 0;
		int epf = 0;
		// int toughness = 0;

		for (int i = 0; i < 4; i++) {
			C_ItemStack* armor = target->getArmor(i);

			if (armor->item == nullptr)
				continue;

			armorPoints += (*armor->item)->getArmorValue();
			epf += (int)getBlastDamageEnchantReduction(armor);
		}

		finalDamage -= finalDamage * armorPoints * 0.04f;  // basic armor reduction

		finalDamage -= finalDamage * std::min(ceilf(std::min(epf, 25) * ((float)75 /* it's unneccessary to simulate randomness */ / 100)), 20.f) * 0.04f;  // enchant reduction

		// absorption and resistance are impossible to predict client side

		auto antiCrystalMod = moduleMgr->getModule<AntiCrystal>();

		int targetY = (int)floorf(antiCrystalMod->isEnabled() ? target->aabb.lower.y - antiCrystalMod->sink : target->aabb.lower.y);
		int crystalY = (int)floorf(crystalPos.y);

		if (targetY < crystalY && mode == dmg_2b2e)
			finalDamage /= 2.f;
		else if (mode == dmg_2b2e)
			finalDamage *= 2.f;

		return finalDamage;
	} else {
		return 0.f;
	}
}
float AutoCrystal::getBlastDamageEnchantReduction(C_ItemStack* armor) {
	float epf = 0.f;

	epf += armor->getEnchantValue(0);        // protection
	epf += armor->getEnchantValue(3) * 2.f;  // blast protection

	return epf;
}

float AutoCrystal::calculateBlockDensity(vec3_t vec, AABB bb, C_BlockSource* region) {
	double d0 = 1.0 / (((double)bb.upper.x - (double)bb.lower.x) * 2.0 + 1.0);
	double d1 = 1.0 / (((double)bb.upper.y - (double)bb.lower.y) * 2.0 + 1.0);
	double d2 = 1.0 / (((double)bb.upper.z - (double)bb.lower.z) * 2.0 + 1.0);
	double d3 = (1.0 - floor(1.0 / d0) * d0) / 2.0;
	double d4 = (1.0 - floor(1.0 / d2) * d2) / 2.0;
	auto player = g_Data.getLocalPlayer();

	if (d0 >= 0.0 && d1 >= 0.0 && d2 >= 0.0) {
		int i = 0;
		int j = 0;

		for (float f = 0.f; f <= 1.f; f = (float)((double)f + d0)) {
			for (float f1 = 0.f; f1 <= 1.f; f1 = (float)((double)f1 + d1)) {
				for (float f2 = 0.f; f2 <= 1.f; f2 = (float)((double)f2 + d2)) {
					double d5 = bb.lower.x + ((double)bb.upper.x - (double)bb.lower.x) * (double)f;
					double d6 = bb.lower.y + ((double)bb.upper.y - (double)bb.lower.y) * (double)f1;
					double d7 = bb.lower.z + ((double)bb.upper.z - (double)bb.lower.z) * (double)f2;
					if (region->rayTraceBlocks(vec3_t(d5 + d3, d6, d7 + d4), vec, player))
						i++;

					j++;
				}
			}
		}

		return (float)i / (float)j;
	} else {
		return 0.f;
	};
};