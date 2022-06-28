#include "ESP.h"

#include "../../../Utils/Target.h"

float ESP::rFloat{255};
float ESP::gFloat{255};
float ESP::bFloat{255};

ESP::ESP() : IModule('O', Category::VISUAL, "draws box around shit") {
	registerEnumSetting("Rainbow", &rainBow, 0);
	rainBow = SettingEnum(this)
				  .addEntry(EnumEntry("Custom Color", 0))
				  .addEntry(EnumEntry("Rainbow", 1));
	registerEnumSetting("ESP Type", &espType, 0);
	espType = SettingEnum(this)
				  .addEntry(EnumEntry("3D", 0))
				  .addEntry(EnumEntry("2D", 1));
	registerBoolSetting("MobEsp", &isMobEsp, isMobEsp);
	registerBoolSetting("ItemEsp", &this->itemEsp, this->itemEsp);
	registerFloatSetting("Red", &rFloat, rFloat, 0.f, 255.f);
	registerFloatSetting("Green", &gFloat, gFloat, 0.f, 255.f);
	registerFloatSetting("Blue", &bFloat, bFloat, 0.f, 255.f);
	// registerFloatSetting("Thickness", &this->thickness, this->thickness, 0.1f, 5.f);
}

ESP::~ESP() {
}

const char* ESP::getModuleName() {
	return ("ESP");
}
const char* ESP::getModName() {
	if (espType.selected == 0) {
		return " [3D]";
	} else {
		return " [CSGO]";
	}
}
static float rcolors[4];

void doRenderStuff(C_Entity* ent, bool isRegularEntitie) {
	static auto espMod = moduleMgr->getModule<ESP>();

	C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
	if (ent->getEntityTypeId() == 64 && (espMod->itemEsp)) {
		// DrawUtils::drawNameTags(ent, 1.f, false, false);
		DrawUtils::setColor(ESP::rFloat, ESP::gFloat, ESP::bFloat, 3.f);
		DrawUtils::drawEntityBox(ent, (float)fmax(0.2f, 1 / (float)fmax(0.2f, (*localPlayer->getPos()).dist(*ent->getPos()))));
	}
	if (ent == nullptr)
		return;
	if (ent == localPlayer)
		return;
	static auto noFriendsModule = moduleMgr->getModule<NoFriends>();
	if (!noFriendsModule->isEnabled() && FriendList::findPlayer(ent->getNameTag()->getText())) {
		DrawUtils::setColor(ESP::rFloat, ESP::gFloat, ESP::bFloat, 1.f);
	} else if (Target::isValidTarget(ent)) {
		if (espMod->doRainbow)
			DrawUtils::setColor(rcolors[0], rcolors[1], rcolors[2], 1.f);
		else
			DrawUtils::setColor(ESP::rFloat, ESP::gFloat, ESP::bFloat, 1.f);
	} else if (espMod->isMobEsp) {
		if (ent->getNameTag()->getTextLength() <= 1 && ent->getEntityTypeId() == 63)
			return;

		if (ent->isInvisible())
			return;

		if (!localPlayer->canAttack(ent, false))
			return;
		if (espMod->doRainbow)
			DrawUtils::setColor(rcolors[0], rcolors[1], rcolors[2], 1.f);
		else
			DrawUtils::setColor(ESP::rFloat, ESP::gFloat, ESP::bFloat, 1.f);
	} else
		return;
	if (espMod->espType.selected == 1)
		DrawUtils::draw2D(ent, (float)fmax(0.2, 1 / (float)fmax(1, localPlayer->eyePos0.dist(ent->eyePos0) * 3.f)));
	else
		DrawUtils::drawEntityBox(ent, (float)fmax(0.2, 1 / (float)fmax(0.2f, localPlayer->eyePos0.dist(ent->eyePos0))));
}

void ESP::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	switch (rainBow.selected) {
	default:
		doRainbow = false;
		break;
	case 1:
		doRainbow = true;
		break;
	}
	switch (espType.selected) {
	default:
		is2d = false;
		break;
	case 1:
		is2d = true;
		break;
	}
	C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();

	if (localPlayer != nullptr && GameData::canUseMoveKeys()) {
		// Rainbow colors
		{
			if (rcolors[3] < 1) {
				rcolors[0] = 0.2f;
				rcolors[1] = 0.2f;
				rcolors[2] = 1.f;
				rcolors[3] = 1;
			}

			Utils::ApplyRainbow(rcolors, 0.0015f);
		}

		g_Data.forEachEntity(doRenderStuff);
	}
}

void ESP::onLevelRender() {
	/* if (!g_Data.getLocalPlayer())
		return;
	std::vector<vec3_t> posList2;
	// Draw Sims Esp
	g_Data.forEachEntity([&](C_Entity* ent, bool valid) {
		if (Target::isValidTarget(ent) && ent->isPlayer()) {
			posList2.clear();
			// Iterate through phi, theta then convert r,theta,phi to  XYZ
			for (double phi = 0.; phi < 2 * PI; phi += PI / 60.)  // Azimuth [0, 2PI]
			{
				for (double theta = 0.; theta < PI; theta += PI / 60.)  // Elevation [0, PI]
				{
					vec3_t point;
					point.x = 0.2 * cos(phi) * sin(theta);
					point.y = 0.2 * sin(phi) * sin(theta);
					point.z = 0.2 * cos(theta);
					vec3_t curPos = ent->eyePos0;
					curPos.y += 0.5f;
					posList2.push_back(curPos.add(point));
				}
			}
			DrawUtils::setColor(0.1f, 0.9f, 0.1f, 255);
			DrawUtils::drawLinestrip3d(posList2);
		}
	});
	*/
}
