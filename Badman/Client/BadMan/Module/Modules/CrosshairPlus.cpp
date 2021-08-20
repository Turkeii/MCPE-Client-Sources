#include "CrosshairPlus.h"

CrosshairPlus::CrosshairPlus() : IModule(0, Category::VISUAL, "Delete crosshair from texturepack") {
	this->registerBoolSetting("Dynamic", &this->dynamic, this->dynamic);
	registerFloatSetting("Gap", &this->gap, this->gap, 0.25f, 15.f);
	registerFloatSetting("Width", &this->width, this->width, 0.25f, 5.f);
	registerFloatSetting("Size", &this->size, this->size, 0.25f, 15.f);
}

CrosshairPlus::~CrosshairPlus() {
}

const char* CrosshairPlus::getModuleName() {
	return "CrosshairPlus";
}
void CrosshairPlus::onEnable() {
	auto player = g_Data.getLocalPlayer();
}

void CrosshairPlus::onMove(C_MoveInputHandler* input) {
	vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
	bool pressed = moveVec2d.magnitude() > 0.10f;
	isMoving = pressed;
}

	void CrosshairPlus::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	if (g_Data.isInGame() && GameData::canUseMoveKeys()) {
		auto theme = moduleMgr->getModule<Theme>();
		C_GuiData* dat = g_Data.getClientInstance()->getGuiData();
	vec2_t windowSize = dat->windowSize;
	static float rcolors[4];
	static float currColor[4];
	static float disabledRcolors[4];
	Utils::ApplyRainbow(rcolors);  // Increase Hue of rainbow color array
	disabledRcolors[0] = std::min(1.f, rcolors[0] * 0.4f + 0.2f);
	disabledRcolors[1] = std::min(1.f, rcolors[1] * 0.4f + 0.2f);
	disabledRcolors[2] = std::min(1.f, rcolors[2] * 0.4f + 0.2f);
	disabledRcolors[3] = 1;
	currColor[3] = rcolors[3];
	Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[1], rcolors[2], currColor[0], currColor[3], currColor[2]);
	currColor[0] += 2.f;
	Utils::ColorConvertHSVtoRGB(currColor[0], currColor[2], currColor[2], currColor[0], currColor[1], currColor[2]);
	if (dynamic == true) {
	//up
		DrawUtils::fillRectangle(vec4_t(windowSize.x / 2 - width,
								windowSize.y / 2 - gap - size - (isMoving ? 2 : 0),
								windowSize.x / 2 + 1.f + width,
								windowSize.y / 2 - 1.f - gap - (isMoving ? 2 : 0)),
							 MC_Color(theme->rFloat, theme->gFloat, theme->bFloat), 0.5f);
	//down
	DrawUtils::fillRectangle(vec4_t(windowSize.x / 2 - width,
									windowSize.y / 2 + gap + 1.f + (isMoving ? 2 : 0) - 0.15f,
									windowSize.x / 2 + 1.f + width,
										windowSize.y / 2 + 1.f + gap + size + (isMoving ? 2 : 0) - 0.15f),
								 MC_Color(theme->rFloat, theme->gFloat, theme->bFloat), 0.5f);
	//left
	DrawUtils::fillRectangle(vec4_t(windowSize.x / 2 - gap - size - (isMoving ? 2 : 0) + 0.15f,
									windowSize.y / 2 - width,
									windowSize.x / 2 - gap - (isMoving ? 2 : 0) + 0.15f,
									windowSize.y / 2 + 1.f + width),
							 MC_Color(theme->rFloat, theme->gFloat, theme->bFloat), 0.5f);
	//right
	DrawUtils::fillRectangle(vec4_t(windowSize.x / 2 + 1 + gap + (isMoving ? 2 : 0),
									windowSize.y / 2 - width,
									windowSize.x / 2 + size + gap + 1 + (isMoving ? 2 : 0),
									windowSize.y / 2 + 1.f + width),
							 MC_Color(theme->rFloat, theme->gFloat, theme->bFloat), 0.5f);
		}
	else 	
		//up
		DrawUtils::fillRectangle(vec4_t(windowSize.x / 2 - width,
										windowSize.y / 2 - gap - size,
										windowSize.x / 2 + 1 + width,
										windowSize.y / 2 - gap),
								 MC_Color(theme->rFloat, theme->gFloat, theme->bFloat), 0.5f);
	//down
	DrawUtils::fillRectangle(vec4_t(windowSize.x / 2 - width,
									windowSize.y / 2 + gap + 1 - 0.15f,
									windowSize.x / 2 + 1 + width,
										windowSize.y / 2 + 1 + gap + size - 0.15f),
								 MC_Color(theme->rFloat, theme->gFloat, theme->bFloat), 0.5f);
	//left
	DrawUtils::fillRectangle(vec4_t(windowSize.x / 2 - gap - size + 0.15f,
									windowSize.y / 2 - width,
									windowSize.x / 2 - gap + 0.15f,
									windowSize.y / 2 + 1 + width),
							 MC_Color(theme->rFloat, theme->gFloat, theme->bFloat), 0.5f);
	//right
	DrawUtils::fillRectangle(vec4_t(windowSize.x / 2 + 1 + gap,
									windowSize.y / 2 - width,
									windowSize.x / 2 + size + gap + 1,
									windowSize.y / 2 + 1 + width),
							 MC_Color(theme->rFloat, theme->gFloat, theme->bFloat), 0.5f);
	}
}
void CrosshairPlus::onDisable() {
	auto player = g_Data.getLocalPlayer();
	*g_Data.getClientInstance()->minecraft->timer = 20.f;
}