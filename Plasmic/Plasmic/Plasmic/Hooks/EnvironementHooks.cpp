#include "EnvironementHooks.h"
#include "../Modules/EnvironementChanger.h"

float RealWorldTime = 0.f;
extern SYSTEMTIME CurrentSystemTime;

typedef float(* _TimeOfDay)(Dimension* dimension, int idk, float idk2);
_TimeOfDay otimeOfDay;

EnvironementChanger* ecm = nullptr;
float HookTimeOfDay(Dimension* dimension, int idk, float idk2) {
	RealWorldTime = otimeOfDay(dimension, idk, idk2);
	getmodbyname(ecm, "Environment Changer", EnvironementChanger)
		if (ecm->isEnabled() && ecm->changeTime)
			if (ecm->usePcTime) {
				float time = ((float)((CurrentSystemTime.wHour * 3600) + (CurrentSystemTime.wMinute * 60) + CurrentSystemTime.wSecond) / 86000.f) - 0.5f;
				if (time < 0.f)
					time = 1.f + time;
				return time;
			} else
				return ecm->time;


	return RealWorldTime;
}


void TimeOfDayHook::init() {
	name = "TimeOfDayHook";

	uintptr_t hookAddress = mem::FindSignature("44 8B C2 B8 F1 19 76 05 F7 EA C1 FA 09 8B C2 C1 E8 1F 03 D0");
	if (hookAddress == NULL) {
		Logf("Unable to hook!\n Sig of %s is broken", name);
		return;
	}
	Logf("%s: %p", name, (void*)hookAddress);

	isInit = true;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)HookTimeOfDay, (LPVOID*)&otimeOfDay);
}






static MC_Color nc;
typedef float*(*_GetOverworldFogColor)(Dimension* dimension, __int64 a2, MC_Color* color, float brightness);
_GetOverworldFogColor ogetOverworldFogColor;

float* HookOverworldGetFogColor(Dimension* dimension, __int64 a2, MC_Color* color, float brightness) {
	if (ecm == nullptr)
		return ogetOverworldFogColor(dimension, a2, color, brightness);
	else if(!ecm->isEnabled() || !ecm->changeFog)
		return ogetOverworldFogColor(dimension, a2, color, brightness);

	
	return ecm->fogColor.getTheColor();
}


void OverworldGetFogColorHook::init() {
	name = "OverworldGetFogColorHook";

	uintptr_t hookAddress = mem::FindSignature("41 0F 10 08 48 8B C2 0F 28 D3 F3 0F 59 1D ?? ?? ?? ?? F3 0F 59 15 ?? ?? ?? ?? F3 0F 58 1D ?? ?? ?? ?? 0F 11 0A");
	if (hookAddress == NULL) {
		Logf("Unable to hook!\n Sig of %s is broken", name);
		return;
	}
	Logf("%s: %p", name, (void*)hookAddress);

	isInit = true;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)HookOverworldGetFogColor, (LPVOID*)&ogetOverworldFogColor);
}





typedef float*(*_GetDimensionFogColor)(Dimension* dimension, MC_Color* color, float brightness);
_GetDimensionFogColor ogetDimensionFogColor;

float* HookDimensionGetFogColor(Dimension* dimension, MC_Color* color, float brightness) {
	if (ecm == nullptr)
		return ogetDimensionFogColor(dimension, color, brightness);
	else if (!ecm->isEnabled() || !ecm->changeFog)
		return ogetDimensionFogColor(dimension, color, brightness);


	return ecm->fogColor.getTheColor();
}


void DimensionGetFogColorHook::init() {
	name = "DimensionGetFogColorHook";

	uintptr_t hookAddress = mem::FindSignature("41 0F 10 00 48 8B C2 0F 11 02");
	if (hookAddress == NULL) {
		Logf("Unable to hook!\n Sig of %s is broken", name);
		return;
	}
	Logf("%s: %p", name, (void*)hookAddress);

	isInit = true;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)HookDimensionGetFogColor, (LPVOID*)&ogetDimensionFogColor);
}


