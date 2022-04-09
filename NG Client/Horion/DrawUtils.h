#pragma once

#include "../Memory/GameData.h"
#include "../SDK/CClientInstance.h"
#include "../SDK/CMinecraftUIRenderContext.h"
#include "../SDK/Tessellator.h"
#include "../Utils/HMath.h"
#include "../Utils/Target.h"
#include "../Utils/Utils.h"

enum class Fonts { DEFAULT,
				   MCFONT,
				   UNICOD,
				   SMOOTH,
				   RUNE };

using mce__VertexFormat__disableHalfFloats_t = void(__fastcall*)(__int64, int, int);
using Tessellator__initializeFormat_t = void(__fastcall*)(__int64, __int64);

extern C_MinecraftUIRenderContext* renderCtx;
extern mce__VertexFormat__disableHalfFloats_t mce__VertexFormat__disableHalfFloats;
extern Tessellator__initializeFormat_t Tessellator__initializeFormat;

struct MC_Color {
	union {
		struct {
			float r, g, b, a;
		};
		float arr[4];
	};
	bool shouldDelete = true;

	MC_Color() {
		this->r = 1;
		this->g = 1;
		this->b = 1;
		this->a = 1;
	};

	MC_Color(const MC_Color& other) {
		this->r = other.r;
		this->g = other.g;
		this->b = other.b;
		this->a = other.a;
		this->shouldDelete = other.shouldDelete;
	}

	MC_Color(const float* arr) {
		this->arr[0] = arr[0];
		this->arr[1] = arr[1];
		this->arr[2] = arr[2];
		this->arr[3] = arr[3];
	};

	MC_Color(const float r, const float g, const float b, const float a = 1) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	};

	MC_Color(const int r, const int g, const int b, const int a = 255) {
		this->r = r / 255.0f;
		this->g = g / 255.0f;
		this->b = b / 255.0f;
		this->a = a / 255.0f;
	};

	
	MC_Color(const float r, const float g, const float b, const float a, const bool shouldDelete) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
		this->shouldDelete = shouldDelete;
	};

	MC_Color lerp(const MC_Color& o, float t) const;
};

enum VertexFormat {

};

class MatrixStack;

class DrawUtils {
public:
	static void setCtx(C_MinecraftUIRenderContext* ctx, C_GuiData* guiData);
	static void setGameRenderContext(__int64 ctx);
	static void flush();
	static void setColor(float r, float g, float b, float a);  // rgba, values from 0 to 1
	static inline void tess__begin(Tessellator* tesselator, int vertexFormat = 3, int numVerticesReserved = 0);
	static C_Font* getFont(Fonts font);
	static Tessellator* get3dTessellator();
	static __int64 getScreenContext();
	static MatrixStack* getMatrixStack();
	static float getTextWidth(std::string* textStr, float textSize = 1, Fonts font = Fonts::SMOOTH);
	static float getFontHeight(float textSize = 1, Fonts font = Fonts::SMOOTH);

	static void drawTriangle(vec2 p1, vec2 p2, vec2 p3);
	static void drawQuad(vec2 p1, vec2 p2, vec2 p3, vec2 p4);
	static void drawElipse(vec2 p1, vec2 p2, vec2 p3, vec2 p4);
	static void drawLine(vec2 start, vec2 end, float lineWidth);  // rgba
	static void drawLinestrip3d(const std::vector<vec3>& points);
	static void drawRoundRectangle(vec4 pos, const MC_Color col, float alpha);
	static void drawLine3d(const vec3& start, const vec3& end);
	static void drawBox3d(vec3 lower, vec3 upper);
	static void drawBoxSides(const vec4& pos, const MC_Color& col, float alpha, float thickness);
	static void drawBoxTops(const vec4& pos, const MC_Color& col, float alpha, float thickness);
	static void drawBoxBottom(const vec4& pos, const MC_Color& col, float alpha, float thickness);
	static void drawTop3(const vec4& pos, const MC_Color& col, float alpha, float thickness);
	static void fillRectangle(vec4 pos, const MC_Color col, float alpha);
	static void fillRectangle2(vec4 pos, const _RGB col, float alpha);
	static inline void fillRectangle(vec2 start, vec2 end) {
		DrawUtils::drawQuad({start.x, end.y}, {end.x, end.y}, {end.x, start.y}, {start.x, start.y});
	}

