#pragma once
#include "../Module.h"


class ComboCounter : public VisualModule {
public:
	bool hookMade = false;

	bool showComboText = true;

	uint16_t comboValue = 0;

	float scale = 1.f;
	ClickguiColor textColor = ClickguiColor(1.f, 1.f, 1.f, 1.f, true);
	ClickguiColor backgroundColor = ClickguiColor(0.156862f, 0.156862f, 0.156862f, 0.4f, true);

	ComboCounter() : VisualModule("Combo Counter", Vec2(10.f, 80.f), Vec2(10.f, 95.f), mltext("Show the amount of hit you do on someone without getting hit.", "Affiche le nombre de coup que vous infligez a votre adversaire\nsans qu'il puisse vous attaquez.")) {
		addBoolSetting(mltext("Show Combo: text", "Afficher le texte Combo:"), "showComboText", showComboText, &showComboText);
		addFloatSetting(mltext("Scale", "Multiplicateur de taille"), "scale", scale, &scale, 0.5f, 1.5f);
		addColorSetting(mltext("Text Color", "Couleur du Texte"), "textColor", textColor, &textColor);
		addColorSetting(mltext("Background Color", "Couleur du Fond"), "backColor", backgroundColor, &backgroundColor);
	}

	void onAttack(Actor* act);
	virtual void onRender() override;
	virtual void onTick(Gamemode* gm);
};