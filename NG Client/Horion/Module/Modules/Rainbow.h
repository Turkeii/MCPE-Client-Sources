#pragma once
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"

class Rainbow : public IModule {
public:
	float opacity = 0.2f;

 Rainbow() : IModule(0x0, Category::VISUAL, "Rainbow module from Ghost Client") {
	registerFloatSetting("Opacity", &opacity, 0.2f, 0.f, 1);
    }
 ~Rainbow(){};
	void onPostRender(C_MinecraftUIRenderContext* renderCtx) {
		static float rcolors[4];
		if (rcolors[3] < 1) {
			rcolors[0] = 0.2f;
			rcolors[1] = 0.2f;
			rcolors[2] = 1.f;
			rcolors[3] = 1;
		}

		Utils::ApplyRainbow(rcolors, 0.0003f);
		auto wid = g_Data.getClientInstance()->getGuiData()->windowSize;
		std::string text = "";
		vec2 textPos = vec2(wid.x / 2.f - DrawUtils::getTextWidth(&text, 180.f) / 2.f, wid.y / 9.5f);
		vec4 rectPos = vec4(textPos.x - 400.f, textPos.y - 400.f, textPos.x + DrawUtils::getTextWidth(&text, 8.f) + 400.f, textPos.y + 400.f);
		DrawUtils::fillRectangle(rectPos, MC_Color(rcolors[0], rcolors[1], rcolors[2]), opacity);
	}
	const char* Rainbow::getModuleName() {
		return "LSD";
	}
};