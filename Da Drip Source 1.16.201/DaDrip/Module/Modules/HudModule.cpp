#include "HudModule.h"
#include "../../DrawUtils.h"
#include "../../Scripting/ScriptManager.h"
#include "../../../Utils/Logger.h"

HudModule::HudModule() : IModule(0x0, Category::HUD, "TabGui") {
	registerFloatSetting("HUD Scale", &this->scale, this->scale, 0.5f, 1.5f);
}

HudModule::~HudModule() {
}

const char* HudModule::getModuleName() {
	return ("TabGui");
}
static std::vector<C_Entity*> playerList;



int Odelay = 0;


void HudModule::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	
	vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
	vec2_t windowSizeReal = g_Data.getClientInstance()->getGuiData()->windowSizeReal;
	float f = 10.f * this->scale;
	std::string tempStr("Movement");
	float len = DrawUtils::getTextWidth(&tempStr, scale) + 7.f;

	vec2_t mousePosition = *g_Data.getClientInstance()->getMousePos();
	mousePosition = mousePosition.div(windowSizeReal);
	mousePosition = mousePosition.mul(windowSize);
	static auto hudEditorMod = moduleMgr->getModule<HudEditor>();

	if (hudEditorMod->isEnabled()) {
		if (g_Data.getClientInstance()->getMouseGrabbed())
			g_Data.getClientInstance()->releaseMouse();
	}

	
	
}






void HudModule::onTick(C_GameMode* gm) {
}

void HudModule::onDisable() {
}
