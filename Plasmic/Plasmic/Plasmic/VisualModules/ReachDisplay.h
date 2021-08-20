#pragma once
#include "../Module.h"


class ReachDisplay : public VisualModule {
public:
	bool oneNumber = false;
	bool showReachText = true;

	Vec3 lastHitboxHitPoint;
	float lastHitValue = 0.f;

	float scale = 1.f;
	ClickguiColor textColor = ClickguiColor(1.f, 1.f, 1.f, 1.f, true);
	ClickguiColor backgroundColor = ClickguiColor(0.156862f, 0.156862f, 0.156862f, 0.4f, true);

	ReachDisplay() : VisualModule("Reach Display", Vec2(10.f, 65.f), Vec2(25.f, 15.f), "Display the reach of your last hit\n*Due to internal ping it isn't 100% accurate") {
		addBoolSetting(mltext("Only one digit after the .", "Un seul nombre apres le ."), "oneNumber", oneNumber, &oneNumber);
		addBoolSetting(mltext("Show Reach: text", "Afficher le texte Reach:"), "showReachText", showReachText, &showReachText);
		addFloatSetting(mltext("Scale", "Multiplicateur de taille"), "scale", scale, &scale, 0.5f, 1.5f);
		addColorSetting(mltext("Text Color", "Couleur du Texte"), "textColor", textColor, &textColor);
		addColorSetting(mltext("Background Color", "Couleur du Fond"), "backColor", backgroundColor, &backgroundColor);
	}

	void CalcHitValue();
	virtual void onRender() override;
};