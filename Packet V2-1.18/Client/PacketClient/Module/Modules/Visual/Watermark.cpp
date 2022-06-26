#include "Watermark.h"
#include "../pch.h"
#include <chrono>

using namespace std;
Watermark::Watermark() : IModule(0, Category::VISUAL, "Displays the watermark") {
	registerEnumSetting("Theme", &mode, 0);
	mode.addEntry("Simple", 0);
	mode.addEntry("New", 1);
	mode.addEntry("Weird", 2);
	mode.addEntry("Skeet", 3);
	mode.addEntry("FirstLetter", 4);
	registerBoolSetting("Gradient", &gradient, &gradient);
	registerIntSetting("Opacity", &opacity, opacity, 0, 255);
	registerFloatSetting("Scale", &scale, scale, 0.5f, 2);
	shouldHide = true;
}

const char* Watermark::getModuleName() {
	return ("Watermark");
}

void Watermark::onEnable() {
}

void Watermark::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr || moduleMgr->getModule<DebugMenu>()->isEnabled()) return;

	auto interfaceMod = moduleMgr->getModule<Interface>();
	auto clickGUI = moduleMgr->getModule<ClickGUIMod>();

	//DrawUtils::drawImage("textures/ui/heart_new.png", vec2_t(positionX + 5, positionY + 50), vec2_t(30, 30), vec2_t(0, 0), vec2_t(1, 1));

	if (g_Data.canUseMoveKeys() && !clickGUI->hasOpenedGUI) {
		string name = player->getNameTag()->getText(); name = Utils::sanitize(name); name = name.substr(0, name.find('\n')); string clientName = interfaceMod->getClientName(); string fpsText = to_string(g_Data.getFPS()) + " fps"; string skeetLen = "Packetsense | " + name + " | " + fpsText; string t = "Packet         | " + name + " | " + fpsText; string sense = "sense"; string newText = clientName + GRAY + "| " + RESET + WHITE + name; string idk = "Packet "; string idk2 = string(GRAY) + clientName; string len = idk + idk2; // why u lookin over here
		float textHeight = 12.f * scale;
		float textPadding = 1.f * scale;

		switch (mode.getSelectedValue()) {
		case 0: aidsLen = DrawUtils::getTextWidth(&clientName, scale) + 2.f; height = textHeight + (textPadding * 2); break;
		case 1: aidsLen = DrawUtils::getTextWidth(&newText, scale) + 6.f; height = textHeight + (textPadding * 2); break;
		case 2: aidsLen = DrawUtils::getTextWidth(&len, scale) + 12.f; height = textHeight + (textPadding * 2); break;
		case 3: aidsLen = DrawUtils::getTextWidth(&skeetLen, scale) + (textPadding * 13); height = textHeight + (textPadding * 2); break;
		}

		float flaot = DrawUtils::getTextWidth(&idk, scale) + 8.F;
		float te = DrawUtils::getTextWidth(&sense, scale) + 8.f;
		vec4_t skeetRect = vec4_t(positionX, positionY, positionX + aidsLen, positionY + textHeight + (textPadding * 2));
		vec4_t simpleRect = vec4_t(positionX, positionY, positionX + aidsLen, positionY + textHeight + (textPadding * 2));
		vec4_t newRect = vec4_t(positionX, positionY, positionX + aidsLen, positionY + textHeight + (textPadding * 2));
		vec4_t idkRect = vec4_t(positionX, positionY, positionX + aidsLen, positionY + textHeight + (textPadding * 2));
		vec4_t newRectTop = vec4_t(newRect.x, newRect.y - 2, newRect.z, newRect.y);

		//DrawUtils::drawRounderRectangle(vec4_t(positionX, positionY, positionX + 15, positionY + 2.F), interfaceColor);
		//DrawUtils::drawCircle(vec4_t(positionX + 10, positionY, positionX + 14, positionY + 2.F), MC_Color(10, 10, 10, 255));

		auto interfaceColor = ColorUtil::interfaceColor(1);
		switch (mode.getSelectedValue()) {
		case 0:
			if (gradient) DrawUtils::drawGradientText(vec2_t(simpleRect.x, simpleRect.y), &clientName, scale, 1, true);
			else DrawUtils::drawText(vec2_t(simpleRect.x, simpleRect.y), &clientName, interfaceColor, scale, 1, true);
			break;
		case 1: // New
			DrawUtils::fillRoundRectangle(newRect, MC_Color(0, 0, 0, opacity), false);
			DrawUtils::fillRectangleA(newRectTop, interfaceColor);
			DrawUtils::drawText(vec2_t(newRect.x + (textPadding * 3), newRect.y + (textPadding * 3)), &newText, interfaceColor, scale, 1, true);
			break;
		case 2: // Weird
			DrawUtils::drawGradientText(vec2_t(simpleRect.x, simpleRect.y), &idk, scale, 1, true);
			DrawUtils::drawText(vec2_t(simpleRect.x + flaot + (textPadding * 2), simpleRect.y - 5), &idk2, MC_Color(), 1, 1, true);
			break;
		case 3: // Skeet
			DrawUtils::fillRectangle(skeetRect, MC_Color(27, 27, 27), 1);
			DrawUtils::drawRectangle(skeetRect, MC_Color(57, 57, 57), 1, 2);
			DrawUtils::drawText(vec2_t(skeetRect.x + (textPadding * 2) + 4.f, skeetRect.y + (textPadding * 2)), &t, MC_Color(255, 255, 255), scale, 1, true);
			DrawUtils::drawGradientText(vec2_t(skeetRect.x + te + (textPadding * 2) + 4.f, skeetRect.y + (textPadding * 2)), &sense, scale, 1, true);
			break;
		case 4: // FirstLetter
			break;
		}
	}
}
