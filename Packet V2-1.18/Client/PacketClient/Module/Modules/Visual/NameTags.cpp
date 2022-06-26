#include "NameTags.h"
#include "../pch.h"

NameTags::NameTags() : IModule(0, Category::VISUAL, "Displays peoples names through walls") {
	registerBoolSetting("Underline", &underline, underline);
	registerBoolSetting("Armor", &displayArmor, displayArmor);
	registerIntSetting("Opacity", &opacity, opacity, 0, 255);
}

const char* NameTags::getModuleName() {
	return ("NameTags");
}

void drawNameTags(C_Entity* ent, bool) {
	static auto nametags = moduleMgr->getModule<NameTags>();

	if (ent->timeSinceDeath > 0)
		return;
	if (ent->getNameTag()->getTextLength() < 1)
		return;
	if (TargetUtil::isValidTarget(ent) && nametags->isEnabled()) {
		nametags->nameTags.insert(Utils::sanitize(ent->getNameTag()->getText()));
		float dist = ent->getPos()->dist(*g_Data.getLocalPlayer()->getPos());
		DrawUtils::drawNameTags(ent, fmax(0.6f, 3.f / dist));
		DrawUtils::flush();
	}
}

void NameTags::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	if (!g_Data.canUseMoveKeys()) return;

	// retarded
	/*if (ingameNametagSetting)
		if (!gotPrevSetting) {
			lastSetting = *ingameNametagSetting;
			gotPrevSetting = true;
			*ingameNametagSetting = false;
		} else
			*ingameNametagSetting = false;  //disable other ppl's nametags*/

	g_Data.forEachEntity(drawNameTags);
}

void NameTags::onDisable() {
	/*if (ingameNametagSetting && gotPrevSetting) {
		*ingameNametagSetting = lastSetting;
		gotPrevSetting = false;
	}*/
}