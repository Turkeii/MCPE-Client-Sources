#pragma once
#include "Utils/mem.h"
#include <thread>
#include "Plasmic/Module.h"


template <typename T>
void Swap(T& a, T& b) {
	T tmp = a;
	a = b;
	b = tmp;
}

//http://lolengine.net/blog/2013/01/13/fast-rgb-to-hsv
void RGBtoHSV(float r, float g, float b, float& out_h, float& out_s, float& out_v) {
	float K = 0.f;
	if (g < b) {
		Swap(g, b);
		K = -1.f;
	}
	if (r < g) {
		Swap(r, g);
		K = -2.f / 6.f - K;
	}

	const float chroma = r - (g < b ? g : b);
	out_h = fabsf(K + (g - b) / (6.f * chroma + 1e-20f));
	out_s = chroma / (r + 1e-20f);
	out_v = r;
};


//http://en.wikipedia.org/wiki/HSL_and_HSV
void HSVtoRGB(float h, float s, float v, float& out_r, float& out_g, float& out_b) {
	if (s == 0.0f) { // gray so no gaming here
		out_r = out_g = out_b = v;
		return;
	}

	h = fmodf(h, 1.0f) / (60.0f / 360.0f);
	int i = (int)h;
	float f = h - (float)i;
	float p = v * (1.0f - s);
	float q = v * (1.0f - s * f);
	float t = v * (1.0f - s * (1.0f - f));

	switch (i) {
	case 0:
		out_r = v; out_g = t; out_b = p; break;
	case 1:
		out_r = q; out_g = v; out_b = p; break;
	case 2:
		out_r = p; out_g = v; out_b = t; break;
	case 3:
		out_r = p; out_g = q; out_b = v; break;
	case 4:
		out_r = t; out_g = p; out_b = v; break;
	case 5:
	default:
		out_r = v; out_g = p; out_b = q; break;
	}
};







void updateRGB() {
	while (mem::isRunning) {

		// Logf("amount of colors: %d     r: %f", ClickguiColor::colors.size(), ClickguiColor::colors[0]->color.r);

		for (uint16_t i = 0; i < ClickguiColor::colors.size(); i++) {
			if (ClickguiColor::colors[i]->isRGB) {
				float* rcolors = (float*)&ClickguiColor::colors[i]->color;

				RGBtoHSV(rcolors[0], rcolors[1], rcolors[2], rcolors[0], rcolors[1], rcolors[2]);

				//rcolors[0] += 0.001f;
				rcolors[0] += ClickguiColor::colors[i]->rgbSpeed;
				if (rcolors[0] >= 1.f)
					rcolors[0] = 0.f;

				HSVtoRGB(rcolors[0], rcolors[1], rcolors[2], rcolors[0], rcolors[1], rcolors[2]);
			}

		}

		std::this_thread::sleep_for(std::chrono::microseconds(15000));
	}
}