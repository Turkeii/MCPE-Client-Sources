#include "NameTags.h"

#include "../../../Utils/Target.h"
#include "../ModuleManager.h"

NameTags::NameTags() : IModule(0, Category::VISUAL, "Shows betterar aways") {
	this->registerBoolSetting("Underline", &this->underline, this->underline);
	this->registerBoolSetting("X Armor", &this->displayArmor, this->displayArmor);
	this->registerFloatSetting("Opacity", &this->opacity, this->opacity, 0.f, 1.f);
}

NameTags::~NameTags() {
}

const char* NameTags::getModuleName() {
	return ("NameTags");
}

void drawNameTags(C_Entity* ent, bool) {
	if (!(g_Data.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
		if (g_Data.isInGame()) {
			C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
			static auto nameTagsMod = moduleMgr->getModule<NameTags>();

			if (ent != localPlayer) {
				if (ent->timeSinceDeath > 0)
					return;
				if (ent->getNameTag()->getTextLength() < 1)
					return;
				if (Target::isValidTarget(ent) && nameTagsMod != nullptr) {
					nameTagsMod->nameTags.insert(Utils::sanitize(ent->getNameTag()->getText()));
					float dist = ent->getPos()->dist(*g_Data.getLocalPlayer()->getPos());
					DrawUtils::drawNameTags(ent, fmax(0.9f, 5.f / dist));
					DrawUtils::flush();
				}
			}
		}
	}
}

void NameTags::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	if (!(g_Data.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
		if (g_Data.isInGame()) {
			C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
			if (localPlayer == nullptr) return;

			if (ingameNametagSetting)
				if (!gotPrevSetting) {
					lastSetting = *ingameNametagSetting;
					gotPrevSetting = true;
					*ingameNametagSetting = false;
				} else
					*ingameNametagSetting = false;  //disable other ppl's nametags

			g_Data.forEachEntity(drawNameTags);
		}
	}
}

void NameTags::onDisable() {
	if (ingameNametagSetting && gotPrevSetting) {
		*ingameNametagSetting = lastSetting;
		gotPrevSetting = true;
		*ingameNametagSetting = true;
	}
}