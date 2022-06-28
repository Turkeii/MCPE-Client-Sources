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
#include "../../path/PathFinder.h"
#include "../../path/PathMovementController.h"
#include "../../path/goals/PathGoal.h"
#include "../../path/goals/PathGoalXZ.h"

using json = nlohmann::json;


TestModule::TestModule() : IModule(0, Category::MISC, "For testing purposes") {
	registerBoolSetting("Only While Jumping", &this->onlyjump, this->onlyjump);
}

TestModule::~TestModule() {
}

const char* TestModule::getModuleName() {
	return "TestModule";
}


void TestModule::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
}
void TestModule::onTick(C_GameMode* gm) {  // Swap list
	C_TextPacket textPacket;
	textPacket.message.setText("Test");
	textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
	textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
	g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
}
