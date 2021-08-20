#include "DvdLogo.h"
#include "../../DrawUtils.h"

DvdLogo::DvdLogo() : IModule(0x0, Category::VISUAL, "WTF?") {
}

DvdLogo::~DvdLogo() {
}

const char* DvdLogo::getModuleName() {
	return ("DVDLogo");
}

void DvdLogo::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	std::string screen("BadMan");
	std::string screen2("Client");

	if (g_Data.getLocalPlayer() != nullptr && GameData::canUseMoveKeys()) {
		float Height = g_Data.getClientInstance()->getGuiData()->heightGame;
		float Width = g_Data.getClientInstance()->getGuiData()->widthGame;

		//up and down shit
		if (positiveY) {
			pos.y += 1.f;
			if (pos.y + 10 * scale * 2 > Height) {
				colorR = rand() % 127 + 127;
				colorG = rand() % 127 + 127;
				colorB = rand() % 127 + 127;
				positiveY = false;
			}
		}
		//these are faster cause it breaks the cylce of hitting the cornors and not moving
		if (!positiveY) {
			pos.y -= 1.f;
			if (pos.y < 0) {
				colorR = rand() % 127 + 127;
				colorG = rand() % 127 + 127;
				colorB = rand() % 127 + 127;
				positiveY = true;
			}
		}

		//left and right shit
		if (positiveX) {
			pos.x += 0.8f;
			if (pos.x + DrawUtils::getTextWidth(&screen, scale) / 2 > Width) {
				colorR = rand() % 127 + 127;
				colorG = rand() % 127 + 127;
				colorB = rand() % 127 + 127;
				positiveX = false;
			}
		}

		if (!positiveX) {
			pos.x -= 0.8f;
			if (pos.x - DrawUtils::getTextWidth(&screen, scale) / 2 < 0) {
				colorR = rand() % 127 + 127;
				colorG = rand() % 127 + 127;
				colorB = rand() % 127 + 127;
				positiveX = true;
			}
		}

		DrawUtils::drawText(vec2_t(pos.x - DrawUtils::getTextWidth(&screen, scale) / 2, pos.y), &screen, MC_Color(colorR, colorG, colorB), scale);                   //BadMan
		DrawUtils::drawText(vec2_t(pos.x - DrawUtils::getTextWidth(&screen2, scale) / 2, pos.y + 10.f * scale), &screen2, MC_Color(colorR, colorG, colorB), scale);  //Client
	}
}

void DvdLogo::onEnable() {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	pos.x = g_Data.getClientInstance()->getGuiData()->widthGame - g_Data.getClientInstance()->getGuiData()->widthGame / 2 - scale / 2;
	pos.y = g_Data.getClientInstance()->getGuiData()->heightGame - g_Data.getClientInstance()->getGuiData()->heightGame / 2 - scale / 2;
	positiveX = true;
	positiveY = true;
	colorR, colorG, colorB = 255;
}