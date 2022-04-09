#include "DrawUtils.h"

#include "Module/ModuleManager.h"
#include <Windows.h>
#include "../Utils/Logger.h"

struct MaterialPtr {
	char padding[0x138];
};

using tess_vertex_t = void(__fastcall*)(Tessellator* _this, float v1, float v2, float v3);
using meshHelper_renderImm_t = void(__fastcall*)(__int64, Tessellator* tesselator, MaterialPtr*);

C_MinecraftUIRenderContext* renderCtx;
C_GuiData* guiData;
__int64 screenContext2d;
__int64 game3dContext;
Tessellator* tesselator;
float* colorHolder;
std::shared_ptr<glmatrixf> refdef;
vec2 fov;
vec2 screenSize;
vec3 origin;
float lerpT;
C_TexturePtr* texturePtr = nullptr;

static MaterialPtr* uiMaterial = nullptr;
static MaterialPtr* entityFlatStaticMaterial = nullptr;

tess_vertex_t tess_vertex;
meshHelper_renderImm_t meshHelper_renderImm;
//mce__VertexFormat__disableHalfFloats_t mce__VertexFormat__disableHalfFloats;
//Tessellator__initializeFormat_t Tessellator__initializeFormat;

bool hasInitializedSigs = false;
void initializeSigs() {
	
	tess_vertex = reinterpret_cast<tess_vertex_t>(FindSignature("40 57 48 83 EC ? 0F 29 74 24 ? 0F 29 7C 24"));
	meshHelper_renderImm = reinterpret_cast<meshHelper_renderImm_t>(FindSignature("40 53 56 57 48 81 EC ?? ?? ?? ?? 49 8B F0 48 8B DA"));
	//mce__VertexFormat__disableHalfFloats = reinterpret_cast<mce__VertexFormat__disableHalfFloats_t>(FindSignature("40 53 48 83 EC ?? 48 8B D9 C7 81 ?? ?? ?? ?? 00 00 00 00 C6 81 ?? ?? ?? ?? 00"));
	//Tessellator__initializeFormat = reinterpret_cast<Tessellator__initializeFormat_t>(FindSignature("48 89 74 24 ?? 57 48 83 EC 20 4C 8B 41 ?? 48 8B FA 4C 2B 41 ?? 48 8B F1 48 83 C1 08 ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? 49 F7 E8 48 D1 FA 48 8B C2 48 C1 E8 3F 48 03 D0 48 3B FA"));
	hasInitializedSigs = true;
}

void DrawUtils::setCtx(C_MinecraftUIRenderContext* ctx, C_GuiData* gui) {
	if (!hasInitializedSigs)
		initializeSigs();
	LARGE_INTEGER EndingTime, ElapsedMicroseconds;
	LARGE_INTEGER Frequency;
	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&EndingTime);
	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - g_Data.getLastUpdateTime();

	ElapsedMicroseconds.QuadPart *= 1000000;
	int ticksPerSecond = 20;
	if (g_Data.getClientInstance()->minecraft != nullptr && reinterpret_cast<__int64>(g_Data.getClientInstance()->minecraft) < 0xFFFFFFFFFFF00000)
		if (g_Data.getClientInstance()->minecraft->timer != nullptr)
			ticksPerSecond = (int)*g_Data.getClientInstance()->minecraft->timer;
	if(ticksPerSecond < 1)
		ticksPerSecond = 1;
	ElapsedMicroseconds.QuadPart /= Frequency.QuadPart / ticksPerSecond;
	lerpT = (ElapsedMicroseconds.QuadPart / 1000000.f);
	if (lerpT > 1)
		lerpT = 1;
	else if (lerpT < 0)
		lerpT = 0;

	guiData = gui;
	renderCtx = ctx;
	screenContext2d = reinterpret_cast<__int64*>(renderCtx)[2];

	tesselator = *reinterpret_cast<Tessellator**>(screenContext2d + 0xB0);
	colorHolder = *reinterpret_cast<float**>(screenContext2d + 0x30);

	glmatrixf* badrefdef = g_Data.getClientInstance()->getRefDef();

	refdef = std::shared_ptr<glmatrixf>(badrefdef->correct());
	fov = g_Data.getClientInstance()->getFov();
	screenSize.x = gui->widthGame;
	screenSize.y = gui->heightGame;
	if (g_Data.getClientInstance()->levelRenderer != nullptr)
		origin = g_Data.getClientInstance()->levelRenderer->getOrigin();

	if (uiMaterial == nullptr) {
		// 2 Sigs, wanted one comes first
		uintptr_t sigOffset = FindSignature("4C 8D 05 ?? ?? ?? ?? 48 8B D3 48 8B CF 48 8B 5C 24 ?? 0F 28 7C 24 ?? 44 0F 28 44 24 ?? 48");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		uiMaterial = reinterpret_cast<MaterialPtr*>(sigOffset + offset + 7);
	}
	
	if (entityFlatStaticMaterial == nullptr && g_Data.isInGame()) {
		entityFlatStaticMaterial = reinterpret_cast<MaterialPtr*>(g_Data.getClientInstance()->itemInHandRenderer->entityLineMaterial.materialPtr);
	}
	
}

void DrawUtils::setColor(float r, float g, float b, float a) {
	colorHolder[0] = r;
	colorHolder[1] = g;
	colorHolder[2] = b;
	colorHolder[3] = a;
	*reinterpret_cast<uint8_t*>(colorHolder + 4) = 1;
}

C_Font* DrawUtils::getFont(Fonts font) {
	static auto TestFont = moduleMgr->getModule<ClickGuiMod>();

	if (TestFont->Fonts.selected == 1)
	return g_Data.getClientInstance()->minecraftGame->mcFont;
	else
	return g_Data.getClientInstance()->minecraftGame->getOldFont();
	
	switch (font) {
	case Fonts::SMOOTH:
		return g_Data.getClientInstance()->minecraftGame->getTheGoodFontThankYou();
		break;
	case Fonts::UNICOD:
		return g_Data.getClientInstance()->minecraftGame->getTheBetterFontYes();
		break;
	case Fonts::RUNE:
		return g_Data.getClientInstance()->_getRuneFont();
		break;
	case Fonts::MCFONT:
		return g_Data.getClientInstance()->minecraftGame->mcFont;
		break;
	default:
		return g_Data.getClientInstance()->_getFont();
		break;
	}
}

Tessellator* DrawUtils::get3dTessellator() {
	auto myTess = *reinterpret_cast<Tessellator**>(game3dContext + 0xB0);
	return myTess;
}

