#pragma once
#include "../Module.h"

#define MODULE_ZOOM_MAXZOOM 50.f
#define MODULE_ZOOM_MINZOOM 1.f



class ZoomModule : public Module {

public:

	float SensivityReduced = 0.2f;
	bool saveScroll = false;

	bool doAnimation = true;
	float animationDuration = 0.1f;

	ZoomModule() : Module("Zoom", 'C', mltext("Can show you how the world look at greater distances.", "Peut vous montrer comment a quoi le monde ressemble\n a de plus grandes distances.")) {
		isToggle = false;
		addBoolSetting(mltext("Save zoom strength between zooms", "Sauvegarder la force du zoom entre chaque zoom"), "SaveZoomScroll", saveScroll, &saveScroll);
		addFloatSetting(mltext("Reduced Sensivity", "Reduction de sensibilite"), "SensivityReduced", SensivityReduced, &SensivityReduced, 0.01f, 1.f);

		addBoolSetting(mltext("Zoom In animation", "Animation lors du zoom"), "doAnimation", doAnimation, &doAnimation);
		addFloatSetting(mltext("Zoom In animation duration", "Duree de l'animation"), "animationDuration", animationDuration, &animationDuration, 0.01f, 2.f);
	}

	virtual void onRender() override;
	virtual void onMouse(MouseButton button, bool isDown, bool& cancel) override;
	virtual void onEnable() override;
	virtual void onDisable() override;

	float zoomValue = 5.f;
	float originalSize = 300.f;

};

