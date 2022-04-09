#include "TPAura.h"

TPAura::TPAura() : IModule(0x0, Category::COMBAT, "TP like fuck so you dont get hit") {
	registerBoolSetting("MobAura", &isMobAura, isMobAura);
	registerBoolSetting("MultiAura", &isMulti, isMulti);
	registerBoolSetting("Lerp", &lerp, lerp);
	registerBoolSetting("UnlimitedRange", &unlim, unlim);
	registerFloatSetting("range", &range, range, 0.5f, 20.f);
	registerIntSetting("TP delay", &delay, delay, 0, 20);
	registerIntSetting("Attack delay", &delay1, delay1, 0, 20);
	registerBoolSetting("AutoWeapon", &autoweapon, autoweapon);
	//registerBoolSetting("hurttime", &hurttime, hurttime);
}

TPAura::~TPAura() {
}

const char* TPAura::getModuleName() {
		return "TPAura";
}

static std::vector<C_Entity*> targetList;

void findEntity0(C_Entity* currentEntity, bool isRegularEntity) {
	static auto TPMod = moduleMgr->getModule<TPAura>();

	if (currentEntity == nullptr) return;
	if (currentEntity == g_Data.getLocalPlayer()) return;  // Skip Local player
	if (!g_Data.getLocalPlayer()->canAttack(currentEntity, false)) return;
	if (!g_Data.getLocalPlayer()->isAlive()) return;
	if (!currentEntity->isAlive()) return;
	if (currentEntity->width <= 0.10f || currentEntity->height <= 0.10f) return;  // Don't hit this pesky antibot on 2b2e.org
	if (TPMod->isMobAura) {
		if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 63) return;
		if (currentEntity == nullptr) return;
		if (currentEntity == g_Data.getLocalPlayer()) return;  // Skip Local player
		if (!currentEntity->isAlive()) return;
		if (!g_Data.getLocalPlayer()->isAlive()) return;
		if (currentEntity->getEntityTypeId() == 71) return;  // endcrystal
		if (currentEntity->getEntityTypeId() == 66) return;  // falling block
		if (currentEntity->getEntityTypeId() == 64) return;  // item
		if (currentEntity->getEntityTypeId() == 69) return;  // xp orb
		if (!Target::isValidTarget(currentEntity)) return;
	} else {
		if (!Target::isValidTarget(currentEntity)) return;
	}

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
	if (!TPMod->unlim) {
		if (dist < TPMod->range) {
			targetList.push_back(currentEntity);
		}
	} else {
		if (dist < TPMod->unlimRange) {
			targetList.push_back(currentEntity);
		}
	}
}

void TPAura::findWeapon() {
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	float damage = 0;
	int slot = supplies->selectedHotbarSlot;
	for (int n = 0; n < 9; n++) {
		C_ItemStack* stack = inv->getItemStack(n);
		if (stack->item != nullptr) {
			float currentDamage = stack->getAttackingDamageWithEnchants();
			if (currentDamage > damage) {
				damage = currentDamage;
				slot = n;
			}
		}
	}
	supplies->selectedHotbarSlot = slot;
}

