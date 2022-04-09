#include "Radar.h"

#include <array>

float currColor[4];
int size = 100;
float pixelSize = 2.5f;
float cent = size / 2.f;
float pxSize = pixelSize / 2.f;
float topPad = -1;
float zoom = 1;
float pxOpacity = 1;
bool RGB = true;
bool grid = true;
// didn't bother puting this onto the header file and making it non-static...
// it's the only one that could be. since everything else is accessed at renderEntity()
float bgOpacity = 0.2f;

Radar::Radar() : IModule(0x0, Category::VISUAL, "Radar") {
	//registerBoolSetting("RGB", &RGB, RGB);
	registerBoolSetting("Show Grid", &grid, true);
	registerIntSetting("Size", &size, size, 50, 200);
	registerFloatSetting("Pixel Size", &pixelSize, pixelSize, 2, 4);
	registerFloatSetting("Zoom", &zoom, zoom, 1.0f / 4.0f, 4.0f);
	registerFloatSetting("Background Opacity", &bgOpacity, bgOpacity, 0.1f, 1.0f);
	registerFloatSetting("Pixel Opacity", &pxOpacity, pxOpacity, 0.1f, 1.0f);
}

Radar::~Radar() {
}

const char* Radar::getModuleName() {
	return "Radar";
}

float effectiveZoom = 1;
float angle = 0;
float c, s;
vec3 playerPos;

void recalculateScale() {
	effectiveZoom = zoom * (size / 100.f);
	cent = size / 2.f;
	pxSize = pixelSize / 2.f * effectiveZoom;
	topPad = g_Data.getGuiData()->heightGame / 2.f;
}

void renderEntity(C_Entity* currentEntity, bool isRegularEntity) {
	if (g_Data.isInGame() && g_Data.getLocalPlayer() != nullptr && g_Data.canUseMoveKeys()) {
		C_LocalPlayer* player = g_Data.getLocalPlayer();
		if (currentEntity == nullptr)
			return;

		if (currentEntity == player)  // Skip Local player
			return;

		if (!player->canAttack(currentEntity, false))
			return;

		if (!currentEntity->isAlive())
			return;

		if (!Target::isValidTarget(currentEntity))
			return;

		vec3* start = currentEntity->getPosOld();
		vec3* end = currentEntity->getPos();

		vec3 lerped = start->lerp(end, DrawUtils::getLerpTime());

		const auto delta = lerped.sub(playerPos);
		const float dist = delta.magnitudexz();

		const vec2 relPos = vec2(
			cent - ((delta.x * c) - (delta.z * s)),
			topPad - ((delta.x * s) + (delta.z * c)));
		if (relPos.x > 0 && relPos.x < size && relPos.y > topPad - cent && relPos.y < topPad + cent) {
			DrawUtils::drawRectangle(vec4(0, topPad - cent, (float)size, topPad + cent), MC_Color(currColor), bgOpacity);
		}
		return;
	}
}

