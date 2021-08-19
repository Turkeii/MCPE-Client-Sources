#include "Killaura.h"

Killaura::Killaura() : IModule(0, Category::COMBAT, "Attacks entities around you automatically") {
	this->registerBoolSetting("SilentRotations", &this->silent, this->silent);
	this->registerBoolSetting("Rotations", &this->rot, this->rot);
	this->registerBoolSetting("MultiAura", &this->isMulti, this->isMulti);
	this->registerBoolSetting("Distance", &this->distanceCheck, this->distanceCheck);
	this->registerBoolSetting("MobAura", &this->isMobAura, this->isMobAura);
	this->registerBoolSetting("Hurttime", &this->hurttime, this->hurttime);
	this->registerBoolSetting("Strafe", &this->cock, this->cock);
	//this->registerBoolSetting("Hold", &this->holdMode, this->holdMode);
	this->registerFloatSetting("range", &this->range, this->range, 3.f, 8.f);
	this->registerIntSetting("delay", &this->delay, this->delay, 0, 5);
}

Killaura::~Killaura() {
}

const char* Killaura::getModuleName() {
	return ("Killaura");
}

static std::vector<C_Entity*> targetList;

void findEntity(C_Entity* currentEntity, bool isRegularEntity) {
	static auto killauraMod = moduleMgr->getModule<Killaura>();

	if (currentEntity == nullptr)
		return;

	if (currentEntity == g_Data.getLocalPlayer())  // Skip Local player
		return;

	if (!g_Data.getLocalPlayer()->canAttack(currentEntity, false))
		return;

	if (!g_Data.getLocalPlayer()->isAlive())
		return;

	if (!currentEntity->isAlive())
		return;

	if (killauraMod->isMobAura) {
		if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 63)
			return;
		if (currentEntity->width <= 0.01f || currentEntity->height <= 0.01f)  // Don't hit this pesky antibot on 2b2e.org
			return;
		if (currentEntity->getEntityTypeId() == 64)  // item
			return;
	} else {
		if (!Target::isValidTarget(currentEntity))
			return;
	}

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < killauraMod->range) {
		targetList.push_back(currentEntity);
	}
}

