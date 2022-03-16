#include "CrystalAura.h"
CrystalAura::CrystalAura() : IModule(0x0, Category::COMBAT, "Automatically place a crystal at the enemy's location and exploade it speedily.") {
	// registerBoolSetting("MultiAura", &multi, multi);

	dmgEnum = SettingEnum(this)
				  .addEntry(EnumEntry("Vanilla", dmg_vanilla))
				  .addEntry(EnumEntry("Java", dmg_java))
				  .addEntry(EnumEntry("2b2eOld", dmg_2b2e))
				  .addEntry(EnumEntry("2b2eLowOld", dmg_2b2elow));

	registerEnumSetting("Damage Mode", &dmgEnum, dmg_java);

	registerBoolSetting("Spoof", &spoof, spoof);
	registerBoolSetting("AutoPlace", &autoplace, autoplace);
	// registerBoolSetting("AutoSwitch", &autoswitch, autoswitch);
	registerIntSetting("Range", &range, range, 1, 10);
	registerIntSetting("Delay", &delay, delay, 0, 20);
	// registerBoolSetting("Hurttime", &HurtTime, HurtTime);
	registerEnumSetting("Rotations", &RotMode, rot_none);
	RotMode = SettingEnum(this)
				  .addEntry(EnumEntry("None", rot_none))
				  .addEntry(EnumEntry("Silent", rot_silent))
				  .addEntry(EnumEntry("Normal", rot_client));

	registerBoolSetting("VisualTarget", &VisTarget, VisTarget);
	registerBoolSetting("TargetHUD", &info, info);
	registerBoolSetting("Render", &render, render);
	// registerBoolSetting("bool", &bool1, bool1);
}

CrystalAura::~CrystalAura() {
}

int K3SRC = 0;
int K3SRC2 = 0;
int K3SRC3 = 0;
const char* CrystalAura::getModuleName() {
	return ("CrystalAura");
}

static std::vector<C_Entity*> targetList7;

void findEntityK3R(C_Entity* currentEntity, bool isRegularEntity) {
	static auto CrystalAuraMod = moduleMgr->getModule<CrystalAura>();

	if (currentEntity == nullptr)
		return;

	if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 71)  // crystal
		return;

	if (currentEntity == g_Data.getLocalPlayer())  // Skip Local player
		return;

	if (!g_Data.getLocalPlayer()->isAlive())
		return;

	if (!currentEntity->isAlive())
		return;

	if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 63)
		return;
	if (currentEntity->width <= 0.01f || currentEntity->height <= 0.01f)  // Don't hit this pesky antibot on 2b2e.org
		return;
	if (currentEntity->getEntityTypeId() == 64)  // item
		return;
	if (currentEntity->getEntityTypeId() == 69)  // xp_orb
		return;
	if (currentEntity->getEntityTypeId() == 80)  // arrow
		return;

	if (!Target::isValidTarget(currentEntity))
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < CrystalAuraMod->range) {
		targetList7.push_back(currentEntity);
	}
}

bool checkTargCollision12(vec3_t* block, C_Entity* ent) {
	std::vector<vec3_t*> corners;
	corners.clear();
	static auto CrystalAuraMod = moduleMgr->getModule<CrystalAura>();
	int dmgMode5 = CrystalAuraMod->dmgEnum.GetSelectedEntry().GetValue();

	if (dmgMode5 == CrystalAuraMod->dmg_2b2e) {
		corners.push_back(new vec3_t(ent->aabb.lower.x, ent->aabb.lower.y, ent->aabb.lower.z));
		corners.push_back(new vec3_t(ent->aabb.lower.x, ent->aabb.lower.y, ent->aabb.upper.z));
		corners.push_back(new vec3_t(ent->aabb.upper.x, ent->aabb.lower.y, ent->aabb.upper.z));
		corners.push_back(new vec3_t(ent->aabb.upper.x, ent->aabb.lower.y, ent->aabb.lower.z));
	}
	int n = 0;
	if (!corners.empty())
		for (auto corner : corners) {
			// DrawUtils::drawText(DrawUtils::worldToScreen(*corners[n]), &std::to_string(n + 1), MC_Color(1.f, 1.f, 1.f));
			// DrawUtils::setColor(1.f, 0.f, 0.f, 1.f);
			// if (g_Data.getLocalPlayer()->region->getBlock(vec3_ti(corners[n]->x, corners[n]->y - 0.5f, corners[n]->z))->toLegacy()->blockId != 0) {
			// DrawUtils::drawBox(vec3_t(floor(corners[n]->x), floor(corners[n]->y - 0.5f), floor(corners[n]->z)), g_Data.getLocalPlayer()->region->getBlock(vec3_ti(corners[n]->x, corners[n]->y - 0.5f, corners[n]->z))->toLegacy()->aabb.upper, 2.f);
			// DrawUtils::drawBox(vec3_t(floor(corners[n]->x), floor(corners[n]->y - 0.5f), floor(corners[n]->z)), vec3_t(floor(corners[n]->x) + 1.f, floor(corners[n]->y - 0.5f) + 1.f, floor(corners[n]->z) + 1.f), 2.f);
			n++;

			if ((floor(corner->x) == floor(block->x)) && (floor(corner->y) == floor(block->y)) && (floor(corner->z) == floor(block->z))) {
				//	DrawUtils::setColor(1.f, 0.f, 0.f, 0.5f);
				//	DrawUtils::drawBox(block->floor(), {floor(block->x) + 1.f, floor(block->y) + 1.f, floor(block->z) + 1.f}, 0.7f, false);
				return true;
				//	}
			}
		}

	return false;
}

