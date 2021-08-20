#pragma once
#include "MCUtilsClass.h"
#include <cstdint>
#include "../../Utils/PlasmicMath.h"



class GuiData {
	char pad_0000[24]; //0x0000
public:
	Vec2 windowSizeReal; //0x0018
	Vec2 windowSizeReal2; //0x0020
	Vec2 windowSizeScaled; //0x0028
private:
	char pad_0030[4]; //0x0030
public:
	float guiScale; //0x0034
	float smallness; //0x0038 yeah idk its like scale but the oposite
private:
	char pad_003C[22]; //0x003C
public:
	uint16_t mouseX; //0x0052
	uint16_t mouseY; //0x0054
private:
	char pad_0056[66]; //0x0056
public:
	class Text itemInHandName; //0x0098
}; //Size: 0x0230



class CMinecraft {
	char pad_0000[16]; //0x0000
public:
	class MinecraftEventing* minecraftEventing; //0x0010
private:
	char pad_0018[32]; //0x0018
public:
	class AllowList* whiteList; //0x0038 This is the white list
private:
	char pad_0040[104]; //0x0040
public:
	struct LevelHolder* levelHolder; //0x00A8
private:
	char pad_00B0[16]; //0x00B0
public:
	class NetworkHandler* networkHandler; //0x00C0
	class LoopbackPacketSender* loopbackPacketSender; //0x00C8
}; //Size: 0x0170



class ServerInstance {
public:
	char pad_0000[152]; //0x0000
	CMinecraft* minecraft; //0x0098
	class NetworkHandler* networkHandler; //0x00A0
	LoopbackPacketSender* loopbackPacketSender; //0x00A8
	char pad_00B0[88]; //0x00B0
}; //Size: 0x0108


struct LevelRenderer {

};

struct BitmapFont {
private:
	char pad_0000[584]; //0x0000
public:
	float smoothbeone; //0x0248
private:
	char pad_024C[44]; //0x024C
public:
	Text fontName; //0x0278

}; //Size: 0x02B8

struct FontContainer {
private:
	char pad_0000[24]; //0x0000
public:
	BitmapFont* font; //0x0018
}; //Size: 0x0020


struct FontList {
	FontContainer* font1; //default font            0x0000
	FontContainer* font01; //default font           0x0008
	FontContainer* font2; //Glyph font              0x0010
	FontContainer* font02; //Glyph font             0x0018
private:
	char pad_0020[32]; //0x0020  this is null so I won'T let you touch them they aint a font
public:
	FontContainer* font3; //looks like default     0x0040
	FontContainer* font03; //looks like default    0x0048
	FontContainer* font4; //"smoother" default     0x0050
	FontContainer* font04; //"smoother default"    0x0058
	FontContainer* smooth1; //0x0060
	FontContainer* smooth01; //0x0068
	FontContainer* smooth2; //0x0070
	FontContainer* smooth02; //0x0078
}; //Size: 0x0080

struct FontRepository {
private:
	char pad_0000[200]; //0x0000
public:
	FontList* fontList; //0x00C8
}; //Size: 0x00D0


class MinecraftGame {
	char pad_0000[200]; //0x0000
public:
	struct FontRepository* fontRepository; //0x00C8
private:
	char pad_00D0[8]; //0x00D0
public:
	BitmapFont* minecraftFont; //0x00D8
private:
	char pad_00E0[384]; //0x00E0
public:
	bool canMoveCamera; //0x0260
private:
	char pad_0261[151]; //0x0261
public:
	class ServerInstance* serverInstance; //0x02F8
#ifndef _1_16_40
private:
	char pad_0300[520]; //0x0300
public:
	class NetworkHandler* networkHandler; //0x0508
private:
	char pad_0510[8]; //0x0510
public:
	class Text xuid; //0x0518
#else
private:
	char pad_0300[488]; //0x0300
public:
	class NetworkHandler* networkHandler; //0x04E8
private:
	char pad_04F0[8]; //0x04F0
public:
	char* xuid; //0x04F8
#endif
public:


}; //Size: 0x0860


