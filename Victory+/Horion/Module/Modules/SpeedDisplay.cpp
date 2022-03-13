#include "SpeedDisplay.h"

Bps::Bps() : IModule(0, Category::GUI, "Speed counter!!!") {
	registerFloatSetting("X", &this->bpsX, this->bpsX, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.x);
	registerFloatSetting("Y", &this->bpsY, this->bpsY, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.y);
	//registerFloatSetting("Scale", &this->scale, this->scale, 0.5f, 1.5f);
}

Bps::~Bps() {
}

const char* Bps::getModuleName() {
	return ("Displays");
}

void Bps::onMove(C_MoveInputHandler* input) {
}
void Bps::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	vec3_t vel = gm->player->velocity;
	if (vel.x < 0.f)
		vel.x *= -1.f;
	if (vel.y < 0.f)
		vel.y *= -1.f;
	if (vel.z < 0.f)
		vel.z *= -1.f;

	speed = sqrtf((vel.x * vel.x) + (vel.z * vel.z));
	speed *= 36.6f;

	if (!gm->player->onGround)
		speed /= 1.5f;
}
void Bps::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	if (g_Data.getClientInstance()->isInGame()) {
		float yVal = bpsY;
		float xVal = bpsX;

		auto Server = g_Data.getRakNetInstance();
		if (Server == nullptr) return;

		std::string IP = Server->serverIp.getText();
		std::string Port = std::to_string(Server->serverPort).c_str();

		vec2_t textPos = vec2_t(xVal, yVal);

		if (Server->serverIp.getTextLength() < 1) {
			IP = "Local World";
		}
		std::string ServerText = "Server: " + IP + ", " + Port;

		vec3_t* pos = g_Data.getLocalPlayer()->getPos();

		std::string coords = "Position : " + std::to_string((int)floorf(pos->x)) + ", " + std::to_string((int)floorf(pos->y)) + ", " + std::to_string((int)floorf(pos->z));
		//std::string Ncoords = "NetherPosition : " + std::to_string((int)floorf(pos->x + 0.001) * 8) + ", " + std::to_string((int)floorf(pos->y)) + ", " + std::to_string((int)floorf(pos->z + 0.001) / 8);

		int health = g_Data.getLocalPlayer()->getHealth();
		auto healthstring3 = std::to_string(health);
		std::string health2 = "Health : " + healthstring3;

		std::string BpsText = "Speed : " + std::string(std::to_string((int)speed)) + " M/S";

		DrawUtils::drawText(vec2_t(bpsX, bpsY - 10), &BpsText, MC_Color(1.f, 1.f, 1.f), scale);
		DrawUtils::drawText(vec2_t(bpsX, bpsY), &health2, MC_Color(1.f, 1.f, 1.f), scale);
		DrawUtils::drawText(vec2_t(bpsX, bpsY - 30.f), &coords, MC_Color(1.f, 1.f, 1.f), scale);
		DrawUtils::drawText(vec2_t(bpsX, bpsY - 20.f), &ServerText, MC_Color(1.f, 1.f, 1.f), scale);
		//DrawUtils::drawText(vec2_t(bpsX, bpsY - 30.f), &Ncoords, MC_Color(1.f, 1.f, 1.f), scale);
		//DrawUtils::drawText(vec2_t(bpsX, bpsY - 30.f), &blockS, MC_Color(1.f, 1.f, 1.f), scale);
		//DrawUtils::drawText(vec2_t(bpsX, bpsY + 10.f), &item, MC_Color(1.f, 1.f, 1.f), scale);


	}
}
void Bps::onDisable() {
	auto player = g_Data.getLocalPlayer();
}
