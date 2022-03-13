#include "TargetHud.h"

TargetHud::TargetHud() : IModule(0, Category::GUI, "Displays info about the target") {
	this->registerFloatSetting("Range", &this->range, this->range, 0.f, 10.f);
}

TargetHud::~TargetHud() {
}

const char* TargetHud::getModuleName() {
	return ("TargetHud");
}

static std::vector<C_Entity*> targetList;

void findEntity1(C_Entity* currentEntity1, bool isRegularEntity) {
	static auto killauraMod = moduleMgr->getModule<TargetHud>();

	if (currentEntity1 == nullptr)
		return;

	if (currentEntity1 == g_Data.getLocalPlayer())  // Skip Local player
		return;

	if (!g_Data.getLocalPlayer()->canAttack(currentEntity1, false))
		return;

	if (!g_Data.getLocalPlayer()->isAlive())
		return;

	if (!currentEntity1->isAlive())
		return;

	if (killauraMod->isMobAura) {
		if (currentEntity1->getNameTag()->getTextLength() <= 1 && currentEntity1->getEntityTypeId() == 63)
			return;
		if (currentEntity1->width <= 0.01f || currentEntity1->height <= 0.01f)  // Don't hit this pesky antibot on 2b2e.org
			return;
		if (currentEntity1->getEntityTypeId() == 64)  // item
			return;
	} else {
		if (!Target::isValidTarget(currentEntity1))
			return;
	}

	float dist = (*currentEntity1->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < killauraMod->range) {
		targetList.push_back(currentEntity1);
	}
}

struct CompareTargetEnArray {
	bool operator()(C_Entity* lhs, C_Entity* rhs) {
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
	}
};

void TargetHud::onTick(C_GameMode* gm) {
	//Loop through all our players and retrieve their information
	targetList.clear();

	g_Data.forEachEntity(findEntity1);

	Odelay++;
	if (distanceCheck)
		std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());

		// Attack all entitys in targetList
		if (isMulti) {
			for (auto& i : targetList) {
				if (!(i->damageTime > 1 && hurttime)) {
					//g_Data.getLocalPlayer()->swing();
					//g_Data.getCGameMode()->attack(i);
					targethud++;
				} else
					targethud = 0;
			}
		} else {
			if (!(targetList[0]->damageTime > 1 && hurttime)) {
				//g_Data.getLocalPlayer()->swing();
				//g_Data.getCGameMode()->attack(targetList[0]);
				targethud++;
			} else
				targethud = 0;
		}
		Odelay = 0;
	}

void TargetHud::onEnable() {
	if (g_Data.getLocalPlayer() == nullptr)
		this->setEnabled(false);
}

void TargetHud::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
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
				if ((targetList[0]->damageTime > 1)) {
				DrawUtils::fillRectangle(vec4_t(duotagteam),
										 MC_Color(1.f, 0.f, 0.f), 0.35f);
					}
				if (!(targetList[0]->damageTime > 1)) {
					DrawUtils::fillRectangle(vec4_t(duotagteam),
											 MC_Color(0.f, 1.f, 0.f), 0.35f);
				}
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
void TargetHud::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
}

void TargetHud::onDisable() {
	targethud = 0;
}