#include "PacketHook.h"
#include "../VisualModules/ReachDisplay.h"

extern void doWorldedit(const char* command, CommandRequestPacket* packet);
typedef void(*_SendPacket)(LoopbackPacketSender* loopbackPacketSender, Packet* packet);
_SendPacket osendPacket;


static bool SendToServerInit = false;
static bool sentAddr = false;
static char lastPacket[256] = { 0 };

uintptr_t** TextPacketVtable = 0;
uintptr_t** CommandRequestVtable = 0;


ReachDisplay* rdp = 0;

void HookSendToServer(LoopbackPacketSender* packetsender, Packet* packet) {
//#ifdef NDEBUG	
//	return osendPacket(packetsender, packet);
//#endif

	bool Cancel = false;
	int games = packet->getID();
	Text packetname;
	packet->getName(&packetname);
	

	//if (games != 144 && games != 123 && games != 19 && games != 44 && games != 9 && games != 77 && games != 33)
	//	Logf("Packet: %d   %s", games, packetname.getText());
	

	if (games == 77) {
		CommandRequestVtable = mem::getVtable(packet);
		CommandRequestPacket* cmdrp = (CommandRequestPacket*)packet;

		const char* commandContent = cmdrp->command.getText();
		if (!strcmp(commandContent, "/gmc"))
			cmdrp->command.setText("/gamemode 1");
		if (!strcmp(commandContent, "/gms"))
			cmdrp->command.setText("/gamemode 0");

#ifndef NDEBUG
		if (commandContent[0] == '/' && commandContent[1] == '/') {
			doWorldedit(commandContent + 2, (CommandRequestPacket*)packet);
			return;
		}
#endif
		
		return osendPacket(packetsender, (Packet*)packet);
	}


	if (games == 9) {
		TextPacketVtable = mem::getVtable(packet);
		TextPacket* tp = (TextPacket*)packet;

		if (tp->message.getText()[0] == '.') {
			CommandManager::onCommand(tp->message.getText() + 1);
			return;
		}
	 
	}

	if (games == 33) {
		if (!rdp) rdp = (ReachDisplay*)ModuleManager::getVisualModuleByName("Reach Display");
		if (rdp)  rdp->lastHitboxHitPoint = ((InteractPacket*)packet)->HitboxColidePoint;
	}
	
	/*if (games == 144) {
		memset(lastPacket, 0, 256);
		memcpy(lastPacket, packet, 256);
		//game::sendClientChat("%s copied into  %p", packetname.getText(), (void*)lastPacket);
		Logger::logf("%s copied into  %p", packetname.getText(), (void*)lastPacket);
		//return osendPacket(packetsender, (Packet*)lastPacket);
	}*/


	if (!Cancel)
		return osendPacket(packetsender, packet);
}





void SendToServerHook::init() {
	name = "SendToServerHook";
	
	//wait for clientinstance
	while (game::clientinstance == 0)
		Sleep(1);

	isInit = true; SendToServerInit = true;
	if (game::clientinstance != nullptr){
		hookAddress = (uintptr_t)(mem::getVtable(game::clientinstance->loopbackPacketSender)[2]);
		MH_CreateHook((LPVOID)hookAddress, (LPVOID)HookSendToServer, (LPVOID*)&osendPacket);
	}

#ifndef _1_16_40
	TextPacketVtable = (uintptr_t**)(mem::mod + 0x33F3290);
	CommandRequestVtable = (uintptr_t**)(mem::mod + 0x3410230);
#else
	TextPacketVtable = (uintptr_t**)(mem::mod + 0x2F896F0);
	CommandRequestVtable = (uintptr_t**)(mem::mod + 0x2F86FD8);
#endif
}



void sendUntouchedPacket(Packet* packet) {
	if (!game::clientinstance || !SendToServerInit || !mem::isRunning)
		return;
	osendPacket(game::clientinstance->loopbackPacketSender, packet);
}