__int64 DrawUtils::getScreenContext() {
	return game3dContext == 0 ? screenContext2d : game3dContext;
}

MatrixStack* DrawUtils::getMatrixStack() {
	return reinterpret_cast<MatrixStack*>(*reinterpret_cast<__int64*>(DrawUtils::getScreenContext() + 0x18i64) + 0x30i64);
}

float DrawUtils::getTextWidth(std::string* textStr, float textSize, Fonts font) {
	TextHolder text(*textStr);

	C_Font* fontPtr = getFont(font);

	float ret = renderCtx->getLineLength(fontPtr, &text, textSize);

	return ret;
}

float DrawUtils::getFontHeight(float textSize, Fonts font) {
	C_Font* fontPtr = getFont(font);

	float ret = fontPtr->getLineHeight() * textSize;

	return ret;
}

void DrawUtils::flush() {
	renderCtx->flushText(0);
}

void DrawUtils::drawTriangle(vec2 p1, vec2 p2, vec2 p3) {
	
	DrawUtils::tess__begin(tesselator, 3, 3);

	tess_vertex(tesselator, p1.x, p1.y, 0);
	tess_vertex(tesselator, p2.x, p2.y, 0);
	tess_vertex(tesselator, p3.x, p3.y, 0);

	meshHelper_renderImm(screenContext2d, tesselator, uiMaterial);
}


void DrawUtils::drawQuad(vec2 p1, vec2 p2, vec2 p3, vec2 p4) {
	DrawUtils::tess__begin(tesselator, 1, 4);

	tess_vertex(tesselator, p1.x, p1.y, 0);
	tess_vertex(tesselator, p2.x, p2.y, 0);
	tess_vertex(tesselator, p3.x, p3.y, 0);
	tess_vertex(tesselator, p4.x, p4.y, 0);

	meshHelper_renderImm(screenContext2d, tesselator, uiMaterial);
}

void DrawUtils::drawElipse(vec2 p1, vec2 p2, vec2 p3, vec2 p4) {
	//Draw Circle
}

void DrawUtils::drawLine(vec2 start, vec2 end, float lineWidth) {
	float modX = 0 - (start.y - end.y);
	float modY = start.x - end.x;

	float len = sqrtf(modX * modX + modY * modY);

	modX /= len;
	modY /= len;
	modX *= lineWidth;
	modY *= lineWidth;

	DrawUtils::tess__begin(tesselator, 3, 6);

	tess_vertex(tesselator, start.x + modX, start.y + modY, 0);
	tess_vertex(tesselator, start.x - modX, start.y - modY, 0);
	tess_vertex(tesselator, end.x - modX, end.y - modY, 0);

	tess_vertex(tesselator, start.x + modX, start.y + modY, 0);
	tess_vertex(tesselator, end.x + modX, end.y + modY, 0);
	tess_vertex(tesselator, end.x - modX, end.y - modY, 0);

	meshHelper_renderImm(screenContext2d, tesselator, uiMaterial);
}

void DrawUtils::drawText(vec2 pos, std::string* textStr, MC_Color color, float textSize, float alpha, Fonts font) {
	TextHolder text(*textStr);
	C_Font* fontPtr = getFont(font);
	static uintptr_t caretMeasureData = 0xFFFFFFFF;

	pos.y -= 1;

	float posF[4];  // vec4 (startX, startY, endX, endY);
	posF[0] = pos.x;
	posF[1] = pos.x + 1000;
	posF[2] = pos.y;
	posF[3] = pos.y + 1000;

	TextMeasureData textMeasure{};
	memset(&textMeasure, 0, sizeof(TextMeasureData));
	textMeasure.textSize = textSize;

	renderCtx->drawText(fontPtr, posF, &text, color.arr, alpha, 0, &textMeasure, &caretMeasureData);
}

void DrawUtils::drawText2(vec2 pos, std::string* textStr, float textSize, float alpha, Fonts font) {
	TextHolder text(*textStr);
	C_Font* fontPtr = getFont(font);
	static uintptr_t caretMeasureData = 0xFFFFFFFF;

	pos.y -= 1;

	float posF[4];  // vec4(startX, startY, endX, endY);
	posF[0] = pos.x;
	posF[1] = pos.x + 1000;
	posF[2] = pos.y;
	posF[3] = pos.y + 1000;

	TextMeasureData textMeasure{};
	memset(&textMeasure, 0, sizeof(TextMeasureData));
	textMeasure.textSize = textSize;

	renderCtx->drawText(fontPtr, posF, &text, MC_Color().arr, alpha, 0, &textMeasure, &caretMeasureData);
}

