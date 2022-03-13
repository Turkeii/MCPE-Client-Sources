#include "InstaBreak.h"

InstaBreak::InstaBreak() : IModule(VK_NUMPAD4, Category::WORLD, "Break any block custom") {
	static int constexpr instantInt = 0;
	static int constexpr packetInt = 1;
	//static int constexpr hastre = 2;

	Modes = SettingEnum(this)
				.addEntry(EnumEntry("Instant", instantInt))
				.addEntry(EnumEntry("Packet", packetInt));
				//.addEntry(EnumEntry("Haste", 2));
 	registerEnumSetting("Mode", &Modes, instantInt);

		//registerIntSetting("Haste Delay", &delay, delay, 0, 20);

}

InstaBreak::~InstaBreak() {
}

void InstaBreak::onTick(C_GameMode* gm) {
	switch (Modes.selected) {
	case 0:
		instant = true;
		packet = false;
		haste = false;
		break;
	case 1:
		instant = false;
		packet = true;
		haste = false;
		break;
	case 2:
		instant = false;
		packet = false;
		haste = true;
		break;
	}
}

const char* InstaBreak::getModuleName() {
	return ("SpeedBreak");
}
  
const char* InstaBreak::getModName() {
	if (instant) {
		return ("Instant");
	} else if (packet) {
		return ("Packet");
	}
}

const char* InstaBreak::getRawModuleName() {
	return "SpeedBreak";
}