#include "PathCommand.h"

bool PathCommand::execute(std::vector<std::string>* args) {
	assertTrue(args->size() > 1);
	static auto mod = moduleMgr->getModule<FollowPath>();
	if (mod->isEnabled()) {
		mod->setEnabled(false);
		return true;
	}

	auto cmd = args->at(1);
	if (cmd == "y") {
		assertTrue(args->size() > 2);
		int yLevel = assertInt(args->at(2));
		assertTrue(yLevel > -64 && yLevel < 321);

		mod->goal = std::make_unique<PathGoalY>((float)yLevel);
		mod->setEnabled(true);

		clientMessageF("Starting search...");
		return true;
	}
	if (cmd == "xz") {
		assertTrue(args->size() > 3);
		int x = assertInt(args->at(2));
		int z = assertInt(args->at(3));

		mod->goal = std::make_unique<PathGoalXZ>(vec3_ti(x, 0, z));
		mod->setEnabled(true);

		clientMessageF("Starting search...");
		return true;
	}
	if (cmd == "xyz") {
		assertTrue(args->size() > 4);
		int x = assertInt(args->at(2));
		int y = assertInt(args->at(3));
		int z = assertInt(args->at(4));

		mod->goal = std::make_unique<PathGoalXYZ>(vec3_ti(x, y, z));
		mod->setEnabled(true);

		clientMessageF("Starting search...");
		return true;
	}
	if (cmd == "e" || cmd == "entity") {
		std::string nameOfPlayer = args->at(2);
		assertTrue(!nameOfPlayer.empty());
		std::string nameOfPlayerLower = std::string(nameOfPlayer);
		std::transform(nameOfPlayerLower.begin(), nameOfPlayerLower.end(), nameOfPlayerLower.begin(), ::tolower);
		nameOfPlayerLower = Utils::sanitize(nameOfPlayerLower);

		vec3_t pos{};
		auto playerFinder = [&](C_Entity* e, bool isNewList) {
			if (e == g_Data.getLocalPlayer())
				return;
			std::string name(e->getNameTag()->getText());
			std::transform(name.begin(), name.end(), name.begin(), ::tolower);

			if (name.find(nameOfPlayerLower) == std::string::npos)
				return;

			pos = e->eyePos0;
		};
		g_Data.forEachEntity(playerFinder);

		if (pos.iszero()) {
			clientMessageF("%s Player \"%s\" could not be found!", WHITE, nameOfPlayer.c_str());
			return true;
		}

		vec3_ti endNode((int)floorf(pos.x), (int)roundf(pos.y - 1.62f), (int)floorf(pos.z));
		mod->goal = std::make_unique<PathGoalXYZ>(endNode);
		mod->setEnabled(true);
		clientMessageF("Starting search...");
		return true;
	}

	return false;
}