void TPAura::onTick(C_GameMode* gm) {
	//Loop through all our players and retrieve their information
	targetList.clear();

	g_Data.forEachEntity(findEntity0);

	Odelay++;
	if (!targetList.empty() && Odelay >= delay) {
		vec3 pos = *targetList[0]->getPos();
		if (turn == 3) {
			pos.y += 2;
			pos.x += -1.f;
			pos.z += 1.f;
			turn = 0;
		} else if (turn == 2) {
			pos.y += 2.f;
			pos.x += -1.f;
			pos.z += -1.f;
			turn = 3;
		} else if (turn == 1) {
			pos.y += 2.f;
			pos.x += 1.f;
			pos.z += -1.f;
			turn = 2;
		} else if (turn == 0) {
			pos.y += 2.f;
			pos.x += 1.f;
			pos.z += 1.f;
			turn = 1;
		}
		if (autoweapon) findWeapon();
		//if (g_Data.getLocalPlayer()->velocity.squaredxzlen() < 0.01) {
		C_MovePlayerPacket p(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
		//}
		C_LocalPlayer* player = g_Data.getLocalPlayer();
		if (!lerp) {
			player->setPos(pos);
		} else {
			float dist2 = gm->player->getPos()->dist(pos);
			//player->lerpMotion(pos);
			player->setPos(pos);   //lerpTo is gone , vec2(1, 1), (int)fmax((int)dist2 * 0.1, 1));
			player->lerpMotion(pos);
		}
		Odelay = 0;
	}

	delay2++;
	g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = false;
	if (!targetList.empty() && delay2 >= delay1) {
		if (isMulti) {
			for (auto& i : targetList) {
				g_Data.getLocalPlayer()->swing();
				g_Data.getCGameMode()->attack(i);
			}
		} else {
			g_Data.getLocalPlayer()->swing();
			g_Data.getCGameMode()->attack(targetList[0]);
		}
		delay2 = 0;
	}
}

void TPAura::onEnable() {
	if (g_Data.getLocalPlayer() == nullptr)
		setEnabled(false);
}

void TPAura::onSendPacket(C_Packet* packet) {
}

void TPAura::onPostRender(C_MinecraftUIRenderContext* ctx) {
	/* if (!targetList.empty() && TPAuratargetHUD && g_Data.isInGame()) {
		vec4 tempPos = vec4(120.f, 5.f, 90.f, 40.f);           //temp pos for the text pos, so we can create a pos that doesn't have player names overlapping from the box to the screen
		vec2 textPos = vec2(tempPos.y, tempPos.x);             //text pos
		vec4 pos = vec4(3.f, 118.f, 75.f + textPos.x, 223.f);  //pos for using
		static float rcolors2[4];                                  // Rainbow color array RGBA
		static float disabledRcolors2[4];                          // Rainbow Colors, but for disabled modules
		static float currColor[4];                                 // ArrayList colors

		// Rainbow color updates
		{
			Utils::ApplyRainbow(rcolors2, 0.001f);  // Increase Hue of rainbow color array
			disabledRcolors2[0] = std::min(1.f, rcolors2[0] * 0.4f + 0.2f);
			disabledRcolors2[1] = std::min(1.f, rcolors2[1] * 0.4f + 0.2f);
			disabledRcolors2[2] = std::min(1.f, rcolors2[2] * 0.4f + 0.2f);
			disabledRcolors2[3] = 1;
		}
		currColor[3] = rcolors2[3];
		Utils::ColorConvertRGBtoHSV(rcolors2[0], rcolors2[1], rcolors2[2], currColor[0], currColor[2], currColor[2]);
		Utils::ColorConvertHSVtoRGB(currColor[0], currColor[2], currColor[3], currColor[0], currColor[0], currColor[1]);
//		std::string name = targetList[0]->getNameTag()->getText();
		std::string distance = "Distance: " + std::to_string((*targetList[0]->getPos()).dist(*g_Data.getLocalPlayer()->getPos()));
		std::string X = "X: " + std::to_string((targetList[0]->getPos()->x));
		std::string Y = "Y: " + std::to_string((targetList[0]->getPos()->y));
		std::string Z = "Z: " + std::to_string((targetList[0]->getPos()->z));
		std::string DmgTime = "DmgTime: " + std::to_string((targetList[0]->damageTime));
		std::string OnGround = "OnGround: " + std::to_string((targetList[0]->onGround));
		std::string isPlayer = "IsPlayer: " + std::to_string((targetList[0]->isPlayer()));
		std::string height = "height: " + std::to_string((targetList[0]->height));
		std::string entityid = "EntityID: " + std::to_string((targetList[0]->getEntityTypeId()));
		DrawUtils::drawRectangle(pos, currColor, 1.f);
		//DrawUtils::drawText(textPos, &name, currColor, 1.f);
		textPos.y += 10.f;
		DrawUtils::drawText(textPos, &distance, currColor, 1.f);
		textPos.y += 10.f;
		DrawUtils::drawText(textPos, &X, currColor, 1.f);
		textPos.y += 10.f;
		DrawUtils::drawText(textPos, &Y, currColor, 1.f);
		textPos.y += 10.f;
		DrawUtils::drawText(textPos, &Z, currColor, 1.f);
		textPos.y += 10.f;
		DrawUtils::drawText(textPos, &DmgTime, currColor, 1.f);
		textPos.y += 10.f;
		DrawUtils::drawText(textPos, &OnGround, currColor, 1.f);
		textPos.y += 10.f;
		DrawUtils::drawText(textPos, &isPlayer, currColor, 1.f);
		textPos.y += 10.f;
		DrawUtils::drawText(textPos, &height, currColor, 1.f);
		textPos.y += 10.f;
		DrawUtils::drawText(textPos, &entityid, currColor, 1.f);
	}*/
}