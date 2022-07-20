#include "ESP.h"

#include "../../../Utils/Target.h"

ESP::ESP() : IModule('O', Category::VISUAL, "Guide item") {
	this->registerBoolSetting("MobEsp", &this->isMobEsp, this->isMobEsp);
	this->registerBoolSetting("ItemEsp", &this->itemEsp, this->itemEsp);
	this->registerBoolSetting("2d", &this->is2d, this->is2d);
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
	if (espMod->itemEsp) {
		if (ent->getEntityTypeId() == 64) { //64=DropItem
			DrawUtils::drawNameTags(ent, 1.f, false, false);
			DrawUtils::setColor(1.f, 0.f, 0.f, 1.f);
			DrawUtils::draw2D(ent, (float)fmax(0.2f, 1 / (float)fmax(1, (*localPlayer->getPos()).dist(*ent->getPos()))));
		}
	}
	if (ent == localPlayer)
		return;
	if (ent->timeSinceDeath > 0)
		return;
	static auto noFriendsModule = moduleMgr->getModule<NoFriends>();
	if (!noFriendsModule->isEnabled() && FriendList::findPlayer(ent->getNameTag()->getText())) {
		DrawUtils::setColor(0.1f, 0.9f, 0.1f, (float)fmax(0.1f, (float)fmin(1.f, 15 / (ent->damageTime + 1))));
	} else if (Target::isValidTarget(ent)) {
		if (!(ent->damageTime > 1)) {
			DrawUtils::setColor(0.f, 1.f, 0.f, (float)fmax(0.1f, (float)fmin(1.f, 15 / (ent->damageTime + 1))));
		} else {
			DrawUtils::setColor(1.f, 0.f, 0.f, (float)fmax(0.1f, (float)fmin(1.f, 15 / (ent->damageTime + 1))));
		}
	} else if (espMod->isMobEsp) {
		if (ent->getNameTag()->getTextLength() <= 1 && ent->getEntityTypeId() == 63)
			return;

		if (ent->isInvisible())
			return;

		if (!localPlayer->canAttack(ent, false))
			return;

		if (!(ent->damageTime > 1)) {
			DrawUtils::setColor(0.f, 1.f, 0.f, (float)fmax(0.1f, (float)fmin(1.f, 15 / (ent->damageTime + 1))));
		} else {
			DrawUtils::setColor(1.f, 0.f, 0.f, (float)fmax(0.1f, (float)fmin(1.f, 15 / (ent->damageTime + 1))));
		}
	} else
		return;
	if (espMod->is2d)
		DrawUtils::draw2D(ent, (float)fmax(0.4f, 1 / (float)fmax(1, localPlayer->getPos()->dist(*ent->getPos()) * 3.f)));
	else
		DrawUtils::drawEntityBox(ent, (float)fmax(0.2f, 1 / (float)fmax(1, localPlayer->getPos()->dist(*ent->getPos()))));
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
