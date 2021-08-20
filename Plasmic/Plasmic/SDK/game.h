#pragma once

#ifndef _IN_FRENCH
//MultiLanguageText
#define mltext(English, French) English
#else
//MultiLanguageText
#define mltext(English, French) French
#endif

#include "sdk.h"
#include "../Plasmic/ClickGui.h"

namespace game {

	extern uint16_t fps;
	extern uint16_t lcps;
	extern uint16_t rcps;


	extern ClickGui* clickGui;


	extern ClientInstance* clientinstance;
	extern LocalPlayer* localPlayer;
	extern MinecraftGame* minecraftGame;
	extern Gamemode* gm;

	extern char currentScreen[128];


	extern void sendPacket(Packet* packet);
	//for color use §§ instead of only § thx (no more then 512 chars)
	extern void sendClientChat(const char* format, ...);
	extern void clearClientChat();

}


#define assertLocalPlayer if (!game::localPlayer) return