void DrawUtils::drawBox(vec3 lower, vec3 upper, float lineWidth, bool outline) {
	
	vec3 diff;
	diff.x = upper.x - lower.x;
	diff.y = upper.y - lower.y;
	diff.z = upper.z - lower.z;

	
	vec3 vertices[8];
	vertices[0] = vec3(lower.x, lower.y, lower.z);
	vertices[1] = vec3(lower.x + diff.x, lower.y, lower.z);
	vertices[2] = vec3(lower.x, lower.y + diff.y, lower.z);
	vertices[3] = vec3(lower.x + diff.x, lower.y + diff.y, lower.z);
	vertices[4] = vec3(lower.x, lower.y, lower.z + diff.z);
	vertices[5] = vec3(lower.x + diff.x, lower.y, lower.z + diff.z);
	vertices[6] = vec3(lower.x, lower.y + diff.y, lower.z + diff.z);
	vertices[7] = vec3(lower.x + diff.x, lower.y + diff.y, lower.z + diff.z);

	// Convert to screen coord
	std::vector<std::tuple<int, vec2>> screenCords;
	for (int i = 0; i < 8; i++) {
		vec2 screen;
		if (refdef->OWorldToScreen(origin, vertices[i], screen, fov, screenSize)) {
			screenCords.emplace_back(outline ? (int) screenCords.size() : i, screen);
		}
	}
	if (screenCords.size() < 2)
		return;  // No lines possible

	if (!outline) {
		for (auto it = screenCords.begin(); it != screenCords.end(); it++) {
			auto from = *it;
			auto fromOrig = vertices[std::get<0>(from)];

			for (auto to : screenCords) {
				auto toOrig = vertices[std::get<0>(to)];

				bool shouldDraw = false;
				// X direction
				shouldDraw |= fromOrig.y == toOrig.y && fromOrig.z == toOrig.z && fromOrig.x < toOrig.x; 
				// Y direction
				shouldDraw |= fromOrig.x == toOrig.x && fromOrig.z == toOrig.z && fromOrig.y < toOrig.y; 
				// Z direction
				shouldDraw |= fromOrig.x == toOrig.x && fromOrig.y == toOrig.y && fromOrig.z < toOrig.z; 
				
				if (shouldDraw)
					drawLine(std::get<1>(from), std::get<1>(to), lineWidth);
			}
		}

		return;
	}
	// Find start vertex
	auto it = screenCords.begin();
	std::tuple<int, vec2> start = *it;
	it++;
	for (; it != screenCords.end(); it++) {
		auto cur = *it;
		if (std::get<1>(cur).x < std::get<1>(start).x) {
			start = cur;
		}
	}

	// Follow outer line
	std::vector<int> indices;

	auto current = start;
	indices.push_back(std::get<0>(current));
	vec2 lastDir(0, -1);
	do {
		float smallestAngle = PI * 2;
		vec2 smallestDir;
		std::tuple<int, vec2> smallestE;
		auto lastDirAtan2 = atan2(lastDir.y, lastDir.x);
		for (auto cur : screenCords) {
			if (std::get<0>(current) == std::get<0>(cur))
				continue;

			// angle between vecs
			vec2 dir = vec2(std::get<1>(cur)).sub(std::get<1>(current));
			float angle = atan2(dir.y, dir.x) - lastDirAtan2;
			if (angle > PI) {
				angle -= 2 * PI;
			} else if (angle <= -PI) {
				angle += 2 * PI;
			}
			if (angle >= 0 && angle < smallestAngle) {
				smallestAngle = angle;
				smallestDir = dir;
				smallestE = cur;
			}
		}
		indices.push_back(std::get<0>(smallestE));
		lastDir = smallestDir;
		current = smallestE;
	} while (std::get<0>(current) != std::get<0>(start) && indices.size() < 8);

	// draw
	
	vec2 lastVertex;
	bool hasLastVertex = false;
	for (auto& indice : indices) {
		vec2 curVertex = std::get<1>(screenCords[indice]);
		if (!hasLastVertex) {
			hasLastVertex = true;
			lastVertex = curVertex;
			continue;
		}
		
		drawLine(lastVertex, curVertex, lineWidth);
		lastVertex = curVertex;
	}
}

void DrawUtils::drawBoxv2(const vec3& lower, const vec3& upper, float lineWidth, bool outline) {
	vec3 vertices[4];
	vertices[0] = vec3(lower.x, lower.y, lower.z);
	vertices[1] = vec3(lower.x + (upper.x - lower.x), lower.y, lower.z);
	vertices[2] = vec3(lower.x, lower.y, lower.z + (upper.z - lower.z));
	vertices[3] = vec3(lower.x + (upper.x - lower.x), lower.y, lower.z + (upper.z - lower.z));

	// Convert to screen coord
	std::vector<std::tuple<int, vec2>> screenCords;
	for (int i = 0; i < 4; i++) {
		vec2 screen;
		if (refdef->OWorldToScreen(origin, vertices[i], screen, fov, screenSize)) {
			screenCords.emplace_back((int)screenCords.size(), screen);
		}
	}
	if (screenCords.size() < 2)
		return;  // No lines possible

	// Find start vertex
	auto it = screenCords.begin();
	std::tuple<int, vec2> start = *it;
	it++;
	for (; it != screenCords.end(); it++) {
		auto cur = *it;
		if (std::get<1>(cur).x < std::get<1>(start).x) {
			start = cur;
		}
	}

	// Follow outer line
	std::vector<int> indices;

	auto current = start;
	indices.push_back(std::get<0>(current));
	vec2 lastDir(0, -1);
	do {
		float smallestAngle = PI * 2;
		vec2 smallestDir;
		std::tuple<int, vec2> smallestE;
		auto lastDirAtan2 = atan2(lastDir.y, lastDir.x);
		for (auto cur : screenCords) {
			if (std::get<0>(current) == std::get<0>(cur))
				continue;

			// angle between vecs
			vec2 dir = vec2(std::get<1>(cur)).sub(std::get<1>(current));
			float angle = atan2(dir.y, dir.x) - lastDirAtan2;
			if (angle > PI) {
				angle -= 2 * PI;
			} else if (angle <= -PI) {
				angle += 2 * PI;
			}
			if (angle >= 0 && angle < smallestAngle) {
				smallestAngle = angle;
				smallestDir = dir;
				smallestE = cur;
			}
		}
		indices.push_back(std::get<0>(smallestE));
		lastDir = smallestDir;
		current = smallestE;
	} while (std::get<0>(current) != std::get<0>(start) && indices.size() < 8);

	// draw

	vec2 lastVertex;
	bool hasLastVertex = false;
	for (auto& indice : indices) {
		vec2 curVertex = std::get<1>(screenCords[indice]);
		if (!hasLastVertex) {
			hasLastVertex = true;
			lastVertex = curVertex;
			continue;
		}
		drawLine(lastVertex, curVertex, lineWidth);
		lastVertex = curVertex;
	}
}

void DrawUtils::drawImage(std::string FilePath, vec2& imagePos, vec2& ImageDimension, vec2& idk) {
	if (texturePtr == nullptr) {
		texturePtr = new C_TexturePtr();
		C_FilePath file(FilePath);
		renderCtx->getTexture(texturePtr, file);
	}

	__int64 yot = 0;
	static unsigned __int64 hashedString = 0xA99285D21E94FC80;
	static uintptr_t flushImageAddr = FindSignature("48 8B C4 48 89 58 10 48 89 70 18 55 57 41 54 41 56 41 57 48 8D A8 ?? ?? ?? ?? 48 81 EC ?? ?? ?? ?? 0F 29 70 C8 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 4D 8B E1");

	if (texturePtr != nullptr) {
		renderCtx->drawImage(texturePtr, imagePos, ImageDimension, yot, idk);
		MC_Color col(1.f, 1.f, 1.f);
		renderCtx->flushImages(col, flushImageAddr, (__int64)&hashedString);
	}
}