struct ClientMoveInputHandler {
private:
	char pad_0000[8]; //0x0000
public:
	Vec2 walkDirrection; //0x0008 first is for sides left 1 sec is 4 frontback front is 1.f
private:
	char pad_0010[56]; //0x0010
public:
	bool pressingSneakkey; //0x0048
	bool pressingSneakkey2; //0x0049
	bool pressingRunkey; //0x004A
	bool pressingJumpkey; //0x004B
	bool pressingSneakkey3; //0x004C
private:
	char pad_004D[15]; //0x004D
public:
	bool pressingRunkey2; //0x005C
private:
	char pad_005D[2]; //0x005D
public:
	bool pressingWalkKey; //0x005F
	bool pressingBackKey; //0x0060
	bool pressingLeftKey; //0x0061
	bool pressingRightKey; //0x0062
private:
	char pad_0063[45]; //0x0063
}; //Size: 0x0090


#ifndef  _1_16_40



class ClientInstance {
	char pad_0000[152]; //0x0000
public:
	class MinecraftGame* minecraftGame; //0x0098
private:
	char pad_00A0[40]; //0x00A0
public:
	class levelRenderer* levelRenderer; //0x00C8
	class LoopbackPacketSender* loopbackPacketSender; //0x00D0
private:
	char pad_00D8[16]; //0x00D8
public:
	struct ClientMoveInputHandler* moveinputHandler; //0x00E8
private:
	char pad_00F0[80]; //0x00F0
public:
	class LocalPlayer* localPlayer; //0x0140

private:
	char pad_0148[904]; //0x0148
public:
	class GuiData* guiData; //0x04D0
}; //Size: 0x0B00

#else

class ClientInstance {
	char pad_0000[128]; //0x0000
	class ClientInstance* clientInstancePtr; //0x0080
	char pad_0088[16]; //0x0088
public:
	class MinecraftGame* minecraftGame; //0x0098
private:
	char pad_00A0[24]; //0x00A0
	class IEntityRegistryOwner* IEntityRegistryOwnerPtr; //0x00B8
	char pad_00C0[8]; //0x00C0
public:
	struct LevelRenderer* levelRenderer; //0x00C8
private:
	char pad_00D0[8]; //0x00D0
public:
	class LoopbackPacketSender* loopbackPacketSender; //0x00D8
private:
	class HolographicPlateform* holographicPlateform; //0x00E0
	class VoiceSystem* voiceSystem; //0x00E8
public:
	struct ClientMoveInputHandler* moveinputHandler; //0x00F0
private:
	char pad_00F8[8]; //0x00F8
	class KeyboardManager* keyboardManager; //0x0100
	class HitDetectSystem* HitDetectSystem; //0x0108
	class UserAuthentication* UserAuthentication; //0x0110
	char pad_0118[8]; //0x0118
	class VanillaSceneFactory* VanillaSceneFactory; //0x0120
	char pad_0128[24]; //0x0128
public:
	class LocalPlayer* localPlayer; //0x0140
private:
	char pad_0148[792]; //0x0148
	class SceneStack* SceneStack; //0x0460
	char pad_0468[16]; //0x0468
	class UIProfanityContext* UIProfanityContext; //0x0478
	class TextToSpeechClient_winrt* TextToSpeechClient_winrt; //0x0480
	char pad_0488[8]; //0x0488
	class TTSEventManager* TTSEventManager; //0x0490
	char pad_0498[48]; //0x0498
public:
	class ItemInHandRender* ItemInHandRender; //0x04C8
private:
	char pad_04D0[8]; //0x04D0
public:
	class GuiData* guiData; //0x04D8
	
}; //Size: 0x1040

#endif // ! _1_16_40
