#include "SessionInfo.h"
#include "../pch.h"
#include <chrono>

using namespace std;
SessionInfo::SessionInfo() : IModule(0, Category::VISUAL, "Displays the SessionInfo") {
	registerEnumSetting("Theme", &mode, 0);
	mode.addEntry("Packet", 0);
	mode.addEntry("Tenacity", 1);
	registerBoolSetting("Outline", &outline, outline);
	registerIntSetting("Opacity", &opacity, opacity, 0, 255);
	shouldHide = true;
}

const char* SessionInfo::getModuleName() {
	return ("SessionInfo");
}

void SessionInfo::onTick(C_GameMode* gm) {
	if (ticks < 1260) ticks += 1;
	else ticks = 0;

	if (ticks2 < 20) ticks2 += 1;
	else ticks2 = 0;

	if (ticks3 < 72000) ticks3 += 1;
	else ticks3 = 0;

	if (ticks == 1260) min += 1;
	if (ticks2 == 20) sec += 1;
	if (ticks3 == 72000) hour += 1;

	if (sec == 60) sec = 0;
	if (min == 60) min = 0;
}

void SessionInfo::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	static auto clickGUI = moduleMgr->getModule<ClickGUIMod>();

	if (g_Data.canUseMoveKeys() && !clickGUI->hasOpenedGUI) {
		auto interfaceColor = ColorUtil::interfaceColor(1);
		string title = "Statistics";
		string title2 = string(BOLD) + "Statistics";
		aidsLen = DrawUtils::getTextWidth(&string("Games Played: 0          "));
		vec4_t rectPos = vec4_t(siX, siY, siX + aidsLen, siY + 55);
		vec4_t rectPos2 = vec4_t(20, 20, 30, 30);
		vec4_t linePos = vec4_t(rectPos.x + 5, rectPos.y + 10, rectPos.z - 5, rectPos.y + 10.5);
		string test = to_string(min) + "m " + to_string(sec) + "s";
		if (hour >= 1) test = to_string(hour) + "h " + test ;
		string add = "";
		string strings = "Games Played: \n" + add + "Play Time: \n" + add + "Kills: \n";
		string game = to_string(games);
		string kill = to_string(kills);
		string gamesPlayed = string(GRAY) + "Games Played: " + string(RESET) + game;
		string playersKilled = string(GRAY) + "Kills: " + string(RESET) + kill;
		string PlayTime = string(GRAY)+ "Play Time: " + string(RESET) + test;
		int kde = 0;
		if (kills > 0) kde = (double)kills / (double)dead;
		 string kd = to_string(kde);
		 string kdStr = "KD: ";
		 string kdStr2 = string(GRAY) + "KD: " + string(RESET) + kd;

		switch (mode.getSelectedValue()) {
		case 0: // Packet
			DrawUtils::drawCenteredString(vec2_t(rectPos.x + 60, rectPos.y + 6), &title2, 1.f, MC_Color(255, 255, 255), true);
			DrawUtils::drawCenteredString(vec2_t(rectPos.x + 60, rectPos.y + 20), &PlayTime, 1.f, MC_Color(255, 255, 255), true);
			DrawUtils::drawCenteredString(vec2_t(rectPos.x + 60, rectPos.y + 30), &gamesPlayed, 1.f, MC_Color(255, 255, 255), true);
			DrawUtils::drawCenteredString(vec2_t(rectPos.x + 60, rectPos.y + 40), &playersKilled, 1.f, MC_Color(255, 255, 255), true);
			DrawUtils::drawCenteredString(vec2_t(rectPos.x + 60, rectPos.y + 50), &kdStr2, 1.f, MC_Color(255, 255, 255), true);
			DrawUtils::fillRoundRectangle(rectPos, MC_Color(0, 0, 0, opacity), false);
			if (outline) DrawUtils::drawRoundRectangle(rectPos, interfaceColor, false);
			DrawUtils::fillRectangleA(linePos, MC_Color(255, 255, 255, 255));
			break;
		case 1: // Tenacity
			DrawUtils::drawText(vec2_t(rectPos.x + 4, rectPos.y + 44), &kdStr, MC_Color(255, 255, 255), 1, 1, true);
			DrawUtils::drawCenteredString(vec2_t(rectPos.x + 60, rectPos.y + 5), &title, 1.f, MC_Color(255, 255, 255), true);
			DrawUtils::drawText(vec2_t(rectPos.x + 4, rectPos.y + 15), &strings, MC_Color(255, 255, 255), 1, 1, true);
			DrawUtils::drawRightAlignedString(&game, vec4_t(rectPos.x, rectPos.y + 13, rectPos.z, rectPos.w), MC_Color(255, 255, 255), true);
			DrawUtils::drawRightAlignedString(&kill, vec4_t(rectPos.x, rectPos.y + 33, rectPos.z, rectPos.w), MC_Color(255, 255, 255), true);
			DrawUtils::drawRightAlignedString(&test, vec4_t(rectPos.x, rectPos.y + 23, rectPos.z, rectPos.w), MC_Color(255, 255, 255), true);
			DrawUtils::drawRightAlignedString(&kd, vec4_t(rectPos.x, rectPos.y + 43, rectPos.z, rectPos.w), MC_Color(255, 255, 255), true);
			DrawUtils::fillRoundRectangle(rectPos, MC_Color(0, 0, 0, opacity), true);
			if (outline) DrawUtils::drawRoundRectangle(rectPos, !clickGUI->hasOpenedGUI ? interfaceColor : MC_Color(255, 255, 255), true);
			DrawUtils::fillRectangleA(linePos, MC_Color(255, 255, 255, 255));
			break;
		}
	}
}
