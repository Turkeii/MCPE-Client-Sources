#include "Target.h"

#include <regex>

#include "../Horion/Module/ModuleManager.h"

C_LocalPlayer** localPlayer;

void Target::init(C_LocalPlayer** cl) {
	localPlayer = cl;
}

bool Target::isValidTarget(C_Entity* ent) {
	static auto freeMod = moduleMgr->getModule<Freecam>();
	if (ent == NULL)
		return false;

	if (!freeMod->isEnabled() && ent == g_Data.getLocalPlayer())
		return false;

	static auto antibot = moduleMgr->getModule<AntiBot>();
	static auto hitboxMod = moduleMgr->getModule<Hitbox>();
	static auto teams = moduleMgr->getModule<Teams>();

	if (!ent->isAlive())
		return false;

	if (!antibot->isEnabled()) return true;

	if (ent->getEntityTypeId() <= 130 && ent->getEntityTypeId() != 63 && antibot->isEntityIdCheckEnabled())
		return false;

	if (teams->isColorCheckEnabled()) {
		std::string targetName = ent->getNameTag()->getText();
		std::string localName = g_Data.getLocalPlayer()->getNameTag()->getText();
		if (targetName.length() > 2 && localName.length() > 2) {
			if (targetName.at(2) == localName.at(2) && ent->isPlayer()) {
				static auto espMod = moduleMgr->getModule<ESP>();
				if (espMod->isEnabled()) {
					C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
					DrawUtils::setColor(0.1f, 0.9f, 0.1f, (float)fmax(0.1f, (float)fmin(1.f, 15 / (ent->damageTime + 1))));
					if (espMod->is2d)
						DrawUtils::draw2D(ent, (float)fmax(0.4f, 1 / (float)fmax(1, localPlayer->eyePos0.dist(ent->eyePos0) * 3.f)));
					else if (espMod->iszephyr)
						DrawUtils::drawZephyr(ent, (float)fmax(0.4f, 1 / (float)fmax(1, localPlayer->eyePos0.dist(ent->eyePos0) * 3.f)));
					else if (espMod->betterESP)
						DrawUtils::drawBetterESP(ent, (float)fmax(0.2f, 1 / (float)fmax(1, localPlayer->eyePos0.dist(ent->eyePos0))));
					else
						DrawUtils::drawEntityBox(ent, (float)fmax(0.2f, 1 / (float)fmax(1, localPlayer->eyePos0.dist(ent->eyePos0))));
				}
				return false;
			}
		}
	}
	if (teams->isAlliedCheckEnabled()) {
		C_LocalPlayer* p = g_Data.getLocalPlayer();
		if (p->isAlliedTo(ent)) return false;
	}

	// Temporarily removed from gui, tons of false negatives
	if (!Target::containsOnlyASCII(ent->getNameTag()->getText()) && antibot->isNameCheckEnabled())
		return false;

	if (FriendList::findPlayer(ent->getNameTag()->getText()) && !moduleMgr->getModule<NoFriends>()->isEnabled())
		return false;

	if (ent->isInvisible() && antibot->isInvisibleCheckEnabled())
		return false;

	if ((ent->isSilent() || ent->isImmobile() || ent->getNameTag()->getTextLength() < 1 || std::string(ent->getNameTag()->getText()).find(std::string("\n")) != std::string::npos) && antibot->isOtherCheckEnabled())
		return false;

	if (!hitboxMod->isEnabled() && antibot->isHitboxCheckEnabled())
		if ((ent->height < 1.5f || ent->width < 0.49f || ent->height > 2.1f || ent->width > 0.9f))
			return false;

	if (!(*localPlayer)->canAttack(ent, false))
		return false;

	if (antibot->isExtraCheckEnabled() && !ent->canShowNameTag())
		return false;

	return true;
}

bool Target::containsOnlyASCII(const std::string& string) {
	for (auto c : string) {
		int n = static_cast<unsigned char>(c);
		if (n > 127 && n != -89) {
			return false;
		}
	}
	return true;
}
