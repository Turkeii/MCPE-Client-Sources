#include "TargetUtil.h"
#include <regex>

C_LocalPlayer** localPlayer;

void TargetUtil::init(C_LocalPlayer** cl) {
	localPlayer = cl;
}

bool TargetUtil::isValidTarget(C_Entity* ent) {
	static auto hackerDetector = moduleMgr->getModule<HackerDetector>();
	static auto hitBoxes = moduleMgr->getModule<HitBoxes>();
	static auto freecam = moduleMgr->getModule<Freecam>();
	static auto antibot = moduleMgr->getModule<AntiBot>();
	static auto teams = moduleMgr->getModule<Teams>();

	if (ent == NULL) return false;
	if (ent == g_Data.getLocalPlayer() && !freecam->isEnabled()) return false;
	if (!ent->isAlive()) return false;
	if (!(*localPlayer)->canAttack(ent, false)) return false;

	if (antibot->isEnabled()) {
		if (antibot->mode.getSelectedValue() == 0) {  // Basic
			if (ent->getEntityTypeId() == 316) return false;

			if (ent->isInvisible()) return false;

			if (!hitBoxes->isEnabled()) if ((ent->height < 1.5f || ent->width < 0.49f || ent->height > 2.1f || ent->width > 0.9f)) return false;

			if (FriendList::findPlayer(ent->getNameTag()->getText())) return false;

			if ((ent->isSilent() || ent->isImmobile() || ent->getNameTag()->getTextLength() < 2)) return false;
		} else {  // Advanced
			if (ent->getEntityTypeId() == 316 && antibot->isEntityIdCheckEnabled()) return false;

			if (!TargetUtil::containsOnlyASCII(ent->getNameTag()->getText()) && antibot->isNameCheckEnabled()) return false;

			if (FriendList::findPlayer(ent->getNameTag()->getText())) return false;

			if (ent->isInvisible() && antibot->isInvisibleCheckEnabled()) return false;

			if ((ent->isSilent() || ent->isImmobile() || ent->getNameTag()->getTextLength() < 1 || std::string(ent->getNameTag()->getText()).find(std::string("\n")) != std::string::npos) && antibot->isOtherCheckEnabled())
				return false;

			if (!hitBoxes->isEnabled() && antibot->isHitboxCheckEnabled()) if ((ent->height < 1.5f || ent->width < 0.49f || ent->height > 2.1f || ent->width > 0.9f)) return false;

			if (antibot->isExtraCheckEnabled() && !ent->canShowNameTag()) return false;
		}
	}

	if (hackerDetector->isEnabled()) {
		if (hackerDetector->immobileCheck && ent->isImmobile() && ent->velocity.magnitudexz() > 0.f) hackerDetector->failedImmobile = true;
	}

	if (teams->isEnabled() && ent->getEntityTypeId() == 316) {
		static auto esp = moduleMgr->getModule<ESP>();
		auto player = g_Data.getLocalPlayer();

		if (teams->isColorCheckEnabled()) {
			std::string TargetUtilName = ent->getNameTag()->getText();
			std::string localName = player->getNameTag()->getText();

			if (TargetUtilName.length() > 2 && localName.length() > 2) {
				if (TargetUtilName.at(2) == localName.at(2) && ent->isPlayer()) {
					if (esp->isEnabled()) {
						DrawUtils::setColor(0.1f, 0.9f, 0.1f, (float)fmax(0.1f, (float)fmin(1.f, 15 / (ent->damageTime + 1))));
						DrawUtils::drawEntityBox(ent, (float)fmax(0.2f, 1 / (float)fmax(1, player->eyePos0.dist(ent->eyePos0))));
					}
					return false;
				}
			}
		}

		if (teams->isAlliedCheckEnabled()) {
			if (player->isAlliedTo(ent)) return false;
		}
	}

	return true;
}

bool TargetUtil::containsOnlyASCII(const std::string& string) {
	for (auto c : string) {
		int n = static_cast<unsigned char>(c);
		if (n > 127 && n != -89) {
			return false;
		}
	}
	return true;
}