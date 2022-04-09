#include "HackerDetect.h"

bool chat = false;
HackerDetect::HackerDetect() : IModule(0x0, Category::SERVER, "Detects Hackers") {
	registerBoolSetting("SendMessage", &chat, chat);
}

HackerDetect::~HackerDetect() {
}

const char* HackerDetect::getModuleName() {
	return "HackerDetect";
}

static std::vector<C_Entity*> targetHackerman;
struct CompareTargetEnArray {
	bool operator()(C_Entity* lhs, C_Entity* rhs) {
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
	}
};

__int64 theVTableOfAnEntityThatIsProbablyActuallyAPlayerAndNotSomeRandomFuckingThingThatMakesYouCrash = Utils::getBase() + 0x3E403A0;

void findHackerman(C_Entity* currentEntity, bool isRegularEntity) {
	if (g_Data.isInGame() && g_Data.getLocalPlayer() != nullptr && g_Data.canUseMoveKeys()) {
		static auto hackerdetect = moduleMgr->getModule<HackerDetect>();

		if (currentEntity == nullptr)
			return;

		if (currentEntity == g_Data.getLocalPlayer())  // Skip Local player
			return;

		if (!g_Data.getLocalPlayer()->canAttack(currentEntity, false))
			return;

		if (!g_Data.getLocalPlayer()->isAlive())
			return;

		if (!currentEntity->isAlive())
			return;

		if (!currentEntity->isPlayer())
			return;
		if (!currentEntity->isValidTarget(currentEntity) || *(__int64*)currentEntity != theVTableOfAnEntityThatIsProbablyActuallyAPlayerAndNotSomeRandomFuckingThingThatMakesYouCrash)
			return;

		float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
		if (dist < 1000) {
			targetHackerman.push_back(currentEntity);
		}
	}
}

void HackerDetect::onTick(C_GameMode* gm) {
	targetHackerman.clear();
	if (g_Data.isInGame() && g_Data.getLocalPlayer() != nullptr && g_Data.canUseMoveKeys() && g_Data.getLocalPlayer()->pointingStruct->getLevelTicks() > 50) {
		g_Data.forEachEntity(findHackerman);
		if (targetHackerman.size() < 1)
			return;
		auto target = targetHackerman[0];
		auto speed = target->getRealSpeed();
		auto name = target->getNameTag()->getText();
		if ((target->getTicksPerSecond() > 0 && target->getTicksPerSecond() < 100 && target->isImmobile() && Utils::getShouldLocalPlayerBeImmobile())) {
			if (!chat)
				g_Data.getClientInstance()->getGuiData()->displayClientMessageF("%s is hacking", name);
			else {
				C_TextPacket textPacket;
				textPacket.message.setText(std::string(name) + " is hacking");
				textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
				textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			}
		}
	}
}

void HackerDetect::onSendPacket(C_Packet* packet) {
}