void DrawUtils::drawNameTags(C_Entity* ent, float textSize, bool drawHealth, bool useUnicodeFont) {
	static auto nametags = moduleMgr->getModule<NameTags>();
	static auto hudModule = moduleMgr->getModule<HudModule>();
	static auto partner = moduleMgr->getModule<Partner>();
	vec2 textPos;
	vec4 rectPos;
	std::string text;
	if (hudModule->displaySecondHalf) {
		text = Utils::sanitize(ent->getNameTag()->getText());
		Utils::replaceString(text, '\n', ' ');
	} else {
		text = Utils::sanitize(ent->getNameTag()->getText());
		text = text.substr(0, text.find('\n'));
	}

	float textWidth = getTextWidth(&text, textSize);
	float textHeight = DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight() * textSize;

	if (refdef->OWorldToScreen(origin, ent->eyePos0.add(0, 0.5f, 0), textPos, fov, screenSize)) {
		auto* player = reinterpret_cast<C_Player*>(ent);
		textPos.y -= textHeight;
		textPos.x -= textWidth / 2.f;
		rectPos.x = textPos.x - 1.f * textSize;
		rectPos.y = textPos.y - 1.f * textSize;
		rectPos.z = textPos.x + textWidth + 1.f * textSize;
		rectPos.w = textPos.y + textHeight + 2.f * textSize;
		vec4 subRectPos = rectPos;
		subRectPos.y = subRectPos.w - 1.f * textSize;
		fillRectangle(rectPos, MC_Color(0, 0, 0), nametags->opacity);
		if (partner->Partnered.selected == 1) {
			if (ent->isAlive() && ent->isPlayer() && nametags->underline) {
				fillRectangle(subRectPos, MC_Color(150, 30, 255), nametags->opacity);
			}
			drawText(textPos, &text, MC_Color(150, 30, 255), textSize);
		} else {
			if (partner->Partnered.selected == 0) {
				if (ent->isAlive() && ent->isPlayer() && nametags->underline) {
					fillRectangle(subRectPos, MC_Color(0, 0, 255), nametags->opacity);
				}
				drawText(textPos, &text, MC_Color(0, 0, 255), textSize);
			} else {
				if (ent->isAlive() && ent->isPlayer() && nametags->underline) {
					fillRectangle(subRectPos, MC_Color(0, 246, 255), nametags->opacity);
				}
				drawText(textPos, &text, MC_Color(0, 246, 255), textSize);
			}
		}
		if (ent->isAlive() && ent->isPlayer() && nametags->displayArmor) {  // is player, show armor
			float scale = textSize * 0.6f;
			float spacing = scale + 15.f;
			float x = rectPos.z + 3.f * textSize;
			float y = rectPos.w - 20.f * scale;
			//armor
			for (int i = 0; i < 4; i++) {
				C_ItemStack* stack = player->getArmor(i);
				if (stack->item != nullptr) {
					DrawUtils::drawItem(stack, vec2(x, y), 1.f, scale, stack->isEnchanted());
					y += scale * spacing;
				}
			}
			//item
			C_PlayerInventoryProxy* supplies = player->getSupplies();
			C_ItemStack* item = supplies->inventory->getItemStack(supplies->selectedHotbarSlot);
			if (item->isValid())
				DrawUtils::drawItem(item, vec2(x, y), 1.f, scale, item->isEnchanted());
		}
	}
}

 void DrawUtils::drawEntityBox(C_Entity* ent, float lineWidth) {
	//vec3* end = ent->getPos();
	//vec3 lerped = ent->getPosOld()->lerp(ent->getPos(), getLerpTime());

	AABB render(ent->eyePos0, ent->width, ent->height, ent->eyePos0.y - ent->aabb.lower.y);
	render.upper.y += 0.1f;

	drawBox(render.lower, render.upper, lineWidth, true);
}

void DrawUtils::drawBetterESP(C_Entity* ent, float lineWidth) {
	//vec3* end = ent->getPos();
	//vec3 lerped = ent->getPosOld()->lerp(ent->getPos(), getLerpTime());

	AABB render(ent->eyePos0, ent->width, ent->height, ent->eyePos0.y - ent->aabb.lower.y);
	render.upper.y += 0.1f;

	drawBox(render.lower, render.upper, lineWidth);
}

void DrawUtils::draw2D(C_Entity* ent, float lineWidth) {
	//vec3* end = ent->getPos();
	//vec3 base = ent->getPosOld()->lerp(ent->getPos(), getLerpTime());

	float ofs = (g_Data.getLocalPlayer()->yaw + 90.f) * (PI / 180);

	vec3 corners[4];
	vec2 corners2d[4];

	corners[0] = vec3(ent->eyePos0.x - ent->width / 1.5f * -sin(ofs), ent->aabb.upper.y + (float)0.1, ent->eyePos0.z - ent->width / 1.5f * cos(ofs));
	corners[1] = vec3(ent->eyePos0.x + ent->width / 1.5f * -sin(ofs), ent->aabb.upper.y + (float)0.1, ent->eyePos0.z + ent->width / 1.5f * cos(ofs));
	corners[2] = vec3(ent->eyePos0.x - ent->width / 1.5f * -sin(ofs), ent->aabb.lower.y, ent->eyePos0.z - ent->width / 1.5f * cos(ofs));
	corners[3] = vec3(ent->eyePos0.x + ent->width / 1.5f * -sin(ofs), ent->aabb.lower.y, ent->eyePos0.z + ent->width / 1.5f * cos(ofs));

	if (refdef->OWorldToScreen(origin, corners[0], corners2d[0], fov, screenSize) &&
		refdef->OWorldToScreen(origin, corners[1], corners2d[1], fov, screenSize) &&
		refdef->OWorldToScreen(origin, corners[2], corners2d[2], fov, screenSize) &&
		refdef->OWorldToScreen(origin, corners[3], corners2d[3], fov, screenSize)) {
		float length = (corners2d[1].x - corners2d[0].x) / 4.f;

		drawLine(corners2d[0], vec2(corners2d[0].x + length, corners2d[0].y), lineWidth);
		drawLine(corners2d[0], vec2(corners2d[0].x, corners2d[0].y + length), lineWidth);

		drawLine(vec2(corners2d[1].x - length, corners2d[1].y), corners2d[1], lineWidth);
		drawLine(corners2d[1], vec2(corners2d[1].x, corners2d[1].y + length), lineWidth);

		drawLine(vec2(corners2d[2].x, corners2d[2].y - length), corners2d[2], lineWidth);
		drawLine(corners2d[2], vec2(corners2d[2].x + length, corners2d[2].y), lineWidth);

		drawLine(vec2(corners2d[3].x, corners2d[3].y - length), corners2d[3], lineWidth);
		drawLine(vec2(corners2d[3].x - length, corners2d[3].y), corners2d[3], lineWidth);	

		/*drawLine(corners2d[0], corners2d[1], lineWidth);
		drawLine(corners2d[0], corners2d[2], lineWidth);
		drawLine(corners2d[3], corners2d[1], lineWidth);
		drawLine(corners2d[3], corners2d[2], lineWidth);*/
	}
}

