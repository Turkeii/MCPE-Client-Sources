#include "../../../Utils/Logger.h"
#include "../../DrawUtils.h"
#include "../../Scripting/ScriptManager.h"
#include "Welcome.h"

Welcome::Welcome() : IModule(0x0, Category::HUD, "Welcome") {
	registerFloatSetting("Scale", &this->scale, this->scale, 0.5f, 1.5f);
}

Welcome::~Welcome() {
}

const char* Welcome::getModuleName() {
	return ("Welcome");
}

void Welcome::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
	constexpr float nameTextSize = 1.5f;
	static const float textHeight = (nameTextSize * 0.7f /* We don't quite want the version string in its own line, just a bit below the name */) * DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight();
	constexpr float borderPadding = 1;
	constexpr float margin = 5;
	static std::string playerName = g_Data.getLocalPlayer()->getNameTag()->getText();

	static std::string name = "welcome " + playerName;

	float nameLength = DrawUtils::getTextWidth(&name, nameTextSize);
	float fullTextLength = nameLength;
	float x = windowSize.x - windowSize.x / 1.85;
	float y = windowSize.y - windowSize.y;
	vec4_t rect = vec4_t(
		windowSize.x - margin - fullTextLength - borderPadding * 415,
		windowSize.y - margin - textHeight,
		windowSize.x - margin + borderPadding,
		windowSize.y - margin);

	DrawUtils::drawText(vec2_t(x, y), &name, MC_Color(255, 255, 255), scale * 1.05f);
}