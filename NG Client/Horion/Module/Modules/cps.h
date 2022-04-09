#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class cps : public IModule {
public:
	float scale = 1.f;
	float cpsX = 0.f;
	float cpsY = 290.5f;

	cps() : IModule(0x0, Category::GUI, "Clicks Per Second") {
		registerFloatSetting("cpsX", &cpsX, cpsX, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.x);
		registerFloatSetting("cpsY", &cpsY, cpsY, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.y);
		registerFloatSetting("Scale", &scale, scale, 0.5f, 1.5f);
	};
	~cps(){};

	void onPostRender(C_MinecraftUIRenderContext* renderCtx) {
		// CPS
		float f = 10.f * this->scale;
		std::string tempStr("Movement");
		float len = DrawUtils::getTextWidth(&tempStr, scale) + 7.f;

		float yVal = cpsY;
		float xVal = cpsX;

		if (!(g_Data.getLocalPlayer() == nullptr)) {
			std::string cpsText = "CPS: " + std::string(WHITE) + std::to_string(g_Data.getLeftCPS()) + " - " + std::to_string(g_Data.getRightCPS());
			vec4 rectPos = vec4(0.5f, yVal + 20.5f * scale, len - 1.5f, yVal + 30.5f * scale);
			vec2 textPos = vec2(xVal, yVal);
			DrawUtils::drawText(vec2{textPos}, &cpsText, MC_Color(184, 0, 255), scale);
		}
		yVal += f;
	}

	virtual const char* getModuleName() override {
		return "CPS";
	}
};