void DrawUtils::drawZephyr(C_Entity* ent, float lineWidth) {
	//vec3* end = ent->getPos();
	//vec3 base = ent->getPosOld()->lerp(ent->getPos(), getLerpTime());

	float ofs = (g_Data.getLocalPlayer()->yaw + 90.f) * (PI / 180);

	vec3 corners[4];
	vec2 corners2d[4];

	corners[0] = vec3(ent->eyePos0.x - ent->width / 1.5f * -sin(ofs), ent->aabb.upper.y + (float)0.1, ent->eyePos0.z - ent->width / 1.5f * cos(ofs));
	corners[1] = vec3(ent->eyePos0.x + ent->width / 1.5f * -sin(ofs), ent->aabb.upper.y + (float)0.1, ent->eyePos0.z + ent->width / 1.5f * cos(ofs));
	corners[2] = vec3(ent->eyePos0.x - ent->width / 1.5f * -sin(ofs), ent->aabb.lower.y, ent->eyePos0.z - ent->width / 1.5f * cos(ofs));
	corners[3] = vec3(ent->eyePos0.x + ent->width / 1.5f * -sin(ofs), ent->aabb.lower.y, ent->eyePos0.z + ent->width / 1.5f * cos(ofs));

	if (refdef->OWorldToScreen(origin, corners[0], corners2d[0], fov, screenSize) &&
		refdef->OWorldToScreen(origin, corners[1], corners2d[1], fov, screenSize) &&
		refdef->OWorldToScreen(origin, corners[2], corners2d[2], fov, screenSize) &&
		refdef->OWorldToScreen(origin, corners[3], corners2d[3], fov, screenSize)) {
		float length = (corners2d[1].x - corners2d[0].x) / 4.f;

		drawLine(corners2d[0], corners2d[1], lineWidth);
		drawLine(corners2d[0], corners2d[2], lineWidth);
		drawLine(corners2d[3], corners2d[1], lineWidth);
		drawLine(corners2d[3], corners2d[2], lineWidth);
	}
}

void DrawUtils::drawItem(C_ItemStack* item, const vec2& itemPos, float opacity, float scale, bool isEnchanted) {
	__int64 scnCtx = reinterpret_cast<__int64*>(renderCtx)[2];
	auto* screenCtx = reinterpret_cast<C_ScreenContext*>(scnCtx);
	C_BaseActorRenderContext baseActorRenderCtx(screenCtx, g_Data.getClientInstance(), g_Data.getClientInstance()->minecraftGame);
	C_ItemRenderer* renderer = baseActorRenderCtx.renderer;
	renderer->renderGuiItemNew(&baseActorRenderCtx, item, 0, itemPos.x, itemPos.y, opacity, scale, isEnchanted);
}

static float currColor[4];

void DrawUtils::drawKeystroke(char key, vec2 pos) {
	static auto Key = moduleMgr->getModule<KeyStrokes>();
	static auto partner = moduleMgr->getModule<Partner>();
	std::string keyString = Utils::getKeyName(key);
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	if (key == *input->spaceBarKey) {
		if (key == *input->spaceBarKey) keyString = "-";
		pos.x += Key->keystrokesX;
		pos.y -= Key->keystrokesY;
		pos.x -= 9.f;
		pos.y += 9.f;
		vec4 rectPos(
			pos.x,
			pos.y,
			pos.x + 64.f,
			pos.y + 15.f);
		vec2 textPos(
			(rectPos.x + (rectPos.z - rectPos.x) / 2) - (DrawUtils::getTextWidth(&keyString) / 2.f),
			rectPos.y + 7.f - DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight() / 2.f);

		fillRectangle(rectPos, GameData::isKeyDown(key) ? MC_Color(85, 85, 85) : MC_Color(12, 12, 12), Key->opacity);
		// rainbow colors
		{
			if (currColor[3] < 1) {
				currColor[0] = 1;
				currColor[1] = 0.2f;
				currColor[2] = 0.2f;
				currColor[3] = 1;
			}
			Utils::ApplyRainbow(currColor, 0.00025f);
		}
		if (Key->keybindsRGB) {
		drawRectangle(rectPos, GameData::isKeyDown(key) ? MC_Color() : MC_Color(currColor), 1.f);
		drawText(textPos, &keyString, MC_Color(currColor), 1.f, 1.f);
		} else 
			if (partner->Partnered.selected == 1)
			drawText(textPos, &keyString, MC_Color(150, 30, 255), 1.f, 1.f);
	      else 
		if (partner->Partnered.selected == 0)
		drawText(textPos, &keyString, MC_Color(0, 0, 255), 1.f, 1.f);
		else
		drawText(textPos, &keyString, MC_Color(0, 246, 255), 1.f, 1.f);
	} else {
		pos.x += Key->keystrokesX;
		pos.y -= Key->keystrokesY;
		pos.x -= 9.f;
		pos.y += 9.f;
		vec4 rectPos(
			pos.x,
			pos.y,
			pos.x + ((key == *input->spaceBarKey) ? 64.f : 20.f),
			pos.y + ((key == *input->spaceBarKey) ? 15.f : 20.f));
		vec2 textPos(
			(rectPos.x + (rectPos.z - rectPos.x) / 2) - (DrawUtils::getTextWidth(&keyString) / 2.f),
			rectPos.y + 10.f - DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight() / 2.f);

		fillRectangle(rectPos, GameData::isKeyDown(key) ? MC_Color(85, 85, 85) : MC_Color(12, 12, 12), Key->opacity);
		if (Key->keybindsRGB) {
		drawRectangle(rectPos, GameData::isKeyDown(key) ? MC_Color() : MC_Color(currColor), 1.f);
		drawText(textPos, &keyString, MC_Color(currColor), 1.f, 1.f);
		} else if (partner->Partnered.selected == 1)
		drawText(textPos, &keyString, MC_Color(150, 30, 255), 1.f, 1.f);
		else if (partner->Partnered.selected == 0)
		drawText(textPos, &keyString, MC_Color(0, 0, 255), 1.f, 1.f);
		else
		drawText(textPos, &keyString, MC_Color(0, 246, 255), 1.f, 1.f);
	}
}

