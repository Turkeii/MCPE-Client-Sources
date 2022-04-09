#include "../../DrawUtils.h"
#include "HackerDetector.h"

HackerDetector::HackerDetector() : IModule(0, Category::EXPLOIT, "shit client moment") {
	registerEnumSetting("Messages", &mode, 0);
	mode.addEntry("Client", 0);
	mode.addEntry("Server", 1);
	//registerBoolSetting("Speed", &speedCheck, speedCheck);
	//registerBoolSetting("Fly", &flyCheck, flyCheck);
	//registerIntSetting("Sensitivity", &sensitivity, sensitivity, -10, 10);
}

HackerDetector::~HackerDetector() {
}

const char* HackerDetector::getModuleName() {
	return ("HackerDetector");
}

static std::vector<C_Entity*> playerList;

void findHackerMan(C_Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity == g_Data.getLocalPlayer())  // Skip Local player
		return;

	if (currentEntity->getEntityTypeId() != 319)  // Players
		return;

	if (!Target::isValidTarget(currentEntity))
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < 255) {
		playerList.push_back(currentEntity);
	}
}

void HackerDetector::onEnable() {
	if (g_Data.getLocalPlayer() == nullptr) setEnabled(false);
	time = 0;
}

void HackerDetector::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	C_TextPacket textPacket;

	playerList.clear();
	g_Data.forEachEntity(findHackerMan);

	if (g_Data.isInGame()) {
		for (auto& i : playerList) {
			name = playerList[0]->getNameTag()->getText();
			name = Utils::sanitize(name);

			vec3_t vel = playerList[0]->velocity;
			// Speed check
			if (vel.x < 0.f)
				vel.x *= -1.f;
			if (vel.y < 0.f)
				vel.y *= -1.f;
			if (vel.z < 0.f)
				vel.z *= -1.f;

			speed = sqrtf((vel.x * vel.x) + (vel.z * vel.z));
			speed *= 36.6f;

			if (!playerList[0]->onGround)
				speed /= 1.5f;

			if (playerList[0]->onGround) {
				if (speed >= 43) failedSpeedA = true;
			} else {  // off ground
				if (speed >= 45) failedSpeedB = true;
			}
			if (speed <= 30) { // reset to prevent bug
				failedSpeedA = false;
				failedSpeedB = false;
			}

			if (failedSpeedA || failedSpeedB) failedSpeed = true;
			else failedSpeed = false;

			// Fly check - wip
			/*if (playerList[0]->onGround)
				time++;
			else if (time >= 30) {
				if (vel.y == 0) failedFlyA = true;
			}
			if (failedFlyA || failedFlyB) failedFly = true;*/

			// Derp check lol
			if (playerList[0]->pitch >= 90 || playerList[0]->pitch <= -90) failedDerp = true;
			else failedDerp = false;

			//NoWeb check
			vec3_t* pos = playerList[0]->getPos();
			vec3_t blockBelow = playerList[0]->eyePos0;
			blockBelow.y -= playerList[0]->height;
			for (int y = (int)pos->y - 3; y < pos->y + 0; y++) {
				if (playerList[0]->region->getBlock(vec3_t{blockBelow})->toLegacy()->blockId == 30 && speed >= 10) failedNoWeb = true;
			}
		}

		Odelay++;
		if (Odelay > 1 * 10) {
			for (auto& i : playerList) {
				if (failedSpeed && speed <= 40)
					return;
				std::string speedAmount = std::string(std::to_string((int)speed));
				std::string pitch = std::string(std::to_string(playerList[0]->pitch));
				if (mode.getSelectedValue() == 0) {  // client
					char* speedAB = failedSpeedA ? "A" : "B";
					char* flyAB = failedFlyA ? "A" : "B";
					if (failedSpeed) clientMessageF("[Packet] %s%s%s has failed %sSpeed-%s (x%s.0)", GRAY, name.c_str(), WHITE, GRAY, speedAB, speedAmount.c_str());
					if (failedFly) clientMessageF("[Packet] %s%s%s has failed %sFly-%s (xVel)", GRAY, name.c_str(), WHITE, GRAY, flyAB);
					if (failedDerp) clientMessageF("[Packet] %s%s%s has failed %sDerp (%s)", GRAY, name.c_str(), WHITE, GRAY, pitch.c_str());
					if (failedDerp) clientMessageF("[Packet] %s%s%s has failed %sNoWeb (%s.0)", GRAY, name.c_str(), WHITE, GRAY, speedAmount.c_str());
				}
				if (mode.getSelectedValue() == 1) {  // server
					if (failedSpeed || failedFly || failedDerp) {
						if (failedSpeed) str = "[Packet] " + name + " has failed Speed-" + std::string(failedSpeedA ? "A" : "B") + " (x" + speedAmount + ".0)";
						if (failedFly) str = "[Packet] " + name + " has failed Fly-" + std::string(failedFlyA ? "A" : "B");
						if (failedDerp) str = "[Packet] " + name + " has failed Derp" + " (" + pitch + ")";
						if (failedNoWeb) str = "[Packet] " + name + " has failed NoWeb" + " (" + speedAmount + ")";
						textPacket.message.setText(str);
						textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
						textPacket.messageType = 69;
						g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
					}
				}
			}
			Odelay = 0;
		}
	}
}

void HackerDetector::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
	auto player = g_Data.getLocalPlayer();
	float x = windowSize.x / 114 + 1;
	float y = windowSize.y - 20;
	float y2 = windowSize.y - 40;

	if (g_Data.isInGame()) {
		for (auto& i : playerList) {

		}
	}
}

void HackerDetector::onDisable() {

}