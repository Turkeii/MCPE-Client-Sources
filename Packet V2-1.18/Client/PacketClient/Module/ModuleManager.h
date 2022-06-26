#pragma once

#include <typeinfo>
#include <vector>
#include <optional>
#include <memory>
#include <mutex>
#include <shared_mutex>

#include "../../Memory/GameData.h"

// Menu
#include "Modules/ConfigManagerMod.h"
#include "Modules/ClickGuiMod.h"
#include "Modules/DebugMenu.h"

// Combat
#include "Modules/Combat/AutoClicker.h"
#include "Modules/Combat/CrystalAura.h"
#include "Modules/Combat/TriggerBot.h"
#include "Modules/Combat/Criticals.h"
#include "Modules/Combat/AutoPlay.h"
#include "Modules/Combat/Killaura.h"
#include "Modules/Combat/Switcher.h"
#include "Modules/Combat/HitBoxes.h"
#include "Modules/Combat/AntiBot.h"
#include "Modules/Combat/AutoPot.h"
#include "Modules/Combat/Aimbot.h"
#include "Modules/Combat/TPAura.h"
#include "Modules/Combat/Reach.h"
#include "Modules/Combat/Regen.h"
#include "Modules/Combat/Teams.h"

// Visual
#include "Modules/Visual/Notifications.h"
#include "Modules/Visual/BlockOutline.h"
#include "Modules/Visual/BreadCrumbs.h"
#include "Modules/Visual/SessionInfo.h"
#include "Modules/Visual/Animations.h"
#include "Modules/Visual/PlayerList.h"
#include "Modules/Visual/WayPoints.h"
#include "Modules/Visual/ArrayList.h"
#include "Modules/Visual/CustomSky.h"
#include "Modules/Visual/Interface.h"
#include "Modules/Visual/TargetHUD.h"
#include "Modules/Visual/Watermark.h"
#include "Modules/Visual/Ambience.h"
#include "Modules/Visual/BlockESP.h"
#include "Modules/Visual/ChestESP.h"
#include "Modules/Visual/Freelook.h"
#include "Modules/Visual/Nametags.h"
#include "Modules/Visual/NoRender.h"
#include "Modules/Visual/Camera.h"
#include "Modules/Visual/Radar.h"
#include "Modules/Visual/Zoom.h"
#include "Modules/Visual/Xray.h"
#include "Modules/Visual/ESP.h"

// Movement
#include "Modules/Movement/TargetStrafeOld.h"
#include "Modules/Movement/TargetStrafe.h"
#include "Modules/Movement/SafeWalk.h"
#include "Modules/Movement/LongJump.h"
#include "Modules/Movement/Velocity.h"
#include "Modules/Movement/FastStop.h"
#include "Modules/Movement/AntiVoid.h"
#include "Modules/Movement/InvMove.h"
#include "Modules/Movement/HiveFly.h"
#include "Modules/Movement/Flight.h"
#include "Modules/Movement/Sprint.h"
#include "Modules/Movement/Spider.h"
#include "Modules/Movement/NoSlow.h"
#include "Modules/Movement/Speed.h"
#include "Modules/Movement/Sneak.h"
#include "Modules/Movement/Jesus.h"
#include "Modules/Movement/KBFly.h"
#include "Modules/Movement/Step.h"

// Player
#include "Modules/Player/ChestStealer.h"
#include "Modules/Player/NoJumpDelay.h"
#include "Modules/Player/InvManager.h"
#include "Modules/Player/BlockReach.h"
#include "Modules/Player/FastPlace.h"
#include "Modules/Player/AutoTotem.h"
#include "Modules/Player/NoRotate.h"
#include "Modules/Player/Scaffold.h"
#include "Modules/Player/Freecam.h"
#include "Modules/Player/NoSwing.h"
#include "Modules/Player/Blink.h"
#include "Modules/Player/Timer.h"
#include "Modules/Player/XP.h"

// Exploit
#include "Modules/Exploit/PacketMultiplier.h"
#include "Modules/Exploit/HackerDetector.h"
#include "Modules/Exploit/AntiImmobile.h"
#include "Modules/Exploit/ChatBypass.h"
#include "Modules/Exploit/NoLagBack.h"
#include "Modules/Exploit/SpeedMine.h"
#include "Modules/Exploit/Disabler.h"
#include "Modules/Exploit/NoPacket.h"
#include "Modules/Exploit/FastUse.h"
#include "Modules/Exploit/Crasher.h"
#include "Modules/Exploit/FreeTP.h"
#include "Modules/Exploit/NoFall.h"
#include "Modules/Exploit/Phase.h"

// Other
#include "Modules/Other/ToggleSounds.h"
#include "Modules/Other/DeathEffects.h"
#include "Modules/Other/PacketLogger.h"
#include "Modules/Other/FollowPath.h"
#include "Modules/Other/TestModule.h"
#include "Modules/Other/HitEffects.h"
#include "Modules/Other/ChatSuffix.h"
#include "Modules/Other/Killsults.h"
#include "Modules/Other/AutoHive.h"
#include "Modules/Other/FallSave.h"
#include "Modules/Other/Breaker.h"
#include "Modules/Other/Spammer.h"
#include "Modules/Other/ClickTP.h"
#include "Modules/Other/AutoGG.h"
#include "Modules/Other/ItemTP.h"
#include "Modules/Other/Nuker.h"
#include "Modules/Other/Derp.h"
#include "Modules/Other/MCF.h"

#include "Modules/Module.h"


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
	void onLoadSettings(void* conf);
	void onSaveSettings(void* conf);
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

	/*\
	 *	Use as follows: well no shit
	 *	IModule* mod = moduleMgr->getModule<NoKnockBack>();
	 *	Check for nullptr directly after that call, as Hooks::init is called before ModuleManager::initModules !
	\*/

	template <typename TRet>
	TRet* getModule() {
		if (!isInitialized())
			return nullptr;
		auto lock = this->lockModuleList();
		for (auto pMod : moduleList) {
			if (auto pRet = dynamic_cast<typename std::remove_pointer<TRet>::type*>(pMod.get())) {

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