bool checkSurrounded21(C_Entity* ent) {
	vec3_t entPos = ent->getPos()->floor();
	entPos.y -= 1;

	std::vector<vec3_ti*> blockChecks;
	blockChecks.clear();

	if (blockChecks.empty()) {
		blockChecks.push_back(new vec3_ti(entPos.x, entPos.y, entPos.z + 1));
		blockChecks.push_back(new vec3_ti(entPos.x, entPos.y, entPos.z - 1));
		blockChecks.push_back(new vec3_ti(entPos.x + 1, entPos.y, entPos.z));
		blockChecks.push_back(new vec3_ti(entPos.x - 1, entPos.y, entPos.z));
	}

	for (auto blocks : blockChecks) {
		if (!checkTargCollision12(&blocks->toVec3t(), ent)) {
			return false;
		}
	}
	return true;
}

std::vector<vec3_t*> getGucciPlacement21(C_Entity* ent) {
	static auto CrystalAuraMod = moduleMgr->getModule<CrystalAura>();
	int dmgMode2 = CrystalAuraMod->dmgEnum.GetSelectedEntry().GetValue();

	std::vector<vec3_t> SurChecker = {
		vec3_t(1, 0, 0),
		vec3_t(0, 0, 1),
		vec3_t(-1, 0, 0),
		vec3_t(0, 0, -1),
	};
	std::vector<vec3_t> SurChecker2 = {
		vec3_t(1, 1, 0),
		vec3_t(0, 1, 1),
		vec3_t(-1, 1, 0),
		vec3_t(0, 1, -1),
	};
	vec3_t entPos = ent->getPos()->floor();
	// for (int y = entPos.y - 2; y <= entPos.y + 0; y++) {
	int y;

	bool sendBack = false;

	for (auto checkThis : SurChecker) {
		for (auto checkThis2 : SurChecker2) {
			auto playerOn = targetList7[0]->getPos();
			auto rndOffPlayerOn = playerOn->floor();
			rndOffPlayerOn.y -= 1.f;

			auto calcSides = rndOffPlayerOn.add(checkThis);
			auto calcSides2 = rndOffPlayerOn.add(checkThis2);

			if (g_Data.getLocalPlayer()->region->getBlock(vec3_ti(calcSides))->toLegacy()->blockId == 0 && dmgMode2 == CrystalAuraMod->dmg_vanilla ? g_Data.getLocalPlayer()->region->getBlock(vec3_ti(calcSides2))->toLegacy()->blockId == 0 : g_Data.getLocalPlayer()->region->getBlock(vec3_ti(calcSides))->toLegacy()->blockId == 0) {
				sendBack = true;
			}
		}
	}
	if (!sendBack) {
		y = entPos.y;
	} else {
		y = entPos.y -= 1;
	}
	std::vector<vec3_t*> finalBlocks;
	std::vector<vec3_ti*> blockChecks;
	blockChecks.clear();
	finalBlocks.clear();
	if (blockChecks.empty()) {
		blockChecks.push_back(new vec3_ti(entPos.x, entPos.y, entPos.z + 1));
		blockChecks.push_back(new vec3_ti(entPos.x, entPos.y, entPos.z - 1));
		blockChecks.push_back(new vec3_ti(entPos.x + 1, entPos.y, entPos.z));
		blockChecks.push_back(new vec3_ti(entPos.x - 1, entPos.y, entPos.z));
	}

	for (auto blocks : blockChecks) {
		auto blkID = g_Data.getLocalPlayer()->region->getBlock(*blocks)->toLegacy()->blockId;
		auto blkIDL = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blocks->x, blocks->y - 1, blocks->z))->toLegacy()->blockId;
		auto blkIDLL = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blocks->x, blocks->y - 2, blocks->z))->toLegacy()->blockId;
		auto blkIDLLL = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blocks->x, blocks->y - 3, blocks->z))->toLegacy()->blockId;
		auto blkIDLLLL = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blocks->x, blocks->y - 4, blocks->z))->toLegacy()->blockId;
		auto blkIDLLLLL = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blocks->x, y, blocks->z))->toLegacy()->blockId;

		if (!checkTargCollision12(&blocks->toVec3t(), ent)) {  // very efficient coding here

			if (blkID == 0 && blkIDL == 0 && (blkIDLL == 49 || blkIDLL == 7)) {
				finalBlocks.push_back(new vec3_t(blocks->x, blocks->y - 1, blocks->z));
			} else if (blkID == 0 && (blkIDL == 7 || blkIDL == 49)) {
				finalBlocks.push_back(new vec3_t(blocks->x, blocks->y, blocks->z));
			}

			/*if (blkID == 0 && blkIDL == 0 && (blkIDLL == 49 || blkIDLL == 7)) {
		finalBlocks.push_back(new vec3_t(blocks->x, blocks->y - 1, blocks->z));
	} else if (blkID == 0 && (blkIDL == 7 || blkIDL == 49)) {
		finalBlocks.push_back(new vec3_t(blocks->x, blocks->y, blocks->z));
	} else if (blkID == 0 && blkIDL == 0 && blkIDLL == 0 && (blkIDLLL == 7 || blkIDLLL == 49)) {
		finalBlocks.push_back(new vec3_t(blocks->x, blocks->y - 2, blocks->z));
	} else if (blkID == 0 && blkIDL == 0 && blkIDLL == 0 && & blkIDLLL == 0 && (blkIDLLLL == 7 || blkIDLLLL == 49)) {
		finalBlocks.push_back(new vec3_t(blocks->x, blocks->y - 3, blocks->z));
	}*/
		} else {
			for (int x = entPos.x - 2; x <= entPos.x + 2; x++) {
				for (int y = entPos.y - 2; y <= entPos.y + 2; y++) {
					for (int z = entPos.z - 2; z <= entPos.z + 2; z++) {
						auto blk = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(x, y, z))->toLegacy()->blockId;
						auto lBlk = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(x, y - 1, z))->toLegacy()->blockId;

						if ((blk == 0 && (lBlk == 49 || lBlk == 7))) {
							finalBlocks.push_back(new vec3_t(x, y, z));
						}
					}
				}
			}
		}
	}
	return finalBlocks;
}

