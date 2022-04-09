#include "Target.h"

#include <regex>

#include "../PacketClient/Module/ModuleManager.h"

C_LocalPlayer** localPlayer;

void Target::init(C_LocalPlayer** cl) {
	localPlayer = cl;
}

bool Target::isValidTarget(C_Entity* ent) {
	static auto antibot = moduleMgr->getModule<AntiBot>();
	static auto hitboxMod = moduleMgr->getModule<Hitbox>();
	static auto teams = moduleMgr->getModule<Teams>();

	if (ent == NULL)
		return false;

	if (ent == g_Data.getLocalPlayer())
		return false;

	//if (!ent->isAlive())
		//return false;

	if (!(*localPlayer)->canAttack(ent, false))
		return false;

	if (antibot->isEnabled()) {
		if (antibot->mode.getSelectedValue() == 0) {  // Basic
			if (ent->getEntityTypeId() == 316)
				return false;

			if (ent->isInvisible())
				return false;

			if (!hitboxMod->isEnabled())
				if ((ent->height < 1.5f || ent->width < 0.49f || ent->height > 2.1f || ent->width > 0.9f))
					return false;

			if (FriendList::findPlayer(ent->getNameTag()->getText()) && !moduleMgr->getModule<NoFriends>()->isEnabled())
				return false;

			if ((ent->isSilent() || ent->isImmobile() || ent->getNameTag()->getTextLength() < 2))
				return false;

		} else {  // Advanced
			if (ent->getEntityTypeId() == 316 && antibot->isEntityIdCheckEnabled())
				return false;

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

			if (antibot->isExtraCheckEnabled() && !ent->canShowNameTag())
				return false;
		}
	}

	if (ent->getEntityTypeId() == 316) {
		if (teams->isColorCheckEnabled()) {
			std::string targetName = ent->getNameTag()->getText();
			std::string localName = g_Data.getLocalPlayer()->getNameTag()->getText();
			if (targetName.length() > 2 && localName.length() > 2) {
				targetName = std::regex_replace(targetName, std::regex("\\§r"), "");
				localName = std::regex_replace(localName, std::regex("\\§r"), "");
				if (targetName.at(0) == localName.at(0)) return false;
			}
		}
		if (teams->isAlliedCheckEnabled()) {
			C_LocalPlayer* p = g_Data.getLocalPlayer();
			if (p->isAlliedTo(ent)) return false;
		}
	}

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
