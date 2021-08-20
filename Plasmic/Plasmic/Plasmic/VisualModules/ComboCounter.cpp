#include "ComboCounter.h"
#include <ctime>





char comboText[50];

void ComboCounter::onRender() {
	assertLocalPlayer;
	if (game::localPlayer->hurtAnimationStatus > 0)
		comboValue = 0;


	if (showComboText)
		sprintf(comboText, "Combo: %i", comboValue);
	else
		sprintf(comboText, "%i", comboValue);

	size.x = RenderUtils::GetTextWidth(comboText, 1.f * scale);
	size.y = RenderUtils::GetTextWidth("W", 1.0f * scale);
	size.x += 6.f;
	size.y += 6.f;

	RenderUtils::FillRectangle(Rect(pos.x, pos.y, pos.x + size.x, pos.y + size.y), backgroundColor.getColor(), backgroundColor.opacity);

	RenderUtils::RenderText(comboText, Vec2(pos.x + 3.f, pos.y + size.y / 12.f), textColor.getColor(), 1.f * scale, textColor.opacity);
	RenderUtils::FlushText();
}


std::chrono::high_resolution_clock attackClock;
std::chrono::steady_clock::time_point lastPlayerHit = attackClock.now();
void ComboCounter::onAttack(Actor* act) {
	if (std::chrono::duration<float>(attackClock.now() - lastPlayerHit).count() > 0.5f) {
		comboValue += 1;
		lastPlayerHit = attackClock.now();
	}
}




void ComboCounter::onTick(Gamemode* gm) {
	if (std::chrono::duration<float>(attackClock.now() - lastPlayerHit).count() > 2.f)
		comboValue = 0;
}