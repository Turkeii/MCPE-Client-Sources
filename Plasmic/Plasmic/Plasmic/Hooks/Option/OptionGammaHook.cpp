#include "OptionGammaHook.h"
#include "../../Modules/Fullbright.h"
#include "../../Modules/Freelook.h"
#include "../../VisualModules/Compass.h"
#include "../../Modules/EnvironementChanger.h"
#include "../../Modules/ChunkBorder.h"
#include "../../Modules/RenderOptions.h"

#include "Option.h"

Fullbright* fullbright = nullptr;
FreeLook* freelook = nullptr;
Compass* compass = nullptr;
EnvironementChanger* envchanger = nullptr;

ChunkBorder* chunkborder = nullptr;

RenderOptions* renderoptions = nullptr;

float getBrightness(Option** optionList) {
	Option::optionList = optionList;

	


	static Option* gamma = Option::getOptionByTranslate(optionList, "options.gamma");
	static Option* showUI = Option::getOptionByTranslate(optionList, "options.hidehud");
	static Option* renderChunkborder = Option::getOptionByTranslate(optionList, "options.dev_showChunkMap");
	static Option* rendersky = Option::getOptionByTranslate(optionList, "options.dev_disableRenderSky");
	static Option* thirdperson = Option::getOptionByName(optionList, "game_thirdperson");

	//perspective
	if (freelook == nullptr) freelook = (FreeLook*)ModuleManager::getModuleByName("Freelook");
	else if (compass == nullptr) compass = (Compass*)ModuleManager::getVisualModuleByName("Direction HUD");
	else 
		if (thirdperson) {
			freelook->cameraPerpective = (int8_t*)&thirdperson->valuei;
			compass->isthirdperson = thirdperson->valuei == 2;
		}
	

	//F1 support
	if (game::clickGui != nullptr && showUI != nullptr)
		game::clickGui->uiHidden = showUI->mini;


	//Should render the sky?
	getmodbyname(envchanger, "Environment Changer", EnvironementChanger)
		if (rendersky)
		if (envchanger->isEnabled() && envchanger->entireSky)
			rendersky->mini = 1;
		else if (renderoptions && renderoptions->isEnabled())
			rendersky->mini = renderoptions->renderSky;
		else
			rendersky->mini = 0;

	//Should show chunkborder
	getmodbyname(chunkborder, "Chunk Border", ChunkBorder)
		if (renderChunkborder)
		if (chunkborder->isEnabled())
			renderChunkborder->mini = 1;
		else
			renderChunkborder->mini = 0;

	getmodbyname(renderoptions, "Render Options", RenderOptions)
		renderoptions->onOptionTick(optionList);



	//Fullbright
	if (fullbright == nullptr)
		fullbright = (Fullbright*)ModuleManager::getModuleByName("Fullbright");
	else
		if (fullbright->isEnabled()) {
			//Option::printOptions(optionList);
			//fullbright->Disable();
			return 25.f;
		}

	//Get the normal gamma value
	if (gamma)
		return gamma->valuef;
	else
		return 0.f;
}



void OptionGammaHook::init() {
	name = "OptionGammaHook";

	uintptr_t hookAddress = mem::FindSignature("48 83 EC 28 80 B9 ?? ?? ?? ?? 00 48 8D 54 24 30 74 36 41 B8 ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 8B 10 48 85 D2 74 3C 48 8B 8A ?? ?? ?? ?? 48 85 C9 74 0A E8 ?? ?? ?? ?? 48 83 C4 28 C3");
	if (hookAddress == NULL) {
		Logf("Unable to hook!\n Sig of %s is broken", name);
		return;
	}
	//Logf("%s: %p", name, (void*)hookAddress);

	isInit = true;

	MH_CreateHook((LPVOID)hookAddress, (LPVOID)getBrightness, 0);
}