void Radar::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	if (g_Data.isInGame() && g_Data.getLocalPlayer() != nullptr && g_Data.canUseMoveKeys()) {
		C_LocalPlayer* player = g_Data.getLocalPlayer();

		if (player == nullptr) return;

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
		recalculateScale();

		DrawUtils::fillRectangle(vec4(0, topPad - cent, (float)size, topPad + cent), MC_Color(0, 0, 0), bgOpacity);

		auto pPos = g_Data.getClientInstance()->levelRenderer->getOrigin();
		playerPos = pPos;

		angle = (180.0f - player->yaw) + 180.0f;
		if (angle < 0) angle += 360;
		angle *= RAD_DEG;

		s = sin(angle) * effectiveZoom;
		c = cos(angle) * effectiveZoom;

		auto computePos = [=](vec2 pos) {
			auto delta = pos.sub(pPos.x, pPos.z);
			return vec2(
				cent - ((delta.x * c) - (delta.y * s)),
				topPad - ((delta.x * s) + (delta.y * c)));
		};

		float chunkX = int(floor(pPos.x)) & ~(15);
		float chunkZ = int(floor(pPos.z)) & ~(15);
		// Draw grid
		if (grid) {
			// we start at the player pos, and clip the grid lines to the view rectangle until the lines are no longer inside, then we repeat the process in the opposite direction, then we do the same for the other axis

			struct FiniteLine {
				vec2 a, b;

				// copied straight from wikipedia line-line intersections
				bool intersectionPointWithInfOther(vec2 oa, vec2 ob, vec2& out) {
					float den = (a.x - b.x) * (oa.y - ob.y) - (a.y - b.y) * (oa.x - ob.x);
					if (den == 0)  // lines are parallel
						return false;

					float t = ((a.x - oa.x) * (oa.y - ob.y) - (a.y - oa.y) * (oa.x - ob.x)) / den;
					if (t >= 0 && t <= 1) {
						out = {a.x + t * (b.x - a.x),
							   a.y + t * (b.y - a.y)};
						return true;
					}
					return false;
				}
			};

			std::array<vec2, 4> clipRectPoints = {vec2{0.f, topPad - cent}, vec2{(float)size, topPad - cent}, vec2{(float)size, topPad + cent}, vec2{0.f, topPad + cent}};
			DrawUtils::drawRectangle(vec4(0, topPad - cent, (float)size, topPad + cent), MC_Color(currColor), bgOpacity);
			std::array<FiniteLine, 4> clipRectLines;
			auto last = clipRectPoints[3];

			for (int i = 0; i < 4; i++) {
				auto cur = clipRectPoints[i];

				clipRectLines[i] = {last, cur};
				last = cur;
			}

			std::vector<FiniteLine> lines;

			auto computeRectIntersections = [&](vec2 p1, vec2 p2) {
				vec2 a, b;
				bool hadIntersection = false;
				for (int i = 0; i < (hadIntersection ? 4 : 3); i++) {
					auto& line = clipRectLines[i];
					bool didIntersect = line.intersectionPointWithInfOther(p1, p2, hadIntersection ? b : a);
					if (didIntersect) {
						if (hadIntersection) {
							lines.push_back({a, b});
							return true;
						}
						hadIntersection = true;
					}
				}
				return false;
			};

			//x axis
			for (float gridX = chunkX; true; gridX += 16) {
				vec2 p1 = computePos({gridX, chunkZ}), p2 = computePos({gridX, chunkZ + 1});
				if (!computeRectIntersections(p1, p2))
					break;
			}
			for (float gridX = chunkX - 16; true; gridX -= 16) {
				vec2 p1 = computePos({gridX, chunkZ}), p2 = computePos({gridX, chunkZ + 1});
				if (!computeRectIntersections(p1, p2))
					break;
			}

			//z axis
			for (float gridZ = chunkZ; true; gridZ += 16) {
				vec2 p1 = computePos({chunkX, gridZ}), p2 = computePos({chunkX + 1, gridZ});
				if (!computeRectIntersections(p1, p2))
					break;
			}
			for (float gridZ = chunkZ - 16; true; gridZ -= 16) {
				vec2 p1 = computePos({chunkX, gridZ}), p2 = computePos({chunkX + 1, gridZ});
				if (!computeRectIntersections(p1, p2))
					break;
			}

			DrawUtils::setColor(0.7f, 0.7f, 0.7f, 0.1f);
			// draw all lines
			for (auto line : lines) {
				DrawUtils::drawLine(line.a, line.b, 0.25f);
			}
		}

		// Draw the chunk the player is in
		if (grid) {
			DrawUtils::setColor(0.9f, 0.9f, 0.9f, 0.6f);
			std::array<vec2, 4> rect = {computePos({chunkX, chunkZ}), computePos({chunkX + 16, chunkZ}), computePos({chunkX + 16, chunkZ + 16}), computePos({chunkX, chunkZ + 16})};
			auto last = rect[3];

			for (int i = 0; i < 4; i++) {
				auto cur = rect[i];

				DrawUtils::drawLine(last, cur, 0.25f);
				last = cur;
			}
		}

		g_Data.forEachEntity(renderEntity);

		const float pxSize = pixelSize * 0.75f * effectiveZoom;
		DrawUtils::setColor(1, 1, 1, pxOpacity);
		vec2 center(cent, topPad);
		DrawUtils::drawTriangle(center.add(-pxSize * 0.9f, pxSize * 2.f), center.add(pxSize * 0.9f, pxSize * 2.f), center);
	}
}