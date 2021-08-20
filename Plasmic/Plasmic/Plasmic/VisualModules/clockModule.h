#pragma once
#include "../Module.h"

class clockModule : public VisualModule {

public:
	bool is24 = false;
	bool showSeconds = false;
	bool isGameTime = false;

	float scale = 1.f;
	ClickguiColor textColor = ClickguiColor(1.f, 1.f, 1.f, 1.f, true);
	ClickguiColor backgroundColor = ClickguiColor(0.156862f, 0.156862f, 0.156862f, 0.4f, true);

	clockModule() : VisualModule("Clock", Vec2(10.f, 20.f), Vec2(50.f,15.f), mltext("Display the time.", "Affiche le temps.")) {
		addBoolSetting(mltext("24 hours format", "Format 24 heures"), "Clock24", is24, &is24, true);
		addBoolSetting(mltext("Show seconds", "Afficher les secondes"), "showSeconds", showSeconds, &showSeconds, true);
		addBoolSetting(mltext("Use game time", "Utiliser le temps du jeu"), "isGameTime", isGameTime, &isGameTime, true);

		addFloatSetting(mltext("Scale", "Multiplicateur de taille"), "scale", scale, &scale, 0.5f, 1.5f);
		addColorSetting(mltext("Text Color", "Couleur du Texte"), "textColor", textColor, &textColor);
		addColorSetting(mltext("Background Color", "Couleur du Fond"), "backColor", backgroundColor, &backgroundColor);
	}


	virtual void onRender() override;
	virtual void onTick(Gamemode* gm) override;

};

