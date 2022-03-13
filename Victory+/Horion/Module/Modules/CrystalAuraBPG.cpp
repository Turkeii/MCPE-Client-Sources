#include "CrystalAuraBPG.h"

static std::vector<C_Entity*> crystalList;
static std::vector<C_Entity*> CAuraTargetList;

int prevSlot3 = -1;
bool caShouldGoAgain = false;

CrystalAuraBPG::CrystalAuraBPG() : IModule(0x0, Category::COMBAT,"AutoCrystal by Kaeruking188 & Brampdgex") {
	registerBoolSetting("SilentSwitch", &this->SilentSwitch, this->SilentSwitch);
	registerIntSetting("Delay", &this->delay, this->delay, 0, 20);
 	//registerIntSetting("Proximity", &this->proximity, this->proximity, 1, 10);
	registerIntSetting("Minimum Range", &this->minrange, this->minrange, 0, 9);
	registerIntSetting("MAX Range", &this->maxrange, this->maxrange, 3, 10);
	//registerIntSetting("CrystalAmount", &this->amount, this->amount, 1, 10);  // anything more than that will make the supercomputer I'm using to test this explode
	//registerBoolSetting("Safe Mode", &this->safe, this->safe);
	//registerBoolSetting("LowPower", &this->lowpower, this->lowpower);
	//registerBoolSetting("On Click", &this->onclick, this->onclick);
	//registerBoolSetting("Destroy Only", &this->dontautoplace, this->dontautoplace);
	//registerBoolSetting("Render", &this->doRender, this->doRender);
	registerBoolSetting("Java", &this->java, this->java);
	//registerBoolSetting("Crystal", &this->renderCrystal, this->renderCrystal);
	//registerBoolSetting("Placement", &this->renderPlacement, this->renderPlacement);
	//registerBoolSetting("TraceLine", &this->renderTrace, this->renderTrace);
}

CrystalAuraBPG::~CrystalAuraBPG() {
}

const char* CrystalAuraBPG::getModName() {
	if (java) {
		return (" Java");
	} else {
		return (" Vanilla");
	}
}

const char* CrystalAuraBPG::getModuleName() {
	return ("AutoCrystal");
}

bool CrystalAuraBPG::findSwitchId() {
	if (SilentSwitch) {
		__int64 id = *g_Data.getLocalPlayer()->getUniqueId();
		C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
		C_Inventory* inv = supplies->inventory;
		for (int n = 0; n < 9; n++) {
			C_ItemStack* stack = inv->getItemStack(n);
			if (stack->item != nullptr) {
				if ((*stack->item)->itemId = 629 && (*stack->item)->itemId != 0) {
					C_MobEquipmentPacket a(id, *stack, n, n);
					g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);
					return true;
				}
			}
		}

		C_MobEquipmentPacket a(id, *g_Data.getLocalPlayer()->getSelectedItem(), supplies->selectedHotbarSlot, supplies->selectedHotbarSlot);
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);
		return false;
	}
}

void CrystalAuraBPG::onEnable() {
}

void findDaTargets(C_Entity* ent, bool isNormal) {
	auto mod = moduleMgr->getModule<CrystalAuraBPG>();
	if (ent == nullptr)          
		return;
	if (ent == g_Data.getLocalPlayer())
		return;

	//if (ent->getEntityTypeId() != 63) {
	//	return;
	//}

	if (!g_Data.getLocalPlayer()->isAlive())
		return;

	if (!ent->isAlive())
		return;
	if (!Target::isValidTarget(ent))
		return;
	if (ent->width <= 0.01f || ent->height <= 0.01f)  // Don't target this pesky antibot on 2b2e.org
		return;
	CAuraTargetList.push_back(ent);
}

