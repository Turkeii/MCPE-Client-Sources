#include "HudModule.h"

#include "../../DrawUtils.h"
#include "../../Scripting/ScriptManager.h"

HudModule::HudModule() : IModule(0, Category::VISUAL, "Displays ArrayList") {
	//registerBoolSetting("Background", &this->arraylistBackground, this->arraylistBackground);
	registerBoolSetting("Keybinds", &this->keybinds, this->keybinds);
	registerBoolSetting("Outline", &this->arraylistOutline, this->arraylistOutline);
	this->registerFloatSetting("Opacity", &this->bgOp, this->bgOp, 0.f, 1.f);
}

HudModule::~HudModule() {
}

const char* HudModule::getModuleName() {
	return ("ArrayList");
}

void HudModule::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
}