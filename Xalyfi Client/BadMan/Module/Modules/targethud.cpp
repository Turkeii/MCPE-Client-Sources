#include "../../../Utils/Logger.h"
#include "../../DrawUtils.h"
#include "../../Scripting/ScriptManager.h"
#include "InventoryView.h"

Targethud::Targethud() : IModule(0x0, Category::GUI, "Displays info about the target") {
	registerFloatSetting("Opacity", &this->Opacity, this->Opacity, 0.15f, 1.f);
	this->registerBoolSetting("Health", &this->health, this->health);
}

Targethud::~Targethud() {
}

const char* Targethud::getModuleName() {
	return ("Targethud");
}

static std::vector<C_Entity*> targetList;
void findEntity99543245(C_Entity* currentEntity, bool isRegularEntity) {
	static auto antibot = moduleMgr->getModule<AntiBot>();
	static auto hitboxMod = moduleMgr->getModule<Hitbox>();
	auto KA = moduleMgr->getModule<Killaura>();
	if (currentEntity == nullptr)
		return;
	if (!hitboxMod->isEnabled() && antibot->isHitboxCheckEnabled())
		if ((currentEntity->height < 1.5f || currentEntity->width < 0.49f || currentEntity->height > 2.1f || currentEntity->width > 0.9f))
			return;
	if (currentEntity == g_Data.getLocalPlayer())  // Skip Local player
		return;

	if (currentEntity->getEntityTypeId() != 63)  // player
		return;
	if (!currentEntity->isAlive())
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < KA->range) {
		targetList.push_back(currentEntity);
	}
}
void Targethud::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	targetList.clear();

	g_Data.forEachEntity(findEntity99543245);
	if (targetList.size() == 1) {
	}
}
void Targethud::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	auto KA = moduleMgr->getModule<Killaura>();
	if (KA->timer5 >= 1 && !targetList.empty() && g_Data.isInGame() && targetList.size() == 1 && KA->isEnabled()) {
		if (this->health) {
			for (auto& i : targetList) {
				auto theme = moduleMgr->getModule<AltTheme>();
				auto theme2 = moduleMgr->getModule<Theme>();
				C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
				auto entity = targetList[0]->getNameTag()->getText();
				auto entity2 = targetList[0]->getNameTag()->getTextLength() + 12;
				int entitydis = (*targetList[0]->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
				auto distance = std::to_string(entitydis);
				std::string DistanceString = "Dist : " + distance;

				int health = targetList[0]->getHealth();
				auto healthstring3 = std::to_string(health);
				std::string healthstring = "Health : " + healthstring3;

				DistanceString = Utils::sanitize(DistanceString);
				std::string message = entity;
				message = Utils::sanitize(message);
				C_GuiData* dat = g_Data.getClientInstance()->getGuiData();
				vec2_t windowSize = dat->windowSize;
				float scale = 3 * 0.26f;
				float spacing = scale + 15.f + 2;
				vec4_t duotagteam = (vec4_t(windowSize.x / 1.5f - (windowSize.x / 7),
											windowSize.y / 1.6f - (windowSize.y / 15),
											windowSize.x / 1.8f + (windowSize.x / 105 + scale * spacing + entity2 + 26 + scale * spacing),
											windowSize.y / 2 - windowSize.y / 11 + windowSize.y / 4));

				DrawUtils::fillRectangle(vec4_t(duotagteam),
										 MC_Color(0.05f, 0.05f, 0.05f), this->Opacity);
				DrawUtils::drawRectangle(vec4_t(duotagteam),
										 MC_Color(theme2->rFloat, theme2->gFloat, theme2->bFloat), 1.f);

				DrawUtils::drawText(vec2_t(windowSize.x / 1.5f - windowSize.x / 7.25f,
										   windowSize.y / 2 - windowSize.y / 5.5f + windowSize.y / 4),
									&message,
									MC_Color(theme->rFloat, theme->gFloat, theme->bFloat), 1.2f);

				DrawUtils::drawText(vec2_t(windowSize.x / 1.5f - windowSize.x / 7.25f,
										   windowSize.y / 2 - windowSize.y / 6.2f + windowSize.y / 4),
									&DistanceString,
									MC_Color(theme->rFloat, theme->gFloat, theme->bFloat), 1.2f);

				DrawUtils::drawText(vec2_t(windowSize.x / 1.5f - windowSize.x / 7.25f,
										   windowSize.y / 2 - windowSize.y / 7.1f + windowSize.y / 4),
									&healthstring,
									MC_Color(theme->rFloat, theme->gFloat, theme->bFloat), 1.2f);
				DrawUtils::flush();
				vec2_t textPos;
				vec4_t rectPos;
				auto* player = reinterpret_cast<C_Player*>(targetList[0]);
				float x = windowSize.x / 1.5f - windowSize.x / 7.15f;
				float y = windowSize.y / 2 - windowSize.y / 8.2f + windowSize.y / 4;
				if (i->getEntityTypeId() == 63) {
					// armor
					for (int i = 0; i < 4; i++) {
						C_ItemStack* stack = player->getArmor(i);
						if (stack->item != nullptr) {
							DrawUtils::drawItem(stack, vec2_t(x, y), 0.84f, scale, stack->isEnchanted());
							x += scale * spacing;
						}
					}
					// item
					{
						C_ItemStack* stack = player->getSelectedItem();
						if (stack->item != nullptr) {
							DrawUtils::drawItem(stack, vec2_t(x, y), 0.84f, scale, stack->isEnchanted());
						}
					}
				}
			}
		} else if (!this->health) {
			for (auto& i : targetList) {
				auto theme = moduleMgr->getModule<AltTheme>();
				auto theme2 = moduleMgr->getModule<Theme>();
				C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
				auto entity = targetList[0]->getNameTag()->getText();
				auto entity2 = targetList[0]->getNameTag()->getTextLength() + 12;
				int entitydis = (*targetList[0]->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
				auto distance = std::to_string(entitydis);
				std::string DistanceString = "Dist : " + distance;
				DistanceString = Utils::sanitize(DistanceString);
				std::string message = entity;
				message = Utils::sanitize(message);
				C_GuiData* dat = g_Data.getClientInstance()->getGuiData();
				vec2_t windowSize = dat->windowSize;
				float scale = 3 * 0.26f;
				float spacing = scale + 15.f + 2;
				vec4_t duotagteam = (vec4_t(windowSize.x / 1.5f - (windowSize.x / 7),
											windowSize.y / 1.6f - (windowSize.y / 15),
											windowSize.x / 1.8f + (windowSize.x / 105 + scale * spacing + entity2 + 26 + scale * spacing),
											windowSize.y / 2 - windowSize.y / 11 + windowSize.y / 4));

				DrawUtils::fillRectangle(vec4_t(duotagteam),
										 MC_Color(0.05f, 0.05f, 0.05f), this->Opacity);
				DrawUtils::drawRectangle(vec4_t(duotagteam),
										 MC_Color(theme2->rFloat, theme2->gFloat, theme2->bFloat), 1.f);

				DrawUtils::drawText(vec2_t(windowSize.x / 1.5f - windowSize.x / 7.25f,
										   windowSize.y / 2 - windowSize.y / 5.5f + windowSize.y / 4),
									&message,
									MC_Color(theme->rFloat, theme->gFloat, theme->bFloat), 1.2f);

				DrawUtils::drawText(vec2_t(windowSize.x / 1.5f - windowSize.x / 7.25f,
										   windowSize.y / 2 - windowSize.y / 6.4f + windowSize.y / 4),
									&DistanceString,
									MC_Color(theme->rFloat, theme->gFloat, theme->bFloat), 1.2f);
				DrawUtils::flush();
				vec2_t textPos;
				vec4_t rectPos;
				auto* player = reinterpret_cast<C_Player*>(targetList[0]);
				float x = windowSize.x / 1.5f - windowSize.x / 7.15f;
				float y = windowSize.y / 2 - windowSize.y / 7.7f + windowSize.y / 4;
				if (i->getEntityTypeId() == 63) {
					// armor
					for (int i = 0; i < 4; i++) {
						C_ItemStack* stack = player->getArmor(i);
						if (stack->item != nullptr) {
							DrawUtils::drawItem(stack, vec2_t(x, y), 0.84f, scale, stack->isEnchanted());
							x += scale * spacing;
						}
					}
					// item
					{
						C_ItemStack* stack = player->getSelectedItem();
						if (stack->item != nullptr) {
							DrawUtils::drawItem(stack, vec2_t(x, y), 0.84f, scale, stack->isEnchanted());
						}
					}
				}
			}
		}
	}
}
void Targethud::onDisable() {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
}

void Targethud::onEnable() {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
}