void DrawUtils::drawLeftMouseKeystroke(vec2 pos) {
	static auto key = moduleMgr->getModule<KeyStrokes>();
	static auto partner = moduleMgr->getModule<Partner>();
	std::string keyString;
	keyString = "LMB";
	pos.x += key->keystrokesX;
	pos.y -= key->keystrokesY;
	pos.x -= 9.f;
	pos.y += 9.f;
	vec4 rectPos(
		pos.x,
		pos.y + 4,
		pos.x + 31.f,
		pos.y + 20.f);
	fillRectangle(rectPos, GameData::GameData::isLeftClickDown() ? MC_Color(85, 85, 85) : MC_Color(12, 12, 12), key->opacity);
	vec2 textPos(
	(rectPos.x + (rectPos.z - rectPos.x) / 2) - (DrawUtils::getTextWidth(&keyString) / 2.f),
	rectPos.y + 8.f - DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight() / 2.f);
	if (key->keybindsRGB) {
	drawRectangle(rectPos, GameData::GameData::isLeftClickDown() ? MC_Color() : MC_Color(currColor), 1.f);
	drawText(textPos, &keyString, MC_Color(currColor), 1.f, 1.f);
	} else if (partner->Partnered.selected == 1)
	drawText(textPos, &keyString, MC_Color(150, 30, 255), 1.f, 1.f);
	else
	if (partner->Partnered.selected == 0)
	drawText(textPos, &keyString, MC_Color(0, 0, 255), 1.f, 1.f);
	else
	drawText(textPos, &keyString, MC_Color(0, 246, 255), 1.f, 1.f);
}

void DrawUtils::drawRightMouseKeystroke(vec2 pos) {
	static auto key = moduleMgr->getModule<KeyStrokes>();
	static auto partner = moduleMgr->getModule<Partner>();
	std::string keyString;
	keyString = "RMB";
	pos.x += key->keystrokesX;
	pos.y -= key->keystrokesY;
	pos.x -= 9.f;
	pos.y += 9.f;
	vec4 rectPos(
		pos.x,
		pos.y + 4,
		pos.x + 31.f,
		pos.y + 20.f);
	fillRectangle(rectPos, GameData::GameData::isRightClickDown() ? MC_Color(85, 85, 85) : MC_Color(12, 12, 12), key->opacity);
	vec2 textPos(
		(rectPos.x + (rectPos.z - rectPos.x) / 2) - (DrawUtils::getTextWidth(&keyString) / 2.f),
		rectPos.y + 8.f - DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight() / 2.f);
	if (key->keybindsRGB) {
	drawRectangle(rectPos, GameData::GameData::isRightClickDown() ? MC_Color() : MC_Color(currColor), 1.f);
	drawText(textPos, &keyString, MC_Color(currColor), 1.f, 1.f);
	} else 
	if (partner->Partnered.selected == 1)
		drawText(textPos, &keyString, MC_Color(150, 30, 255), 1.f, 1.f);
	else
	if (partner->Partnered.selected == 0)
	drawText(textPos, &keyString, MC_Color(0, 0, 255), 1.f, 1.f);
	else
	drawText(textPos, &keyString, MC_Color(0, 246, 255), 1.f, 1.f);
}

void DrawUtils::CPS(vec2 pos) {
	static auto key = moduleMgr->getModule<KeyStrokes>();
	static auto partner = moduleMgr->getModule<Partner>();
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	{
		std::string cpsText = "CPS: " + std::to_string(g_Data.getLeftCPS()) + " - " + std::to_string(g_Data.getRightCPS());
		pos.x += key->keystrokesX;
		pos.y -= key->keystrokesY;
		pos.x -= 9.f;
		pos.y += 9.f;
		vec4 rectPos(
			// box
			pos.x,
			pos.y,
			pos.x + 64.f,
			pos.y + 15.f);
		vec2 textPos(
			(rectPos.x + (rectPos.z - rectPos.x) / 2) - (DrawUtils::getTextWidth(&cpsText) / 2.f),
			rectPos.y + 7.f - DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight() / 2.f);

		fillRectangle(rectPos, g_Data.getLeftCPS() or g_Data.getRightCPS() ? MC_Color(12, 12, 12) : MC_Color(12, 12, 12), key->opacity);
		if (key->keybindsRGB) {
			drawRectangle(rectPos, g_Data.getLeftCPS() or g_Data.getRightCPS() ? MC_Color(currColor) : MC_Color(currColor), 1.f);
			drawText(textPos, &cpsText, MC_Color(currColor), 1.f, 1.f);
		} else 
		if (partner->Partnered.selected == 1)
		drawText(textPos, &cpsText, MC_Color(150, 30, 255), 1.f, 1.f);
		else
		if (partner->Partnered.selected == 0)
		drawText(textPos, &cpsText, MC_Color(0, 0, 255), 1.f, 1.f);
		else
		drawText(textPos, &cpsText, MC_Color(0, 246, 255), 1.f, 1.f);
	}
}
vec2 DrawUtils::worldToScreen(const vec3& world) {
	vec2 ret{-1, -1};
	refdef->OWorldToScreen(origin, world, ret, fov, screenSize);
	return ret;
}
void DrawUtils::drawLine3d(const vec3& start, const vec3& end) {
	if(game3dContext == 0 || entityFlatStaticMaterial == 0)
		return;

	auto myTess = DrawUtils::get3dTessellator();

	DrawUtils::tess__begin(myTess, 4, 2);

	auto start1 = start.sub(origin);
	auto end1 = end.sub(origin);

	tess_vertex(myTess, start1.x, start1.y, start1.z);
	tess_vertex(myTess, end1.x, end1.y, end1.z);

	meshHelper_renderImm(game3dContext, myTess, entityFlatStaticMaterial);
}
void DrawUtils::drawBox3d(vec3 lower, vec3 upper) {
	if (game3dContext == 0 || entityFlatStaticMaterial == 0)
		return;

	auto myTess = DrawUtils::get3dTessellator();

	DrawUtils::tess__begin(myTess, 4, 12);

	vec3 diff;
	diff.x = upper.x - lower.x;
	diff.y = upper.y - lower.y;
	diff.z = upper.z - lower.z;

	lower = lower.sub(origin);

	vec3 vertices[8];
	vertices[0] = vec3(lower.x, lower.y, lower.z);
	vertices[1] = vec3(lower.x + diff.x, lower.y, lower.z);
	vertices[2] = vec3(lower.x, lower.y, lower.z + diff.z);
	vertices[3] = vec3(lower.x + diff.x, lower.y, lower.z + diff.z);

	vertices[4] = vec3(lower.x, lower.y + diff.y, lower.z);
	vertices[5] = vec3(lower.x + diff.x, lower.y + diff.y, lower.z);
	vertices[6] = vec3(lower.x, lower.y + diff.y, lower.z + diff.z);
	vertices[7] = vec3(lower.x + diff.x, lower.y + diff.y, lower.z + diff.z);

	#define line(m, n) tess_vertex(myTess, m.x, m.y, m.z); \
		tess_vertex(myTess, n.x, n.y, n.z);
	
	#define li(m, n) line(vertices[m], vertices[n]);

	li(0, 1);
	li(1, 3);
	li(3, 2);
	li(2, 0);

	li(4, 5);
	li(5, 7);
	li(7, 6);
	li(6, 4);

	li(0, 4);
	li(1, 5);
	li(2, 6);
	li(3, 7);

	#undef li
	#undef line
	
	meshHelper_renderImm(game3dContext, myTess, entityFlatStaticMaterial);
}
void DrawUtils::fillRectangle(vec4 pos, const MC_Color col, float alpha) {
	DrawUtils::setColor(col.r, col.g, col.b, alpha);
	DrawUtils::drawQuad({pos.x, pos.w}, {pos.z, pos.w}, {pos.z, pos.y}, {pos.x, pos.y});
}

