#include "ModuleManager.h"
#include "../../Utils/Logger.h"
#include "../../Utils/Json.hpp"

using json = nlohmann::json;

ModuleManager::ModuleManager(GameData* gameData) {
	this->gameData = gameData;
}

ModuleManager::~ModuleManager() {
	initialized = false;
	auto lock = this->lockModuleListExclusive();
	this->moduleList.clear();
}

void ModuleManager::initModules() {
	logF("Initializing modules");
	{
		auto lock = this->lockModuleListExclusive();

		moduleList.push_back(std::shared_ptr<IModule>(new HudModule()));
		moduleList.push_back(std::shared_ptr<IModule>(new ArrayList()));
		moduleList.push_back(std::shared_ptr<IModule>(new Watermark()));
		moduleList.push_back(std::shared_ptr<IModule>(new Notifications()));
		moduleList.push_back(std::shared_ptr<IModule>(new FreeTP()));
		moduleList.push_back(std::shared_ptr<IModule>(new CameraMod()));
		moduleList.push_back(std::shared_ptr<IModule>(new Animations()));
		moduleList.push_back(std::shared_ptr<IModule>(new Blink()));
		moduleList.push_back(std::shared_ptr<IModule>(new LongJump()));
		moduleList.push_back(std::shared_ptr<IModule>(new TPAura()));
		moduleList.push_back(std::shared_ptr<IModule>(new Disabler()));
		moduleList.push_back(std::shared_ptr<IModule>(new InvManager()));
		moduleList.push_back(std::shared_ptr<IModule>(new ChestStealer()));
		moduleList.push_back(std::shared_ptr<IModule>(new Speed()));
		//moduleList.push_back(std::shared_ptr<IModule>(new TargetStrafeOld()));
		moduleList.push_back(std::shared_ptr<IModule>(new TargetStrafe()));
		moduleList.push_back(std::shared_ptr<IModule>(new Reach()));
		moduleList.push_back(std::shared_ptr<IModule>(new ESP()));
		moduleList.push_back(std::shared_ptr<IModule>(new Aimbot()));
		moduleList.push_back(std::shared_ptr<IModule>(new ChestESP()));
		moduleList.push_back(std::shared_ptr<IModule>(new BlockESP()));
		moduleList.push_back(std::shared_ptr<IModule>(new BlockOutline()));
		moduleList.push_back(std::shared_ptr<IModule>(new Velocity()));
		moduleList.push_back(std::shared_ptr<IModule>(new Step())); //
		moduleList.push_back(std::shared_ptr<IModule>(new Flight()));
		moduleList.push_back(std::shared_ptr<IModule>(new Phase()));
		moduleList.push_back(std::shared_ptr<IModule>(new Freecam()));
		moduleList.push_back(std::shared_ptr<IModule>(new Sprint()));
		moduleList.push_back(std::shared_ptr<IModule>(new Scaffold()));
		moduleList.push_back(std::shared_ptr<IModule>(new NoFall()));
		moduleList.push_back(std::shared_ptr<IModule>(new Nuker()));
		moduleList.push_back(std::shared_ptr<IModule>(new InstaBreak()));
		moduleList.push_back(std::shared_ptr<IModule>(new Xray()));
		moduleList.push_back(std::shared_ptr<IModule>(new Breaker()));
		moduleList.push_back(std::shared_ptr<IModule>(new ClickGuiMod()));
		moduleList.push_back(std::shared_ptr<IModule>(new Hitbox()));
		moduleList.push_back(std::shared_ptr<IModule>(new InventoryMove()));
		moduleList.push_back(std::shared_ptr<IModule>(new AutoClicker()));
		moduleList.push_back(std::shared_ptr<IModule>(new NameTags()));
		moduleList.push_back(std::shared_ptr<IModule>(new Killaura()));
		moduleList.push_back(std::shared_ptr<IModule>(new MidClick()));
		moduleList.push_back(std::shared_ptr<IModule>(new BlockReach()));
		moduleList.push_back(std::shared_ptr<IModule>(new NoFriends()));
		moduleList.push_back(std::shared_ptr<IModule>(new AntiBot()));
		moduleList.push_back(std::shared_ptr<IModule>(new Timer()));
		moduleList.push_back(std::shared_ptr<IModule>(new NoSwing()));
		moduleList.push_back(std::shared_ptr<IModule>(new Zoom()));
		moduleList.push_back(std::shared_ptr<IModule>(new Teams()));
		moduleList.push_back(std::shared_ptr<IModule>(new Freelook()));
		moduleList.push_back(std::shared_ptr<IModule>(new Sneak()));
		moduleList.push_back(std::shared_ptr<IModule>(new AntiImmobile()));
		moduleList.push_back(std::shared_ptr<IModule>(new TimeChanger()));
		moduleList.push_back(std::shared_ptr<IModule>(new Radar()));
		moduleList.push_back(std::shared_ptr<IModule>(new CustomSky()));
		moduleList.push_back(std::shared_ptr<IModule>(new XP()));
		moduleList.push_back(std::shared_ptr<IModule>(new FastStop()));
		moduleList.push_back(std::shared_ptr<IModule>(new Spammer()));
		moduleList.push_back(std::shared_ptr<IModule>(new Criticals()));
		moduleList.push_back(std::shared_ptr<IModule>(new CrystalAura()));
		moduleList.push_back(std::shared_ptr<IModule>(new Packet()));
		moduleList.push_back(std::shared_ptr<IModule>(new Spider()));
		//moduleList.push_back(std::shared_ptr<IModule>(new SpawnTP()));
		moduleList.push_back(std::shared_ptr<IModule>(new ItemTP()));
		//moduleList.push_back(std::shared_ptr<IModule>(new BreadCrumbs()));
		moduleList.push_back(std::shared_ptr<IModule>(new HackerDetector()));
		moduleList.push_back(std::shared_ptr<IModule>(new Switcher()));
		moduleList.push_back(std::shared_ptr<IModule>(new ClickTP()));
		moduleList.push_back(std::shared_ptr<IModule>(new Jesus()));
		moduleList.push_back(std::shared_ptr<IModule>(new AntiVoid()));
		moduleList.push_back(std::shared_ptr<IModule>(new Derp()));
		moduleList.push_back(std::shared_ptr<IModule>(new FastPlace()));
		moduleList.push_back(std::shared_ptr<IModule>(new AutoTotem()));
		moduleList.push_back(std::shared_ptr<IModule>(new TargetHUD()));
		moduleList.push_back(std::shared_ptr<IModule>(new NoSlow()));

#ifdef _DEBUG
		//moduleList.push_back(std::shared_ptr<IModule>(new PlayerList()));
		moduleList.push_back(std::shared_ptr<IModule>(new HudEditorMod()));
		moduleList.push_back(std::shared_ptr<IModule>(new TestModule()));
		moduleList.push_back(std::shared_ptr<IModule>(new HiveFly()));
		//moduleList.push_back(std::shared_ptr<IModule>(new TriggerBot()));
		// Broken

		//Keep this, stuff for Hive when extreme bypassing
		moduleList.push_back(std::shared_ptr<IModule>(new KBFly()));
		moduleList.push_back(std::shared_ptr<IModule>(new FallSave()));
		moduleList.push_back(std::shared_ptr<IModule>(new NoJumpDelay()));
#endif

		// Sort modules alphabetically
		std::sort(moduleList.begin(), moduleList.end(), [](auto lhs, auto rhs) {
			auto current = lhs;
			auto other = rhs;
			return std::string{*current->getModuleName()} < std::string{*other->getModuleName()};
		});

		initialized = true;
	}
	
	getModule<Notifications>()->setEnabled(true);
	getModule<ClickGuiMod>()->setEnabled(false);
	getModule<HudModule>()->setEnabled(true);
	getModule<ArrayList>()->setEnabled(true);
	getModule<Watermark>()->setEnabled(true);
	getModule<AntiBot>()->setEnabled(true);
	getModule<AntiBot>()->setEnabled(true);
	getModule<Sprint>()->setEnabled(true);
	if (!g_Data.canUseMoveKeys()) {
		auto notification = g_Data.addNotification("", "Packet Client is now Injected!"); // example, the dll wont build since it isnt implemented yet
		notification->duration = 20;
	}
}

