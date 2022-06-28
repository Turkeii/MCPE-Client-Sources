#include "Tower.h"

#include "../../DrawUtils.h"
uintptr_t HiveBypass12 = Utils::getBase() + 0x8F3895;   // Second one of 89 41 ? 0F B6 42 ? 88 41 ? F2 0F 10 42 ? F2 0F 11 41 ? 8B 42 ? 89 41 ? 8B 42 ? 89 41 ? 8B 42 ? 89 41 ? 8B 42 ? 48 83 C2 ? 89 41 ? 48 83 C1 ? E8 ? ? ? ? 0F B6 43
uintptr_t HiveBypass22 = Utils::getBase() + 0x8F87C7;  // C7 40 ? ? ? ? ? 48 8B 8D ? ? ? ? 48 33 CC E8 ? ? ? ? 4C 8D 9C 24
bool rot;
bool rot1;
Tower::Tower() : IModule(0, Category::WORLD, "Like scaffold, but vertically and a lot faster ") {
	registerFloatSetting("motion", &motion, motion, 0.3f, 1.f);
	registerBoolSetting("Center", &center, false);
	registerBoolSetting("Hive", &rot, false);
	registerBoolSetting("Rotations", &rot1, false);
}


Tower::~Tower() {
}

const char* Tower::getModuleName() {
	return ("Tower");
}
bool Tower::Center() {
	vec3_t yR = vec3_t(floor(g_Data.getLocalPlayer()->getPos()->x), g_Data.getLocalPlayer()->getPos()->y, floor(g_Data.getLocalPlayer()->getPos()->z));
	yR.x += 0.5f;
	// yR.y += 2.3f;
	yR.z += 0.5f;
	g_Data.getLocalPlayer()->setPos(yR);
	return true;
}
bool Tower::tryTower(vec3_t blockBelow) {
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();

	if (input == nullptr)
		return false;

	blockBelow = blockBelow.floor();

	DrawUtils::drawBox(blockBelow, vec3_t(blockBelow).add(1), 0.4f);

	C_Block* block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blockBelow));
	C_BlockLegacy* blockLegacy = (block->blockLegacy);
	if (blockLegacy->material->isReplaceable) {
		vec3_ti blok(blockBelow);

		// Find neighbour
		static std::vector<vec3_ti*> checklist;
		if (checklist.empty()) {
			checklist.push_back(new vec3_ti(0, -1, 0));
			checklist.push_back(new vec3_ti(0, 1, 0));

			checklist.push_back(new vec3_ti(0, 0, -1));
			checklist.push_back(new vec3_ti(0, 0, 1));

			checklist.push_back(new vec3_ti(-1, 0, 0));
			checklist.push_back(new vec3_ti(1, 0, 0));
		}
		bool foundCandidate = false;
		int i = 0;
		for (auto current : checklist) {
			vec3_ti calc = blok.sub(*current);
			if (!((g_Data.getLocalPlayer()->region->getBlock(calc)->blockLegacy))->material->isReplaceable) {
				// Found a solid block to click
				foundCandidate = true;
				blok = calc;
				break;
			}
			i++;
		}
		if (foundCandidate && GameData::isKeyDown(*input->spaceBarKey)) {
			vec3_t moveVec;
			moveVec.x = g_Data.getLocalPlayer()->velocity.x;
			moveVec.y = motion;
			moveVec.z = g_Data.getLocalPlayer()->velocity.z;
			g_Data.getLocalPlayer()->lerpMotion(moveVec);
			bool idk = true;
			if (center) Center();
			g_Data.getCGameMode()->buildBlock(&blok, i, idk);

			return true;
		}
	}
	return false;
}

void Tower::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	if (rot) {
		g_Data.getLocalPlayer()->pointingStruct->rayHitType = 0;
		Utils::nopBytes((unsigned char*)HiveBypass12, 3);
		Utils::patchBytes((unsigned char*)HiveBypass22, (unsigned char*)"\xC7\x40\x18\x00\x00\x00\x00", 7);
	}
	if (g_Data.getLocalPlayer() == nullptr)
		return;
	if (!g_Data.canUseMoveKeys())
		return;
	auto selectedItem = g_Data.getLocalPlayer()->getSelectedItem();
	if (!selectedItem->isValid() || !(*selectedItem->item)->isBlock())  // Block in hand?
		return;

	vec3_t blockBelow = g_Data.getLocalPlayer()->eyePos0;  // Block below the player
	blockBelow.y -= g_Data.getLocalPlayer()->height;
	blockBelow.y -= 0.5f;

	// Adjustment by velocity
	float speed = g_Data.getLocalPlayer()->velocity.magnitudexy();
	vec3_t vel = g_Data.getLocalPlayer()->velocity;
	vel.normalize();  // Only use values from 0 - 1

	if (!tryTower(blockBelow)) {
		if (speed > 0.05f) {
			blockBelow.z -= vel.z * 0.4f;
			if (!tryTower(blockBelow)) {
				blockBelow.x -= vel.x * 0.4f;
				if (!tryTower(blockBelow) && g_Data.getLocalPlayer()->isSprinting()) {
					blockBelow.z += vel.z;
					blockBelow.x += vel.x;
					tryTower(blockBelow);
				}
			}
		}
	}
}
void Tower::onDisable() {
	Utils::patchBytes((unsigned char*)HiveBypass12, (unsigned char*)"\x89\x41\x18", 3);
	Utils::patchBytes((unsigned char*)HiveBypass22, (unsigned char*)"\xC7\x40\x18\x03\x00\x00\x00", 7);
}
void Tower::onPlayerTick(C_Player* plr) {
	if (rot1) {
		plr->pitch = 90;
	}
}