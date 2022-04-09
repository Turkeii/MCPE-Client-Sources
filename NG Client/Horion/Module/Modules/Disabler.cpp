#include "Disabler.h"

#include <chrono>
#include <queue>

Disabler::Disabler(): IModule(0x0, Category::SERVER, "Disabler for servers") {
	registerEnumSetting("disabler Types", &disablerMode, 0);
	disablerMode = (*new SettingEnum(this))
	 .addEntry(EnumEntry("Hive", 0))
	 .addEntry(EnumEntry("CubeCraft", 1));
}

std::queue<std::pair<NetworkLatencyPacket, unsigned __int64> > latencyPacketQueue;
std::queue<std::pair<NetworkLatencyPacket, unsigned __int64> > emptyPacketQueue;

bool sendingEpicThingy = false;

const char* Disabler::getModuleName() {
	return ("Disabler");
}

void Disabler::onEnable() {
	latencyPacketQueue = emptyPacketQueue;
}

void Disabler::onTick(C_GameMode* gm) {
	if (hive) {
		unsigned __int64 now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		while (!latencyPacketQueue.empty() && now - latencyPacketQueue.front().second >= 1000) {
			NetworkLatencyPacket packetToSend = latencyPacketQueue.front().first;
			sendingEpicThingy = true;
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&packetToSend);
			sendingEpicThingy = false;
			latencyPacketQueue.pop();
		}
	}
}

void Disabler::onMove(C_MoveInputHandler* input) {
}

void Disabler::onSendPacket(C_Packet* packet) {
	if (packet->isInstanceOf<NetworkLatencyPacket>()) {
		if (sendingEpicThingy == false) {
				NetworkLatencyPacket* currentPacket = (NetworkLatencyPacket*)packet;
				unsigned __int64 now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
				if (disablerMode.selected == 0) latencyPacketQueue.push({*currentPacket, now}); // Only push to vector if it's Hive mode 
				currentPacket->timeStamp = 69420;
			}
	} 
	else if (disablerMode.selected == 1 && packet->isInstanceOf<PlayerAuthInputPacket>()) {
		PlayerAuthInputPacket* pkt = (PlayerAuthInputPacket*)packet;
		pkt->velocity = vec3(0, 0, 0);
	}
}