void ModuleManager::disable() {
	auto lock = this->lockModuleList();
	for (auto& mod : this->moduleList) {
		if (mod->isEnabled())
			mod->setEnabled(false);
	}
}

void ModuleManager::onLoadConfig(void* confVoid) {
	auto conf = reinterpret_cast<json*>(confVoid);
	if (!isInitialized())
		return;
	auto lock = this->lockModuleList();
	for (auto& mod : this->moduleList) {
		mod->onLoadConfig(conf);
	}
	getModule<ClickGuiMod>()->setEnabled(false);
}

void ModuleManager::onSaveConfig(void* confVoid) {
	auto conf = reinterpret_cast<json*>(confVoid);
	if (!isInitialized())
		return;
	auto lock = this->lockModuleList();
	for (auto& mod : this->moduleList) {
		mod->onSaveConfig(conf);
	}
}

void ModuleManager::onPlayerTick(C_Player* plr) {
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& mod : moduleList) {
		if (mod->isEnabled() || mod->callWhenDisabled())
			mod->onPlayerTick(plr);
	}
}

void ModuleManager::onWorldTick(C_GameMode* gameMode) {
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& mod : moduleList) {
		if (mod->isEnabled() || mod->callWhenDisabled())
			mod->onWorldTick(gameMode);
	}
}

