#include "RenderContextHook.h"
#include "../../SDK/game.h"
#include "../Manager.h"


#define performanceTest 0


typedef void(__stdcall* _RenderUIContext)(__int64 a1, MinecraftUIRenderContext* Ctx);
_RenderUIContext orenderUIContext;


//fps counting
static std::chrono::high_resolution_clock fpsclock;
static std::chrono::steady_clock::time_point start = fpsclock.now();

uint8_t counterStatus = 0;
extern uint16_t leftclickCalc[10];
extern uint16_t rightclickCalc[10];
uint16_t framecounts[10] = {0};


static bool isInit = false;

extern bool LazyGuiRedraw;
extern bool skipNextLazyness;
extern bool skipTwoLazyness;


void OnSecondTimerCalc() {
	if ((std::chrono::duration<float>(fpsclock.now() - start).count()) > 0.097f) {
		game::fps = framecounts[counterStatus];
		if (!LazyGuiRedraw)
			game::fps /= 3;
		framecounts[counterStatus] = 0;

		//CPS
		game::lcps = leftclickCalc[counterStatus];
		game::rcps = rightclickCalc[counterStatus];
		leftclickCalc[counterStatus] = 0;
		rightclickCalc[counterStatus] = 0;


		counterStatus++;
		if (counterStatus == 10)
			counterStatus = 0;
		start = fpsclock.now();
	}
	
}




