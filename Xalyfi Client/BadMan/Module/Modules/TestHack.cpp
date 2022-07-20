#include "TestHack.h"

TestHack::TestHack() : IModule(0x0, Category::MOVEMENT, "TestHack") {
	registerFloatSetting("Speed", &this->speed, this->speed, 0.5f, 3.f);
	registerFloatSetting("Y-Start", &this->ystart, this->ystart, 0.5f, 2.f);
	registerFloatSetting("Y-Flying", &this->yflying, this->yflying, 0.5f, 2.f);
	registerIntSetting("TP-Delay", &this->delaytp, this->delaytp, 1, 10);
	registerIntSetting("TP-Distance", &this->tpdist, this->tpdist, 1, 10);
}

TestHack::~TestHack() {
}

const char* TestHack::getModuleName() {
	return "TestHack";
}

bool TestHack::isFlashMode() {
	return true;
}

void TestHack::onEnable() {
	g_Data.getLocalPlayer()->setPos((*g_Data.getLocalPlayer()->getPos()).add(vec3_t(0.f, ystart, 0.f)));
}

void TestHack::onTick(C_GameMode* gm) {
	float calcYaw = (gm->player->yaw + 90) * (PI / 180);

	gameTick++;

	vec3_t pos = *g_Data.getLocalPlayer()->getPos();
	pos.y += 1.3f;
	C_MovePlayerPacket a(g_Data.getLocalPlayer(), pos);
	g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);
	pos.y -= 1.3f;
	C_MovePlayerPacket a2(g_Data.getLocalPlayer(), pos);
	g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a2);

	vec3_t moveVec;
	moveVec.x = cos(calcYaw) * speed;
	moveVec.y = -0;
	moveVec.z = sin(calcYaw) * speed;

	gm->player->lerpMotion(moveVec);

	if (gameTick >= delaytp) {
		gameTick = 0;
		float yaw = gm->player->yaw * (PI / 180);
		float length = tpdist;

		float x = -sin(yaw) * length;
		float z = cos(yaw) * length;

		gm->player->setPos(pos.add(vec3_t(x, yflying, z)));
	}
}

void TestHack::onDisable() {
	g_Data.getLocalPlayer()->velocity = vec3_t(0, 0, 0);
}
