#include "ESP.h"

#include "../../../Utils/Target.h"

ESP::ESP() : IModule('O', Category::VISUAL, "Makes it easier to find entities around you") {
	this->registerBoolSetting("rainbow", &this->doRainbow, this->doRainbow);
	this->registerBoolSetting("MobEsp", &this->isMobEsp, this->isMobEsp);
	this->registerBoolSetting("ItemEsp", &this->itemEsp, this->itemEsp);
	this->registerBoolSetting("2d", &this->is2d, this->is2d);
	this->registerFloatSetting("Red", &this->customR, this->customR, 0.f, 1.f);
	this->registerFloatSetting("Green", &this->customG, this->customG, 0.f, 1.f);
	this->registerFloatSetting("Blue", &this->customB, this->customB, 0.f, 1.f);
}

ESP::~ESP() {
}

const char* ESP::getModuleName() {
	return ("ESP");
}
float customColors[4];
float customRF;
float customGF;
float customBF;

static float rcolors[4];


void doRenderStuff(C_Entity* ent, bool isRegularEntitie) {
	static auto espMod = moduleMgr->getModule<ESP>();
	
	C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
	if (ent != localPlayer) {

		if (espMod->itemEsp) {
			if (ent->getEntityTypeId() == 64) {
				//DrawUtils::drawNameTags(ent, 1.f, false, false);
				DrawUtils::setColor(1.f, 0.f, 0.f, 1.f);
				DrawUtils::draw2D(ent, (float)fmax(0.2f, 1 / (float)fmax(1, (*localPlayer->getPos()).dist(*ent->getPos()))));
			}
		}
		if (ent->timeSinceDeath > 0)
			return;
		if (FriendList::findPlayer(ent->getNameTag()->getText()) && ent->getNameTag()->getTextLength() >= 1 && ent->getEntityTypeId() == 63 && !moduleMgr->getModule<NoFriends>()->isEnabled()) {
			DrawUtils::setColor(0.f, 1.f, 0.f, (float)fmax(0.1f, (float)fmin(1.f, 15 / (ent->damageTime + 1))));
		} else if (Target::isValidTarget(ent)) {
			if (espMod->doRainbow)
				DrawUtils::setColor(rcolors[0], rcolors[1], rcolors[2], (float)fmax(0.1f, (float)fmin(1.f, 15 / (ent->damageTime + 1))));
			else
				DrawUtils::setColor(((float)espMod->customR / (float)1.f), ((float)espMod->customG / (float)1.f), ((float)espMod->customB / (float)1.f), (float)fmax(0.1f, (float)fmin(1.f, 15 / (ent->damageTime + 1))));
		} else if (espMod->isMobEsp) {
			if (ent->getNameTag()->getTextLength() <= 1 && ent->getEntityTypeId() == 63)
				return;

			if (ent->isInvisible())
				return;

			if (!g_Data.getLocalPlayer()->canAttack(ent, false))
				return;
			DrawUtils::setColor(0.2f, 0.2f, 0.9f, (float)fmax(0.1f, (float)fmin(1.f, 15 / (ent->damageTime + 1))));
		} else
			return;
		if (espMod->is2d)
			DrawUtils::draw2D(ent, (float)fmax(0.4f, 1 / (float)fmax(1, (*localPlayer->getPos()).dist(*ent->getPos()) * 3.f)));
		else 
			DrawUtils::drawEntityBox(ent, (float)fmax(0.2f, 1 / (float)fmax(1, (*localPlayer->getPos()).dist(*ent->getPos()))));
	}
	
}

void ESP::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();

	if (localPlayer != nullptr && GameData::canUseMoveKeys()) {
		// Rainbow colors
		{
			if (rcolors[3] < 1) {
				rcolors[0] = 0.2f;
				rcolors[1] = 0.2f;
				rcolors[2] = 1.f;
				rcolors[3] = 1;
			}

			Utils::ApplyRainbow(rcolors, 0.0015f);
		} //0.0015f
		g_Data.forEachEntity(doRenderStuff);
	}
}