void DrawUtils::drawBoxTops(const vec4& pos, const MC_Color& col, float alpha, float thickness) {
	DrawUtils::setColor(col.r, col.g, col.b, alpha);
	DrawUtils::drawLine({pos.x, pos.w}, {pos.z, pos.w}, thickness);
	DrawUtils::drawLine({pos.z, pos.y}, {pos.x, pos.y}, thickness);
}

void DrawUtils::drawBoxSides(const vec4& pos, const MC_Color& col, float alpha, float thickness) {
	DrawUtils::setColor(col.r, col.g, col.b, alpha);
	DrawUtils::drawLine({pos.z, pos.y}, {pos.z, pos.w}, thickness);
	DrawUtils::drawLine({pos.x, pos.y}, {pos.x, pos.w}, thickness);
}

void DrawUtils::drawTop3(const vec4& pos, const MC_Color& col, float alpha, float lineWidth) {
	lineWidth /= 2;
	fillRectangle(vec4(pos.x - lineWidth, pos.y - lineWidth, pos.z + lineWidth, pos.y + lineWidth), col, alpha);  // TOP
	fillRectangle(vec4(pos.x - lineWidth, pos.y, pos.x + lineWidth, pos.w), col, alpha);                          // LEFT
	fillRectangle(vec4(pos.z - lineWidth, pos.y, pos.z + lineWidth, pos.w), col, alpha);                          //
}

void DrawUtils::drawBoxBottom(const vec4& pos, const MC_Color& col, float alpha, float thickness) {
	DrawUtils::setColor(col.r, col.g, col.b, alpha);
	DrawUtils::drawLine({pos.z, pos.y}, {pos.x, pos.y}, thickness);
}

void DrawUtils::fillRectangle2(vec4 pos, const _RGB col, float alpha) {
	DrawUtils::setColor(col.r, col.g, col.b, alpha);
	DrawUtils::drawQuad({pos.x, pos.w}, {pos.z, pos.w}, {pos.z, pos.y}, {pos.x, pos.y});
}

void DrawUtils::DrawOutline(vec2 position, vec2 size, MC_Color colour, float width) {
	if (renderCtx == nullptr) return;
	renderCtx->drawRect(vec4(position.x, position.x + size.x, position.y, position.y + size.y), MC_Color(colour), colour.a, (int)width);
};

MC_Color MC_Color::lerp(const MC_Color& o, float t) const {
	return MC_Color(Utils::lerp(r, o.r, t), Utils::lerp(g, o.g, t), Utils::lerp(b, o.b, t), Utils::lerp(a, o.a, t));
}
void DrawUtils::tess__begin(Tessellator* tess, int vertexFormat, int numVerticesReserved) {
	__int64 tesselator = reinterpret_cast<__int64>(tess);

	using tess_begin_t = void(__fastcall*)(Tessellator*, int, int);
	static tess_begin_t tess_begin = reinterpret_cast<tess_begin_t>(FindSignature("48 89 5C 24 ?? 55 48 83 EC ?? 80 B9 ?? ?? ?? ?? 00 45"));
	tess_begin(tess, vertexFormat, numVerticesReserved);
	/*if (!*(unsigned char*)(tesselator + 0x1FC) && !*(unsigned char*)(tesselator + 0x1B5)) {
		mce__VertexFormat__disableHalfFloats(tesselator, 0, 0);
		*(unsigned char*)(tesselator + 8) = vertexFormat;
		*(unsigned char*)(tesselator + 0x1B4) = 0;
		*(unsigned char*)(tesselator + 0x1FC) = 1;
		*(unsigned char*)(tesselator + 0x1FD) = 0;
		*(unsigned int*)(tesselator + 0x16C) = 0;
		*(__int64*)(tesselator + 0x150) = *(__int64*)(tesselator + 0x148);
		if (!*(unsigned char*)tesselator)
			*(unsigned char*)(tesselator + 0xC8) = 1;
		if (numVerticesReserved != 0)
			Tessellator__initializeFormat(tesselator + 8, numVerticesReserved);
	}*/
}
void DrawUtils::setGameRenderContext(__int64 ctx) {
	game3dContext = ctx;
	if (g_Data.getClientInstance()->levelRenderer != nullptr)
		origin = g_Data.getClientInstance()->levelRenderer->getOrigin();

	if(ctx){
		LARGE_INTEGER EndingTime, ElapsedMicroseconds;
		LARGE_INTEGER Frequency;
		QueryPerformanceFrequency(&Frequency);
		QueryPerformanceCounter(&EndingTime);
		ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - g_Data.getLastUpdateTime();

		ElapsedMicroseconds.QuadPart *= 1000000;
		int ticksPerSecond = 20;
		if(g_Data.getClientInstance()->minecraft)
			ticksPerSecond = (int)*g_Data.getClientInstance()->minecraft->timer;
		if(ticksPerSecond < 1)
			ticksPerSecond = 1;
		ElapsedMicroseconds.QuadPart /= Frequency.QuadPart / ticksPerSecond;
		lerpT = (ElapsedMicroseconds.QuadPart / 1000000.f);
		if (lerpT > 1)
			lerpT = 1;
		else if (lerpT < 0)
			lerpT = 0;
	}
}
float DrawUtils::getLerpTime() {
	return lerpT;
}
vec3 DrawUtils::getOrigin() {
	return origin;
}
void DrawUtils::drawLinestrip3d(const std::vector<vec3>& points) {
	if(game3dContext == 0 || entityFlatStaticMaterial == 0)
		return;

	auto myTess = DrawUtils::get3dTessellator();

	DrawUtils::tess__begin(myTess, 5, (int)points.size());

	/*
	 * 1: quads
	 * 2: triangle list
	 * 3: trianglestrip (6)
	 * 4: line list
	 * 5: line strip (7)
	 */

	for(const auto& p : points){
		auto pD = p.sub(origin);
		tess_vertex(myTess, pD.x, pD.y, pD.z);
	}
	

	meshHelper_renderImm(game3dContext, myTess, entityFlatStaticMaterial);
}

