#include "Yaw.h"
bool lockpitch;
bool lockyaw;
bool byDirection;
int pitch = 0;
int yaw = 0;
Yaw::Yaw() : IModule(0, Category::PLAYER, "Locks your yaw") {
	registerBoolSetting("Lock Yaw", &lockyaw, false);
	registerBoolSetting("By Direction", &byDirection, false);
	registerEnumSetting("Direction", &Direction, 0);
	Direction = SettingEnum(this)
					.addEntry(EnumEntry("North", 0))
					.addEntry(EnumEntry("NE", 1))
					.addEntry(EnumEntry("East", 2))
					.addEntry(EnumEntry("SE", 3))
					.addEntry(EnumEntry("South", 4))
					.addEntry(EnumEntry("SW", 5))
					.addEntry(EnumEntry("West", 6))
					.addEntry(EnumEntry("NW", 7));
	registerIntSetting("Yaw", &yaw, 0, -180, 180);
	registerBoolSetting("Lock Pitch", &lockpitch, false);
	registerIntSetting("Pitch", &pitch, 0, -180, 180);
}

Yaw::~Yaw() {
}

const char* Yaw::getModuleName() {
	return "Yaw";
}

void Yaw::onPlayerTick(C_Player* plr) {
	if (byDirection == true) {
		switch (Direction.selected) {
		default:
			plr->yaw = 180;
			break;
		case 1:
			plr->yaw = 225;
			break;
		case 2:
			plr->yaw = 270;
			break;
		case 3:
			plr->yaw = 315;
			break;
		case 4:
			plr->yaw = 0;
			break;
		case 5:
			plr->yaw = 45;
			break;
		case 6:
			plr->yaw = 90;
			break;
		case 7:
			plr->yaw = 135;
			break;
		}
	} else if (byDirection == false && lockyaw) {
			plr->yaw = (yaw);
		}
	if (lockpitch) {
		plr->pitch = (pitch);
	}
}
//ported from phobos learned a lot from this