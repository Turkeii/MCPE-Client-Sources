#include "ChatHook.h"
#include "../Modules/AutoGG.h"


static Text empty32Bytes;
bool ChatHookInit = false;
typedef __int64(*_DoGame)(GuiData* guiData, uint32_t messageType, NewChatMessage* chatmessage, Text* message, Text* Zero32Times1, Text* Zero32Times2, uintptr_t pass0, Text* Zero32Times3, Text* Zero32Times4, unsigned int a10);
_DoGame oSendChat = NULL;



AutoGG* ggmod;
__int64 HookSendChat(GuiData* guiData, uint32_t messageType, NewChatMessage* chatmessage, Text* message, Text* Zero32Times1, Text* Zero32Times2, uintptr_t pass0, Text* Zero32Times3, Text* Zero32Times4, unsigned int a10) {
	
	if (!ggmod)
		ggmod = (AutoGG*)ModuleManager::getModuleByName("AutoGG");
	if (ggmod)
		if (ggmod->onChat(message->getText()))
			return 0;

	return oSendChat(guiData, messageType, chatmessage, message, &empty32Bytes, &empty32Bytes, 0, &empty32Bytes, &empty32Bytes, a10);
}


void ChatHook::init() {
	if (ChatHookInit)
		return; //as its going to be in the list still

	name = "sch"; //SendChatHook, -2 triggered antivirus!
	
#ifndef _1_16_40
	uintptr_t hookAddress = mem::FindSignature("48 8B C4 48 89 58 10 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ?? ?? ?? ?? 48 81 EC ?? ?? ?? ?? 0F 29 70 ?? 0F 29 78 ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 49 8B F1 4D 8B E8 44 8B FA 89 54 24 ?? 4C 8B E1");
#else
	uintptr_t hookAddress = mem::FindSignature("48 8B C4 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ?? ?? ?? ?? 48 81 EC ?? ?? ?? ?? 48 C7 45 00 ?? ?? ?? ?? 48 89 58 10 0F 29 70 B8 0F 29 78 A8 48 8B 05");
#endif

	if (hookAddress == NULL) {
		Logf("Unable to hook!\n Sig of %s is broken", name);
		return;
	}
	Logf("%s: %p", name, (void*)hookAddress);

	isInit = true; ChatHookInit = true;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)HookSendChat, (LPVOID*)&oSendChat);
	MH_EnableHook((LPVOID)hookAddress);
}


//for color use §§ instead of §
static char msg[513];
void sendChatMessage(const char* format, va_list list) {
	//crash idk u and I don't want this to change thx
	if (!game::clientinstance || !ChatHookInit || !mem::isRunning)
		return;

	//building string
	vsprintf(msg, format, list);

	//Color support
	for (uint16_t i = 0; i < 513; i++) {
		if (msg[i] == 0)
			break;
		if (msg[i] == '§') {
			msg[i] = (char)194;
			i++;
#ifndef NDEBUG
			if (msg[i] != '§') {
				Text TheText("The text below is wrongly formated, you should use 2 color symbols instead of one!");
				oSendChat(game::clientinstance->guiData, 2, (NewChatMessage*)&empty32Bytes, &TheText, &empty32Bytes, &empty32Bytes, 0, &empty32Bytes, &empty32Bytes, 3);
				break;
			}
#else
			msg[i] = (char)167;
#endif
		}
	}

	//send it!
	Text theText(msg);
	oSendChat(game::clientinstance->guiData, 2, (NewChatMessage*)&empty32Bytes, &theText, &empty32Bytes, &empty32Bytes, 0, &empty32Bytes, &empty32Bytes, 3);
}

void clearChat() {
	if (!game::clientinstance || !ChatHookInit || !mem::isRunning)
		return;

	Text cleartext("");
	for (int i = 0; i < 512; i++) 
		oSendChat(game::clientinstance->guiData, 2, (NewChatMessage*)&empty32Bytes, &cleartext, &empty32Bytes, &empty32Bytes, 0, &empty32Bytes, &empty32Bytes, 3);
}