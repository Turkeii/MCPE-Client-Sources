#include "SpeedCounter.h"
#include <cmath>

char speedText[20];



/*
void SpeedCounter::onTick(Gamemode* gm) {
	float speed = 0.f;
	Vec3 vel = game::localPlayer->velocity2;

	if (vel.x < 0.f)
		vel.x *= -1.f;
	if (vel.z < 0.f)
		vel.z *= -1.f;

	speed = sqrtf((vel.x * vel.x) + (vel.z * vel.z));
	speed *= 20.f;

	

	sprintf(speedText, "%.3f blocks/s", speed);
}*/
void SpeedCounter::onTick(Gamemode* gm) {
	float speed = 0.f;
	Vec3 vel = game::localPlayer->velocity;

	if (vel.x < 0.f)
		vel.x *= -1.f;
	if (vel.y < 0.f)
		vel.y *= -1.f;
	if (vel.z < 0.f)
		vel.z *= -1.f;

	speed = sqrtf((vel.x * vel.x) + (vel.z * vel.z));
	speed *= 36.63f;

	if (!game::localPlayer->isOnGround)
		speed /= 1.5f;

	sprintf(speedText, "%.3f blocks/s", speed);
}

/*
static Vec3 LastPos;
static long long LastSec = 0;
static float speed = 0.f;
void SpeedCounter::onTick(Gamemode* gm) {
	Vec3 vel = game::localPlayer->actorPosition;
	speed += Vec2(vel.x, vel.z).Distance(Vec2(LastPos.x, LastPos.z));
	LastPos = vel;

	if (LastSec < time(NULL)) {
		LastSec = time(NULL);
		sprintf(speedText, "%.3f blocks/s", speed);
		speed = 0.f;
	}
	
}
*/

void SpeedCounter::onRender() {
	

	size.x = RenderUtils::GetTextWidth(speedText, 1.f * scale);
	size.y = RenderUtils::GetTextWidth("W", 1.0f * scale);
	size.x += 6.f;
	size.y += 6.f;

	RenderUtils::FillRectangle(Rect(pos.x, pos.y, pos.x + size.x, pos.y + size.y), backgroundColor.getColor(), backgroundColor.opacity);

	RenderUtils::RenderText(speedText, Vec2(pos.x + 3.f, pos.y + size.y / 12.f), textColor.getColor(), 1.f * scale, textColor.opacity);
	RenderUtils::FlushText();
}