#include "Blink.h"
#include "../../DrawUtils.h"

#include "../../../SDK/CCamera.h"

Blink::Blink() : IModule('L', Category::MISC, "Stops you from sending packets and then sends them in a bunch") {
}

Blink::~Blink() {
	this->getMovePlayerPacketHolder()->clear();
	this->getPlayerAuthInputPacketHolder()->clear();
}

const char* Blink::getModuleName() {
	return ("Blink");
}

void Blink::onTick(C_GameMode* gm) {
	if (g_Data.getLocalPlayer() == nullptr) return;
//	gm->player->fallDistance = 0.f;

	vec3_t floorPos = *g_Data.getLocalPlayer()->getPos();
	floorPos.y = g_Data.getLocalPlayer()->getAABB()->lower.y + 0.1f;

	linePoints.push_back(floorPos);



}



void Blink::onEnable() {
	if (g_Data.getLocalPlayer() == nullptr) return;
//	startPos = g_Data.getLocalPlayer()->aabb.lower;
//	startPosTop = g_Data.getLocalPlayer()->aabb.upper;

}

void Blink::onDisable() {
	if (g_Data.getLocalPlayer() == nullptr) return;

	linePoints.clear();
		

}


void Blink::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	if (g_Data.getLocalPlayer() == nullptr) return;
	

	if (!linePoints.empty()) {
		
		DrawUtils::drawText(DrawUtils::worldToScreen(linePoints[0]), &std::string("0"), MC_Color(0.f, 1.f, 1.f, 1.f));
	}


//	if (startPos != nullptr && startPosTop != nullptr) {
		
	//	DrawUtils::drawBox(startPos, startPosTop (float)fmax(0.4f, 1 / (float)fmax(1, (*localPlayer->getPos()).dist(*ent->getPos()) * 3.f)));
		//DrawUtils::drawBox(startPos, startPosTop, (float)fmax(0.4f, 1 / (float)fmax(1, (*g_Data.getLocalPlayer()->getPos()).dist(startPos) * 3.f)));
	
	
	//}

}



void Blink::onLevelRender() {
	
	if (g_Data.getLocalPlayer() == nullptr) return;

/*
	auto cameraMgr = g_Data.getClientInstance()->getCameraManager();
	if (cameraMgr == nullptr)
		return;
	auto cam = cameraMgr->getCameraOrDebugCamera();
	if (cam == nullptr)
		return;
	vec3_t forward{};
	cam->getForwardVector(&forward);
	//*/
	//const vec3_t origin = g_Data.getClientInstance()->levelRenderer->origin.add(forward.mul(0.2f) /*place the start of the line slightly forward so it won't get clipped*/);
	if (!linePoints.empty()) {
		DrawUtils::setColor(0, 255, 255, 1.f);
		DrawUtils::drawLinestrip3d(linePoints);
		

	}
	
	/*	g_Data.forEachEntity([&](C_Entity* ent, bool valid) {
		if (ent != g_Data.getLocalPlayer() && Target::isValidTarget(ent)) {
			DrawUtils::setColor(255, 0, 0, 1);
			DrawUtils::drawLine3d(origin, *ent->getPos());
		}
	});*/
}