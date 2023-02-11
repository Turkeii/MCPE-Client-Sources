#include "Radar.h"
#include <array>
#include "../pch.h"

int size = 85;
float pixelSize = 2.5f;
float cent = size / 2.f;
float pxSize = 2.5f / 2.f;
float topPad = -1.f;
float zoom = 0.70f;
int opacity = 150;

float effectiveZoom = 1.f;
vec3_t playerPos;
float angle = 0;
float c, s;

Radar::Radar() : IModule(0, Category::VISUAL, "Displays nearby players") {
	registerBoolSetting("Grid", &grid, grid);
	registerIntSetting("Opacity", &opacity, opacity, 0, 255);
	registerFloatSetting("Zoom", &zoom, zoom, 0.6f / 2.0f, 2.0f);
}

const char* Radar::getModuleName() {
	return "Radar";
}

void recalculateScale() {
	effectiveZoom = zoom * (size / 100.f);
	cent = size / 2.f;
	pxSize = pixelSize / 2.f * effectiveZoom;
	topPad = g_Data.getGuiData()->heightGame / 2.f;
}

void renderEntity(C_Entity* currentEntity, bool isRegularEntity) {
	C_LocalPlayer* player = g_Data.getLocalPlayer();
	if (currentEntity == nullptr)
		return;

	if (currentEntity == player)  // Skip Local player
		return;

	if (!player->canAttack(currentEntity, false))
		return;

	if (!currentEntity->isAlive())
		return;

	if (!TargetUtil::isValidTarget(currentEntity))
		return;

	vec3_t* start = currentEntity->getPosOld();
	vec3_t* end = currentEntity->getPos();

	vec3_t lerped = start->lerp(end, DrawUtils::getLerpTime());

	const auto delta = lerped.sub(playerPos);
	const float dist = delta.magnitudexz();

	const vec2_t relPos = vec2_t(
		cent - ((delta.x * c) - (delta.z * s)),
		topPad - ((delta.x * s) + (delta.z * c)));
	if (relPos.x > 0 && relPos.x < size && relPos.y > topPad - cent && relPos.y < topPad + cent) {
		DrawUtils::fillRoundRectangle(vec4_t(relPos.x - pxSize, relPos.y - pxSize, relPos.x + pxSize, relPos.y + pxSize), MC_Color(255, 255, 255, 255), false);
	}
}

void Radar::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	// Background
	DrawUtils::fillRoundRectangle(vec4_t(0, topPad - cent, (float)size, topPad + cent), MC_Color(0, 0, 0, opacity), false);

	auto pPos = g_Data.getClientInstance()->levelRenderer->getOrigin();
	playerPos = pPos;

	angle = (180.0f - player->yaw) + 180.0f;
	if (angle < 0) angle += 360;
	angle *= RAD_DEG;

	s = sin(angle) * effectiveZoom;
	c = cos(angle) * effectiveZoom;

	auto computePos = [=](vec2_t pos) {
		auto delta = pos.sub(pPos.x, pPos.z);
		return vec2_t(
			cent - ((delta.x * c) - (delta.y * s)),
			topPad - ((delta.x * s) + (delta.y * c)));
	};

	int chunkX = int(floor(pPos.x)) & ~(15);
	int chunkZ = int(floor(pPos.z)) & ~(15);

	// Draw
	if (grid) {
		struct FiniteLine {
			vec2_t a, b;
			bool intersectionPointWithInfOther(vec2_t oa, vec2_t ob, vec2_t& out) {
				float den = (a.x - b.x) * (oa.y - ob.y) - (a.y - b.y) * (oa.x - ob.x);
				if (den == 0)
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

		std::array<vec2_t, 4> clipRectPoints = {vec2_t{0.f, topPad - cent}, vec2_t{(float)size, topPad - cent}, vec2_t{(float)size, topPad + cent}, vec2_t{0.f, topPad + cent}};
		std::array<FiniteLine, 4> clipRectLines;
		auto last = clipRectPoints[3];

		for (int i = 0; i < 4; i++) {
			auto cur = clipRectPoints[i];

			clipRectLines[i] = {last, cur};
			last = cur;
		}

		std::vector<FiniteLine> lines;
		auto computeRectIntersections = [&](vec2_t p1, vec2_t p2) {
			vec2_t a, b;
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

		// X
		for (int gridX = chunkX; true; gridX += 16) {
			vec2_t p1 = computePos({gridX, chunkZ}), p2 = computePos({gridX, chunkZ + 1});
			if (!computeRectIntersections(p1, p2))
				break;
		}
		for (int gridX = chunkX - 16; true; gridX -= 16) {
			vec2_t p1 = computePos({gridX, chunkZ}), p2 = computePos({gridX, chunkZ + 1});
			if (!computeRectIntersections(p1, p2))
				break;
		}

		// Z
		for (int gridZ = chunkZ; true; gridZ += 16) {
			vec2_t p1 = computePos({chunkX, gridZ}), p2 = computePos({chunkX + 1, gridZ});
			if (!computeRectIntersections(p1, p2))
				break;
		}
		for (int gridZ = chunkZ - 16; true; gridZ -= 16) {
			vec2_t p1 = computePos({chunkX, gridZ}), p2 = computePos({chunkX + 1, gridZ});
			if (!computeRectIntersections(p1, p2))
				break;
		}

		DrawUtils::setColor(0.7f, 0.7f, 0.7f, 0.1f);
		for (auto line : lines) {
			DrawUtils::drawLine(line.a, line.b, 0.25f);
		}
	}

	// Draw Chunk
	if (grid) {
		DrawUtils::setColor(0.9f, 0.9f, 0.9f, 0.6f);
		std::array<vec2_t, 4> rect = {computePos({chunkX, chunkZ}), computePos({chunkX + 16, chunkZ}), computePos({chunkX + 16, chunkZ + 16}), computePos({chunkX, chunkZ + 16})};
		auto last = rect[3];

		for (int i = 0; i < 4; i++) {
			auto cur = rect[i];

			DrawUtils::drawLine(last, cur, 0.25f);
			last = cur;
		}
	}

	g_Data.forEachEntity(renderEntity);

	const float pxSize = pixelSize * 0.75f * effectiveZoom;
	DrawUtils::setColor(1, 1, 1, 1.f);
	vec2_t center(cent, topPad);
	DrawUtils::drawTriangle(center.add(-pxSize * 0.9f, pxSize * 2.f), center.add(pxSize * 0.9f, pxSize * 2.f), center);
}