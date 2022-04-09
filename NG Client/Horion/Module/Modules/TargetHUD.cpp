#include "TargetHUD.h"

TargetHUD::TargetHUD() : IModule(0, Category::VISUAL, "TargetHUD") {
}

TargetHUD::~TargetHUD() {
}

const char* TargetHUD::getModuleName() {
	return ("TargetHUD");
}

static std::vector<C_Entity*> targetList3;

void findPlayers2(C_Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity == g_Data.getLocalPlayer())
		return;

	if (!g_Data.getLocalPlayer()->canAttack(currentEntity, false)) return;
	if (!g_Data.getLocalPlayer()->isAlive()) return;
	if (!currentEntity->isAlive()) return;
	if (currentEntity->getEntityTypeId() != 319) return;  // Players
	if (!Target::isValidTarget(currentEntity)) return;
	if (currentEntity->getEntityTypeId() == 1677999) return;  // Villager
	if (currentEntity->getEntityTypeId() == 51) return; // NPC

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < 10) {
		targetList3.push_back(currentEntity);
	}
}


struct CompareTargetEnArray {
	bool operator()(C_Entity* lhs, C_Entity* rhs) {
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
	}
};

void TargetHUD::onTick(C_GameMode* gm) {
	// Loop through all our players and retrieve their information
	targetList3.clear();

	g_Data.forEachEntity(findPlayers2);

	for (auto& i : targetList3) {
		if (!(i->damageTime > 1 && hurttime)) {
			targethud++;
		} else
			targethud = 0;
	}
}

