#include "Bps.h"

Bps::Bps() : IModule(0, Category::GUI, "Speed counter") {
	registerFloatSetting("bpsX", &this->bpsX, this->bpsX, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.x);
	registerFloatSetting("bpsY", &this->bpsY, this->bpsY, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.y);
	registerFloatSetting("Scale", &this->scale, this->scale, 0.5f, 1.5f);
}

Bps::~Bps() {
}

const char* Bps::getModuleName() {
	return ("Bps");
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
			auto theme2 = moduleMgr->getModule<AltTheme>();
			float yVal = bpsY;
			float xVal = bpsX;

			
			std::string BpsText = "Blocks Per Second: " + std::string(std::to_string((int)speed));

			DrawUtils::drawText(vec2_t(bpsX, bpsY), &BpsText, MC_Color(theme2->rFloat, theme2->gFloat, theme2->bFloat), scale);
		}
	}
void Bps::onDisable() {
	auto player = g_Data.getLocalPlayer();
}
