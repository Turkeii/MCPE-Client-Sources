#include "PlayerList.h"
#include "../../DrawUtils.h"
#include "../ModuleManager.h"

PlayerList::PlayerList() : IModule(0x0, Category::GUI, "draws a list of nearby players next to the array list") {
	registerBoolSetting("Show Armour", &this->armour, this->armour);
}

PlayerList::~PlayerList() {
}

const char* PlayerList::getModuleName() {
	return ("PlayerList");
}

static std::vector<C_Entity*> playerList;

void findPlayers(C_Entity* currentEntity, bool isRegularEntity) {
	//log(*currentEntity->getNameTag()->getText());
	if (currentEntity == nullptr)
		return;

	if (!Target::isValidTarget(currentEntity))
		return;

	if (currentEntity->getEntityTypeId() != 63)  // player
		return;

	playerList.push_back(currentEntity);
}

void PlayerList::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;

	if ((g_Data.getLocalPlayer() != nullptr)) {
		int runs2 = 0;
		playerList.clear();
		g_Data.forEachEntity(findPlayers);
		if (!playerList.empty()) {
			//g_Data.forEachEntity()
			for (auto& ye : playerList) {
				float distye = (*ye->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
				char eeeee = *ye->getNameTag()->getText();
				std::string why = ye->getNameTag()->getText();
				std::string* isThisSoBroken = &why;
				//	log(*playerList[0]->getNameTag()->getText());
				if (runs2 == 0) {
					if (strcmp(g_Data.getLocalPlayer()->getNameTag()->getText(), ye->getNameTag()->getText()) == 0) {
						DrawUtils::drawText(vec2_t(windowSize.x - 120.f, 30.f), isThisSoBroken, MC_Color(0, 0, 255), 1.f);
					} else if (FriendList::findPlayer(ye->getNameTag()->getText()) && !moduleMgr->getModule<NoFriends>()->isEnabled()) {
						DrawUtils::drawText(vec2_t(windowSize.x - 120.f, 30.f), isThisSoBroken, MC_Color(0, 255, 0), 1.f);
					} else {
						static auto ThemeMod = moduleMgr->getModule<Theme>();
						static float rcolors[4];
						if (ThemeMod->rainbow) {
							if (rcolors[3] < 1) {
								rcolors[0] = 1;
								rcolors[1] = 0.2f;
								rcolors[2] = 0.2f;
								rcolors[3] = 1;
							}

							Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[1], rcolors[2], rcolors[0], rcolors[1], rcolors[2]);  // perfect code, dont question this

							rcolors[0] += 0.0015f;
							if (rcolors[0] >= 1) {
								rcolors[0] = 0;
							}

							Utils::ColorConvertHSVtoRGB(rcolors[0], rcolors[1], rcolors[2], rcolors[0], rcolors[1], rcolors[2]);
							DrawUtils::drawText(vec2_t(windowSize.x - 120.f, 30.f + (10.f * runs2)), isThisSoBroken, MC_Color(rcolors), 1.f);
						} else {
							DrawUtils::drawText(vec2_t(windowSize.x - 120.f, 30.f + (10.f * runs2)), isThisSoBroken, MC_Color(Theme::rFloat, Theme::gFloat, Theme::bFloat), 1.f);
						}
					}

				} else {
					if (strcmp(g_Data.getLocalPlayer()->getNameTag()->getText(), ye->getNameTag()->getText()) == 0) {
						DrawUtils::drawText(vec2_t(windowSize.x - 120.f, 30.f), isThisSoBroken, MC_Color(0, 0, 255), 1.f);
					} else if (FriendList::findPlayer(ye->getNameTag()->getText()) && !moduleMgr->getModule<NoFriends>()->isEnabled()) {
						DrawUtils::drawText(vec2_t(windowSize.x - 120.f, 30.f), isThisSoBroken, MC_Color(0, 255, 0), 1.f);
					} else {
						static auto ThemeMod = moduleMgr->getModule<Theme>();
						static float rcolors[4];
						if (ThemeMod->rainbow) {
							if (rcolors[3] < 1) {
								rcolors[0] = 1;
								rcolors[1] = 0.2f;
								rcolors[2] = 0.2f;
								rcolors[3] = 1;
							}

							Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[1], rcolors[2], rcolors[0], rcolors[1], rcolors[2]);  // perfect code, dont question this

							rcolors[0] += 0.0015f;
							if (rcolors[0] >= 1) {
								rcolors[0] = 0;
							}

							Utils::ColorConvertHSVtoRGB(rcolors[0], rcolors[1], rcolors[2], rcolors[0], rcolors[1], rcolors[2]);
							DrawUtils::drawText(vec2_t(windowSize.x - 120.f, 30.f + (10.f * runs2)), isThisSoBroken, MC_Color(rcolors), 1.f);
						} else {
							DrawUtils::drawText(vec2_t(windowSize.x - 120.f, 30.f + (10.f * runs2)), isThisSoBroken, MC_Color(Theme::rFloat, Theme::gFloat, Theme::bFloat), 1.f);
						}
					}
				}
				if (armour) {
					static float constexpr scale2 = 0.6f;
					static float constexpr opacity2 = 0.25f;
					static float constexpr spacing2 = scale2 + 10.f;
					float x2 = windowSize.x - 159.f;
					float y2 = 30.f;
					if (runs2 == 0) {
						y2 = 30.f;
					} else {
						y2 = 30.f + (10.f * runs2);
					}
					for (int i2 = 0; i2 < 4; i2++) {
						C_ItemStack* stack2 = ye->getArmor(i2);
						if (stack2->item != nullptr) {
							DrawUtils::drawItem(stack2, vec2_t(x2, y2), opacity2, scale2, stack2->isEnchanted());
							x2 += scale * spacing2;
						}
					}
				}
				runs2++;
			}
		}
	}
}
