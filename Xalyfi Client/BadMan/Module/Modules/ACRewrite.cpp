#include <tuple>

#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "ACRewrite.h"

bool shouldPlace = false;
bool shouldDestroy = false;

bool disableAutoplace = false;

bool rotate = false;
vec2_t rotateTarget = {0.f, 0.f};

bool packetSent = false;
bool isPlayerAuthInput = false;

int switchCooldown = 0;

int renderTimer;

void BPGRewrite::onPreTick(C_GameMode* gm) {
	if (renderTimer > 0)
		renderTimer--;

	renderCrystal = (renderTimer > 0);

	packetSent = false;
	isPlayerAuthInput = false;
	rotate = false;

	if (switchCooldown > 0)
		return;

	if (!gm->player->isAlive())
		return;

	if (gm->player->getHealth() < (float)minHealth)
		return;

	if (!GameData::canUseMoveKeys())  // TODO: Find out if 2b2e.org kicks you for placing in inventory
		return;

	if (!GameData::isRightClickDown() && rightClick) {
		if (previousSlot != -1) {
			gm->player->getSupplies()->selectedHotbarSlot = previousSlot;
		}
		previousSlot = -1;
		return;
	}

	if (!autoPlace)
		disableAutoplace = true;

	static int oBDelay = 0;
	static int oPDelay = 0;

	bool placed = false;

	vec3_t playerPos = *gm->player->getPos();

	std::vector<C_Entity*> targetList;
	std::vector<C_Entity*> allEnts;

	if (oPDelay >= placeDelay && !disableAutoplace) {
		oPDelay = 0;

		g_Data.forEachEntity([&](C_Entity* ent, bool isNormal) {
			if (!ent->isAlive())
				return;

			if (ent->getPos()->dist(*gm->player->getPos()) > 12.f + maxDistance)
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

		if (!targetList.empty()) {
			if (findCrystal(gm)) {
				if (switchCooldown > 0)
					return;

				placed = doPlace(targetList, allEnts, gm);

				if (rotations.GetSelectedEntry().GetValue() == rotations_antikick && placeDelay == breakDelay) {
					// Allow AutoDestroy to work if we are going to take priority over it again
					disableAutoplace = true;
				}
			}
		} else if (!rightClick && !flash) {
			if (previousSlot != -1) {
				gm->player->getSupplies()->selectedHotbarSlot = previousSlot;
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

			if (ent->getPos()->dist(*gm->player->getPos()) > maxDistance)
				return;

			if (destroyEnum.GetSelectedEntry().GetValue() == destroy_check) {
				if (ent->getPos()->dist(*gm->player->getPos()) < minDistance)
					return;

				float dmg = computeExplosionDamage(ent, gm->player, gm->player->region, dmgEnum.GetSelectedEntry().GetValue());

				if (dmg > (float)maxSelfDmg)
					return;

				if (gm->player->getHealth() - dmg <= 1.f && !suicide)
					return;

				if (targetList.empty())
					return;

				bool enoughTargets = false;
				bool enoughDmg = false;

				for (auto i : targetList) {
					if (i->getPos()->dist(*ent->getPos()) < 12.f) {
						enoughTargets = true;
					}

					if (computeExplosionDamage(ent, i, gm->player->region, dmgEnum.GetSelectedEntry().GetValue()) >= minDamage) {
						enoughDmg = true;
					}
				}

				if (!enoughTargets && !enoughDmg)
					return;
			}

			if (botCheck) {
				// Crystal Y level changes depending on the server but their x and y are always 0.5

				float offX = ent->getPos()->sub(ent->getPos()->floor()).x;
				float offZ = ent->getPos()->sub(ent->getPos()->floor()).z;

				if (offX != 0.5f || offZ != 0.5f)
					return;
			}

			//if (ent->getPos()->floor().add(0.5f, 0.5f, 0.5f).dist(*ent->getPos()) > 0.2f) {
			//	logF("Bot check failed");
			//	return;
			//} Uncomment when 2b2e inevitably adds bot crystals

			crystalList.push_back(ent);
		});

		doDestroy(crystalList, gm, placed);
	} else {
		oBDelay++;
	}
}

void BPGRewrite::onTick(C_GameMode* gm) {
	if (switchCooldown > 0)
		switchCooldown--;

	int rotationMode = rotations.GetSelectedEntry().GetValue();

	if (rotate && !packetSent && !isPlayerAuthInput && rotationMode == rotations_antikick) {
		C_MovePlayerPacket pkt(g_Data.getLocalPlayer(), *gm->player->getPos());
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&pkt);

		rotate = false;
		packetSent = false;
	}

	if ((!toBreak.empty() || !toPlace.empty()) && !moduleMgr->getModule<NoSwing>()->isEnabled())
		gm->player->swing();

	// The preTick code did the funny for us so we can just blindly use the toPlace and toBreak stuff
	for (auto it = toPlace.begin(); it != toPlace.end(); ++it) {
		if (rotationMode == rotations_normal) {
			C_MovePlayerPacket pkt(g_Data.getLocalPlayer(), *gm->player->getPos());

			vec2_t calcAngle = gm->player->getPos()->CalcAngle((*it).toVec3t().add(0.5f, 0.5f, 0.5f));

			pkt.pitch = calcAngle.x;
			pkt.yaw = calcAngle.y;
			pkt.headYaw = calcAngle.y;

			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&pkt);
		}
		gm->buildBlock(it._Ptr, 0);

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

	toBreak = swap;  // Fix crash

	for (auto i : toBreak) {
		if (rotationMode == rotations_antikick) {
			C_MovePlayerPacket pkt(g_Data.getLocalPlayer(), *gm->player->getPos());

			vec2_t calcAngle = gm->player->getPos()->CalcAngle(*i->getPos());

			pkt.pitch = calcAngle.x;
			pkt.yaw = calcAngle.y;
			pkt.headYaw = calcAngle.y;

			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&pkt);
		}
		gm->attack(i);
	}

	toBreak.clear();
}

