#include "cps.h"
#include "../../DrawUtils.h"
#include "../../Scripting/ScriptManager.h"
#include "../../../Utils/Logger.h"


cps::cps() : IModule(0x0, Category::GUI, "Clicks Per Second") {

registerFloatSetting("cpsX", &this->cpsX, this->cpsX, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.x);
registerFloatSetting("cpsY", &this->cpsY, this->cpsY, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.y);
registerFloatSetting("Scale", &this->scale, this->scale, 0.5f, 1.5f);
}

cps::~cps() {
}

const char* cps::getModuleName() {
	return ("CPS");
}

void cps::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	 
	 // CPS
	float f = 10.f * this->scale;
	std::string tempStr("Movement");
	float len = DrawUtils::getTextWidth(&tempStr, scale) + 7.f;

	float yVal = cpsY;
	float xVal = cpsX;
	 
	if (!(g_Data.getLocalPlayer() == nullptr)) {
	std::string cpsText = "CPS: " + std::to_string(g_Data.getLeftCPS()) + " - " + std::to_string(g_Data.getRightCPS());
	vec4_t rectPos = vec4_t(0.5f, yVal + 20.5f * scale, len - 1.5f, yVal + 30.5f * scale);
	vec2_t textPos = vec2_t(xVal, yVal);
	DrawUtils::drawText(textPos, &cpsText, MC_Color(AltTheme::rFloat, AltTheme::gFloat, AltTheme::bFloat), scale);
	yVal += f;
	}
}