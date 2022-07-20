#include "InventoryView.h"
#include "../../DrawUtils.h"
#include "../../Scripting/ScriptManager.h"
#include "../../../Utils/Logger.h"


SessionInfo::SessionInfo() : IModule(0x0, Category::GUI, "Renders Session Info") {
	registerFloatSetting("invPosX", &this->invX, this->invX, 5.f, g_Data.getClientInstance()->getGuiData()->windowSize.x);
	registerFloatSetting("invPosY", &this->invY, this->invY, 5.f, g_Data.getClientInstance()->getGuiData()->windowSize.y);
	registerFloatSetting("Opacity", &this->Opacity, this->Opacity, 0.15f, 1.f);
}

SessionInfo::~SessionInfo() {
}

const char* SessionInfo::getModuleName() {
	return ("SessionInfo");
}

static std::vector<C_Entity*> targetList;
void findEntity9954245(C_Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity == g_Data.getLocalPlayer())  // Skip Local player
		return;

	if (currentEntity->getEntityTypeId() != 63)  // player
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < 7) {
		targetList.push_back(currentEntity);
	}
}
void SessionInfo::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	if (ticktock == 20 && g_Data.isInGame()) {
		ticktock = 0;
		timer3++;
	} else
		ticktock++;
	if (timer3 == 60 && g_Data.isInGame()) {
		timer3 = 0;
		timer4++;
	}
	if (timer4 == 60 && g_Data.isInGame()) {
		timer4 = 0;
		timer5++;
	}
	targetList.clear();

	g_Data.forEachEntity(findEntity9954245);
	if (!targetList.empty() && g_Data.isInGame()) {
		if (GameData::canUseMoveKeys()) {
			if (targetList[0]->isAlive() && targetList[0]->height > 1.5f && targetList[0]->damageTime > 1) {
				foundPlayer = true;
			}

			if (foundPlayer && !targetList[0]->isAlive() && !targetList[0]->canShowNameTag() && targetList[0]->getDeathTime() >= 0 && targetList[0]->getNameTag()->getTextLength() > 1) {
				isDead = true;
			}

			if (isDead) {
				foundPlayer = false;
				gameTick++;
				isDead = false;
			}
		}
	}
	if (targetList.empty()) {
		foundPlayer = false;
		isDead = false;
	}
}
void SessionInfo::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	auto theme = moduleMgr->getModule<AltTheme>();
	auto theme2 = moduleMgr->getModule<Theme>();
	vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
	float yVal = invY;
	float xVal = invX;
	
	// Session info

	if (g_Data.isInGame()) {  //session time
		std::string sestime = "Session time :";
		int F = timer3;
		int A = timer4;
		int B = timer5;
		std::string Seconds = std::to_string(F) + "s";
		std::string Minutes = std::to_string(A) + "m";
		std::string Hours = std::to_string(B) + "h";

		std::string SessionInfo = sestime + " " + Hours + " " + Minutes + " " + Seconds;
		//box
		DrawUtils::setColor(0.03f, 0.03f, 0.03f, this->Opacity);
		DrawUtils::fillRectangle(vec2_t(invX, invY),
								 vec2_t(invX + 75.f + DrawUtils::getTextWidth(&SessionInfo, 1.f),
										invY + 38));


		//sessioninfo top
		DrawUtils::setColor(theme2->rFloat, theme2->gFloat, theme2->bFloat, 1.f);
		DrawUtils::drawLine(vec2_t(invX, invY),
							vec2_t(invX + 75.f + DrawUtils::getTextWidth(&SessionInfo, 1.f),
								   invY),
							0.5f); 

		std::string sesinfo = "Session Information";
		DrawUtils::drawText(vec2_t(invX + 5, invY + 3), &sesinfo,
							MC_Color(theme->rFloat, theme->gFloat, theme->bFloat), 1.f);
		//midline

		DrawUtils::setColor(theme->rFloat, theme->gFloat, theme->bFloat, 0.88f);
		DrawUtils::drawLine(vec2_t(invX + 5, invY + 13),
							vec2_t(invX + 72.f + DrawUtils::getTextWidth(&SessionInfo, 1.f),
								   invY + 13),
							0.36f);
		
		//session time
		DrawUtils::drawText(vec2_t(invX + 5, invY + 16), &SessionInfo,
							MC_Color(theme->rFloat, theme->gFloat, theme->bFloat), 1.f);
		
		
		//kills
		std::string kilstring = "Kills : ";
		int i = gameTick;
		std::string killed = std::to_string(i);
		std::string Kills = kilstring + killed;
		DrawUtils::drawText(vec2_t(invX + 5, invY + 27), &Kills,
							MC_Color(theme->rFloat, theme->gFloat, theme->bFloat), 1.f);
	}
}