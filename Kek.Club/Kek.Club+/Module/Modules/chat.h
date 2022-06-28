#pragma once
#include "Module.h"
class Chat : public IModule {
public:
	Chat() : IModule(0x0, Category::MISC, "Say Da | Kek.Club+ in da chat") {
	}
	~Chat(){};

	// Inherited via IModule
	virtual const char* getModuleName() {
		return ("Chat");
	};
	virtual void onSendPacket(C_Packet* packet) {
		if (packet->isInstanceOf<C_TextPacket>()) {
			C_TextPacket* funy = reinterpret_cast<C_TextPacket*>(packet);
			std::string Sentence;
			std::string end;
			end = " | Kek.Club+";
			Sentence = funy->message.getText() + end;
			funy->message.resetWithoutDelete();
			funy->message.setText(Sentence);
		}
	};
};