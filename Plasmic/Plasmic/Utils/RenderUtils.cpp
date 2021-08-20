#include "RenderUtils.h"
#include "../SDK/game.h"


bool RenderUtils::isMinecraftia = false;
extern bool LazyGuiRedraw;

class MinecraftUIRenderContext* RenderUtils::CachedContext = nullptr; //Resolve Compile Error
struct BitmapFont* RenderUtils::CachedFont = nullptr;

void RenderUtils::SetContext(class MinecraftUIRenderContext* Context, struct BitmapFont* Font) {
	CachedContext = Context;
	CachedFont = Font;
}

void RenderUtils::SetFont(bool minecraftiafont) {
	if (minecraftiafont) {
		RenderUtils::isMinecraftia = true;
		RenderUtils::CachedFont = game::minecraftGame->minecraftFont;
	ClickGui::sendNotificationf("Switched to Minecraftia font", (int)minecraftiafont);
	}
	else {
		RenderUtils::isMinecraftia = false;
		if (game::minecraftGame->fontRepository->fontList->font1->font->fontName.reservedLenght > 15 && game::minecraftGame->fontRepository->fontList->font1->font->smoothbeone == 1.f)
			CachedFont = game::minecraftGame->fontRepository->fontList->font1->font;
		else if (game::minecraftGame->fontRepository->fontList->font2->font->fontName.reservedLenght > 15 && game::minecraftGame->fontRepository->fontList->font1->font->smoothbeone == 1.f)
			CachedFont = game::minecraftGame->fontRepository->fontList->font2->font;
		else if (game::minecraftGame->fontRepository->fontList->font3->font->fontName.reservedLenght > 15 && game::minecraftGame->fontRepository->fontList->font1->font->smoothbeone == 1.f)
			CachedFont = game::minecraftGame->fontRepository->fontList->font3->font;
		else if (game::minecraftGame->fontRepository->fontList->font4->font->fontName.reservedLenght > 15 && game::minecraftGame->fontRepository->fontList->font1->font->smoothbeone == 1.f)
			CachedFont = game::minecraftGame->fontRepository->fontList->font4->font;
		else if (game::minecraftGame->fontRepository->fontList->smooth1->font->fontName.reservedLenght > 15 && game::minecraftGame->fontRepository->fontList->font1->font->smoothbeone == 1.f)
			CachedFont = game::minecraftGame->fontRepository->fontList->smooth1->font;
		else if (game::minecraftGame->fontRepository->fontList->smooth2->font->fontName.reservedLenght > 15 && game::minecraftGame->fontRepository->fontList->font1->font->smoothbeone == 1.f)
			CachedFont = game::minecraftGame->fontRepository->fontList->smooth2->font;
		else {
			if (game::minecraftGame->fontRepository->fontList->font1->font->fontName.reservedLenght > 15)
				CachedFont = game::minecraftGame->fontRepository->fontList->font1->font;
			else if (game::minecraftGame->fontRepository->fontList->font2->font->fontName.reservedLenght > 15)
				CachedFont = game::minecraftGame->fontRepository->fontList->font2->font;
			else if (game::minecraftGame->fontRepository->fontList->font3->font->fontName.reservedLenght > 15)
				CachedFont = game::minecraftGame->fontRepository->fontList->font3->font;
			else if (game::minecraftGame->fontRepository->fontList->font4->font->fontName.reservedLenght > 15)
				CachedFont = game::minecraftGame->fontRepository->fontList->font4->font;
			else if (game::minecraftGame->fontRepository->fontList->smooth1->font->fontName.reservedLenght > 15)
				CachedFont = game::minecraftGame->fontRepository->fontList->smooth1->font;
			else if (game::minecraftGame->fontRepository->fontList->smooth2->font->fontName.reservedLenght > 15)
				CachedFont = game::minecraftGame->fontRepository->fontList->smooth2->font;
			else {
				ClickGui::sendNotificationf("could not enable smooth font.");
				CachedFont = game::minecraftGame->minecraftFont;
				RenderUtils::isMinecraftia = true;
				return;
			}
		}
	ClickGui::sendNotificationf("Switched to Smooth font", (int)minecraftiafont);
	}
}

void RenderUtils::FlushText() {
	if (CachedContext != nullptr) CachedContext->flushText(0);
}


float RenderUtils::GetTextWidth(const char* text, float textSize) {
	if (CachedContext != nullptr) {
		Text myText(text);

		if (isMinecraftia) {
			float tw = 0.f;
			if (text == "W") {
				text = "Wl";
				tw = 3.5f;
			}
			else if (text == "W.") {
				text = "Wl.";
				tw = 3.5f;
			}

			textSize /= 1.30f;
			return CachedContext->getLineLength(CachedFont, &myText, textSize, false) + tw;
		}

		return CachedContext->getLineLength(CachedFont, &myText, textSize, false);
	}
	return 0.f;
}

void RenderUtils::FillRectangle(Rect position, MC_Color color, float alpha) {
	if (LazyGuiRedraw && alpha > 0.1f)
		alpha += 0.35f;
	if (CachedContext != nullptr) 
		CachedContext->fillRectangle(Rect(position.x, position.z, position.y, position.w), color, alpha);
	
}

void RenderUtils::DrawRectangle(Rect position, MC_Color color, float alpha, float lineWidth) {

	if (CachedContext != nullptr) {
		lineWidth /= 2;
		FillRectangle(Rect(position.x - lineWidth, position.y - lineWidth, position.z + lineWidth, position.y + lineWidth), color, alpha);
		FillRectangle(Rect(position.x - lineWidth, position.y, position.x + lineWidth, position.w), color, alpha);
		FillRectangle(Rect(position.z - lineWidth, position.y, position.z + lineWidth, position.w), color, alpha);
		FillRectangle(Rect(position.x - lineWidth, position.w - lineWidth, position.z + lineWidth, position.w + lineWidth), color, alpha);
	}
}


static uintptr_t TextRenderCaretMeasureData = 0xFFFFFFFF;

char lastChar;
void useText(char* gamer) {
	memcpy(&lastChar, gamer, 1);
}

void RenderUtils::RenderText(const char* text, Vec2 textPos, MC_Color color, float textSize, float alpha) {
	if (CachedContext == nullptr || CachedFont == nullptr)
		return;
	//if (LazyGuiRedraw)
	//	alpha = 1.0f;

	
	Rect pos(textPos.x, textPos.x + 100, textPos.y, textPos.y + 100);
	Text myText(text);

	if (isMinecraftia) {
		pos = Rect(textPos.x, textPos.x + 100, textPos.y + 1.5f, textPos.y + 100);
		textSize /= 1.3f;
	}
	
	//idk...
	useText(myText.getText());
	CachedContext->drawText(CachedFont, &pos, &myText, color, alpha, 0, &textSize, &TextRenderCaretMeasureData);
}
