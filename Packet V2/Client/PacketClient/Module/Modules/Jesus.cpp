#include "../../Module/ModuleManager.h"
#include "../../../Utils/Logger.h"
#include "Jesus.h"

Jesus::Jesus() : IModule(0, Category::MOVEMENT, "Allows you to walk on Liquids") {
	registerEnumSetting("Mode", &mode, 0);
	mode.addEntry("Solid", 0);
	mode.addEntry("Bounce", 1);
	registerFloatSetting("Height", &height, height, 0.1, 3);
}

Jesus::~Jesus() {
}

const char* Jesus::getRawModuleName() {
	return "Jesus";
}

const char* Jesus::getModuleName() {
	if (mode.getSelectedValue() == 0) { // Solid
		name = std::string("Jesus ") + std::string(GRAY) + std::string("Solid");
		return name.c_str();
	} else if (mode.getSelectedValue() == 1) {  // BouncY
		name = std::string("Jesus ") + std::string(GRAY) + std::string("Bounce");
		return name.c_str();
	}
}

bool Jesus::tryJesus(vec3_t blockBelow) {
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	auto player = g_Data.getLocalPlayer();
	blockBelow = blockBelow.floor();

	C_Block* block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blockBelow));
	C_BlockLegacy* blockLegacy = (block->blockLegacy);
	if (blockLegacy->material->isLiquid) {
		vec3_ti blok(blockBelow);

		static std::vector<vec3_ti*> checklist;
		if (checklist.empty()) {
			checklist.push_back(new vec3_ti(0, -1, 0));
			checklist.push_back(new vec3_ti(0, 1, 0));

			checklist.push_back(new vec3_ti(0, 0, -1));
			checklist.push_back(new vec3_ti(0, 0, 1));

			checklist.push_back(new vec3_ti(-1, 0, 0));
			checklist.push_back(new vec3_ti(1, 0, 0));
		}

		bool foundWater = false;
		int i = 0;
		for (auto current : checklist) {
			vec3_ti calc = blok.sub(*current);
			bool Y = ((g_Data.getLocalPlayer()->region->getBlock(calc)->blockLegacy))->material->isLiquid;
			if (!((g_Data.getLocalPlayer()->region->getBlock(calc)->blockLegacy))->material->isLiquid) {
				foundWater = true;
				blok = calc;
				break;
			}
			i++;
		}
		if (foundWater) {
			if (!GameData::isKeyDown(*input->sneakKey)) {
				if (mode.getSelectedValue() == 0) {  // Solid
					if (smthwateridk) {
						player->velocity.y = 0.0f;
						player->onGround = true;
					}
				}
				if (mode.getSelectedValue() == 1) {  // Bouncy boi
					player->velocity.y = height;
				}
			}
			return true;
		}
	}
	return false;
}

void Jesus::onTick(C_GameMode* gm) {
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	auto freecam = moduleMgr->getModule<Freecam>();
	auto flight = moduleMgr->getModule<Flight>();
	auto freeTP = moduleMgr->getModule<FreeTP>();
	if (g_Data.getLocalPlayer() == nullptr)
		return;

	if (freecam->isEnabled() || freeTP->isEnabled() || flight->isEnabled())
		return;

	if (!GameData::isKeyDown(*input->sneakKey)) {
		if (gm->player->isInWater() || gm->player->isInLava()) {
			smthwateridk = false;
			gm->player->velocity.y = 0.2;
		} else {
			smthwateridk = true;
		}
	}

	// Adjustment by velocity
	float speed = g_Data.getLocalPlayer()->velocity.magnitudexz();
	vec3_t vel = g_Data.getLocalPlayer()->velocity;
	vel = vel.normalize();

	vec3_t blockBelow = g_Data.getLocalPlayer()->eyePos0;  // Block below the player
	blockBelow.y -= g_Data.getLocalPlayer()->height;
	blockBelow.y -= 0.0;

	if (!tryJesus(blockBelow)) {
		if (speed > 0.05f) {  // Are we actually walking?
			blockBelow.z -= vel.z * 0.4f;
			if (!tryJesus(blockBelow)) {
				blockBelow.x -= vel.x * 0.4f;
				if (!tryJesus(blockBelow) && g_Data.getLocalPlayer()->isSprinting()) {
					blockBelow.z += vel.z;
					blockBelow.x += vel.x;
					tryJesus(blockBelow);
				}
			}
		}
	}
}