void RenderCallback(__int64 a1, MinecraftUIRenderContext* Ctx) {

#if performanceTest == 1
	std::chrono::high_resolution_clock ptestClock;
	auto ptestStart = ptestClock.now();
	static double longest = 0.0;
#endif

	if (LazyGuiRedraw) {
		static char numFrame = 1;
		if (skipTwoLazyness) {
			skipNextLazyness = true; skipTwoLazyness = false; }
		else if (skipNextLazyness)
			skipNextLazyness = false;
		else
			numFrame++;

		if (numFrame == 3)
			numFrame = 0;
		else
			return orenderUIContext(a1, Ctx);
	}

	if (!isInit) {
		if (game::minecraftGame == nullptr)
			return;
	
		if (game::minecraftGame->fontRepository->fontList->font1->font->fontName.reservedLenght > 15 && game::minecraftGame->fontRepository->fontList->font1->font->smoothbeone == 1.f)
			RenderUtils::SetContext(Ctx, game::minecraftGame->fontRepository->fontList->font1->font);
		else if (game::minecraftGame->fontRepository->fontList->font2->font->fontName.reservedLenght > 15 && game::minecraftGame->fontRepository->fontList->font1->font->smoothbeone == 1.f)
			RenderUtils::SetContext(Ctx, game::minecraftGame->fontRepository->fontList->font2->font);
		else if (game::minecraftGame->fontRepository->fontList->font3->font->fontName.reservedLenght > 15 && game::minecraftGame->fontRepository->fontList->font1->font->smoothbeone == 1.f)
			RenderUtils::SetContext(Ctx, game::minecraftGame->fontRepository->fontList->font3->font);
		else if (game::minecraftGame->fontRepository->fontList->font4->font->fontName.reservedLenght > 15 && game::minecraftGame->fontRepository->fontList->font1->font->smoothbeone == 1.f)
			RenderUtils::SetContext(Ctx, game::minecraftGame->fontRepository->fontList->font4->font);
		else if (game::minecraftGame->fontRepository->fontList->smooth1->font->fontName.reservedLenght > 15 && game::minecraftGame->fontRepository->fontList->font1->font->smoothbeone == 1.f)
			RenderUtils::SetContext(Ctx, game::minecraftGame->fontRepository->fontList->smooth1->font);
		else if (game::minecraftGame->fontRepository->fontList->smooth2->font->fontName.reservedLenght > 15 && game::minecraftGame->fontRepository->fontList->font1->font->smoothbeone == 1.f)
			RenderUtils::SetContext(Ctx, game::minecraftGame->fontRepository->fontList->smooth2->font);
		else {
			if (!isInit) {
				if (game::minecraftGame->fontRepository->fontList->font1->font->fontName.reservedLenght > 15)
					RenderUtils::SetContext(Ctx, game::minecraftGame->fontRepository->fontList->font1->font);
				else if (game::minecraftGame->fontRepository->fontList->font2->font->fontName.reservedLenght > 15)
					RenderUtils::SetContext(Ctx, game::minecraftGame->fontRepository->fontList->font2->font);
				else if (game::minecraftGame->fontRepository->fontList->font3->font->fontName.reservedLenght > 15)
					RenderUtils::SetContext(Ctx, game::minecraftGame->fontRepository->fontList->font3->font);
				else if (game::minecraftGame->fontRepository->fontList->font4->font->fontName.reservedLenght > 15)
					RenderUtils::SetContext(Ctx, game::minecraftGame->fontRepository->fontList->font4->font);
				else if (game::minecraftGame->fontRepository->fontList->smooth1->font->fontName.reservedLenght > 15)
					RenderUtils::SetContext(Ctx, game::minecraftGame->fontRepository->fontList->smooth1->font);
				else if (game::minecraftGame->fontRepository->fontList->smooth2->font->fontName.reservedLenght > 15)
					RenderUtils::SetContext(Ctx, game::minecraftGame->fontRepository->fontList->smooth2->font);
				else {
					Logf("Could not find epic font");
					RenderUtils::SetContext(Ctx, game::minecraftGame->minecraftFont);
					isInit = true;
					RenderUtils::isMinecraftia = true;
					return;
				}
			}
		}

		isInit = true;
	}
		
	//increment fpsCount
	for (uint8_t i = 0; i < 10; i++)
		framecounts[i]++;
	



	if (game::clickGui != nullptr) {
		

		for (uint16_t i = 0; i < ModuleManager::moduleList.size(); i++) {
			if (ModuleManager::moduleList[i] != nullptr)
				if (ModuleManager::moduleList[i]->isEnabled())
					ModuleManager::moduleList[i]->onRender();
		}


		if (game::clickGui->shouldRenderVisualModules())
			for (uint16_t i = 0; i < ModuleManager::visualModuleList.size(); i++)
				if (ModuleManager::visualModuleList[i] != nullptr)
					if (ModuleManager::visualModuleList[i]->isEnabled())
						ModuleManager::visualModuleList[i]->onRender();

		if (game::clickGui->isEnabled())
			game::clickGui->onRender();

		game::clickGui->notificationRenderer();
	}
	
	/*char ptest[50] = { 0 };
	sprintf(ptest, "server: %s", game::minecraftGame->networkHandler->raknetInstance->serverTextIP.getText());
	RenderUtils::RenderText(ptest, Vec2(0.0, 15.0f), MC_Color(0.0f, 1.0f, 0.0f), 1.f, 1.f);
	sprintf(ptest, "server: %s\0", game::minecraftGame->networkHandler->raknetInstance->numericIP.getText());
	RenderUtils::RenderText(ptest, Vec2(0.0, 25.0f), MC_Color(0.0f, 1.0f, 0.0f), 1.f, 1.f);*/
#if performanceTest == 1
	auto ptestStop = ptestClock.now();
	double duration = std::chrono::duration<double>(ptestStop - ptestStart).count();

	char ptest[50] = { 0 };
	sprintf(ptest, "took: %f", duration);
	RenderUtils::RenderText(ptest, Vec2(0.0, 0.0f), MC_Color(0.0f, 1.0f, 0.0f), 1.f, 1.f);
	if (duration > longest)
		longest = duration;
	sprintf(ptest, "max: %f\0", longest);
	RenderUtils::RenderText(ptest, Vec2(0.0, 15.0f), MC_Color(0.0f, 1.0f, 0.0f), 1.f, 1.f);


#endif
	//RenderUtils::FlushText();

	orenderUIContext(a1, Ctx);
}


void RenderContextHook::init() {
	name = "RenderContextHook";

#ifndef _1_16_40
	uintptr_t hookAddress = mem::FindSignature("48 8B C4 48 89 58 ?? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ?? ?? ?? ?? 48 81 EC ?? ?? ?? ?? 0F 29 70 ?? 0F 29 78 ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 4C 8B F2 48 89 54 24");
#else
	uintptr_t hookAddress = mem::FindSignature("48 8B C4 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ?? ?? ?? ?? 48 81 EC ?? ?? ?? ?? 48 C7 45 ?? FE FF FF FF 48 89 58 ?? 0F 29 70 ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 48 89 54 24");
#endif

	if (hookAddress == NULL) {
		Logf("Unable to hook!\n Sig of %s is broken", name);
		return;
	}
	Logf("%s: %p", name, (void*)hookAddress);

	isInit = true;

	MH_CreateHook((LPVOID)hookAddress, (LPVOID)RenderCallback, (LPVOID*)&orenderUIContext);
	MH_EnableHook((LPVOID)hookAddress);
}




