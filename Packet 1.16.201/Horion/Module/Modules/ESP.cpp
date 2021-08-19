#include "ESP.h"

#include "../../../Utils/Target.h"

ESP::ESP() : IModule(0, Category::VISUAL, "Outlines a players hitbox") {
	//this->registerBoolSetting("MobEsp", &this->isMobEsp, this->isMobEsp);
	//this->registerBoolSetting("2d", &this->is2d, this->is2d);
}

ESP::~ESP() {
}

const char* ESP::getModuleName() {
	return ("PlayerESP");
}

static float rcolors[4];

void doRenderStuff(C_Entity* ent, bool isRegularEntitie) {
	static auto espMod = moduleMgr->getModule<ESP>();
	
	C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
	if (ent != localPlayer) {
		if (ent->timeSinceDeath > 0)
			return;
		if (FriendList::findPlayer(ent->getNameTag()->getText()) && !moduleMgr->getModule<NoFriends>()->isEnabled()) {
			DrawUtils::setColor(0.1f, 0.9f, 0.1f, (float)fmax(0.1f, (float)fmin(1.f, 15 / (ent->damageTime + 1))));
		} else if (Target::isValidTarget(ent)) {
				DrawUtils::setColor(0.9f, 0.9f, 0.9f, (float)fmax(0.1f, (float)fmin(1.f, 15 / (ent->damageTime + 1))));
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

	if (localPlayer != nullptr && GameData::canUseMoveKeys()) 
		g_Data.forEachEntity(doRenderStuff);
	
}
