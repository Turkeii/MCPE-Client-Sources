#include "Announcer.h"
#include "../../../Utils/Utils.h"
#include "../ModuleManager.h"

Announcer::Announcer() : IModule(0x0, Category::MISC, "Tells the chat what you're doing") {
	registerBoolSetting("Module", &this->Module, this->Module);
	registerBoolSetting("Distance", &this->WalkingDist, this->WalkingDist);
	registerBoolSetting("Movement", &this->movement, this->movement);
	registerBoolSetting("#BadMan", &this->BadMan, this->BadMan);
	registerBoolSetting("bypass", &this->bypass, this->bypass);
	registerIntSetting("Distance Delay", &this->delay, this->delay, 0, 20);
}

Announcer::~Announcer() {
}

const char* Announcer::getModuleName() {
	return ("Announcer");
}

void Announcer::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();


	if (movement) {
		if (GameData::isKeyDown(*input->forwardKey)) {
			if (forwardYes == 0) {
				C_TextPacket textPacket;
				textPacket.message.setText(bypass ? (walking + " | " + Utils::randomString(8)) : BadMan ? (walking + " #BadManOnTop") : walking);
				textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
				textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
				forwardYes = 1;
			}
		} else {
			forwardYes = 0;
		}

		if (GameData::isKeyDown(*input->backKey)) {
			if (backYes == 0) {
				C_TextPacket textPacket;
				textPacket.message.setText(bypass ? (backwards + " | " + Utils::randomString(8)) : BadMan ? (backwards + " #BadManOnTop") : backwards);
				textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
				textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
				backYes = 1;
			}
		} else {
			backYes = 0;
		}

		if (GameData::isKeyDown(*input->rightKey)) {
			if (rightYes == 0) {
				C_TextPacket textPacket;
				textPacket.message.setText(bypass ? (right + " | " + Utils::randomString(8)) : BadMan ? (right + " #BadManOnTop") : right);
				textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
				textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
				rightYes = 1;
			}
		} else {
			rightYes = 0;
		}

		if (GameData::isKeyDown(*input->leftKey)) {
			if (leftYes == 0) {
				C_TextPacket textPacket;
				textPacket.message.setText(bypass ? (left + " | " + Utils::randomString(8)) : BadMan ? (left + " #BadManOnTop") : left);
				textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
				textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
				leftYes = 1;
			}
		} else {
			leftYes = 0;
		}

		if (GameData::isKeyDown(*input->spaceBarKey)) {
			if (jumpYes == 0) {
				C_TextPacket textPacket;
				textPacket.message.setText(bypass ? (jump + " | " + Utils::randomString(8)) : BadMan ? (jump + " #BadManOnTop") : jump);
				textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
				textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
				jumpYes = 1;
			}
		} else {
			jumpYes = 0;
		}

		if (GameData::isKeyDown(*input->sneakKey)) {
			if (sneakYes == 0) {
				C_TextPacket textPacket;
				textPacket.message.setText(bypass ? (sneak + " | " + Utils::randomString(8)) : BadMan ? (sneak + " #BadManOnTop") : sneak);
				textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
				textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
				sneakYes = 1;
			}
		} else {
			sneakYes = 0;
		}
	}

	if (WalkingDist) {

		if (resetPos) {
			posBefore = player->currentPos;
			resetPos = false;
		}

		posNow = player->currentPos;

		int posX = round(posBefore.x - posNow.x);
		int posY = round(posBefore.y - posNow.y);
		int posZ = round(posBefore.z - posNow.z);

		int distance = sqrt(posX * posX + posY * posY + posZ * posZ);

		dist = std::to_string(distance);

		Odelay++;
		if (Odelay > delay * 20) {
			C_TextPacket textPacket;
			textPacket.message.setText(bypass ? (message + dist + blocks + " | " + Utils::randomString(8)) : BadMan ? (message + dist + blocks + " #BadManOnTop") : message + dist + blocks);
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			resetPos = true;
			Odelay = 0;
		}
	}

}

void Announcer::onEnable() {
	resetPos = true;
}
