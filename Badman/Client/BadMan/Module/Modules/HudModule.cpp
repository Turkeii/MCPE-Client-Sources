#include "HudModule.h"
#include "../../DrawUtils.h"
#include "../../Scripting/ScriptManager.h"
#include "../../../Utils/Logger.h"

float HudModule::opacity{1};

HudModule::HudModule() : IModule(0x0, Category::GUI, "Edit HUD elements") {
	registerBoolSetting("TabGui", &this->tabgui, this->tabgui);
	//registerBoolSetting("ClickToggle", &this->clickToggle, this->clickToggle);
	//registerBoolSetting("Always show", &this->alwaysShow, this->alwaysShow);
	registerIntSetting("Y height", &this->Yheight, this->Yheight, 0, 180);
	registerIntSetting("X height", &this->Xheight, this->Xheight, 0, 5);
	registerFloatSetting("HUD Scale", &this->scale, this->scale, 0.5f, 1.5f);
	registerFloatSetting("TabGUI Opacity", &opacity, opacity, 0.f, 1.f);

}

HudModule::~HudModule() {
}

const char* HudModule::getModuleName() {
	return ("HUD");
}

int Odelay = 0;

void HudModule::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
	vec2_t windowSizeReal = g_Data.getClientInstance()->getGuiData()->windowSizeReal;
	float f = 10.f * this->scale;
	std::string tempStr("Movement");
	float len = DrawUtils::getTextWidth(&tempStr, scale) + 7.f;
	float startY = tabgui ? 6 * f : 0.f;
	if (tabgui && scriptMgr.getNumEnabledScripts() > 0)
		startY += f;
}

void HudModule::onTick(C_GameMode* gm) {
}

void HudModule::onDisable() {
}
