#pragma once
#include "../Module.h"

class EnvironementChanger : public Module {
public:

	bool changeTime = true;
	bool usePcTime = false;
	float time = 0.5;

	bool changeFog = true;
	bool entireSky = false;
	ClickguiColor fogColor = ClickguiColor(1.f, 0.f, 0.f, 1.f, false);

	EnvironementChanger() : Module("Environment Changer", 0, mltext("Change the environment around you.", "Vous permet de changer l'environement qui vous entoure.")) {
		addBoolSetting(mltext("Change time", "Changer le temps"), "changeTime", changeTime, &changeTime);
		addBoolSetting(mltext("Use IRL time", "Utiliser le temps irl"), "usePcTime", usePcTime, &usePcTime);
		addFloatSetting(mltext("Time", "Temps"), "Time", time, &time, 0.f, 1.f);
		addBoolSetting(mltext("Change fog color", "Changer la couleur du brouillard"), "changeFog", changeFog, &changeFog);
		addBoolSetting(mltext("Change entire sky color", "Changer la couleur du ciel en entier"), "entireSky", entireSky, &entireSky);
		addColorSetting(mltext("Fog color","Couleur du brouillard"), "fogColor", fogColor, &fogColor);
	}

};

