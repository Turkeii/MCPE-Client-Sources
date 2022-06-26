#include "PlayerList.h"
#include "../pch.h"

using namespace std;
PlayerList::PlayerList() : IModule(VK_TAB, Category::VISUAL, "Displays all players in your render distance") {
	registerEnumSetting("Theme", &theme, 0);
	theme.addEntry("Normal", 0);
	theme.addEntry("Ketamine", 1);
	registerBoolSetting("Hold", &hold, hold);
}

const char* PlayerList::getModuleName() {
	return "PlayerList";
}

static vector<C_Entity*> playerList;
void findPlayers(C_Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr) return;
	if (!g_Data.getLocalPlayer()->canAttack(currentEntity, false)) return;
	if (!g_Data.getLocalPlayer()->isAlive()) return;
	if (!currentEntity->isAlive()) return;
	if (currentEntity->getEntityTypeId() != 319) return;
	if (currentEntity->getNameTag()->getTextLength() <= 1) return;
	playerList.push_back(currentEntity);
}

struct CompareTargetEnArray {
	bool operator()(C_Entity* lhs, C_Entity* rhs) {
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
	}
};

bool PlayerList::isHoldMode() {
	return hold;
}

void PlayerList::onEnable() {
	playerList.clear();
}

void PlayerList::onTick(C_GameMode* gm) {
	playerList.clear();
	g_Data.forEachEntity(findPlayers);
	//sort(playerList.begin(), playerList.end(), CompareTargetEnArray());
}

void PlayerList::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	static auto clickGUI = moduleMgr->getModule<ClickGUIMod>();
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	auto interfaceColor = ColorUtil::interfaceColor(1);
	if (g_Data.canUseMoveKeys() || !clickGUI->hasOpenedGUI) {
		string aids = "---------------------------------";
		string headerStr = "Player                      HP         Dist";
		string hpString = "                                       100%";
		float te = DrawUtils::getTextWidth(&aids, 1.F) + 8.F;

		vec4_t rectPos = vec4_t(g_Data.getClientInstance()->getGuiData()->widthGame / 2, 1, 1, 1);
		rectPos2 = vec4_t(positionX, positionY, positionX + te, positionY);
		vec4_t headerPos = vec4_t(positionX, positionY - 10, positionX + te, positionY);
		vec4_t headerPos2 = vec4_t(positionX, positionY, positionX + te, positionY + 1);
		vec2_t textPos = vec2_t(rectPos.x, rectPos.y);
		vec2_t textPos2 = vec2_t(rectPos2.x + 55, rectPos2.y - 3);

		for (auto& i : playerList) {
			textPos.y += 8; textPos2.y += 10; rectPos2.w += 10.2f;
			string test = i->getNameTag()->getText(); test = Utils::sanitize(test); test = test.substr(0, test.find('\n'));
			float dist = (*i->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
			string distance = "                                                               " + to_string((int)dist) + "ft";

			switch (theme.getSelectedValue()) {
			case 0:
				DrawUtils::drawCenteredString(textPos, &test, 1.f, MC_Color(255, 255, 255), true);
				break;
			case 1:
				DrawUtils::drawCenteredString(textPos2, &test, 1.f, MC_Color(255, 255, 255), true);
				DrawUtils::drawCenteredString(textPos2, &hpString, 1.f, MC_Color(25, 255, 25), true);
				DrawUtils::drawCenteredString(textPos2, &distance, 1.f, MC_Color(255, 255, 255), true);
				break;
			}
		}
		switch (theme.getSelectedValue()) {
		case 1:
			DrawUtils::drawText(vec2_t(headerPos.x + 2, headerPos.y + 1), &headerStr, MC_Color(255, 255, 255), 1, 1, true);
			DrawUtils::fillRectangleA(rectPos2, MC_Color(0, 0, 0, 100));
			DrawUtils::fillRectangleA(headerPos, MC_Color(0, 0, 0, 150));
			DrawUtils::fillRectangleA(headerPos2, interfaceColor);
			break;
		}
	}
}

void PlayerList::onDisable() {
	playerList.clear();
}