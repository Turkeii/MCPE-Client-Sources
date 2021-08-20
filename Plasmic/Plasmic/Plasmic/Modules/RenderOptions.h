#pragma once
#include "../Module.h"
#include "../Hooks/Option/Option.h"


class RenderOptions : public Module {
public:

	int nRenderDistance = 16;
	bool renderEntity = false;
	bool renderBlockEntity = false;
	bool renderParticles = false;
	bool renderSky = false;
	bool renderWeather = false;
	bool renderHUD = false;
	bool renderItemInHand = false;


	RenderOptions() : Module("Render Options", 0, mltext("Gives you more rendering options.\nThe default options are not your current ones.", "Vous donne plus d'options d'affichage.\nCeux par defaut ne sont pas les votres actuellement.")) {
		addIntSetting(mltext("Render distance (relog to apply)", "Distance d'affichage (deco reco)"), "nRenderDistance", nRenderDistance, &nRenderDistance, 4, 150);
	
		addBoolSetting(mltext("Disable render for entities", "Desactiver le rendu des entitees"), "renderEntity", renderEntity, &renderEntity);
		addBoolSetting(mltext("Disable render for tile entities", "Desactiver le rendu des TileEntities"), "renderBlockEntity", renderBlockEntity, &renderBlockEntity);
		addBoolSetting(mltext("Disable render for particles", "Desactiver le rendu des particu?les"), "renderParticles", renderParticles, &renderParticles);
		addBoolSetting(mltext("Disable render for the sky", "Desactiver le rendu du ciel"), "renderSky", renderSky, &renderSky);
		addBoolSetting(mltext("Disable render for weather", "Desactiver le rendu de la meteo"), "renderWeather", renderWeather, &renderWeather);
		addBoolSetting(mltext("Disable render for HUD", "Desactiver le rendu du HUD"), "renderHUD", renderHUD, &renderHUD);
		addBoolSetting(mltext("Disable render for ItemInHand", "Desactiver le rendu de ItemInHand"), "renderItemInHand", renderItemInHand, &renderItemInHand);
		
	}



	Option* viewdistance;
	Option* renderentities;
	Option* renderblockentities;
	Option* renderparticles;
	Option* rendersky;
	Option* renderweather;
	Option* renderhud;
	Option* renderiteminhand;

	
	//bool printed = false;
	bool optionInit = false;

	void onOptionTick(Option** list) {
		if (!isEnabled())
			return;
		if (optionInit)
			return;


		viewdistance = Option::getOptionByName(list, "gfx_viewdistance");
		renderentities = Option::getOptionByTranslate(list, "options.dev_disableRenderEntities");
		renderblockentities = Option::getOptionByTranslate(list, "options.dev_disableRenderBlockEntities");
		renderparticles = Option::getOptionByTranslate(list, "options.dev_disableRenderParticles");
		rendersky = Option::getOptionByTranslate(list, "options.dev_disableRenderSky");
		renderweather = Option::getOptionByTranslate(list, "options.dev_disableRenderWeather");
		renderhud = Option::getOptionByTranslate(list, "options.dev_disableRenderHud");
		renderiteminhand = Option::getOptionByTranslate(list, "options.dev_disableRenderItemInHand");


		optionInit = true;

	/*	if (!printed) {
			Option::printOptions(list);
			printed = true;
		}*/


	}

	virtual void onTick(Gamemode* gm) override {

		if (viewdistance)
			viewdistance->valuei = nRenderDistance;
		if (renderentities)
			renderentities->mini = renderEntity;
		if (renderblockentities)
			renderblockentities->mini = renderBlockEntity;
		if (renderparticles)
			renderparticles->mini = renderParticles;
		if (rendersky)
			rendersky->mini = renderSky;
		if (renderweather)
			renderweather->mini = renderWeather;
		if (renderhud)
			renderhud->mini = renderHUD;
		if (renderiteminhand)
			renderiteminhand->mini = renderItemInHand;




	}

};
