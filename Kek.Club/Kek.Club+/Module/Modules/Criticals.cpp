#include "Criticals.h"

Criticals::Criticals() : IModule(0, Category::COMBAT, "Fall Down Fast") {
	registerBoolSetting("Extra Packets", &packets, packets);
	registerEnumSetting("Mode", &mode, 0);
	mode = (*new SettingEnum(this)).addEntry(EnumEntry("Patch", 0))
		.addEntry(EnumEntry("PacketWrite", 1))
		.addEntry(EnumEntry("PacketSend", 2))
		.addEntry(EnumEntry("PacketSendV2", 3));
}

Criticals::~Criticals() {
}

const char* Criticals::getModuleName() {
	return "Criticals";
}

void Criticals::onTick(C_GameMode* gm) {
	if (g_Data.getLocalPlayer() == nullptr) return;

	if (mode.selected == 2) {
		C_MovePlayerPacket offG(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos(), false);
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&offG);
		if (packets) {
			C_MovePlayerPacket onG(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos(), true);
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&onG);
		}
	}
}

void Criticals::onSendPacket(C_Packet* packet) {
	if (g_Data.getLocalPlayer() == nullptr) return;

	if (packet->isInstanceOf<C_MovePlayerPacket>() && mode.selected == 1) {
		C_MovePlayerPacket* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
		movePacket->onGround = false;
	}
}

void Criticals::onAttack(C_Entity* attackedEnt) {
	static auto nofall = moduleMgr->getModule<NoFall>();

	if (mode.selected == 3) {
		if (nofall->isEnabled()) {
			noFallWasEnabled = true;
			nofall->setEnabled(false);
		}
		C_MovePlayerPacket offG(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos(), false);
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&offG);
		if (packets) {
			C_MovePlayerPacket onG(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos(), true);
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&onG);
		}
		if (noFallWasEnabled) {
			nofall->setEnabled(false);
			noFallWasEnabled = false;
		}
	}
}

void* targetaddy;
void Criticals::onEnable() {
	if (g_Data.getLocalPlayer() == nullptr)
		setEnabled(false);

	if (mode.selected == 0) {
		if (targetaddy == nullptr)
			targetaddy = (void*)(FindSignature("73 5A 80 B9 D8 01 ? ? ? 75 51"));
		unsigned char* patch = (unsigned char*)"\x90\x90\x90\x90\x90\x90\x90\x90\x90";
		Utils::patchBytes((unsigned char*)((uintptr_t)targetaddy), patch, 9);
	}
}

void Criticals::onDisable() {
	if (mode.selected == 0) {
		unsigned char* patch = (unsigned char*)"\x73\x5A\x80\xB9\xD8\x01\x00\x00\x00";
		Utils::patchBytes((unsigned char*)((uintptr_t)targetaddy), patch, 9);
	}
}

const char* Criticals::getModName() {
	if (mode.selected == 0)
		return " [Patch]";
	if (mode.selected == 1)
		return " [PacketWrite]";
	if (mode.selected == 2)
		return " [PacketSend]";
	if (mode.selected == 3)
		return " [PacketSendV2]";
	return "";
}
