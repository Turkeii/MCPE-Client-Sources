#include "TestModule.h"
#include "../../../Utils/Logger.h"
#include "../../../Utils/VoxelIntersector.h"
#include "../../DrawUtils.h"
#include "../../../SDK/MatrixStack.h"
#include <deque>
#include <array>
#include <unordered_set>
#include <glm/mat4x4.hpp>
#include <glm/trigonometric.hpp>			//radians
#include <glm/ext/matrix_transform.hpp>		// perspective, translate, rotate
#include <glm/ext/matrix_relational.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "../../../Utils/Json.hpp"

using json = nlohmann::json;


TestModule::TestModule() : IModule(0, Category::TEAMS, "JOIN THE DISCORD") {
	enum1 = SettingEnum(this)
		.addEntry(EnumEntry("1", 1))
		.addEntry(EnumEntry("2", 2))
		.addEntry(EnumEntry("3", 3));
	
	registerFloatSetting("float1", &this->float1, 0, -10, 10);
	registerIntSetting("int1", &this->int1, 0, -10, 10);
	registerEnumSetting("Enum1", &enum1, 0);
	registerBoolSetting("bool1", &this->bool1, true);
}

TestModule::~TestModule() {
}

const char* TestModule::getModuleName() {
	return "discord.gg/killaura";
}

void TestModule::onEnable() {
	clientMessageF("discord.gg/killaura leaked this! rxversed#0001");
}

void TestModule::onTick(C_GameMode* gm) {
}

void TestModule::onDisable() {

}