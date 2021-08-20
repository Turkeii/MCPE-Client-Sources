#pragma once
#include "../Module.h"

class frameCounter : public VisualModule {
public: 
	float reducedWidth = 0.f;
	float scale = 1.f;
	ClickguiColor textColor = ClickguiColor(1.f, 1.f, 1.f, 1.f, true);
	ClickguiColor backgroundColor = ClickguiColor(0.156862f, 0.156862f, 0.156862f, 0.4f, true);


	frameCounter() : VisualModule("FPS", Vec2(10.f, 5.f), Vec2(25.f, 15.f), mltext("Display the amount of fps.", "Affiche le nombre de fps.")) {
		addFloatSetting(mltext("Reduced Width", "Reduction de Largeur"), "reducedWidth", reducedWidth, &reducedWidth, 0.0f, 25.0f);
		addFloatSetting(mltext("Scale", "Multiplicateur de taille"), "scale", scale, &scale, 0.5f, 1.5f);
		addColorSetting(mltext("Text Color", "Couleur du Texte"), "textColor", textColor, &textColor);
		addColorSetting(mltext("Background Color", "Couleur du Fond"), "backColor", backgroundColor, &backgroundColor);
	}

	virtual void onTick(Gamemode* gm) override;
	virtual void onRender() override;
};

