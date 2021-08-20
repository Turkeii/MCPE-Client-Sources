#pragma once
#include "MCUtilsClass.h"
#include "../../Utils/PlasmicMath.h"

struct NetworkIdentifier {};

class Packet {
public:

	virtual void Function0() {  }
	virtual int getID() { return 0; }
	virtual Text* getName(Text* out_text) { return out_text; }
	virtual void write(uintptr_t game) {  }
	virtual void read() {  }
	virtual void readExtended() {  }
}; //Size: 0x0080

//thats all going in packet hook.
extern uintptr_t** TextPacketVtable;
extern uintptr_t** CommandRequestVtable;


class TextPacket : public Packet {
	char pad_0000[32]; //0x0000
public:
	uint8_t messageType; //0x0028
	char pad_0029[7]; //0x0029
public:
	 Text name; //0x0030
	 Text message; //0x0050
private:
	char pad_0070[24]; //0x0070
public:
	bool requireTranslation; //0x0088
private:
	char pad_0089[7]; //0x0089
public:
	 Text xuid; //0x0090
	 Text xuid2; //0x00B0

	 TextPacket() {mem::ApplyVtable(this, TextPacketVtable);}
	 TextPacket(Text TheMessage, Text Username, Text XUID, uint8_t MessageType = 1, bool TranslationNeeded = false) {
		 mem::ApplyVtable(this, TextPacketVtable);

		 memcpy(&name, &Username, sizeof(Text));
		 memcpy(&xuid, &XUID, sizeof(Text));
		 memcpy(&xuid2, &xuid, sizeof(Text));
		 requireTranslation = TranslationNeeded;
		 messageType = MessageType;

		 memcpy(&message, &TheMessage, sizeof(Text));
	 }

}; //Size: 0x00E8



class PlayerAuthInputPacket : public Packet {
	char pad_0008[32]; //0x0008
public:
	Vec2 headRot; //0x0028
	Vec3 playerPos; //0x0030
	float cameraRotation; //0x003C
	Vec3 Velocity; //0x0040
	Vec2 dirrection; //0x004C
private:
	char pad_0054[14]; //0x0054
public:
	uint8_t keyStatus; //0x0062 shift = 2, sprint = 1, jump = 10   (they wull + if multiple at a time, this is the keydown)
private:
	char pad_0063[13]; //0x0063
public:
	uint32_t tick; //0x0070
private:
	char pad_0074[40]; //0x0074
};

class LevelSoundEventPacket : public Packet {
	char pad_0000[38]; //0x0000
public:
	int32_t soundID; //0x0028
	Vec3 soundLocation; //0x002C
	uint32_t anumberig; //0x0038
private:
	char pad_003C[4]; //0x003C
}; //Size: 0x0040

class MovePlayerPacket : public Packet {
	char pad_0008[40]; //0x0008
public:
	Vec3 playerLocation; //0x0030
	Vec2 lookingAt; //0x003C
	float cameraLookingAt; //0x0044
private:
	char pad_0048[36]; //0x0048

}; //Size: 0x006C



class PlayerActionPacket : public Packet {
	char pad_0008[48]; //0x0008
public:
	
	int action; //use PlayerAction enum 4 that    0x0038
	char pad_003C[56]; //0x003C
	Vec3 playerPos; //0x0074
};

class CommandRequestPacket : public Packet {
	char pad_0008[32]; //0x0008
public:
	class Text command; //0x0028
	char pad_0048[16]; //0x0048


	CommandRequestPacket() { mem::ApplyVtable(this, CommandRequestVtable); }
	CommandRequestPacket(Text Command) {
		mem::ApplyVtable(this, CommandRequestVtable);

		memcpy(&command, &Command, sizeof(Text));
	}


}; //Size: 0x0050




class InteractPacket : public Packet{
	char pad_0008[40]; //0x0008
public:
	int64_t entityRuntimeID; //0x0030
	Vec3 HitboxColidePoint; //0x0038
	char pad_0044[4]; //0x0044
}; //Size: 0x0048


















class LoopbackPacketSender {
	char pad_0008[8]; //0x0008
public:
	class NetworkHandler* networkHandler; //0x0010

	virtual void Function0();
	virtual void send(Packet* packet);
	virtual void sendToServer(Packet* packet);
	virtual void sendToClient(NetworkIdentifier id, Packet* packet, UCHAR idk);
	virtual void sendToClients();
	virtual void sendBroadcast(Packet* packet);
	virtual void sendBroadcast();
	virtual void flush();
}; //Size: 0x00E8


class RakNetInstance {
#ifndef _1_16_40
	char pad_0000[864]; //0x0000
#else
	char pad_0000[848]; //0x0000
#endif
public:
	class Text numericIP; //0x0360
	class Text serverTextIP; //0x0380
	uint32_t serverPort; //0x03A0
private:
	char pad_03A4[188]; //0x03A4
public:

	bool isonaServer() { return !(serverTextIP.textLength == 0); }

}; //Size: 0x0460



#ifndef _1_16_40
class NetworkHandler {
	char pad_0000[48]; //0x0000
public:
	class RakNetInstance* raknetInstance; //0x0030
private:
	char pad_0038[272]; //0x0038
}; //Size: 0x0148
#else
class NetworkHandler {
	char pad_0000[24]; //0x0000
public:
	class RakNetInstance* raknetInstance; //0x0018
private:
	char pad_0020[232]; //0x0020
}; //Size: 0x0108
#endif