void TargetHUD::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	static auto partner = moduleMgr->getModule<Partner>();
	std::sort(targetList3.begin(), targetList3.end(), CompareTargetEnArray());
	if (g_Data.isInGame() && !targetList3.empty() && g_Data.canUseMoveKeys && g_Data.getLocalPlayer()->canOpenContainerScreen() && targethud >= 1 && targetList3[0]->isPlayer()) {
		// Atributes
		AbsorptionAttribute attribute = AbsorptionAttribute();
		HealthAttribute attribute2 = HealthAttribute();
		float Absorbtion = ((int)targetList3[0]->getAttribute(&attribute)->currentValue);
		float Health = ((int)targetList3[0]->getAttribute(&attribute2)->currentValue);
		float HealthMax = ((int)targetList3[0]->getAttribute(&attribute2)->maximumValue);

		vec2 res = g_Data.getClientInstance()->getGuiData()->windowSize;
		C_LocalPlayer* Player = g_Data.getClientInstance()->getLocalPlayer();
		if (Player != nullptr) {
			vec4 rectPos((res.x / 2.f) + (res.x / 20.f), (res.y / 2.f) + (res.y / 24.f), (res.x / 2.f) + (res.x / 6.f), (res.y / 2.f) + (res.y / 8.f));  // vec4 rectPos((res.x / 2.f) + (res.x / 20.f), (res.y / 2.f) - (res.y / 24.f), (res.x / 2.f) + (res.x / 6.f), (res.y / 2.f) + (res.y / 24.f));
			float rectWidth = rectPos.z - rectPos.x;

			// counter for fade
			counter++;
			if (counter == 100)
				counter--;

			// The actual box
			{
				// Gives the rounded corners effect
				if (partner->Partnered.selected == 0) {
					DrawUtils::fillRectangle(vec4{rectPos.x - 1, rectPos.y - 8, rectPos.z + 1, rectPos.w + 1}, MC_Color(0, 0, 0), counter / 340.33333f);
					DrawUtils::drawRectangle(vec4{rectPos.x - 1, rectPos.y - 8, rectPos.z + 1, rectPos.w + 1}, MC_Color(0, 0, 255), counter / 340.33333f);
				} else if (partner->Partnered.selected == 1) {
					DrawUtils::fillRectangle(vec4{rectPos.x - 1, rectPos.y - 8, rectPos.z + 1, rectPos.w + 1}, MC_Color(0, 0, 0), counter / 340.33333f);
					DrawUtils::drawRectangle(vec4{rectPos.x - 1, rectPos.y - 8, rectPos.z + 1, rectPos.w + 1}, MC_Color(150, 30, 255), counter / 340.33333f);
				} else if (partner->Partnered.selected == 2) {
					DrawUtils::fillRectangle(vec4{rectPos.x - 1, rectPos.y - 8, rectPos.z + 1, rectPos.w + 1}, MC_Color(0, 0, 0), counter / 340.33333f);
					DrawUtils::drawRectangle(vec4{rectPos.x - 1, rectPos.y - 8, rectPos.z + 1, rectPos.w + 1}, MC_Color(0, 255, 255), counter / 340.33333f);
				} else {
					DrawUtils::fillRectangle(vec4{rectPos.x - 1, rectPos.y - 8, rectPos.z + 1, rectPos.w + 1}, MC_Color(0, 0, 0), counter / 340.33333f);
					DrawUtils::drawRectangle(vec4{rectPos.x - 1, rectPos.y - 8, rectPos.z + 1, rectPos.w + 1}, MC_Color(0, 255, 255), counter / 340.33333f);
				}
			}

			// all the displays

			// Gets the targets name, then makes it not go to next line
			std::string targetName;
			auto Hud = moduleMgr->getModule<HudModule>();
			if (Hud->displaySecondHalf) {
				targetName = Utils::sanitize(targetList3[0]->getNameTag()->getText());
				Utils::replaceString(targetName, '\n', ' ');
			} else {
				targetName = Utils::sanitize(targetList3[0]->getNameTag()->getText());
				targetName = targetName.substr(0, targetName.find('\n'));
			}

			std::string HealthString = std::to_string(((int)Health));
			std::string HealthMaxString = std::to_string(((int)HealthMax));
			std::string distance = "Distance: " + std::to_string((int)(*targetList3[0]->getPos()).dist(*g_Data.getLocalPlayer()->getPos()));
			std::string healthDisplay = "Health: " + HealthString + "/" + HealthMaxString;
			std::string armor = "Armor: ";
			std::string absorptionDisplay;
			// Absorbtion Bar
			if (Absorbtion > 0) {
				// DrawUtils::drawRectangle(vec4(rectPos.x + .2f, rectPos.y + (res.y / 18.f), rectPos.x + 1 * rectWidth, rectPos.y + (res.y / 18.f) + ((rectPos.w - (rectPos.y + (res.y / 18.f))) / 2)), MC_Color(255, 255, 85), counter / 100.f);
				std::string absorptionString = std::to_string((int)(Absorbtion));
				absorptionDisplay = " Absorption: " + absorptionString;
				float absorptionBarWidth = (Absorbtion / HealthMax) * rectWidth;
				if (!(targetList3[0]->damageTime > 1))
					DrawUtils::fillRectangle(vec4(rectPos.x + .2f, rectPos.y + (res.y / 18.f), rectPos.x + absorptionBarWidth, rectPos.y + (res.y / 18.f) + ((rectPos.w - (rectPos.y + (res.y / 18.f))) / 2)), MC_Color(255, 255, 85), counter / 100.f);
				else
					DrawUtils::fillRectangle(vec4(rectPos.x + .2f, rectPos.y + (res.y / 18.f), rectPos.x + absorptionBarWidth, rectPos.y + (res.y / 18.f) + ((rectPos.w - (rectPos.y + (res.y / 18.f))) / 2)), MC_Color(255, 255, 0), counter / 100.f);
			}

			// The text
			{
				DrawUtils::drawText(vec2(rectPos.x + (res.x / 900.f), rectPos.y - 17 + (res.y / 35.f)), &targetName, MC_Color(255, 255, 255), 1.f, counter / 100.f);             // name
				DrawUtils::drawText(vec2(rectPos.x + (res.x / 900.f), rectPos.y - 9 + (res.y / 35.f)), &distance, MC_Color(255, 255, 255), 0.7f, counter / 100.f);               // distance
				DrawUtils::drawText(vec2(rectPos.x + 35 + (res.x / 900.f), rectPos.y - 4 + (res.y / 35.f)), &absorptionDisplay, MC_Color(255, 255, 85), 0.7f, counter / 100.f);  // absorbtion
				DrawUtils::drawText(vec2(rectPos.x + (res.x / 900.f), rectPos.y - 4 + (res.y / 35.f)), &healthDisplay, MC_Color(255, 255, 255), 0.7f, counter / 100.f);          // health
				DrawUtils::drawText(vec2(rectPos.x + (res.x / 900.f), rectPos.y + 1 + (res.y / 35.f)), &armor, MC_Color(255, 255, 255), 0.7f, counter / 100.f);                  // armor
				vec2 armorPos = vec2(rectPos.x + (res.x / 35.f), rectPos.y + 0 + (res.y / 35.f));

				static float constexpr opacity = 10;
				float scale = 2 * 0.26f;
				float spacing = scale + 15.f + 2;

				auto* player = reinterpret_cast<C_Player*>(targetList3[0]);

				for (int t = 0; t < 4; t++) {
					C_ItemStack* stack = player->getArmor(t);
					if (stack->isValid()) {
						DrawUtils::drawItem(stack, vec2(armorPos), 1, scale, false);
						armorPos.x += scale * spacing;
					}
				}
				C_PlayerInventoryProxy* supplies = player->getSupplies();
				C_ItemStack* item = supplies->inventory->getItemStack(supplies->selectedHotbarSlot);
				if (item->isValid()) DrawUtils::drawItem(item, vec2(armorPos), opacity, scale, item->isEnchanted());
			}
			DrawUtils::flush();

			// Health Bar
			{
				float healthBarWidth = (Health / HealthMax) * rectWidth;
				if (!(targetList3[0]->damageTime > 1)) {
					DrawUtils::fillRectangle(vec4(rectPos.x + .2f, rectPos.y + (res.y / 18.f) + ((rectPos.w - (rectPos.y + (res.y / 18.f))) / 2), rectPos.x + healthBarWidth, rectPos.w), MC_Color(0, 200, 0), counter / 100.f);
					// DrawUtils::drawRectangle(vec4(rectPos.x + .2f, rectPos.y + (res.y / 18.f) + ((rectPos.w - (rectPos.y + (res.y / 18.f))) / 2), rectPos.x + 1 * rectWidth, rectPos.w), MC_Color(0, 255, 0), counter / 100.f);
				} else {
					DrawUtils::fillRectangle(vec4(rectPos.x + .2f, rectPos.y + (res.y / 18.f) + ((rectPos.w - (rectPos.y + (res.y / 18.f))) / 2), rectPos.x + healthBarWidth, rectPos.w), MC_Color(255, 0, 0), counter / 100.f);
					// DrawUtils::drawRectangle(vec4(rectPos.x + .2f, rectPos.y + (res.y / 18.f) + ((rectPos.w - (rectPos.y + (res.y / 18.f))) / 2), rectPos.x + 1 * rectWidth, rectPos.w), MC_Color(255, 0, 0), counter / 100.f);
				}
			}
			rectPos.y += res.y / 12.f;
			rectPos.w += res.y / 12.f;
		}

		DrawUtils::flush();
	}
}