	static inline void drawRectangle(vec2 start, vec2 end, float lineWidth = 1.0f) {
		lineWidth /= 2;
		fillRectangle({start.x - lineWidth, start.y - lineWidth}, {end.x + lineWidth, start.y + lineWidth});  // TOP
		fillRectangle({start.x - lineWidth, start.y}, {start.x + lineWidth, end.y});                          // LEFT
		fillRectangle({end.x - lineWidth, start.y}, {end.x + lineWidth, end.y});                              //
		fillRectangle({start.x - lineWidth, end.y - lineWidth}, {end.x + lineWidth, end.y + lineWidth});
	}
	static inline void drawRectangle(vec4 pos, MC_Color col, float alpha, float lineWidth = 1.0f) {
		lineWidth /= 2;
		fillRectangle(vec4(pos.x - lineWidth, pos.y - lineWidth, pos.z + lineWidth, pos.y + lineWidth), col, alpha);  // TOP
		fillRectangle(vec4(pos.x - lineWidth, pos.y, pos.x + lineWidth, pos.w), col, alpha);                          // LEFT
		fillRectangle(vec4(pos.z - lineWidth, pos.y, pos.z + lineWidth, pos.w), col, alpha);                          //
		fillRectangle(vec4(pos.x - lineWidth, pos.w - lineWidth, pos.z + lineWidth, pos.w + lineWidth), col, alpha);
	}
	static inline void drawrightRectangle(vec4 pos, MC_Color col, float alpha, float lineWidth = 1.0f) {
		lineWidth /= 2;
		fillRectangle(vec4(pos.z - lineWidth, pos.y, pos.z + lineWidth, pos.w), col, alpha);                          //right
		fillRectangle(vec4(pos.x - lineWidth, pos.w - lineWidth, pos.z + lineWidth, pos.w + lineWidth), col, alpha);
	}
	static inline void drawleftRectangle(vec4 pos, MC_Color col, float alpha, float lineWidth = 1.0f) {
		lineWidth /= 2;
		fillRectangle(vec4(pos.x - lineWidth, pos.y, pos.x + lineWidth, pos.w), col, alpha);                          // LEFT
		fillRectangle(vec4(pos.x - lineWidth, pos.w - lineWidth, pos.z + lineWidth, pos.w + lineWidth), col, alpha);
	}
	static inline void drawTopAndBottomRectangle(vec4 pos, MC_Color col, float alpha, float lineWidth = 1.0f) {
		lineWidth /= 2;
		fillRectangle(vec4(pos.x - lineWidth, pos.w - lineWidth, pos.z + lineWidth, pos.w + lineWidth), col, alpha);
		fillRectangle(vec4(pos.x - lineWidth, pos.y - lineWidth, pos.z + lineWidth, pos.y + lineWidth), col, alpha);  // TOP
	}
	static void drawImage(std::string filePath, vec2& ImagePos, vec2& ImageDimension, vec2& idk);

	static void drawText(vec2 pos, std::string* text, MC_Color color, float textSize = 1, float alpha = 1, Fonts font = Fonts::SMOOTH);
	static void drawText2(vec2 pos, std::string* text, float textSize = 1, float alpha = 1, Fonts font = Fonts::SMOOTH);
	static void drawBox(vec3 lower, vec3 upper, float lineWidth, bool outline = false);
	static void drawBoxv2(const vec3& lower, const vec3& upper, float lineWidth, bool outline = false);
	static void drawEntityBox(C_Entity* ent, float lineWidth);
	static void drawBetterESP(C_Entity* ent, float lineWidth);
	static void draw2D(C_Entity* ent, float lineWidth);
	static void drawZephyr(C_Entity* ent, float lineWidth);
	static void drawNameTags(C_Entity* ent, float textSize, bool drawHealth = false, bool useUnicodeFont = false);
	static void drawItem(C_ItemStack* item, const vec2& ItemPos, float opacity, float scale, bool isEnchanted);
	static void drawKeystroke(char key, vec2 pos);
	static void drawLeftMouseKeystroke(vec2 pos);
	static void drawRightMouseKeystroke(vec2 pos);
	static void CPS(vec2 pos);
	static void DrawOutline(vec2 position, vec2 size, MC_Color colour, float width);
	static void drawTracer(const vec3& ent, int damageTime = 0);
	static float getLerpTime();
	static vec3 getOrigin();

	static vec2 worldToScreen(const vec3& world);
};