void BPGRewrite::onSendPacket(C_Packet* pkt) {
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

void BPGRewrite::onPreRender(C_MinecraftUIRenderContext* ctx) {
	if (!g_Data.isInGame()) {
		previousSlot = -1;
		if (flash)
			setEnabled(false);
	} else if (renderPlaced && GameData::canUseMoveKeys()) {
		if (renderCrystal) {
			DrawUtils::setColor(0.f, 1.f, 0.f, 1.f);
			DrawUtils::drawBox(latestCrystal.pos.toVec3t(), latestCrystal.pos.add(1, 1, 1).toVec3t(), 1.f, true);

			vec2_t textPos = DrawUtils::worldToScreen(latestCrystal.pos.toVec3t().add(0.5f, 0.5f, 0.5f));
			std::string text = std::to_string((int)latestCrystal.enemyDmg);
			textPos.x -= DrawUtils::getTextWidth(&text, 0.8f) / 2.f;
			textPos.y -= DrawUtils::getFontHeight(0.8f) / 2.f;

			DrawUtils::drawText(textPos, &text, MC_Color(1.f, 1.f, 1.f), 0.8f);
		}
	}
}

void BPGRewrite::onEnable() {
	if (flash && g_Data.getCGameMode() != nullptr) {
		findCrystal(g_Data.getCGameMode());
	}
}

void BPGRewrite::onDisable() {
	if (previousSlot != -1 && g_Data.getLocalPlayer() != nullptr) {
		g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot = previousSlot;
	}
	previousSlot = -1;
}

bool BPGRewrite::isTooFar(vec2_t left, vec2_t right) {
	return right.sub(left).magnitude() > 10.f;
}

void BPGRewrite::doDestroy(std::vector<C_Entity*> crystalList, C_GameMode* gm, bool didPlace) {
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

					if (!BPGRewrite::isTooFar(leftAngle, tgtRot))
						leftEnts.push_back(i);

					if (!BPGRewrite::isTooFar(rightAngle, tgtRot))
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
	}
}

