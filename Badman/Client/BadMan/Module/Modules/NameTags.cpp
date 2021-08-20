#include "NameTags.h"

#include "../../../Utils/Target.h"
#include "../ModuleManager.h"

float NameTags::opacity{1};

NameTags::NameTags() : IModule(0x0, Category::VISUAL, "Shows better nametags above players that can be seen from a lot more far aways") {
	this->registerBoolSetting("Display Armor", &this->displayArmor, this->displayArmor);
	this->registerBoolSetting("Display Health", &this->displayhealth, this->displayhealth);
	registerFloatSetting("NameTags Opacity", &opacity, opacity, 0.f, 1.f);
	this->registerIntSetting("Red", &this->customR, this->customR, 0, 255);
	this->registerIntSetting("Green", &this->customG, this->customG, 0, 255);
	this->registerIntSetting("Blue", &this->customB, this->customB, 0, 255);
}

NameTags::~NameTags() {
}

const char* NameTags::getModuleName() {
	return ("NameTags");

}

void drawNameTags(C_Entity* ent, bool isRegularEntitie) {
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
			DrawUtils::drawNameTags(ent, fmax(1.f, 3.f / dist + 0.4f));
			DrawUtils::flush();
			} else if (FriendList::findPlayer(ent->getNameTag()->getText()) && ent->getNameTag()->getTextLength() >= 1 && ent->getEntityTypeId() == 63) {
			nameTagsMod->nameTags.insert(Utils::sanitize(ent->getNameTag()->getText()));
			float dist = ent->getPos()->dist(g_Data.getClientInstance()->levelRenderer->origin);
			DrawUtils::drawNameTags(ent, 1.f, true, true);
			DrawUtils::flush();
			
			}	
	}
}

void NameTags::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();

	if (nameTags.size() > 100)
		nameTags.clear();

	if (localPlayer != nullptr && GameData::canUseMoveKeys()) {
		std::vector<C_Entity*> temp;
		vec3_t origin = g_Data.getClientInstance()->levelRenderer->origin;
		for (int i = 0; i < g_Data.getEntityList()->getListSize(); i++)
			temp.push_back(g_Data.getEntityList()->get(i));
		std::sort(temp.begin(), temp.end(), [origin](const C_Entity* lhs, const C_Entity* rhs) {
			return origin.dist(*lhs->getPos()) > origin.dist(*rhs->getPos());
		});
		for (C_Entity* ent : temp)
			drawNameTags(ent, true);
	} else {
		nameTags.clear();
	}
}
