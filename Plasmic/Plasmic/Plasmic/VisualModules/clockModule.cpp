#include "clockModule.h"


static MC_Color White(255, 255, 255);
static char clockTimeText[50] = "Time: 0000000";


SYSTEMTIME CurrentSystemTime;
extern float RealWorldTime;

void UpdateRealTime() {
	GetLocalTime((LPSYSTEMTIME)&CurrentSystemTime);
}

static uint16_t lastSec = 0;
void clockModule::onTick(Gamemode* gm) {

	
	

	if (!isGameTime) {
		if (lastSec == CurrentSystemTime.wSecond)
			return;
		lastSec = CurrentSystemTime.wSecond;

		if (showSeconds)
			if (is24)
				sprintf(clockTimeText, mltext("Time: %02d : %02d : %02d", "Temps: %02d : %02d : %02d"), CurrentSystemTime.wHour, CurrentSystemTime.wMinute, CurrentSystemTime.wSecond);
			else
				sprintf(clockTimeText, mltext("Time: %02d : %02d : %02d %s", "Temps: %02d : %02d : %02d %s"), CurrentSystemTime.wHour - 12, CurrentSystemTime.wMinute, CurrentSystemTime.wSecond, CurrentSystemTime.wHour > 12 ? "PM" : "AM");	
		else
			if (is24)
				sprintf(clockTimeText, mltext("Time: %02d : %02d", "Temps: %02d : %02d"), CurrentSystemTime.wHour, CurrentSystemTime.wMinute);
			else
				sprintf(clockTimeText, mltext("Time: %02d : %02d %s", "Temps: %02d : %02d %s"), (CurrentSystemTime.wHour > 12 ? CurrentSystemTime.wHour - 12 : CurrentSystemTime.wHour), CurrentSystemTime.wMinute, CurrentSystemTime.wHour > 12 ? "PM" : "AM");
	} else {


		float time = RealWorldTime - 0.5f;
		if (time < 0.f) 
			time = 1.0f + time;

		int hours = 0;
		int mins = 0;
		int seconds = (int)(time * 86000.f);

		while (seconds > 3599) { seconds -= 3600; hours++; }
		while (seconds > 60) { seconds -= 60; mins++; }


		if (showSeconds)
			if (is24)
				sprintf(clockTimeText, mltext("Time: %02d : %02d : %02d", "Temps: %02d : %02d : %02d"), hours, mins, seconds);
			else
				sprintf(clockTimeText, mltext("Time: %02d : %02d : %02d %s", "Temps: %02d : %02d : %02d %s"), hours - 12, mins, seconds, hours > 12 ? "PM" : "AM");
		else
			if (is24)
				sprintf(clockTimeText, mltext("Time: %02d : %02d", "Temps: %02d : %02d"), hours, CurrentSystemTime.wMinute);
			else
				sprintf(clockTimeText, mltext("Time: %02d : %02d %s", "Temps: %02d : %02d %s"), hours - 12, mins, hours  > 12 ? "PM" : "AM");
	}

		
}


void clockModule::onRender() {
	
	
	size.x = RenderUtils::GetTextWidth(clockTimeText, 1.f * scale);
	size.y = RenderUtils::GetTextWidth("W", 1.0f * scale);
	size.x += 6.f;
	size.y += 6.f;


	RenderUtils::FillRectangle(Rect(pos.x, pos.y, pos.x + size.x, pos.y + size.y), backgroundColor.getColor(), backgroundColor.opacity);

	RenderUtils::RenderText(clockTimeText, Vec2(pos.x + 3.f, pos.y + size.y / 12.f), textColor.getColor(), 1.f * scale, textColor.opacity);
	RenderUtils::FlushText();
}


