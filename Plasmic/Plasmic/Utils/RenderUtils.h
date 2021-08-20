#pragma once
#include <Windows.h>
#include <Psapi.h>

#include <string>
#include <chrono>
#include "PlasmicMath.h"
#include "../SDK/Minecraft/MCUtilsClass.h"
#include "../SDK/Minecraft/MinecraftUIRenderContext.h"


#include <MinHook.h>

#define INRANGE(x,a,b)   (x >= a && x <= b)
#define GET_BYTE( x )    (GET_BITS(x[0]) << 4 | GET_BITS(x[1]))
#define GET_BITS( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))





class RenderUtils {
private:
	static class MinecraftUIRenderContext* CachedContext;
	static struct BitmapFont* CachedFont;
public:
	static bool isMinecraftia;

	static void SetContext(class MinecraftUIRenderContext* Context, struct BitmapFont* Font);
	static void SetFont(bool minecraftia);

	static void FlushText();
	static float GetTextWidth(const char* text, float textSize);
	static void RenderText(const char* text, Vec2 textPos, MC_Color colour, float textSize, float alpha);


	static void FillRectangle(Rect position, MC_Color color, float alpha);
	static void DrawRectangle(Rect position, MC_Color color, float alpha, float lineWidth);

};
