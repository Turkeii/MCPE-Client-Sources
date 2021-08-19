#include "ESP.h"

#include "../../../Utils/Target.h"

ESP::ESP() : IModule('O', Category::VISUAL, "Makes it easier to find entities around you") {
	this->registerBoolSetting("rainbow", &this->doRainbow, this->doRainbow);
	this->registerBoolSetting("MobEsp", &this->isMobEsp, this->isMobEsp);
	this->registerBoolSetting("ItemEsp", &this->itemEsp, this->itemEsp);
	this->registerBoolSetting("2d", &this->is2d, this->is2d);
	this->registerIntSetting("Red", &this->customR, this->customR, 0, 255);
	this->registerIntSetting("Green", &this->customG, this->customG, 0, 255);
	this->registerIntSetting("Blue", &this->customB, this->customB, 0, 255);
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
		if (ent->getEntityTypeId() == 64 && (espMod->itemEsp)) {
			//DrawUtils::drawNameTags(ent, 1.f, false, false);
			DrawUtils::setColor(1.f, 0.f, 0.f, 1.f);
			DrawUtils::drawEntityBox(ent, (float)fmax(0.2f, 1 / (float)fmax(1, (*localPlayer->getPos()).dist(*ent->getPos()))));
		}
		if (ent->timeSinceDeath > 0)
			return;

		if (ent->getEntityTypeId() == 63) {
			if (!FriendList::findPlayer(ent->getNameTag()->getText())) {
				DrawUtils::setColor(1.f, 1.f, 1.f, 1.f);
			}
			if (FriendList::findPlayer(ent->getNameTag()->getText())) {
				DrawUtils::setColor(0.f, 1.f, 1.f, 1.f);
			}
		} else {
			return;
		}

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
		}  //0.0015f
		g_Data.forEachEntity(doRenderStuff);
	}
}
