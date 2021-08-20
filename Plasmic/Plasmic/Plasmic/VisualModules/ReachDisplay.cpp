#include "ReachDisplay.h"

void ReachDisplay::CalcHitValue() {
	assertLocalPlayer;
	//Vec3 headpos = game::localPlayer->headpos;

	if (lastHitboxHitPoint.x == 0.f || lastHitboxHitPoint.y == 0.f || lastHitboxHitPoint.z == 0.f)
		return;

	Vec3 headpos = game::localPlayer->actorPosition;
	headpos.y += 0.3f;
//	game::clickGui->sendNotificationf("%f %f %f   %f %f %f", headpos.x, headpos.y, headpos.z, lastHitboxHitPoint.x, lastHitboxHitPoint.y, lastHitboxHitPoint.z);

	lastHitValue = headpos.Distance(lastHitboxHitPoint);

}




char reachText[50];

void ReachDisplay::onRender() {
	if (oneNumber)
		if (showReachText)
			sprintf(reachText, "Reach: %.1f", lastHitValue);
		else
			sprintf(reachText, "%.1f", lastHitValue);
	else
		if (showReachText)
			sprintf(reachText, "Reach: %.3f", lastHitValue);
		else
			sprintf(reachText, "%.3f", lastHitValue);

	size.x = RenderUtils::GetTextWidth(reachText, 1.f * scale);
	size.y = RenderUtils::GetTextWidth("W", 1.0f * scale);
	size.x += 6.f;
	size.y += 6.f;

	RenderUtils::FillRectangle(Rect(pos.x, pos.y, pos.x + size.x, pos.y + size.y), backgroundColor.getColor(), backgroundColor.opacity);

	RenderUtils::RenderText(reachText, Vec2(pos.x + 3.f, pos.y + size.y / 12.f), textColor.getColor(), 1.f * scale, textColor.opacity);
	RenderUtils::FlushText();
}