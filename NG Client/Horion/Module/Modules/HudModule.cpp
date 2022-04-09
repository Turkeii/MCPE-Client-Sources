#include "HudModule.h"
#include "../../DrawUtils.h"
#include "../ModuleManager.h"

HudModule::HudModule() : IModule(0x0, Category::GUI, "Displays Hud") {
	registerBoolSetting("Buttons", &Buttons, Buttons);
	registerBoolSetting("RGB", &rgb, rgb);
	registerBoolSetting("MSG", &Msg, Msg);
	registerBoolSetting("Show Second Names", &displaySecondHalf, displaySecondHalf);
	registerBoolSetting("Always show", &alwaysShow, alwaysShow);
	registerBoolSetting("Watermark", &watermark, watermark);
	registerFloatSetting("Opacity", &opacity, opacity, 0.0f, 1.f);
	registerFloatSetting("Scale", &scale, scale, 0.5f, 1.5f);
	registerBoolSetting("Notifications", &notifications, notifications);
}

HudModule::~HudModule() {
}

static float currColor[4];

const char* HudModule::getModuleName() {
		return "HUD";
}

void HudModule::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	// rainbow colors
	{
		if (currColor[3] < 1) {
			currColor[0] = 1;
			currColor[1] = 0.2f;
			currColor[2] = 0.2f;
			currColor[3] = 1;
		}
		Utils::ApplyRainbow(currColor, 0.00025f);
	}

	vec2 windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
	float f = 10.f * scale;
	std::string tempStr("Movement");
	float len = DrawUtils::getTextWidth(&tempStr, scale) + 7.f;
	float startY = tabgui ? 6 * f : 0.f;
	if (tabgui)
		startY += f;

	{  // Hello thing
		static auto partner = moduleMgr->getModule<Partner>();
		if (!(g_Data.getLocalPlayer() == nullptr || !Msg || !GameData::canUseMoveKeys())) {
			if (partner->Partnered.selected == 0) {
				std::string fpsText = "sup bitch";
				if (partner->Partnered.selected == 0)
					DrawUtils::drawText(vec2(windowSize.x / 2 - 20, windowSize.y - windowSize.y + 10), &fpsText, MC_Color(0, 0, 255), scale);
			} else {
				std::string fpsText = "NG Client on Top!";
				if (!partner->Partnered.selected == 0)
					DrawUtils::drawText(vec2(windowSize.x / 2 - 20, windowSize.y - windowSize.y + 10), &fpsText, MC_Color(184, 0, 255), scale);
			}
		}
	}
}
