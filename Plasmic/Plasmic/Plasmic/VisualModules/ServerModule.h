#pragma once
#include "../Module.h"

class ServerModule : public VisualModule {

public:
	bool showPort = false;

	float scale = 1.f;
	ClickguiColor textColor = ClickguiColor(1.f, 1.f, 1.f, 1.f, true);
	ClickguiColor backgroundColor = ClickguiColor(0.156862f, 0.156862f, 0.156862f, 0.4f, true);

	ServerModule() : VisualModule("Server", Vec2(10.f, 46.f), Vec2(50.f,15.f), mltext("Display the ip of the server you are playing on.", "Affiche l'ip du serveur sur le quel vous jouez.")) {
		addBoolSetting(mltext("Show server port", "Afficher le port du serveur"), "showPort", showPort, &showPort, true);

		addFloatSetting(mltext("Scale", "Multiplicateur de taille"), "scale", scale, &scale, 0.5f, 1.5f);
		addColorSetting(mltext("Text Color", "Couleur du Texte"), "textColor", textColor, &textColor);
		addColorSetting(mltext("Background Color", "Couleur du Fond"), "backColor", backgroundColor, &backgroundColor);
	}

	void onRender();

};