void ModuleManager::onTick(C_GameMode* gameMode) {
	if (!isInitialized())
		return;
	auto lock = this->lockModuleList();
	for (auto& mod : this->moduleList) {
		if (mod->isEnabled() || mod->callWhenDisabled())
			mod->onTick(gameMode);
	}
}

void ModuleManager::onAttack(C_Entity* attackEnt) {
	if (!isInitialized())
		return;

	auto lock = this->lockModuleList();
	for (auto& mod : this->moduleList) {
		if (mod->isEnabled() || mod->callWhenDisabled())
			mod->onAttack(attackEnt);
	}
}

void ModuleManager::onKeyUpdate(int key, bool isDown) {
	if (!isInitialized())
		return;
	auto lock = this->lockModuleList();
	for (auto& mod : this->moduleList) {
		mod->onKeyUpdate(key, isDown);
	}
}

void ModuleManager::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	if (!isInitialized())
		return;
	auto mutex = this->lockModuleList();

	for (auto& mod : this->moduleList) {
		if (mod->isEnabled() || mod->callWhenDisabled())
			mod->onPreRender(renderCtx);
	}
}

void ModuleManager::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	if (!isInitialized())
		return;
	auto mutex = this->lockModuleList();

	for (auto& mod : this->moduleList) {
		if (mod->isEnabled() || mod->callWhenDisabled())
			mod->onPostRender(renderCtx);
	}
}

void ModuleManager::onSendPacket(C_Packet* packet) {
	if (!isInitialized())
		return;
	auto lock = this->lockModuleList();
	for (auto& it : moduleList) {
		if (it->isEnabled() || it->callWhenDisabled())
			it->onSendPacket(packet);
	}
}

std::vector<std::shared_ptr<IModule>>* ModuleManager::getModuleList() {
	return &this->moduleList;
}

int ModuleManager::getModuleCount() {
	return (int)moduleList.size();
}

int ModuleManager::getEnabledModuleCount() {
	int i = 0;
	auto lock = this->lockModuleList();
	for (auto& it : moduleList) {
		if (it->isEnabled()) i++;
	}
	return i;
}
void ModuleManager::onMove(C_MoveInputHandler* hand) {
	if (!isInitialized())
		return;
	auto lock = this->lockModuleList();
	for (auto& it : moduleList) {
		if (it->isEnabled() || it->callWhenDisabled())
			it->onMove(hand);
	}
}
void ModuleManager::onLevelRender() {
	if (!isInitialized())
		return;
	auto lock = this->lockModuleList();
	for (auto& it : moduleList) {
		if (it->isEnabled() || it->callWhenDisabled())
			it->onLevelRender();
	}
}

ModuleManager* moduleMgr = new ModuleManager(&g_Data);

