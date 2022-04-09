#pragma once
#include "Module.h"
#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class fps : public IModule {
public:
	float scale = 1.f;
	float fpsX = 0.f;
	float fpsY = 280.5f;

	fps() : IModule(0x0, Category::GUI, "Frames Per Second") {
		registerFloatSetting("fpsX", &fpsX, fpsX, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.x);
		registerFloatSetting("fpsY", &fpsY, fpsY, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.y);
		registerFloatSetting("Scale", &scale, scale, 0.5f, 1.5f);
	};
	~fps(){};

	void onPostRender(C_MinecraftUIRenderContext* renderCtx) {
		// fps
		float f = 10.f * this->scale;
		std::string tempStr("Movement");
		float len = DrawUtils::getTextWidth(&tempStr, scale) + 7.f;

		float yVal = fpsY;
		float xVal = fpsX;

		if (!(g_Data.getLocalPlayer() == nullptr)) {
			std::string fpsText = "FPS: " + std::string(WHITE) + std::to_string(g_Data.getFPS());
			vec4 rectPos = vec4(0.5f, yVal + 20.5f * scale, len - 1.5f, yVal + 30.5f * scale);
			vec2 textPos = vec2(xVal, yVal);
			DrawUtils::drawText(vec2{textPos}, &fpsText, MC_Color(184, 0, 255), scale);
		}
		yVal += f;
	}

	virtual const char* getModuleName() override {
		return "Fps";
	}
};