void DrawUtils::drawTracer(const vec3& ent, int damageTime) {
	static float rcolors2[4];           // Rainbow color array RGBA
	static float disabledRcolors2[4];  // Rainbow Colors, but for disabled modules
	static float currColor[4];        // ArrayList colors

	// Rainbow color updates
	{
		Utils::ApplyRainbow(rcolors2, 0.001f);  // Increase Hue of rainbow color array
		disabledRcolors2[0] = std::min(1.f, rcolors2[0] * 0.4f + 0.2f);
		disabledRcolors2[1] = std::min(1.f, rcolors2[1] * 0.4f + 0.2f);
		disabledRcolors2[2] = std::min(1.f, rcolors2[2] * 0.4f + 0.2f);
		disabledRcolors2[3] = 1;
	}
	int a = 0;
	int b = 0;
	int c = 0;
	c++;
	b++;
	currColor[3] = rcolors2[3];
	Utils::ColorConvertRGBtoHSV(rcolors2[0], rcolors2[1], rcolors2[2], currColor[0], currColor[1], currColor[2]);
	currColor[0] += 5.f / a * c;
	Utils::ColorConvertHSVtoRGB(currColor[0], currColor[0], currColor[1], currColor[0], currColor[0], currColor[1]);

	static auto tracerMod = moduleMgr->getModule<Tracer>();
	vec2 target;
	refdef->OWorldToScreen(origin, ent, target, fov, screenSize);
	//vec2 mid(((g_Data.getClientInstance()->getGuiData()->widthGame) / 2), ((g_Data.getClientInstance()->getGuiData()->heightGame) / 2));
	static auto partner = moduleMgr->getModule<Partner>();
	if (partner->Partnered.selected == 0) {
		if (target != vec2(0, 0)) {

			if (tracerMod->type.selected == 1) {
				vec2 mid(((g_Data.getClientInstance()->getGuiData()->widthGame) / 2), ((g_Data.getClientInstance()->getGuiData()->heightGame - 330) / 2));
				if (target != vec2(0, 0)) {
					if (tracerMod->RGB) {
						DrawUtils::setColor(disabledRcolors2[0], disabledRcolors2[1], disabledRcolors2[2], 1);
					} else {
						DrawUtils::setColor(((float)0 / (float)255), ((float)0 / (float)255), ((float)255 / (float)255), (float)fmax(0.1f, (float)fmin(1.f, 15 / (damageTime + 1))));
					}
					DrawUtils::drawLine(mid, target, 0.2f);
				}
			}
			if (tracerMod->type.selected == 2) {
				vec2 mid(((g_Data.getClientInstance()->getGuiData()->widthGame) / 2), ((g_Data.getClientInstance()->getGuiData()->heightGame + 330) / 2));
				if (target != vec2(0, 0)) {
					if (tracerMod->RGB) {
						DrawUtils::setColor(disabledRcolors2[0], disabledRcolors2[1], disabledRcolors2[2], 1);
					} else {
						DrawUtils::setColor(((float)0 / (float)255), ((float)0 / (float)255), ((float)255 / (float)255), (float)fmax(0.1f, (float)fmin(1.f, 15 / (damageTime + 1))));
					}
					DrawUtils::drawLine(mid, target, 0.2f);
				}
			}
			if (tracerMod->type.selected == !1) {
				vec2 mid(((g_Data.getClientInstance()->getGuiData()->widthGame) / 2), ((g_Data.getClientInstance()->getGuiData()->heightGame) / 2));
				if (target != vec2(0, 0)) {
					if (tracerMod->RGB) {
						DrawUtils::setColor(disabledRcolors2[0], disabledRcolors2[1], disabledRcolors2[2], 1);
					} else {
						DrawUtils::setColor(((float)0 / (float)255), ((float)0 / (float)255), ((float)255 / (float)255), (float)fmax(0.1f, (float)fmin(1.f, 15 / (damageTime + 1))));
					}
					DrawUtils::drawLine(mid, target, 0.2f);
				}
			}
		}
	} else {
		if (target != vec2(0, 0)) {

			if (tracerMod->type.selected == 1) {
				vec2 mid(((g_Data.getClientInstance()->getGuiData()->widthGame) / 2), ((g_Data.getClientInstance()->getGuiData()->heightGame - 330) / 2));
				if (target != vec2(0, 0)) {
					if (tracerMod->RGB) {
						DrawUtils::setColor(disabledRcolors2[0], disabledRcolors2[1], disabledRcolors2[2], 1);
					} else {
						DrawUtils::setColor(((float)tracerMod->customR / (float)255), ((float)tracerMod->customG / (float)255), ((float)tracerMod->customB / (float)255), (float)fmax(0.1f, (float)fmin(1.f, 15 / (damageTime + 1))));
					}
					DrawUtils::drawLine(mid, target, 0.2f);
				}
			}
			if (tracerMod->type.selected == 2) {
				vec2 mid(((g_Data.getClientInstance()->getGuiData()->widthGame) / 2), ((g_Data.getClientInstance()->getGuiData()->heightGame + 330) / 2));
				if (target != vec2(0, 0)) {
					if (tracerMod->RGB) {
						DrawUtils::setColor(disabledRcolors2[0], disabledRcolors2[1], disabledRcolors2[2], 1);
					} else {
						DrawUtils::setColor(((float)tracerMod->customR / (float)255), ((float)tracerMod->customG / (float)255), ((float)tracerMod->customB / (float)255), (float)fmax(0.1f, (float)fmin(1.f, 15 / (damageTime + 1))));
					}
					DrawUtils::drawLine(mid, target, 0.2f);
				}
			}
			if (tracerMod->type.selected == !1) {
				vec2 mid(((g_Data.getClientInstance()->getGuiData()->widthGame) / 2), ((g_Data.getClientInstance()->getGuiData()->heightGame) / 2));
				if (target != vec2(0, 0)) {
					if (tracerMod->RGB) {
						DrawUtils::setColor(disabledRcolors2[0], disabledRcolors2[1], disabledRcolors2[2], 1);
					} else {
						DrawUtils::setColor(((float)tracerMod->customR / (float)255), ((float)tracerMod->customG / (float)255), ((float)tracerMod->customB / (float)255), (float)fmax(0.1f, (float)fmin(1.f, 15 / (damageTime + 1))));
					}
					DrawUtils::drawLine(mid, target, 0.2f);
				}
			}
		}
	}
}