bool hasPlacedA = false;

void CrystalAura::onEnable() {
	auto supplies = g_Data.getLocalPlayer()->getSupplies();

	OldSlot = supplies->selectedHotbarSlot;

	K3SRC = 0;
	hasPlacedA = false;
}
vec3_t espPosLowerp;
vec3_t espPosUpperp;
vec3_t crystalPosp;
std::vector<vec3_t*> placeArrp;
std::vector<vec3_t*> hitArrp;
void CrystalAura::onTick(C_GameMode* gm) {
	switch (RotMode.selected) {
	case 0:
		silent = false;
		noSilent = false;
		break;
	case 1:
		silent = true;
		noSilent = false;
		break;
	case 2:
		silent = false;
		noSilent = true;
		break;
	}

	int dmgMode2 = dmgEnum.GetSelectedEntry().GetValue();

	if (dmgMode2 == dmg_2b2elow || dmgMode2 == dmg_2b2e) {
		doMultiple = true;
	} else {
		doMultiple = false;
	}

	targetList7.clear();

	g_Data.forEachEntity(findEntityK3R);
	hitArrp.clear();
	placeArrp.clear();

	if (autoplace)
		if ((K3SRC >= this->delay) && !(targetList7.empty())) {
			K3SRC = 0;
			if (multi) {
				for (auto& i : targetList7) {
					std::vector<vec3_t*> gucciPositions = getGucciPlacement21(i);

					auto supplies = g_Data.getLocalPlayer()->getSupplies();
					auto inv = supplies->inventory;

					// 615 = normal id for crystal || 616 = crystal id for nukkit servers
					if (!gucciPositions.empty())
						if (g_Data.getLocalPlayer()->getSelectedItem()->getItem()->isCrystal()) {
							placeArrp.clear();
							for (auto place : gucciPositions) {
								if (hasPlacedA && !doMultiple) break;
								if (targetList7.empty()) return;
								if (!(targetList7[0]->damageTime > 1 && HurtTime)) {
									gm->buildBlock(&vec3_ti(place->x, place->y - 1, place->z), 1, false);
									placeArrp.push_back(new vec3_t(place->x, place->y - 1, place->z));
									vec2_t angle2 = g_Data.getLocalPlayer()->getPos()->CalcAngle(*place).normAngles();
									C_MovePlayerPacket pkt(g_Data.getLocalPlayer(), *gm->player->getPos());
									if (noSilent) {
										gm->player->pitch = angle2.x;
										gm->player->yaw = angle2.y;
										gm->player->bodyYaw = angle2.y;
										gm->player->yawUnused1 = angle2.y;
									} else {
										pkt.pitch = angle2.x;
										pkt.yaw = angle2.y;
										pkt.headYaw = angle2.y;
										g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&pkt);
									}
								}
								hasPlacedA = true;
							}

							gucciPositions.clear();
						} else if (!targetList7.empty()) {
							K3SRC++;
						}
				}
			} else {
				std::vector<vec3_t*> gucciPositions = getGucciPlacement21(targetList7[0]);

				auto supplies = g_Data.getLocalPlayer()->getSupplies();
				auto inv = supplies->inventory;

				// 615 = normal id for crystal || 616 = crystal id for nukkit servers
				if (!gucciPositions.empty())
					if (g_Data.getLocalPlayer()->getSelectedItemId() == 615 || g_Data.getLocalPlayer()->getSelectedItemId() == 632) {
						placeArrp.clear();
						for (auto place : gucciPositions) {
							if (hasPlacedA && !doMultiple) break;
							if (targetList7.empty()) return;
							if (!(targetList7[0]->damageTime > 1 && HurtTime)) {
								gm->buildBlock(&vec3_ti(place->x, place->y - 1, place->z), 1, false);
								placeArrp.push_back(new vec3_t(place->x, place->y - 1, place->z));
								vec2_t angle2 = g_Data.getLocalPlayer()->getPos()->CalcAngle(*place).normAngles();
								C_MovePlayerPacket pkt(g_Data.getLocalPlayer(), *gm->player->getPos());
								if (noSilent) {
									gm->player->pitch = angle2.x;
									gm->player->yaw = angle2.y;
									gm->player->bodyYaw = angle2.y;
									gm->player->yawUnused1 = angle2.y;
								} else {
									pkt.pitch = angle2.x;
									pkt.yaw = angle2.y;
									pkt.headYaw = angle2.y;
									g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&pkt);
								}
							}

							hasPlacedA = true;
						}

						gucciPositions.clear();
					} else if (!targetList7.empty()) {
						K3SRC++;
					}
			}
		}

	// if (K3SRC2 >= 20) {
	//		hasPlaced = false;
	// }

	g_Data.forEachEntity([](C_Entity* ent, bool b) {
		auto player = g_Data.getLocalPlayer();
		static auto CrystalAuraMod = moduleMgr->getModule<CrystalAura>();

		if (targetList7.empty()) return;
		int id = ent->getEntityTypeId();
		int range = moduleMgr->getModule<CrystalAura>()->range;
		if (id == 71 && g_Data.getLocalPlayer()->getPos()->dist(*ent->getPos()) <= range) {
			g_Data.getCGameMode()->attack(ent);
			vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*ent->getPos());
			C_MovePlayerPacket pkt(g_Data.getLocalPlayer(), *player->getPos());
			// g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&pkt);
			if (CrystalAuraMod->noSilent) {
				player->pitch = angle.x;
				player->yaw = angle.y;
				player->bodyYaw = angle.y;
				player->yawUnused1 = angle.y;
			} else {
				pkt.pitch = angle.x;
				pkt.yaw = angle.y;
				pkt.headYaw = angle.y;
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&pkt);
			}
			hasPlacedA = false;

			if (!moduleMgr->getModule<NoSwing>()->isEnabled())
				g_Data.getLocalPlayer()->swingArm();
		}
	});  //*/
}

void CrystalAura::onDisable() {
	auto supplies = g_Data.getLocalPlayer()->getSupplies();

	supplies->selectedHotbarSlot = OldSlot;

	K3SRC = 0;
	hasPlacedA = false;
}

void CrystalAura::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	
	C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
	if (localPlayer != nullptr && GameData::canUseMoveKeys() && render) {
		if (!placeArrp.empty()) {
			for (auto postt : placeArrp) {
				DrawUtils::setColor(0.0f, 1.0f, 0.0f, 1.f);
				DrawUtils::drawBox(postt->floor(), vec3_t(floor(postt->x) + 1.f, floor(postt->y) + 1.f, floor(postt->z) + 1.f), 1.f, false);
			}
		}
		if (!hitArrp.empty()) {
			for (auto postt : hitArrp) {
				DrawUtils::setColor(0.0f, 1.0f, 0.0f, 1.f);
				DrawUtils::drawBox(postt->floor(), vec3_t(floor(postt->x) + 1.f, floor(postt->y) + 1.f, floor(postt->z) + 1.f), 1.f, false);
			}
		}  //*/
	}
}