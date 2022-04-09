#include "PacketLogger.h"
#include <iomanip>
#include <basetsd.h>

PacketLogger::PacketLogger() : IModule(0x0, Category::WORLD, "Logging Packets! (PlayerAuthInput & SubChunkRequest don't display for spam reasons)") {
	registerBoolSetting("Packet Addr", &packetadd, &packetadd);
	registerEnumSetting("Mode", &addressType, 0);
	addressType = SettingEnum(this)
					  .addEntry(EnumEntry("CE Address", 0))
					  .addEntry(EnumEntry("IDA Address", 1));
}

PacketLogger::~PacketLogger() {
}

const char* PacketLogger::getModuleName() {
	return ("PacketLogger");
}

void PacketLogger::onSendPacket(C_Packet* packet) {
	if (packetadd && addressType.selected == 0) {
		C_LocalPlayer* player = g_Data.getLocalPlayer();
		uint64_t currVTable = *(UINT64*)packet;
		std::stringstream stream;
		stream << std::hex << (currVTable - Utils::getBase());
		std::string result(stream.str());
		std::string packetText = packet->getName()->getText() + (std::string) " (Minecraft.Windows.exe+" + result + ")";
		TextHolder txt = TextHolder(packetText);
		player->displayClientMessage(&txt);
	}

	if (packetadd && addressType.selected == 1) {
		C_LocalPlayer* player = g_Data.getLocalPlayer();
		uint64_t currVTable = *(UINT64*)packet;
		std::stringstream stream;
		stream << std::hex << (currVTable - Utils::getBase() + 0x140000000);
		std::string result(stream.str());
		std::string packetText = packet->getName()->getText() + std::string(" = ") + result;
		TextHolder txt = TextHolder(packetText);
		player->displayClientMessage(&txt);
	}

	if (!packetadd) {
		if (packet->isInstanceOf<C_PlayerActionPacket>()) {
			auto pk = reinterpret_cast<C_PlayerActionPacket*>(packet);
			g_Data.getClientInstance()->getGuiData()->displayClientMessageF("%s action=%i", packet->getName()->getText(), pk->action);
			return;
		}

		if (packet->isInstanceOf<LevelSoundEventPacket>()) {
			auto pk = reinterpret_cast<LevelSoundEventPacket*>(packet);
			g_Data.getClientInstance()->getGuiData()->displayClientMessageF("%s sound=%i", packet->getName()->getText(), pk->sound);
			return;
		}
		if (strcmp(packet->getName()->getText(), "PlayerAuthInputPacket") != 0 && strcmp(packet->getName()->getText(), "SubChunkRequestPacket") != 0) {
			g_Data.getClientInstance()->getGuiData()->displayClientMessageF("%s", packet->getName()->getText());
		}
	}
}