void Killaura::findWeapon() {
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

struct CompareTargetEnArray {
	bool operator()(C_Entity* lhs, C_Entity* rhs) {
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
	}
};

void Killaura::onTick(C_GameMode* gm) {
	/*if ((holdMode && GameData::isLeftClickDown())) {
		if (cock && targetList.empty()) {
			auto stepMod = moduleMgr->getModule<Step>();
			{
				stepMod->height = 1.5f;
			}
		}
		if (rot && targetList.empty()) {
			auto stepMod = moduleMgr->getModule<Step>();
			{
				stepMod->height = 1.5f;
			}
		}
		//Loop through all our players and retrieve their information
		targetList.clear();

		g_Data.forEachEntity(findEntity);

		Odelay++;
		if (distanceCheck)
			std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
		if (!targetList.empty() && Odelay >= delay) {
			if (autoweapon) findWeapon();
			if (g_Data.getLocalPlayer()->velocity.squaredxzlen() < 0.01) {
				C_MovePlayerPacket p(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);  // make sure to update rotation if player is standing still
			}

			// Attack all entitys in targetList
			if (isMulti) {
				for (auto& i : targetList) {
					if (!(i->damageTime > 1 && hurttime)) {
						g_Data.getLocalPlayer()->swing();
						g_Data.getCGameMode()->attack(i);
					}
				}
			} else {
				if (!(targetList[0]->damageTime > 1 && hurttime)) {
					g_Data.getLocalPlayer()->swing();
					g_Data.getCGameMode()->attack(targetList[0]);
				}
			}
			Odelay = 0;
		}

		for (auto& i : targetList) {
			if (cock && !targetList.empty()) {
				vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*i->getPos());
				auto weewee = g_Data.getLocalPlayer();
				weewee->setRot(angle);
				if (strcmp(g_Data.getRakNetInstance()->serverIp.getText(), "geo.hivebedrock.network") == 0) {  // Only on The Hive
					//g_Data.getGuiData()->displayClientMessageF("[PACKET] this->oldRot; stepMod->height = 0.5625f; *g_Data.getClientInstance()->minecraft->timer = 17.f;");
					auto hfMod = moduleMgr->getModule<HiveFly>();
					if (hfMod->isEnabled()) {
						*g_Data.getClientInstance()->minecraft->timer = 24.f;  // Slowdown to prevent: Bluebird, CIA
						auto stepMod = moduleMgr->getModule<Step>();
						{
							stepMod->height = 0.5625f;
						}
					}
				}
			}
			if (rot && !targetList.empty()) {
				vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*i->getPos());
				auto weewee = g_Data.getLocalPlayer();
				weewee->yawUnused2 = angle.x;
				weewee->yawUnused2 = angle.y;
				weewee->yawUnused1 = angle.x;
				weewee->yawUnused1 = angle.y;
				if (strcmp(g_Data.getRakNetInstance()->serverIp.getText(), "geo.hivebedrock.network") == 0) {  // Only on The Hive
					auto stepMod = moduleMgr->getModule<Step>();
					{
						stepMod->height = 0.5625f;
					}
					//g_Data.getGuiData()->displayClientMessageF("[PACKETLOG] this->rot; stepMod->height = 0.5625f; timer->17");
					auto hfMod = moduleMgr->getModule<HiveFly>();
					if (hfMod->isEnabled()) {
						*g_Data.getClientInstance()->minecraft->timer = 19.f;  // Slowdown to prevent: Bluebird, CIA, AC ban
					}
				}
			}
		}
	}*/
		if (cock && targetList.empty()) {
			auto stepMod = moduleMgr->getModule<Step>();
			{
				stepMod->height = 1.5f;
			}
			/*auto logMod = moduleMgr->getModule<PacketLogger>();
		if (logdMod->isEnabled()) {
			g_Data.getGuiData()->displayClientMessageF("[PACKETLOG] this->oldRot; stepMod->height = 1.5f");
		}*/
		}
		if (rot && targetList.empty()) {
			auto stepMod = moduleMgr->getModule<Step>();
			{
				stepMod->height = 1.5f;
			}
		}
		//Loop through all our players and retrieve their information
		targetList.clear();

		g_Data.forEachEntity(findEntity);

		Odelay++;
		if (distanceCheck)
			std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
		if (!targetList.empty() && Odelay >= delay) {
			if (autoweapon) findWeapon();
			if (g_Data.getLocalPlayer()->velocity.squaredxzlen() < 0.01) {
				C_MovePlayerPacket p(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);  // make sure to update rotation if player is standing still
			}

			// Attack all entitys in targetList
			if (isMulti) {
				for (auto& i : targetList) {
					if (!(i->damageTime > 1 && hurttime)) {
						g_Data.getLocalPlayer()->swing();
						g_Data.getCGameMode()->attack(i);
						targethud++;
					} else
						targethud = 0;
				}
			} else {
				if (!(targetList[0]->damageTime > 1 && hurttime)) {
					g_Data.getLocalPlayer()->swing();
					g_Data.getCGameMode()->attack(targetList[0]);
					targethud++;
				} else
					targethud = 0;
			}
			Odelay = 0;
		}

		for (auto& i : targetList) {
			if (cock && !targetList.empty()) {
				vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*i->getPos());
				auto weewee = g_Data.getLocalPlayer();
				weewee->setRot(angle);
				if (strcmp(g_Data.getRakNetInstance()->serverIp.getText(), "geo.hivebedrock.network") == 0) {  // Only on The Hive
																											   //g_Data.getGuiData()->displayClientMessageF("[PACKET] this->oldRot; stepMod->height = 0.5625f; *g_Data.getClientInstance()->minecraft->timer = 17.f;");
					auto stepMod = moduleMgr->getModule<Step>();
					{
						stepMod->height = 0.5625f;
					}
			}
		}
		for (auto& i : targetList) {
			vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*i->getPos());
			if (rot && !targetList.empty()) {
				auto weewee = g_Data.getLocalPlayer();
				if (weewee->pitch != 0 && weewee->yaw != 0)
					weewee->yaw = angle.y;
					weewee->pitch = angle.x;
			}
		}
	}
}

