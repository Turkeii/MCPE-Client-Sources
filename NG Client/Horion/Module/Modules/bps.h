#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class bps : public IModule {
public:
	float scale = 1.f;
	float bpsX = 0.f;
	float bpsY = 270.5f;

	bps() : IModule(0x0, Category::GUI, "Clicks Per Second") {
		registerFloatSetting("bpsX", &bpsX, bpsX, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.x);
		registerFloatSetting("bpsY", &bpsY, bpsY, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.y);
		registerFloatSetting("Scale", &scale, scale, 0.5f, 1.5f);
	};
	~bps(){};

	void onPostRender(C_MinecraftUIRenderContext* renderCtx) {
		// bps
		float f = 10.f * this->scale;
		std::string tempStr("Movement");
		float len = DrawUtils::getTextWidth(&tempStr, scale) + 7.f;

		float yVal = bpsY;
		float xVal = bpsX;

		if (!(g_Data.getLocalPlayer() == nullptr)) {
			auto player = g_Data.getLocalPlayer();
			std::string bpsText = "BPS: " + std::string(WHITE) + std::to_string((int)player->getBlocksPerSecond()) + std::string(".") + std::to_string((int)(player->getBlocksPerSecond() * 10) - ((int)player->getBlocksPerSecond() * 10));
			vec4 rectPos = vec4(0.5f, yVal + 20.5f * scale, len - 1.5f, yVal + 30.5f * scale);
			vec2 textPos = vec2(xVal, yVal);
			DrawUtils::drawText(vec2{textPos}, &bpsText, MC_Color(184, 0, 255), scale);
			}
			yVal += f;
		}

	virtual const char* getModuleName() override {
		return "Bps";
	}
};