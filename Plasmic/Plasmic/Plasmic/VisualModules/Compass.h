#pragma once
#include "../Module.h"

class Compass : public VisualModule {
public:

	float scale = 1.f;
	ClickguiColor textColor = ClickguiColor(1.f, 1.f, 1.f, 1.f, true);
	ClickguiColor backgroundColor = ClickguiColor(0.4f, 0.4f, 0.4f, 0.f, true);

	int compassAmount = 45;
	float compassWidth = 100.f;
	int fadeAt = 20;
	bool isthirdperson = false;

	Compass() : VisualModule("Direction HUD", Vec2(50.f, 10.f), Vec2(100.f, 10.f), mltext("Shows what dirrection you are looking at.", "Vous montre dans quel dirrection vous regardez.")) {
	
		addIntSetting(mltext("Range", "Portee sur la boussole"), "compassAmount", compassAmount, &compassAmount, 20, 100);
		addFloatSetting(mltext("Width", "Taille horizontal"), "compassWidth", compassWidth, &compassWidth, 50.f, 250.f);
		
		addIntSetting(mltext("FadingAt", "Fond a"), "fadeAt", fadeAt, &fadeAt, 0, 100);

		addFloatSetting(mltext("Scale", "Multiplicateur de taille"), "scale", scale, &scale, 0.5f, 1.5f);
		addColorSetting(mltext("Text Color", "Couleur du Texte"), "textColor", textColor, &textColor);
		addColorSetting(mltext("Background Color", "Couleur du Fond"), "backColor", backgroundColor, &backgroundColor);
	}

	virtual void onRender() override;

};

