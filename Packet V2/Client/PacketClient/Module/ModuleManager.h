#pragma once

#include <typeinfo>
#include <vector>
#include <optional>
#include <memory>
#include <mutex>
#include <shared_mutex>

#include "../../Memory/GameData.h"

#include "Modules/HudModule.h"
#include "Modules/ArrayList.h"
#include "Modules/Watermark.h"
#include "Modules/Notifications.h"
#include "Modules/FreeTP.h"
#include "Modules/CameraMod.h"
#include "Modules/Animations.h"
#include "Modules/Blink.h"
#include "Modules/LongJump.h"
#include "Modules/TPAura.h"
#include "Modules/Disabler.h"
#include "Modules/InvManager.h"
#include "Modules/ChestStealer.h"
#include "Modules/Speed.h"
#include "Modules/TargetStrafeOld.h"
#include "Modules/TargetStrafe.h"
#include "Modules/Reach.h"
#include "Modules/ESP.h"
#include "Modules/Aimbot.h"
#include "Modules/ChestESP.h"
#include "Modules/BlockESP.h"
#include "Modules/BlockOutline.h"
#include "Modules/Velocity.h"
#include "Modules/Step.h" // 
#include "Modules/Flight.h"
#include "Modules/Phase.h"
#include "Modules/Freecam.h"
#include "Modules/Sprint.h"
#include "Modules/Scaffold.h"
#include "Modules/NoFall.h"
#include "Modules/Nuker.h"
#include "Modules/InstaBreak.h"
#include "Modules/Xray.h"
#include "Modules/Breaker.h"
#include "Modules/ClickGuiMod.h"
#include "Modules/Hitbox.h"
#include "Modules/InventoryMove.h"
#include "Modules/AutoClicker.h"
#include "Modules/Nametags.h"
#include "Modules/Killaura.h"
#include "Modules/MidClick.h"
#include "Modules/BlockReach.h"
#include "Modules/NoFriends.h"
#include "Modules/AntiBot.h"
#include "Modules/Timer.h"
#include "Modules/NoSwing.h"
#include "Modules/Zoom.h"
#include "Modules/Teams.h"
#include "Modules/Freelook.h"
#include "Modules/Sneak.h"
#include "Modules/AntiImmobile.h"
#include "Modules/TimeChanger.h"
#include "Modules/Radar.h"
#include "Modules/CustomSky.h"
#include "Modules/XP.h"
#include "Modules/FastStop.h"
#include "Modules/Spammer.h"
#include "Modules/Criticals.h"
#include "Modules/CrystalAura.h"
#include "Modules/Packet.h"
#include "Modules/Spider.h"
#include "Modules/SpawnTP.h"
#include "Modules/ItemTP.h"
#include "Modules/BreadCrumbs.h"
#include "Modules/HackerDetector.h"
#include "Modules/Switcher.h"
#include "Modules/ClickTP.h"
#include "Modules/Jesus.h"
#include "Modules/AntiVoid.h"
#include "Modules/Derp.h"
#include "Modules/FastPlace.h"
#include "Modules/AutoTotem.h"
#include "Modules/TargetHUD.h"
#include "Modules/NoSlow.h"
#include "Modules/Module.h"

#ifdef _DEBUG
#include "Modules/PlayerList.h"
#include "Modules/HudEditorMod.h"
#include "Modules/TestModule.h"
#include "Modules/HiveFly.h"

#include "Modules/FallSave.h"
#include "Modules/KBFly.h"
#include "Modules/NoJumpDelay.h"
// Broken
#include "Modules/TriggerBot.h"
#endif


class ModuleManager {
private:
	GameData* gameData;
	std::vector<std::shared_ptr<IModule>> moduleList;
	bool initialized = false;
	std::shared_mutex moduleListMutex;

public:
	~ModuleManager();
	ModuleManager(GameData* gameData);
	void initModules();
	void disable();
	void onLoadConfig(void* conf);
	void onSaveConfig(void* conf);
	void onTick(C_GameMode* gameMode);
	void onAttack(C_Entity* attackedEnt);
	void onPlayerTick(C_Player* plr);
	void onWorldTick(C_GameMode* gameMode);
	void onKeyUpdate(int key, bool isDown);
	void onPreRender(C_MinecraftUIRenderContext* renderCtx);
	void onPostRender(C_MinecraftUIRenderContext* renderCtx);
	void onLevelRender();
	void onMove(C_MoveInputHandler* handler);
	void onSendPacket(C_Packet*);

	std::shared_lock<std::shared_mutex> lockModuleList() { return std::shared_lock(this->moduleListMutex); }
	std::unique_lock<std::shared_mutex> lockModuleListExclusive() { return std::unique_lock(this->moduleListMutex); }
	
	std::shared_mutex* getModuleListLock() { return &this->moduleListMutex; }

	bool isInitialized() { return initialized; };
	std::vector<std::shared_ptr<IModule>>* getModuleList();

	int getModuleCount();
	int getEnabledModuleCount();

	/*
	 *	Use as follows: 
	 *		IModule* mod = moduleMgr.getModule<NoKnockBack>(); 
	 *	Check for nullptr directly after that call, as Hooks::init is called before ModuleManager::initModules !	
	 */
	template <typename TRet>
	TRet* getModule() {
		if (!isInitialized())
			return nullptr;
		auto lock = this->lockModuleList();
		for (auto pMod : moduleList) {
			if (auto pRet = dynamic_cast<typename std::remove_pointer<TRet>::type*>(pMod.get())){
				
				return pRet;
			}
		}
		return nullptr;
	};

	// Dont Use this functions unless you absolutely need to. The function above this one works in 99% of cases
	std::optional<std::shared_ptr<IModule>> getModuleByName(const std::string name) {
		if (!isInitialized())
			return nullptr;
		std::string nameCopy = name;
		std::transform(nameCopy.begin(), nameCopy.end(), nameCopy.begin(), ::tolower);
		
		auto lock = this->lockModuleList();
		for (std::vector<std::shared_ptr<IModule>>::iterator it = this->moduleList.begin(); it != this->moduleList.end(); ++it) {
			std::shared_ptr<IModule> mod = *it;
			std::string modNameCopy = mod->getRawModuleName();
			std::transform(modNameCopy.begin(), modNameCopy.end(), modNameCopy.begin(), ::tolower);
			if (modNameCopy == nameCopy)
				return std::optional<std::shared_ptr<IModule>>(mod);
		}
		return std::optional<std::shared_ptr<IModule>>();
	}
};

extern ModuleManager* moduleMgr;