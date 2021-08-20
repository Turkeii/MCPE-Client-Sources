#pragma once
#include "../Module.h"


class SpeedCounter : public VisualModule {
public:
	float scale = 1.f;
	ClickguiColor textColor = ClickguiColor(1.f, 1.f, 1.f, 1.f, true);
	ClickguiColor backgroundColor = ClickguiColor(0.156862f, 0.156862f, 0.156862f, 0.4f, true);

	SpeedCounter() : VisualModule("Speed Counter", Vec2(10.f, 50.f), Vec2(10.f, 65.f), mltext("Display your speed in blocks\n*Might not be totally acurate if you are in the air.", "Affiche votre vitesse en blocks/s\n*Ne sera peut etre pas precis si vous etes dans les airs.")) {
		addFloatSetting(mltext("Scale", "Multiplicateur de taille"), "scale", scale, &scale, 0.5f, 1.5f);
		addColorSetting(mltext("Text Color", "Couleur du Texte"), "textColor", textColor, &textColor);
		addColorSetting(mltext("Background Color", "Couleur du Fond"), "backColor", backgroundColor, &backgroundColor);
	}

	virtual void onTick(Gamemode* gm) override;
	virtual void onRender() override;
};