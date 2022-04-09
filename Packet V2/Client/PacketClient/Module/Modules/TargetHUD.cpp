#include "TargetHUD.h"

TargetHUD::TargetHUD() : IModule(0, Category::VISUAL, "cukepis") {
	registerEnumSetting("Mode", &mode, 0);
	mode.addEntry("Packet", 0);
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

	if (!g_Data.getLocalPlayer()->canAttack(currentEntity, false))
		return;

	if (!g_Data.getLocalPlayer()->isAlive())
		return;

	if (!currentEntity->isAlive())
		return;

	if (currentEntity->getEntityTypeId() != 319)  // Players
		return;

	if (!Target::isValidTarget(currentEntity))
		return;

	if (currentEntity->getEntityTypeId() == 1677999)  // Villager
		return;

	if (currentEntity->getEntityTypeId() == 51)  // NPC
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < 10) {
		targetList3.push_back(currentEntity);
	}
}

void TargetHUD::onEnable() {
}

struct CompareTargetEnArray {
	bool operator()(C_Entity* lhs, C_Entity* rhs) {
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
	}
};

void TargetHUD::onTick(C_GameMode* gm) {
	//Loop through all our players and retrieve their information
	targetList3.clear();

	g_Data.forEachEntity(findPlayers2);

	for (auto& i : targetList3) {
		if (!(i->damageTime > 1 && hurttime)) {
			targethud++;
		} else targethud = 0;
	}
}

void TargetHUD::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	if (targetList3.size() == 1 && targethud > 1) {
		for (auto& i : targetList3) {
			if (i->getEntityTypeId() == 319) {
				if (mode.getSelectedValue() == 0) {
					vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
					static auto hudMod = moduleMgr->getModule<HudModule>();
					vec3_t* pos = targetList3[0]->getPos();
					std::string namestr = "Name: ";
					std::string name = namestr + targetList3[0]->getNameTag()->getText();
					std::string position = "Position: " + std::to_string((int)floorf(pos->x)) + " " + std::to_string((int)floorf(pos->y)) + " " + std::to_string((int)floorf(pos->z));

					name = Utils::sanitize(name);
					name = name.substr(0, name.find('\n'));

					float margin = windowSize.x / 5;
					constexpr float borderPadding = 1;
					constexpr float unused = 5;
					constexpr float idek = 5;

					float nameLength = DrawUtils::getTextWidth(&name) + 20;

					static const float rectHeight = (idek, unused) * DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight();

					vec4_t rectPos = vec4_t(
						windowSize.x - margin - nameLength - 15 - borderPadding * 2,
						windowSize.y - margin - rectHeight + 10,
						windowSize.x - margin + borderPadding - 2,
						windowSize.y - margin + 11);

					vec4_t LinePos = vec4_t(
						windowSize.x - margin - nameLength - 6.5 - borderPadding * 2,
						windowSize.y - margin - rectHeight + 49,
						windowSize.x - margin + borderPadding - 10.5,
						windowSize.y - margin + 7);

					vec2_t TextPos = vec2_t(rectPos.x + 8, rectPos.y + 5);
					vec2_t armorPos = vec2_t(rectPos.x + 5.5, rectPos.y + 24);
					vec2_t TextPos2 = vec2_t(rectPos.x + 8, rectPos.y + 15);

					if (targetList3[0]->damageTime >= 1) {
						vec2_t TextPosIdk = vec2_t(LinePos.x + 55, LinePos.y + 2);
						std::string Health = " ";
						DrawUtils::drawText(TextPosIdk, &Health, MC_Color(255, 255, 255), 0.67, 1, true);
					}

					if (targetList3[0]->damageTime >= 1) {
						DrawUtils::fillRectangle(LinePos, MC_Color(255, 0, 0), 0.5);
						DrawUtils::drawRectangle(LinePos, MC_Color(255, 0, 0), 1);
					} else {
						DrawUtils::fillRectangle(LinePos, MC_Color(0, 255, 0), 0.5);
						DrawUtils::drawRectangle(LinePos, MC_Color(0, 255, 0), 1);
					}

					DrawUtils::flush();

					if (i->getEntityTypeId() == 319) {
						static float constexpr opacity = 10;
						float scale = 3 * 0.26f;
						float spacing = scale + 15.f + 2;

						auto* player = reinterpret_cast<C_Player*>(targetList3[0]);

						for (int t = 0; t < 4; t++) {
							C_ItemStack* stack = player->getArmor(t);
							if (stack->isValid()) {
								DrawUtils::drawItem(stack, vec2_t(armorPos), 1, scale, false);
								armorPos.x += scale * spacing;
							}
						}
						C_PlayerInventoryProxy* supplies = player->getSupplies();
						C_ItemStack* item = supplies->inventory->getItemStack(supplies->selectedHotbarSlot);
						if (item->isValid()) DrawUtils::drawItem(item, vec2_t(armorPos), opacity, scale, item->isEnchanted());
					}

					DrawUtils::drawRoundRectangle(rectPos, MC_Color(0, 0, 0), 0.3);
					//DrawUtils::drawRectangle(rectPos, MC_Color(0, 0, 0), 0.35);
					DrawUtils::drawText(TextPos2, &position, MC_Color(255, 255, 255), 1, 1, true);
					DrawUtils::drawText(TextPos, &name, MC_Color(255, 255, 255), 1, 1, true);
				}
			}
		}
	}
}

void TargetHUD::onDisable() {
}