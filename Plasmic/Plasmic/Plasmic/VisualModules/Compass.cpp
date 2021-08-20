#include "Compass.h"
#include <cmath>


void Compass::onRender() {
	if (game::localPlayer == 0)
		return;
	
	float middle = (size.x / 2.f) + pos.x;
	char text[8] = { 0 };
	float rotation = game::localPlayer->cameraRotation;
	if (isthirdperson)
		if (rotation < 0)
			rotation += 180.f;
		else if (rotation > 0)
			rotation += 180.f;

	size.x = compassWidth * scale;
	size.y = 23.f * scale;
	RenderUtils::FillRectangle(Rect(pos.x, pos.y, pos.x + size.x, pos.y + size.y), backgroundColor.getColor(), backgroundColor.opacity);

	int compassStart = (int)round(rotation);
	sprintf(text, "%d", compassStart);
	RenderUtils::RenderText(text, Vec2(middle - (RenderUtils::GetTextWidth(text, 0.8f*scale) / 2.f), pos.y), textColor.getColor(), 0.8f*scale, textColor.opacity);

	
	
	for (int compass = -compassAmount; compass < compassAmount; compass++) {
		int compassValue = compassStart + compass;
		if (compassValue < 0)
			compassValue += 360;
		if (compassValue > 359)
			compassValue -= 360;
		
		//this is easily the WORST fix ever
		switch (compassValue) {
		case 0:
		case 15:
		case 30:
		case 45:
		case 60:
		case 75:
		case 90:
		case 105:
		case 120:
		case 135:
		case 150:
		case 165:
		case 180:
		case 195:
		case 210:
		case 225:
		case 240:
		case 255:
		case 270:
		case 285:
		case 300:
		case 315:
		case 330:
		case 345:
			break;
		default:
			continue;
		}
			//we have a 15
			float loc = ((compass + compassAmount) * size.x) / (compassAmount + compassAmount);
			loc += pos.x;
		//	Logf("%d", compass);
			float nscale = scale;
			float nalpha = 1.f;
			if (compass < 0) {
				int game = compass + compassAmount;
					if (game <= fadeAt) {
						nscale = (float)(game * fadeAt) / (fadeAt * fadeAt);
						nalpha = nscale - 0.25f;
						nscale *= scale;
					}
			} else if (compass > 0) {
				int game = (compass - (compassAmount - fadeAt));
					if (game > 0) {
						game = fadeAt - game;
						nscale = (float)(game * fadeAt) / (fadeAt * fadeAt);
						nalpha = nscale - 0.25f;
						nscale *= scale;
					}
			}
				
			switch (compassValue) {
			case 0:
				RenderUtils::RenderText("N", Vec2(loc - (RenderUtils::GetTextWidth("N", 0.75f*nscale) / 2.f), pos.y + (14.0f * nscale)), textColor.getColor(), 0.75f*nscale, textColor.opacity * nalpha);
				RenderUtils::FillRectangle(Rect(loc - 0.5f, pos.y + (8.0f * nscale), loc + 0.5f, pos.y + (14.0f * nscale)), textColor.getColor(), textColor.opacity * nalpha);
				break;
			case 45:
				RenderUtils::RenderText("NE", Vec2(loc - (RenderUtils::GetTextWidth("NE", 0.75f*nscale) / 2.f), pos.y + (14.0f * nscale)), textColor.getColor(), 0.75f*nscale, textColor.opacity * nalpha);
				RenderUtils::FillRectangle(Rect(loc - 0.5f, pos.y + (8.0f * nscale), loc + 0.5f, pos.y + (14.0f * nscale)), textColor.getColor(), textColor.opacity * nalpha);
				break;
			case 90:
				RenderUtils::RenderText("E", Vec2(loc - (RenderUtils::GetTextWidth("E", 0.75f*nscale) / 2.f), pos.y + (14.0f * nscale)), textColor.getColor(), 0.75f*nscale, textColor.opacity * nalpha);
				RenderUtils::FillRectangle(Rect(loc - 0.5f, pos.y + (8.0f * nscale), loc + 0.5f, pos.y + (14.0f * nscale)), textColor.getColor(), textColor.opacity * nalpha);
				break;
			case 135:
				RenderUtils::RenderText("SE", Vec2(loc - (RenderUtils::GetTextWidth("SE", 0.75f*nscale) / 2.f), pos.y + (14.0f * nscale)), textColor.getColor(), 0.75f*nscale, textColor.opacity * nalpha);
				RenderUtils::FillRectangle(Rect(loc - 0.5f, pos.y + (8.0f * nscale), loc + 0.5f, pos.y + (14.0f * nscale)), textColor.getColor(), textColor.opacity * nalpha);
				break;
			case 180:
				RenderUtils::RenderText("S", Vec2(loc - (RenderUtils::GetTextWidth("S", 0.75f*nscale) / 2.f), pos.y + (14.0f * nscale)), textColor.getColor(), 0.75f*nscale, textColor.opacity * nalpha);
				RenderUtils::FillRectangle(Rect(loc - 0.5f, pos.y + (8.0f * nscale), loc + 0.5f, pos.y + (14.0f * nscale)), textColor.getColor(), textColor.opacity * nalpha);
				break;
			case 225:
				RenderUtils::RenderText("SW", Vec2(loc - (RenderUtils::GetTextWidth("SW", 0.75f*nscale) / 2.f), pos.y + (14.0f * nscale)), textColor.getColor(), 0.75f*nscale, textColor.opacity * nalpha);
				RenderUtils::FillRectangle(Rect(loc - 0.5f, pos.y + (8.0f * nscale), loc + 0.5f, pos.y + (14.0f * nscale)), textColor.getColor(), textColor.opacity * nalpha);
				break;
			case 270:
				RenderUtils::RenderText("W", Vec2(loc - (RenderUtils::GetTextWidth("W", 0.75f*nscale) / 2.f), pos.y + (14.0f * nscale)), textColor.getColor(), 0.75f*nscale, textColor.opacity * nalpha);
				RenderUtils::FillRectangle(Rect(loc - 0.5f, pos.y + (8.0f * nscale), loc + 0.5f, pos.y + (14.0f * nscale)), textColor.getColor(), textColor.opacity * nalpha);
				break;
			case 315:
				RenderUtils::RenderText("NW", Vec2(loc - (RenderUtils::GetTextWidth("NW", 0.75f*nscale) / 2.f), pos.y + (14.0f * nscale)), textColor.getColor(), 0.75f*nscale, textColor.opacity * nalpha);
				RenderUtils::FillRectangle(Rect(loc - 0.5f, pos.y + (8.0f * nscale), loc + 0.5f, pos.y + (14.0f * nscale)), textColor.getColor(), textColor.opacity * nalpha);
				break;
			default:
				sprintf(text, "%d", compassValue);
				RenderUtils::RenderText(text, Vec2(loc - ((RenderUtils::GetTextWidth(text, 0.65f) * nscale) / 2.f), pos.y + (12.0f * nscale)), textColor.getColor(), 0.65f*nscale, textColor.opacity * nalpha);
				RenderUtils::FillRectangle(Rect(loc - 0.5f, pos.y + (8.0f * nscale), loc + 0.5f, pos.y + (12.0f * nscale)), textColor.getColor(), textColor.opacity * nalpha);
			}


	}
	
	RenderUtils::FlushText();
}