void findCrystals(C_Entity* ent, bool isNormal) {
	auto mod = moduleMgr->getModule<CrystalAuraBPG>();
	if (!(ent->getEntityTypeId() == 71))  // only crystals
		return;
	auto player = g_Data.getLocalPlayer();
	if (ent->getPos()->dist(*player->getPos()) > mod->maxrange && !mod->safe)
		return;
	if (ent->getPos()->dist(*player->getPos()) < mod->minrange && !mod->safe)
		return;
	if (mod->safe) {
		bool valid = false;
		for (auto current : mod->validPositions) {
			if (ent->getPos()->dist(current) < 1) {
				valid = true;
				break;
			}
		}
		if (!valid)
			return;
	}
	crystalList.push_back(ent);
}
int gapDelay = 0;
int CAuraDelay = 0;
//pog
void CrystalAuraBPG::onTick(C_GameMode* gm) {
	if (!GameData::isRightClickDown() && onclick) {
		CAuraDelay = delay + 0;
		return;
	}

	g_Data.forEachEntity([](C_Entity* ent, bool b) {
		int id = ent->getEntityTypeId();
		int range = moduleMgr->getModule<CrystalAuraBPG>()->maxrange;
		if (id == 71 && g_Data.getLocalPlayer()->getPos()->dist(*ent->getPos()) <= range) {
			g_Data.getCGameMode()->attack(ent);
			g_Data.getLocalPlayer()->swingArm();
		}
	});

	if (/*(CAuraDelay > delay || caShouldGoAgain) && */!dontautoplace) {
		// autoplace mode
		CAuraDelay = 0;
		CAuraTargetList.clear();
		g_Data.forEachEntity(findDaTargets);
		if (!CAuraTargetList.empty()) {
			traceEnd = CAuraTargetList[0]->eyePos0;
			findOptimalBlock(CAuraTargetList, gm);
		}
	} else {
		// Destroy Mode

	/* crystalList.clear();
		g_Data.forEachEntity(findCrystals);
		if (!crystalList.empty()) {
			for (auto current : crystalList) {
				crystalPosition = current->getAABB()->centerPoint();

				auto localPlayer = g_Data.getLocalPlayer();
				auto selectedItemId = localPlayer->getSelectedItemId();
				if (localPlayer->getSelectedItem()->item != nullptr) {
					if (localPlayer->getSelectedItem()->getItem()->itemId != 629) {
						if (gapDelay >= 3) {
							g_Data.getCGameMode()->attack(current);
							g_Data.getLocalPlayer()->swing();
							gapDelay = 0;
						} else {
							gapDelay++;
						}
					}
				} else {
					if (gapDelay >= 3) {
						g_Data.getCGameMode()->attack(current);
						g_Data.getLocalPlayer()->swing();
						gapDelay = 0;
					} else {
						gapDelay++;
					}
				}
			}
		} */
		CAuraDelay++;
	}
}

void CrystalAuraBPG::onDisable() {
	if (SilentSwitch) {
	if (g_Data.getLocalPlayer() == nullptr)
		return;
	__int64 id = *g_Data.getLocalPlayer()->getUniqueId();
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_MobEquipmentPacket a(id, *g_Data.getLocalPlayer()->getSelectedItem(), supplies->selectedHotbarSlot, supplies->selectedHotbarSlot);
	g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);
}

	validPositions.clear();
}

