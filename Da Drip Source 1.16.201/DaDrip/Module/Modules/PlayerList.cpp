#include "PlayerList.h"

#include "../../../Utils/Logger.h"
#include "../../DrawUtils.h"
#include "../../Scripting/ScriptManager.h"

PlayerList::PlayerList() : IModule(0x0, Category::HUD, "Displays a list of players on your screen in render distance") {
	registerFloatSetting("Scale", &this->scale, this->scale, 0.5f, 1.5f);
	registerBoolSetting("the_fellas", &this->thefellas, this->thefellas);
}

PlayerList::~PlayerList() {
}

const char* PlayerList::getModuleName() {
	return ("PlayerList");
}

static std::vector<C_Entity*> playerList;

void findPlayers(C_Entity* currentEntity, bool isRegularEntity) {
	static auto playerMod = moduleMgr->getModule<PlayerList>();
	//log(*currentEntity->getNameTag()->getText());
	if (currentEntity == nullptr)
		return;

	if (playerMod->thefellas && !FriendList::findPlayer(currentEntity->getNameTag()->getText())) return;

	if (currentEntity == g_Data.getLocalPlayer()) return;
	//	if (!Target::isValidTarget(currentEntity))
	//	return;

	if (currentEntity->getEntityTypeId() != 63)  // player
		return;

	playerList.push_back(currentEntity);
}

void PlayerList::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
	vec2_t windowSizeReal = g_Data.getClientInstance()->getGuiData()->windowSizeReal;

	if ((g_Data.getLocalPlayer() != nullptr)) {  //player list
		int runs2 = 0;
		float initialYVal = 30.f;
		playerList.clear();
		g_Data.forEachEntity(findPlayers);
		if (thefellas) {
			DrawUtils::drawText(vec2_t(windowSize.x - 120.f, initialYVal - 12.f), &std::string("the_fellas:"), MC_Color(255, 255, 255));
		}
		if (!playerList.empty()) {
			//g_Data.forEachEntity()
			for (auto& ye : playerList) {
				float distye = (*ye->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
				char eeeee = *ye->getNameTag()->getText();
				std::string why = ye->getNameTag()->getText();
				std::string* isThisSoBroken = &why;
				//	log(*playerList[0]->getNameTag()->getText());

				//	windowSize.x - 120.f, 30.f

				DrawUtils::drawText(vec2_t(windowSize.x - 140.f, initialYVal), &why, (FriendList::findPlayer(why) ? (MC_Color(0, 255, 255)) : MC_Color(255, 255, 255)));
				initialYVal += 10.f;
				
				static float constexpr scale2 = 0.6f;
				static float constexpr opacity2 = 0.25f;
				static float constexpr spacing2 = scale2 + 15.f;
				float x2 = windowSize.x - 190.f;
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
				runs2++;
			}
		}
	}
}