bool BPGRewrite::doPlace(std::vector<C_Entity*> targetList, std::vector<C_Entity*> allEnts, C_GameMode* gm) {
	struct CrystalStruct {
		vec3_ti blockPos;
		vec3_t entPos;
		float selfDamage;
		float enemyDmgAvg;
		float maxDamage;
	};

	std::vector<CrystalStruct> candidates;

	vec3_t playerPos = *gm->player->getPos();
	vec3_ti posFloored = playerPos.floor();

	int rangeInt = (int)ceilf(maxDistance);

	int dmgMode = dmgEnum.GetSelectedEntry().GetValue();

	for (int x = posFloored.x - rangeInt; x < posFloored.x + rangeInt; x++) {
		for (int y = posFloored.y - rangeInt; y < posFloored.y + rangeInt; y++) {
			for (int z = posFloored.z - rangeInt; z < posFloored.z + rangeInt; z++) {
				if (y < 0 || y >= 256)
					continue;

				vec3_ti blockPos(x, y, z);
				vec3_t center = blockPos.toVec3t().add(0.5f, 0.5f, 0.5f);

				if (center.dist(playerPos) > maxDistance || center.add(0.f, 1.f, 0.f).dist(playerPos) > maxDistance)  // Make sure we can place AND destroy
					continue;

				if (center.add(0.f, 1.f, 0.f).dist(playerPos) < minDistance)
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

						if (dmg > 0.f) {
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

				if (!valid || selfDmg > (float)maxSelfDmg || (gm->player->getHealth() - selfDmg <= 1.f && !suicide) || !closeEnough)
					continue;

				if (!tryRaytrace(center.add(0.f, 1.f, 0.f), playerPos, gm->player->region)) {
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
		}
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
	vec2_t targetRot = playerPos.CalcAngle(bestPos.toVec3t().add(0.5f, 0.5f, 0.5f));

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

bool BPGRewrite::findCrystal(C_GameMode* gm) {
	C_PlayerInventoryProxy* supplies = gm->player->getSupplies();

	int prevSlot = supplies->selectedHotbarSlot;

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

float BPGRewrite::computeExplosionDamage(vec3_t crystalPos, C_Entity* target, C_BlockSource* reg, int mode) {
	float explosionRadius = 12.f;  // 6 * 2

	vec3_t pos = *target->getPos();

	float dist = pos.dist(crystalPos) / explosionRadius;

	if (dist <= 1.f) {
		float exposure;
		float impact;
		int damage;
		if (mode != dmg_vanilla) {
			exposure = 1;
			if (mode == dmg_java) {
				exposure = calculateBlockDensity(crystalPos, AABB(target->aabb.lower, vec3_t(target->aabb.upper.x, fminf(target->aabb.lower.y + 1, target->aabb.upper.y), target->aabb.upper.z)), reg);
			}
			impact = (1 - dist) * exposure;
			damage = (int)(((impact * impact + impact) / 2) * 8 * explosionRadius + 1);
		} else {
			using getSeenPercent_t = float(__fastcall*)(C_BlockSource*, vec3_t const&, AABB const&);
			static getSeenPercent_t getSeenPercent = reinterpret_cast<getSeenPercent_t>(FindSignature("40 53 55 41 56 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4"));

			exposure = getSeenPercent(reg, crystalPos, target->aabb);
			impact = (1 - dist) * exposure;
			damage = (int)((impact * impact * 3.5f + impact * 0.5f * 7.f) * explosionRadius + 1.f);
		}
		float finalDamage = (float)damage;

		int armorPoints = 0;
		int epf = 0;
		//int toughness = 0;

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

		int targetY = (int)floorf(antiCrystalMod->isEnabled() ? target->aabb.lower.y - antiCrystalMod->distance : target->aabb.lower.y);
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

float BPGRewrite::getBlastDamageEnchantReduction(C_ItemStack* armor) {
	float epf = 0.f;

	epf += armor->getEnchantValue(0);        // protection
	epf += armor->getEnchantValue(3) * 2.f;  // blast protection

	return epf;
}

float BPGRewrite::calculateBlockDensity(vec3_t vec, AABB bb, C_BlockSource* region) {
	double d0 = 1.0 / (((double)bb.upper.x - (double)bb.lower.x) * 2.0 + 1.0);
	double d1 = 1.0 / (((double)bb.upper.y - (double)bb.lower.y) * 2.0 + 1.0);
	double d2 = 1.0 / (((double)bb.upper.z - (double)bb.lower.z) * 2.0 + 1.0);
	double d3 = (1.0 - floor(1.0 / d0) * d0) / 2.0;
	double d4 = (1.0 - floor(1.0 / d2) * d2) / 2.0;

	if (d0 >= 0.0 && d1 >= 0.0 && d2 >= 0.0) {
		int i = 0;
		int j = 0;

		for (float f = 0.f; f <= 1.f; f = (float)((double)f + d0)) {
			for (float f1 = 0.f; f1 <= 1.f; f1 = (float)((double)f1 + d1)) {
				for (float f2 = 0.f; f2 <= 1.f; f2 = (float)((double)f2 + d2)) {
					double d5 = bb.lower.x + ((double)bb.upper.x - (double)bb.lower.x) * (double)f;
					double d6 = bb.lower.y + ((double)bb.upper.y - (double)bb.lower.y) * (double)f1;
					double d7 = bb.lower.z + ((double)bb.upper.z - (double)bb.lower.z) * (double)f2;

					if (tryRaytrace(vec3_t(d5 + d3, d6, d7 + d4), vec, region)) {
						++i;
					}
					++j;
				}
			}
		}

		return (float)i / (float)j;
	} else {
		return 0.f;
	}
}

/*bool __forceinline collisionRayTrace(C_Block* block, vec3_t vec31, vec3_t vec32) {


	Vec3d vec3d = start.subtract((double)pos.getX(), (double)pos.getY(), (double)pos.getZ());
	Vec3d vec3d1 = end.subtract((double)pos.getX(), (double)pos.getY(), (double)pos.getZ());
	bool raytraceresult = boundingBox.calculateIntercept(vec3d, vec3d1);
	return !raytraceresult ? null : new RayTraceResult(raytraceresult.hitVec.addVector((double)pos.getX(), (double)pos.getY(), (double)pos.getZ()), raytraceresult.sideHit, pos);
}*/

bool BPGRewrite::tryRaytrace(vec3_t vec31, vec3_t vec32, C_BlockSource* region) {
	struct HitResult {
		char pad[0x18] = {0};
		int hitType = 0;  // 3 = MISS
		char pad2[0x50] = {0};
	};

	auto result = new HitResult();

	using BlockSource_ClipT = HitResult*(__fastcall*)(C_BlockSource*, HitResult*, vec3_t&, vec3_t&, bool, bool, int, bool, bool);
	static auto clip = reinterpret_cast<BlockSource_ClipT>(FindSignature("40 55 56 57 41 56 48 8D AC 24 ?? ?? ?? ??"));
	return false;
}