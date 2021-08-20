#include "game.h"




uint16_t game::fps;
uint16_t game::lcps;
uint16_t game::rcps;


ClickGui* game::clickGui;


ClientInstance* game::clientinstance;
LocalPlayer* game::localPlayer;
MinecraftGame* game::minecraftGame;
Gamemode* game::gm;

char game::currentScreen[128] = {0};




extern void sendChatMessage(const char* format, va_list list);
void game::sendClientChat(const char* format, ...) {
	va_list list;
	va_start(list, format);
	sendChatMessage(format, list);
}
extern void clearChat();
void game::clearClientChat() {
	clearChat();
}


extern void sendUntouchedPacket(Packet* packet);
void game::sendPacket(Packet* packet) {
	sendUntouchedPacket(packet);
}