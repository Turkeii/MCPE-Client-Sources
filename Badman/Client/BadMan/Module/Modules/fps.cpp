#include "fps.h"
#include "../../DrawUtils.h"
#include "../../Scripting/ScriptManager.h"
#include "../../../Utils/Logger.h"


fps::fps() : IModule(0x0, Category::GUI, "Frames Per Second") {

registerFloatSetting("fpsX", &this->fpsX, this->fpsX, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.x);
registerFloatSetting("fpsY", &this->fpsY, this->fpsY, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.y);
registerFloatSetting("Scale", &this->scale, this->scale, 0.5f, 1.5f);
}

fps::~fps() {
}

const char* fps::getModuleName() {
	return ("FPS");
}

void fps::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	 
	 // fps
	float f = 10.f * this->scale;
	std::string tempStr("Movement");
	float len = DrawUtils::getTextWidth(&tempStr, scale) + 7.f;

	float yVal = fpsY;
	float xVal = fpsX;
	 
	if (!(g_Data.getLocalPlayer() == nullptr)) {
	std::string fpsText = "FPS: " + std::to_string(g_Data.getFPS());
	vec4_t rectPos = vec4_t(0.5f, yVal + 20.5f * scale, len - 1.5f, yVal + 30.5f * scale);
	vec2_t textPos = vec2_t(xVal, yVal);
	DrawUtils::drawText(textPos, &fpsText, MC_Color(AltTheme::rFloat, AltTheme::gFloat, AltTheme::bFloat), scale);
	yVal += f;
	}
}