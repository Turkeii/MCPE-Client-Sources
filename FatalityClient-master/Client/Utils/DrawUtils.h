#pragma once

#include "../Memory/GameData.h"
#include "../SDK/CClientInstance.h"
#include "../SDK/CMinecraftUIRenderContext.h"
#include "../Utils/TargetUtil.h"
#include "../SDK/Tessellator.h"
#include "../Utils/HMath.h"
#include "../Utils/Utils.h"

enum class Fonts {
	DEFAULT,
	UNICOD,
	SMOOTH,
	RUNE
};

using mce__VertexFormat__disableHalfFloats_t = void(__fastcall*)(__int64, int, int);
using Tessellator__initializeFormat_t = void(__fastcall*)(__int64, __int64);

extern C_MinecraftUIRenderContext* renderCtx;
extern mce__VertexFormat__disableHalfFloats_t mce__VertexFormat__disableHalfFloats;
extern Tessellator__initializeFormat_t Tessellator__initializeFormat;

struct MC_Color {
	union {
		struct { float r, g, b, a; };
		float arr[4]{};
	};

	MC_Color() {
		this->r = 1;
		this->g = 1;
		this->b = 1;
		this->a = 1;
	};

	MC_Color(const float r, const float g, const float b, const float a = 255) {
		this->r = r / 255.0f;
		this->g = g / 255.0f;
		this->b = b / 255.0f;
		this->a = a / 255.0f;
	};
};

enum VertexFormat {
};

class MatrixStack;

class DrawUtils {
public:
	static void draw2DBox(float width, float height, float lineWidth, float offset, MC_Color color);
	static void drawBetter2D(C_Entity* ent, float lineWidth);
	static void setCtx(C_MinecraftUIRenderContext* ctx, C_GuiData* guiData);
	static void setGameRenderContext(__int64 ctx);
	static void flush();
	static void toUpper(std::string& str);
	static void toLower(std::string& str);
	static void drawSteve(vec4_t(pos));
	static void setColor(float r, float g, float b, float a);  // rgba, values from 0 to 1
	static inline void tess__begin(Tessellator* tesselator, int vertexFormat = 3, int numVerticesReserved = 0);
	static C_Font* getFont(Fonts font);
	static Tessellator* get3dTessellator();
	static __int64 getScreenContext();
	static MatrixStack* getMatrixStack();
	static float getTextWidth(std::string* textStr, float textSize = 1, Fonts font = Fonts::SMOOTH);
	static float getFontHeight(float textSize = 1, Fonts font = Fonts::SMOOTH);
	static void drawTriangle(vec2_t p1, vec2_t p2, vec2_t p3);
	static void drawQuad(vec2_t p1, vec2_t p2, vec2_t p3, vec2_t p4);
	static void drawLine(vec2_t start, vec2_t end, float lineWidth);  // rgba
	static void drawAnimatedLine(vec2_t start, vec2_t end, MC_Color col, float alpha, float speed, float width);
	static void drawLineStrip3D(const std::vector<vec3_t>& points, int mode);
	static void drawLine3d(const vec3_t& start, const vec3_t& end);
	static void drawBox3d(vec3_t lower, vec3_t upper);
	static void fillRectangle(vec4_t pos, const MC_Color col, float alpha);
	static void fillRectangleA(vec4_t pos, MC_Color col);
	static void drawWarning(vec4_t pos, const MC_Color col, float alpha);
	static void drawRoundRectangle(vec4_t pos, const MC_Color col, bool rounder);
	static void drawRoundRectangle2(vec4_t pos, const MC_Color col);
	static void fillRoundRectangle(vec4_t pos, const MC_Color col, bool rounder);
	static void drawButton(vec4_t pos, vec2_t textPos, std::string* textStr, const MC_Color color, const MC_Color hoverColor);

	static inline void fillRectangle(vec2_t start, vec2_t end) {
		DrawUtils::drawQuad({ start.x, end.y }, { end.x, end.y }, { end.x, start.y }, { start.x, start.y });
	}
	static inline void fillRectangleA(vec2_t start, vec2_t end) {
		DrawUtils::drawQuad({ start.x, end.y }, { end.x, end.y }, { end.x, start.y }, { start.x, start.y });
	}
	static inline void drawRectangle(vec2_t start, vec2_t end, float lineWidth = 1.0f) {
		lineWidth /= 2;
		fillRectangle({ start.x - lineWidth, start.y - lineWidth }, { end.x + lineWidth, start.y + lineWidth });  // TOP
		fillRectangle({ start.x - lineWidth, start.y }, { start.x + lineWidth, end.y });                          // LEFT
		fillRectangle({ end.x - lineWidth, start.y }, { end.x + lineWidth, end.y });                              //
		fillRectangle({ start.x - lineWidth, end.y - lineWidth }, { end.x + lineWidth, end.y + lineWidth });
	}
	static inline void drawRectangle(vec4_t pos, MC_Color col, float alpha, float lineWidth = 1.0f) {
		lineWidth /= 2;
		fillRectangle(vec4_t(pos.x - lineWidth, pos.y - lineWidth, pos.z + lineWidth, pos.y + lineWidth), col, alpha);  // TOP
		fillRectangle(vec4_t(pos.x - lineWidth, pos.y, pos.x + lineWidth, pos.w), col, alpha);                          // LEFT
		fillRectangle(vec4_t(pos.z - lineWidth, pos.y, pos.z + lineWidth, pos.w), col, alpha);                          //
		fillRectangle(vec4_t(pos.x - lineWidth, pos.w - lineWidth, pos.z + lineWidth, pos.w + lineWidth), col, alpha);
	}

	static inline void drawBottomLine(vec4_t pos, MC_Color col, float alpha, float lineWidth = 1.0f) {
		lineWidth /= 2;
		fillRectangle(vec4_t(pos.x - lineWidth, pos.w - lineWidth, pos.z + lineWidth, pos.w + lineWidth), col, alpha);
	}

	static void drawCircle(vec4_t(pos), MC_Color col);
	static void drawImage(std::string filePath, vec2_t& imagePos, vec2_t& imageDimension, vec2_t& idk, vec2_t& idk2, MC_Color flushColor = MC_Color(255.f, 255.f, 255.f));
	static void drawText(vec2_t pos, std::string* text, MC_Color color, float textSize = 1.f, float alpha = 1.f, bool hasShadow = false, Fonts font = Fonts::SMOOTH);
	static void drawCenteredString(vec2_t pos, std::string* textStr, float textSize, MC_Color color, bool hasShadow);
	static void drawRightAlignedString(std::string* textStr, vec4_t pos, MC_Color color, bool hasShadow);
	static void drawGradientText(vec2_t pos, std::string* text, float textSize = 1.f, float alpha = 1.f, bool hasShadow = false);
	static void drawBox(vec3_t lower, vec3_t upper, float lineWidth, bool outline = false, bool fill = false);
	static void drawEntityBox(C_Entity* ent, float lineWidth);
	static void draw2D(C_Entity* ent, float lineWidth);
	static void drawNameTags(C_Entity* ent, float textSize, bool drawHealth = false, bool useUnicodeFont = false);
	static void drawItem(C_ItemStack* item, vec2_t ItemPos, float opacity, float scale, bool isEnchanted);
	static void drawKeystroke(char key, vec2_t pos);
	static int fadeOut(int startingAlpha, int speed);
	static float getLerpTime();
	static vec3_t getOrigin();

	static vec2_t worldToScreen(const vec3_t& world);
};