void Killaura::onEnable() {
	if (g_Data.getLocalPlayer() == nullptr)
		this->setEnabled(false);
}

void Killaura::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	if (g_Data.isInGame() && targetList.size() == 1) {
		if (targethud > 1) {
			for (auto& i : targetList) {
		C_GuiData* dat = g_Data.getClientInstance()->getGuiData();
				vec2_t windowSize = dat->windowSize;
		std::string text = targetList[0]->getNameTag()->getText();
		text = Utils::sanitize(text);
		std::string realname = "Name : " + text;
		int dist2 = (*targetList[0]->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
		auto dist = std::to_string(dist2);
		auto distancestring = std::string("Dist : " + dist);
		vec4_t duotagteam = (vec4_t(windowSize.x / 1.5f - (windowSize.x / 7),
									windowSize.y / 1.6f - (windowSize.y / 13),
									windowSize.x / 1.8f + (windowSize.x / 9 + targetList[0]->getNameTag()->textLength),
									windowSize.y / 2 - windowSize.y / 8 + windowSize.y / 4));
		DrawUtils::fillRectangle(vec4_t(duotagteam),
								 MC_Color(0.05f, 0.05f, 0.05f), 0.35f);
		DrawUtils::drawRectangle(vec4_t(duotagteam),
								 MC_Color(1.f, 1.f, 1.f), 1.f);

		
			DrawUtils::drawText(vec2_t(windowSize.x / 1.5f - windowSize.x / 7.25f,
								   windowSize.y / 2 - windowSize.y / 5.2f + windowSize.y / 4),
							&realname,
							MC_Color(1.f, 1.f, 1.f), 1.f);
		
		DrawUtils::drawText(vec2_t(windowSize.x / 1.5f - windowSize.x / 7.25f,
								   windowSize.y / 2 - windowSize.y / 5.8f + windowSize.y / 4),
							&distancestring,
							MC_Color(1.f, 1.f, 1.f), 1.f);
		DrawUtils::flush();
		vec2_t textPos;
		vec4_t rectPos;
		auto* player = reinterpret_cast<C_Player*>(targetList[0]);
		float x = windowSize.x / 1.5f - windowSize.x / 7.1f;
		float y = windowSize.y / 2 - windowSize.y / 6.4f + windowSize.y / 4;
		float scale = 3 * 0.26f;
		float spacing = scale + 15.f + 2;
		if (i->getEntityTypeId() == 63) {
			// armor
			for (int i = 0; i < 4; i++) {
				C_ItemStack* stack = player->getArmor(i);
				if (stack->item != nullptr) {
					DrawUtils::drawItem(stack, vec2_t(x, y), 1.f, scale, stack->isEnchanted());
					x += scale * spacing;
				}
			}
			// item
			{
				C_ItemStack* stack = player->getSelectedItem();
				if (stack->item != nullptr) {
					DrawUtils::drawItem(stack, vec2_t(x, y), 1.f, scale, stack->isEnchanted());
						}
					}
				}
			}
		}
	}
}
	void Killaura::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
}

void Killaura::onSendPacket(C_Packet* packet) {
	if (packet->isInstanceOf<C_MovePlayerPacket>() && g_Data.getLocalPlayer() != nullptr && silent) {
		if (!targetList.empty()) {
			auto* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
			vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos());
			movePacket->pitch = angle.x;
			movePacket->headYaw = angle.y;
			movePacket->yaw = angle.y;
		}
	}
}

void Killaura::onDisable() {
	auto stepMod = moduleMgr->getModule<Step>();
	targethud = 0;
	{
		stepMod->height = 1.5f;
	}
}