void CrystalAuraBPG::findOptimalBlock(std::vector<C_Entity*> list, C_GameMode* gm) {
	std::vector<vec3_t> candidates;
	std::vector<std::vector<float>> candidates2;  // this SHOULD fix data loss

	calculations = 0;
	sorts = 0;
	ents.clear();

	if (multiaura) {
		for (int n = 0; n < amount; n++) {
			std::vector<C_Entity*> a;
			ents.push_back(a);
		}
		// now assign entities accordingly
		for (int n = 0; n < list.size(); n++) {
			int i = n / list.size() * amount;  // index for nested array
			if (i == ents.size())
				i--;  // make sure we don't index a non-existant array
			ents.at(i).push_back(list.at(n));
		}
	} else {
		ents.push_back(list);
	}

	C_Entity* surroundedEnt;

	for (auto cl : ents) {  // this loop will create the initial list of candidates
		if (multiaura) {
			for (auto ce : cl) {
				vec3_t pos = ce->getPos()->floor();
				for (float x = pos.x - proximity; !(x > pos.x + proximity); x++) {
					for (float y = pos.y - proximity; !(y > pos.y + proximity); y++) {
						for (float z = pos.z - proximity; !(z > pos.z + proximity); z++) {
							vec3_t cp(vec3_t(x, y, z));  // candidate position
							vec3_ti cp2(cp);
							std::vector<float> cpf;  // candidate in float array format
							vec3_t ourPos = gm->player->currentPos;
							if (y > 0) {
								if (cp.dist(ourPos) >= minrange && cp.dist(ourPos) <= maxrange) {
									if (cp.dist(pos) <= proximity) {
										calculations += 3;
										C_Block* cbb(gm->player->region->getBlock(vec3_ti(x, y - 1, z)));  // block below candidate
										C_Block* cb(gm->player->region->getBlock(vec3_ti(x, y, z)));       // block inside candidate
										C_Block* cbu(gm->player->region->getBlock(vec3_ti(x, y + 1, z)));  // block above candidate
										if (cbb->toLegacy()->blockId == 7 || cbb->toLegacy()->blockId == 49) {
											if (cb->toLegacy()->blockId == 0 && cbu->toLegacy()->blockId == 0) {
												candidates.push_back(cp);
											}
										}
									}
								}
							}
						}
					}
				}
			}
		} else {
			C_Entity* ce(cl[0]);
			if (ce != nullptr)
				surroundedEnt = ce;

			vec3_t pos = ce->getPos()->floor();
			for (float x = pos.x - proximity; !(x > pos.x + proximity); x += 1.f) {
				for (float y = pos.y - proximity; !(y > pos.y + proximity); y += 1.f) {
					for (float z = pos.z - proximity; !(z > pos.z + proximity); z += 1.f) {
						vec3_t cp(x, y, z);  // candidate position
						vec3_ti cp2(cp);
						vec3_t ourPos = *g_Data.getLocalPlayer()->getPos();
						if (y > 0) {
							if (cp.dist(ourPos) >= minrange && cp.dist(ourPos) <= maxrange) {
								if (cp.dist(pos) <= proximity) {
									calculations += 3;
									C_Block* cbb(gm->player->region->getBlock(vec3_ti(x, y - 1, z)));  // block below candidate
									C_Block* cb(gm->player->region->getBlock(vec3_ti(x, y, z)));       // block inside candidate
									C_Block* cbu(gm->player->region->getBlock(vec3_ti(x, y + 1, z)));  // block above candidate
									if (cbb->toLegacy()->blockId == 7 || cbb->toLegacy()->blockId == 49) {
										if (cb->toLegacy()->blockId == 0 && cbu->toLegacy()->blockId == 0) {
											cp.x = x;
											cp.y = y;
											cp.z = z;
											candidates.push_back(cp);                   // when doing this the coordinate values are lost
											candidates2.push_back(packFloatArray(cp));  // very epic code
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	for (std::vector<float> a : candidates2) {
		vec3_t p = unpackFloatArray(a);
	}
	std::vector<int> dmgVals;
	if (candidates.empty())
		return;        // don't do 10,000 useless calculations if there aren't any god damn blocks to place crystals on
	if (!multiaura) {  // took a while to write this, had to make optimizations
		vec3_t entPos = *(ents[0][0]->getPos());
		vec3_t pos = *(g_Data.getLocalPlayer()->getPos());
		std::vector<vec3_t> newList;
		while (true) {
			dmgVals.clear();
			for (vec3_t cp : candidates) {
				int dmg = 0;
				if (lowpower) {
					dmg = getExplosionDamage(cp.add(vec3_t(0.5f, 0.f, 0.5f)), pos);  // get damage to player
				} else {
					AABB* aabb = &gm->player->aabb;
					for (float x = aabb->lower.x; !(x > aabb->upper.x); x += float(abs(aabb->upper.x - aabb->lower.x) / 4)) {
						for (float y = aabb->lower.y; !(y > aabb->upper.y); y += float((aabb->upper.y - aabb->lower.y) / 4)) {
							for (float z = aabb->lower.z; !(z > aabb->upper.z); z += float((aabb->upper.z - aabb->lower.z) / 4)) {
								vec3_t posCurrent(x, y, z);
								dmg += getExplosionDamage(cp.add(vec3_t(0.5f, 0.f, 0.5f)), posCurrent);
							}
						}
					}
				}
				dmgVals.push_back(dmg);
			}
			newList = sortByDamage(candidates, dmgVals, true);
			sorts++;
			candidates.clear();
			for (int n = 0; n < newList.size(); n++) {
				if (n < amount || n < floor(newList.size() / 5))
					candidates.push_back(newList.at(n));  // keep the top results
			}

			dmgVals.clear();
			for (vec3_t cp : candidates) {
				int dmg = 0;
				if (lowpower) {
					dmg = getExplosionDamage(cp.add(vec3_t(0.5f, 0.f, 0.5f)), entPos);  // get damage to enemy
				} else {
					AABB* aabb = &ents[0][0]->aabb;
					for (float x = aabb->lower.x; !(x > aabb->upper.x); x += float(abs(aabb->upper.x - aabb->lower.x) / 4)) {
						for (float y = aabb->lower.y; !(y > aabb->upper.y); y += float((aabb->upper.y - aabb->lower.y) / 4)) {
							for (float z = aabb->lower.z; !(z > aabb->upper.z); z += float((aabb->upper.z - aabb->lower.z) / 4)) {
								vec3_t posCurrent(x, y, z);
								dmg += getExplosionDamage(cp.add(vec3_t(0.5f, 0.f, 0.5f)), posCurrent);
							}
						}
					}
				}
				dmgVals.push_back(dmg);
			}
			newList = sortByDamage(candidates, dmgVals, false);
			sorts++;
			candidates.clear();
			for (int n = 0; n < newList.size(); n++) {
				if (n < amount || n < floor(newList.size() / 2))
					candidates.push_back(newList.at(n));  // keep the top half results
			}
			candidates = newList;
			if (candidates.size() <= amount) {
				break;
			}
		}
	} else {
		for (int i = 0; i < ents.size(); i++) {
			auto currentList = ents[i];  // I am sick and tired of writing std::vector<>
			if (!currentList.empty()) {  // here we go again.
				vec3_t pos = gm->player->currentPos;
				while (candidates.size() > 1) {
					dmgVals.clear();
					int dmg = 0;
					for (auto cp : candidates) {
						if (lowpower) {
							dmg = getExplosionDamage(cp.add(vec3_t(0.5f, 0.f, 0.5f)), pos);  // get damage to player
							dmgVals.push_back(dmg);
						} else {
							AABB* aabb = &gm->player->aabb;
							for (float x = aabb->lower.x; !(x > aabb->upper.x); x += float(abs(aabb->upper.x - aabb->lower.x) / 4)) {
								for (float y = aabb->lower.y; !(y > aabb->upper.y); y += float((aabb->upper.y - aabb->lower.y) / 4)) {
									for (float z = aabb->lower.z; !(z > aabb->upper.z); z += float((aabb->upper.z - aabb->lower.z) / 4)) {
										vec3_t posCurrent(x, y, z);
										dmg += getExplosionDamage(cp.add(vec3_t(0.5f, 0.f, 0.5f)), posCurrent);
									}
								}
							}
						}
					}
					candidates = sortByDamage(candidates, dmgVals, true);
					sorts++;
					std::vector<vec3_t> newList;
					for (int n = 0; n > candidates.size(); n++) {
						if (n < 1 || n <= floor(candidates.size() / 5))
							newList.push_back(candidates.at(1));  // keep the top fifth results because we really value the player
					}
					candidates = newList;

					dmgVals.clear();
					for (auto cp : candidates) {
						int dmg = 0;
						for (auto ent : currentList) {
							if (lowpower) {
								dmg += getExplosionDamage((cp.add(vec3_t(0.5f, 0.f, 0.5f))), *ent->getPos());  // get damage to all enemies
							} else {
								AABB* aabb = &ent->aabb;
								for (float x = aabb->lower.x; !(x > aabb->upper.x); x += float(abs(aabb->upper.x - aabb->lower.x) / 4)) {
									for (float y = aabb->lower.y; !(y > aabb->upper.y); y += float((aabb->upper.y - aabb->lower.y) / 4)) {
										for (float z = aabb->lower.z; !(z > aabb->upper.z); z += float((aabb->upper.z - aabb->lower.z) / 4)) {
											vec3_t posCurrent(x, y, z);
											dmg += getExplosionDamage(cp.add(vec3_t(0.5f, 0.f, 0.5f)), posCurrent);
										}
									}
								}
							}
						}
						dmgVals.push_back(dmg);
					}
					candidates = sortByDamage(candidates, dmgVals, false);
					sorts++;
					newList.clear();
					for (int n = 0; n > candidates.size(); n++) {
						if (n < 1 || n <= floor(candidates.size() / 2))
							newList.push_back(candidates.at(n));  // keep the top half results
					}
					candidates = newList;
				}
				candidates.clear();
			}
		}
	}

	std::vector<vec3_t> blocksToPlace;
	bool epicCheck = false;
	for (auto c : candidates) {
		blocksToPlace.push_back(c);
	}
	validPositions.clear();
	auto localPlayer = g_Data.getLocalPlayer();
	auto selectedItemId = localPlayer->getSelectedItemId();
	//checkSurrounded(surroundedEnt);
	if (!checkSurrounded(surroundedEnt)) {
		//	for (int n = 0; n < blocksToPlace.size(); n++) {
		//	vec3_ti pos(blocksToPlace[n]);
		if (selectedItemId == 629) {
			vec3_ti placeHere = getGucciPlacement(surroundedEnt);
			traceStart = placeHere.toVec3t();
			traceStart.y += 1;

			//pos2.y -= 1;
			placePos = placeHere.toVec3t();

			g_Data.getCGameMode()->buildBlock(&placeHere, 0);
		
			caShouldGoAgain = false;
	}
} else {
		for (int n = 0; n < blocksToPlace.size(); n++) {
			if (selectedItemId != 629)
				break;
			vec3_ti pos(blocksToPlace[n]);
			vec3_ti pos2(pos);
			traceStart = pos2.toVec3t();
			traceStart.y += 1;
			pos2.y -= 1;
			placePos = pos2.toVec3t();

			g_Data.getCGameMode()->buildBlock(&pos2, 3);

			g_Data.getCGameMode()->buildBlock(&pos, 3);


			//validPositions.push_back(blocksToPlace2[n2]);
			validPositions.push_back(blocksToPlace[n]);
			caShouldGoAgain = false;
		}
	}
	if (!blocksToPlace.empty() && selectedItemId != 629 && selectedItemId != 259 && selectedItemId != 629 /*Don't switch if the player is gappling*/ && !onclick) {
		if (g_Data.getLocalPlayer()->getSelectedItemId() == 629)
			caShouldGoAgain = true;
	}
	// god damnit C++
	/*
	Will any PC be powerful enough? Hell yes! How do I know? Heres how:
	Blocks are accessed every tick so they can be rendered. Render distance goes up to 64 chunks.
	64 * 16 = 640 + 384 = 1024 blocks away.
	1024^2 * 3.14 = 3294198 blocks times 256 for Y and do that every tick.
	Thats a grand total of 16,866,297,130. So I don't think we need to worry about a couple hundred thousand if minecraft does it
	16 billion times a second anyway. Actually, wait a minute, thats really suspicious. 
	Oh right. GPU acceleration.
	*/
}

std::vector<vec3_t> CrystalAuraBPG::sortByDamage(std::vector<vec3_t> posList, std::vector<int> damageValues, bool preferLow) {
	std::vector<vec3_t> newList;
	std::vector<std::vector<vec3_t>> groups;
	for (int n = 0; n < posList.size(); n++) {
		groups.push_back(newList);  // Use newList as an empty array to push because lazy
	}
	for (int index = 0; index < posList.size(); index++) {
		int rank = 0;
		for (int cmpvar : damageValues) {
			if (damageValues[index] < cmpvar && preferLow)
				rank++;
			if (damageValues[index] > cmpvar && !preferLow)
				rank++;
		}
		groups.at(rank).push_back(posList.at(index));  // we do this so that equal values are handled properly
	}
	for (std::vector<vec3_t> current : groups) {
		for (vec3_t p : current) {
			if (!current.empty())
				newList.push_back(p);
		}
	}
	return newList;
}

int CrystalAuraBPG::getExplosionDamage(vec3_t pos1, vec3_t pos2) {
	/* calculation rules:
	+1 for every block far away the explosion is
	+20 for every non-blast proof block blocking the explosion
	+40 for every blast-proof block blocking the explosion
	*/
	int protection = 0;
	if (pos1.dist(pos2) > 12.f)
		return 69420;
	protection += pos1.dist(pos2) * 4;  // add 1 for every block far away
	int i = pos1.dist(pos2) * 4;
	for (float n = 0.f; !(n > i); n++) {
		vec3_t pos = pos2.sub(pos1).div(i).mul(n).floor();
		calculations += 1;
		C_Block* block = g_Data.getLocalPlayer()->region->getBlock(pos1.add(pos).floor());
		if (block->toLegacy()->blockId == 7 || block->toLegacy()->blockId == 49) {
			protection += 40;
		} else if (block->toLegacy()->material->isSolid) {
			protection += 20;
		}
		if (!block->toLegacy()->blockId == 7 || block->toLegacy()->blockId == 49) {
			protection += 1;
		}
	}

	return protection;
	return 0;
}

// added these functions because I am lazy as hell

vec3_t CrystalAuraBPG::unpackFloatArray(std::vector<float> a) {
	vec3_t b;
	b.x = a[0];
	b.y = a[1];
	b.z = a[2];
	return b;
}

std::vector<float> CrystalAuraBPG::packFloatArray(vec3_t a) {
	std::vector<float> b;
	b.push_back(a.x);
	b.push_back(a.y);
	b.push_back(a.z);
	return b;
}
vec3_t posRender;
vec3_t posRender2;
vec3_t floorRender;
bool CrystalAuraBPG::checkSurrounded(C_Entity* ent) {
	vec3_t entFloor = ent->getPos()->floor();
	bool notSurrounded = false;
    entFloor.x = floor(entFloor.x) + 0.5f;
	entFloor.y = floor(entFloor.y) - 1.f;
	entFloor.z = floor(entFloor.z) + 0.5f;  //so this gets the block they are standing on
	floorRender = entFloor;
	//ok so now we need to check the blocks around them to see if we can place on them
	vec3_ti checkHere = entFloor;
	vec3_ti checkHereUpper;
	posRender = checkHere.toVec3t();
	posRender2 = checkHereUpper.toVec3t();

	checkHere.x += 1;
	checkHereUpper = vec3_ti(checkHere.x, checkHere.y + 1, checkHere.z);
	posRender = checkHere.toVec3t();
	posRender2 = checkHereUpper.toVec3t();
	if (g_Data.getLocalPlayer()->region->getBlock(checkHere)->toLegacy()->blockId == 49 || g_Data.getLocalPlayer()->region->getBlock(checkHere)->toLegacy()->blockId == 7) {
		if (g_Data.getLocalPlayer()->region->getBlock(checkHereUpper)->toLegacy()->blockId == 0) {
			notSurrounded = true;
			return false;
		}
	}

	checkHere.x -= 1;
	checkHereUpper = vec3_ti(checkHere.x, checkHere.y + 1, checkHere.z);
	posRender = checkHere.toVec3t();
	posRender2 = checkHereUpper.toVec3t();
	if (g_Data.getLocalPlayer()->region->getBlock(checkHere)->toLegacy()->blockId == 49 || g_Data.getLocalPlayer()->region->getBlock(checkHere)->toLegacy()->blockId == 7) {
		if (g_Data.getLocalPlayer()->region->getBlock(checkHereUpper)->toLegacy()->blockId == 0) {
			notSurrounded = true;
			return false;
		}
	}

	checkHere.x += 1;
	checkHere.z += 1;
	checkHereUpper = vec3_ti(checkHere.x, checkHere.y + 1, checkHere.z);
	posRender = checkHere.toVec3t();
	posRender2 = checkHereUpper.toVec3t();
	if (g_Data.getLocalPlayer()->region->getBlock(checkHere)->toLegacy()->blockId == 49 || g_Data.getLocalPlayer()->region->getBlock(checkHere)->toLegacy()->blockId == 7) {
		if (g_Data.getLocalPlayer()->region->getBlock(checkHereUpper)->toLegacy()->blockId == 0) {
			notSurrounded = true;
			return false;
		}
	}

	checkHere.z -= 1;
	checkHereUpper = vec3_ti(checkHere.x, checkHere.y + 1, checkHere.z);
	if (g_Data.getLocalPlayer()->region->getBlock(checkHere)->toLegacy()->blockId == 49 || g_Data.getLocalPlayer()->region->getBlock(checkHere)->toLegacy()->blockId == 7) {
		if (g_Data.getLocalPlayer()->region->getBlock(checkHereUpper)->toLegacy()->blockId == 0) {
			notSurrounded = true;
			return false;
		}
	}
	checkHere.z += 0;
	posRender = checkHere.toVec3t();
	posRender2 = checkHereUpper.toVec3t();
	if (!notSurrounded)
		return true;
}

vec3_t CrystalAuraBPG::getGucciPlacement(C_Entity* ent) {
	vec3_t entFloor = ent->getPos()->floor();
	entFloor.x = floor(entFloor.x) + 0.5f;
	entFloor.y = floor(entFloor.y) - 0.5f;
	entFloor.z = floor(entFloor.z) + 0.5f;  //so this gets the block they are standing on
	floorRender = entFloor;
	//ok so now we need to check the blocks around them to see if we can place on them
	vec3_ti checkHere = entFloor;
	vec3_ti checkHereUpper;
	posRender = checkHere.toVec3t();
	posRender2 = checkHereUpper.toVec3t();

	checkHere.x += 1;
	checkHereUpper = vec3_ti(checkHere.x, checkHere.y + 1, checkHere.z);
	posRender = checkHere.toVec3t();
	posRender2 = checkHereUpper.toVec3t();
	if (g_Data.getLocalPlayer()->region->getBlock(checkHere)->toLegacy()->blockId == 49 || g_Data.getLocalPlayer()->region->getBlock(checkHere)->toLegacy()->blockId == 7) {
		if (g_Data.getLocalPlayer()->region->getBlock(checkHereUpper)->toLegacy()->blockId == 0) {
			return checkHere.toVec3t();
		}
	}

	checkHere.x -= 1;
	checkHereUpper = vec3_ti(checkHere.x, checkHere.y + 1, checkHere.z);

	posRender = checkHere.toVec3t();
	posRender2 = checkHereUpper.toVec3t();

	if (g_Data.getLocalPlayer()->region->getBlock(checkHere)->toLegacy()->blockId == 49 || g_Data.getLocalPlayer()->region->getBlock(checkHere)->toLegacy()->blockId == 7) {
		if (g_Data.getLocalPlayer()->region->getBlock(checkHereUpper)->toLegacy()->blockId == 0) {
			return checkHere.toVec3t();
		}
	}

	checkHere.x += 1;
	checkHere.z += 1;
	checkHereUpper = vec3_ti(checkHere.x, checkHere.y + 1, checkHere.z);

	posRender = checkHere.toVec3t();
	posRender2 = checkHereUpper.toVec3t();

	if (g_Data.getLocalPlayer()->region->getBlock(checkHere)->toLegacy()->blockId == 49 || g_Data.getLocalPlayer()->region->getBlock(checkHere)->toLegacy()->blockId == 7) {
		if (g_Data.getLocalPlayer()->region->getBlock(checkHereUpper)->toLegacy()->blockId == 0) {
			return checkHere.toVec3t();
		}
	}

	checkHere.z -= 1;
	checkHereUpper = vec3_ti(checkHere.x, checkHere.y + 1, checkHere.z);

	posRender = checkHere.toVec3t();
	posRender2 = checkHereUpper.toVec3t();

	if (g_Data.getLocalPlayer()->region->getBlock(checkHere)->toLegacy()->blockId == 49 || g_Data.getLocalPlayer()->region->getBlock(checkHere)->toLegacy()->blockId == 7) {
		if (g_Data.getLocalPlayer()->region->getBlock(checkHereUpper)->toLegacy()->blockId == 0) {
			return checkHere.toVec3t();
		}
	}
	checkHere.z += 0;
	posRender = checkHere.toVec3t();
	posRender2 = checkHereUpper.toVec3t();
}

void CrystalAuraBPG::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	if (g_Data.getLocalPlayer() != nullptr && g_Data.canUseMoveKeys()) {
		if (doRender) {
			DrawUtils::setColor(1.0f, 0.f, 0.f, 0.2f);
			if (renderCrystal)
				DrawUtils::drawBox(vec3_t(crystalPosition.x - 0.3f, crystalPosition.y - 0.3f + 1.f, crystalPosition.z - 0.3f), vec3_t(crystalPosition.x + 0.3f, crystalPosition.y + 0.3f, crystalPosition.z + 0.3f + 1.f), 0.4f, true);
			if (renderPlacement) {
					DrawUtils::setColor(1.f, 1.f, 1.f, 0.5f);
					DrawUtils::drawBox(vec3_t((floor(placePos.x)), (floor(placePos.y) + 1.f), (floor(placePos.z))), vec3_t((floor(placePos.x) + 1.f), (floor(placePos.y) + 0.f), (floor(placePos.z) + 1.f)), 0.4f, false, false);
			}	
		}

		if (renderTrace) {
			DrawUtils::setColor(0.0f, 1.f, 0.f, 1.0f);
			DrawUtils::drawBox(vec3_t(floor(posRender.x) + 0.f, floor(posRender.y) + 0.f, floor(posRender.z) + 0.f), vec3_t(floor(posRender.x) + 1.f, floor(posRender.y) + 1.f, floor(posRender.z) + 1.f), 1.f, true, true);

			DrawUtils::setColor(0.0f, 0.f, 1.f, 1.0f);
			DrawUtils::drawBox(vec3_t(floor(posRender2.x) + 0.f, floor(posRender2.y) + 0.f, floor(posRender2.z) + 0.f), vec3_t(floor(posRender2.x) + 1.f, floor(posRender2.y) + 1.f, floor(posRender2.z) + 1.f), 1.f, true);

			DrawUtils::setColor(1.0f, 0.f, 1.f, 1.0f);
			DrawUtils::drawBox(vec3_t(floor(floorRender.x) + 0.f, floor(floorRender.y) + 0.f, floor(floorRender.z) + 0.f), vec3_t(floor(floorRender.x) + 1.f, floor(floorRender.y) + 1.f, floor(floorRender.z) + 1.f), 1.f, true);
		}
	}
}

