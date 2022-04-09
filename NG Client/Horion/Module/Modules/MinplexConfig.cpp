#include "../../Module/ModuleManager.h"
#include "MinplexConfig.h"

MinplexConfig::MinplexConfig() : IModule(0x0, Category::CONFIG, "Auto Loads Best Config For Minplex") {
}

MinplexConfig::~MinplexConfig() {
}

const char* MinplexConfig::getModuleName() {
	return ("Minplex");
}

void MinplexConfig::onEnable() {
	// Disable All and Unbind All
	auto lock = moduleMgr->lockModuleList();
	std::vector<std::shared_ptr<IModule>>* modules = moduleMgr->getModuleList();
	for (auto it = modules->begin(); it != modules->end(); ++it) {
		auto mod = *it;
		mod->setEnabled(false);
		mod->setKey(0x0);
	}

	// Modules
	static auto zoom = moduleMgr->getModule<Zoom>();
	static auto HudMod = moduleMgr->getModule<HudModule>();
	static auto gui = moduleMgr->getModule<GUI>();
	static auto KillMod = moduleMgr->getModule<Killaura>();
	static auto ESPMod = moduleMgr->getModule<ESP>();
	static auto Stop = moduleMgr->getModule<FastStop>();
	static auto AutoArm = moduleMgr->getModule<AutoArmor>();
	static auto Sprint = moduleMgr->getModule<AutoSprint>();
	static auto BowBot = moduleMgr->getModule<BowAimbot>();
	static auto Scaff = moduleMgr->getModule<Scaffold>();
	static auto NoSlow = moduleMgr->getModule<NoSlowDown>();
	static auto ClickGUI = moduleMgr->getModule<ClickGuiMod>();
	static auto ReachMod = moduleMgr->getModule<Reach>();
	static auto Bright = moduleMgr->getModule<Camera>();
	static auto Web = moduleMgr->getModule<NoWeb>();
	static auto JesusSUS = moduleMgr->getModule<Jesus>();
	static auto Tags = moduleMgr->getModule<NameTags>();
	static auto Hop = moduleMgr->getModule<Bhop>();
	static auto Mid = moduleMgr->getModule<MidClick>();
	static auto Select = moduleMgr->getModule<selectionHighlight>();
	static auto AntiBotMod = moduleMgr->getModule<AntiBot>();
	static auto Cleaner = moduleMgr->getModule<InventoryCleaner>();
	static auto ViewMod = moduleMgr->getModule<ViewModel>();
	static auto AntiKBMod = moduleMgr->getModule<Velocity>();
	static auto ArrayList = moduleMgr->getModule<GUI>();
	static auto partner = moduleMgr->getModule<Partner>();
	static auto xpmod = moduleMgr->getModule<XP>();
	static auto serverinfo = moduleMgr->getModule<ServerInfo>();
	static auto cpsmod = moduleMgr->getModule<cps>();
	static auto fpsmod = moduleMgr->getModule<fps>();
	static auto bpsmod = moduleMgr->getModule<bps>();
	static auto coordinates = moduleMgr->getModule<Coordinates>();

	// Toggle All Needed Mods
	gui->setEnabled(true);
	HudMod->setEnabled(true);
	ClickGUI->setEnabled(false);
	AntiBotMod->setEnabled(true);
	Select->setEnabled(true);
	AntiKBMod->setEnabled(true);
	NoSlow->setEnabled(true);
	BowBot->setEnabled(true);
	AutoArm->setEnabled(true);
	ViewMod->setEnabled(true);
	Sprint->setEnabled(true);
	Cleaner->setEnabled(false);
	Tags->setEnabled(true);
	Bright->setEnabled(true);
	Stop->setEnabled(true);
	Mid->setEnabled(true);
	Web->setEnabled(true);
	ReachMod->setEnabled(true);
	JesusSUS->setEnabled(true);
	ESPMod->setEnabled(true);
	xpmod->setEnabled(true);
	serverinfo->setEnabled(true);
	fpsmod->setEnabled(true);
	cpsmod->setEnabled(true);
	bpsmod->setEnabled(true);
	coordinates->setEnabled(true);

	// Set All Settings
	
	// partner
	partner->Partnered.selected = 2;
	// Bps
	bpsmod->bpsX = 0.f;
	bpsmod->bpsY = 270.5f;
	// Fps
	fpsmod->fpsX = 0.f;
	fpsmod->fpsY = 280.5f;
	// Cps
	cpsmod->cpsX = 0.f;
	cpsmod->cpsY = 290.5f;
	//Serverinfo
	serverinfo->serverInfoX = 0.f;
	serverinfo->serverInfoY = 300.5f;
	// Zoom
	zoom->setKey('R');
	zoom->strength = 0.5f;
	// Killaura
	KillMod->setKey('C');
	KillMod->range = 4.50f;
	KillMod->delay = 2;
	KillMod->rots.selected = 1;
	KillMod->info = true;
	KillMod->hurttime = false;
	KillMod->isMobAura = false;
	KillMod->noSwing = false;
	// Scaffold
	Scaff->setKey('V');
	Scaff->staircaseMode = true;
	Scaff->fagNigas = true;
	Scaff->UpwardsFlyinNigas = 0.50f;
	Scaff->autoselect = true;
	Scaff->Fullselect = true;
	Scaff->spoof = false;
	Scaff->spam = false;
	Scaff->rot = true;
	Scaff->SukinMyBigJuicyAss = true;
	Scaff->noSwing = false;
	Scaff->yLock = false;
	Scaff->predict = true;
	Scaff->GayNigaFags = true;
	Scaff->THICCC = false;
	// Bhop
	Hop->setKey('F');
	Hop->speed = 0.90f;
	Hop->hive = true;
	// Selection Highlight
	Select->thickness = 0.40f;
	Select->opacityVal = 1.f;
	Select->selectRainbow = false;
	Select->doOutline = true;
	Select->rSelect = 1.f;
	Select->bSelect = 1.f;
	Select->gSelect = 1.f;
	// BowAimbot
	BowBot->predict = true;
	BowBot->visualize = true;
	// ESP
	ESPMod->betterESP = false;
	ESPMod->circle = false;
	ESPMod->doRainbow = false;
	ESPMod->is2d = false;
	ESPMod->iszephyr = true;
	ESPMod->isMobEsp = false;
	// FullBright
	Bright->intensity = 25.f;
	// NameTags
	Tags->displayArmor = true;
	Tags->underline = true;
	Tags->opacity = .12f;
	// Viewmodel
	ViewMod->xTrans = 0.35f;
	ViewMod->yTrans = 0.06f;
	ViewMod->zTrans = -0.74f;
	ViewMod->doTranslate = true;
	ViewMod->doScale = false;
	ViewMod->doRotation = false;
	ViewMod->spin = false;
	// AutoSprint
	Sprint->alldirections = true;
	// AntiBot
	AntiBotMod->hitboxCheck = true;
	AntiBotMod->extraCheck = false;
	AntiBotMod->entityIdCheck = true;
	AntiBotMod->nameCheck = true;
	AntiBotMod->otherCheck = false;
	AntiBotMod->invisibleCheck = false;
	// InvCleaner
	Cleaner->setKey('N');
	Cleaner->autoSort = true;
	Cleaner->keepArmor = true;
	Cleaner->keepBlocks = true;
	Cleaner->keepBow = false;
	Cleaner->keepFood = true;
	Cleaner->keepPick = false;
	Cleaner->keepShovel = false;
	Cleaner->keepTools = true;
	Cleaner->openInv = false;
	// ClickGUI
	ClickGUI->setKey(VK_TAB);
	ClickGUI->showTooltips = true;
	// Arraylist
	ArrayList->Fluxbar = true;
	ArrayList->bar = false;
	ArrayList->underbar = false;
	ArrayList->rgb = true;
	ArrayList->ice = false;
	ArrayList->bottom = false;
	ArrayList->opacity = 0.20f;
	ArrayList->rcolor = 0.f;
	ArrayList->gcolor = 0.f;
	ArrayList->bcolor = 0.f;
	// HUDModule
	HudMod->Hud = true;
	HudMod->rgb = false;
	HudMod->Msg = false;
	HudMod->watermark = true;
	HudMod->notifications = false;
	HudMod->bools = false;
	HudMod->displaySecondHalf = false;
	HudMod->alwaysShow = false;
	HudMod->opacity = 0.28f;
	HudMod->scale = 0.75f;
	// Reach
	ReachMod->reachValue = 7.f;

	// Tell User Binds
	g_Data.getGuiData()->displayClientMessageF("=======================================");
	g_Data.getGuiData()->displayClientMessageF("%s[%sAutoConfig%s] InvCleaner is bound to N", WHITE, LIGHT_PURPLE, WHITE);
	g_Data.getGuiData()->displayClientMessageF("%s[%sAutoConfig%s] ClickGUI is bound to TAB", WHITE, LIGHT_PURPLE, WHITE);
	g_Data.getGuiData()->displayClientMessageF("%s[%sAutoConfig%s] Bhop is bound to F", WHITE, LIGHT_PURPLE, WHITE);
	g_Data.getGuiData()->displayClientMessageF("%s[%sAutoConfig%s] Scaffold is bound to V", WHITE, LIGHT_PURPLE, WHITE);
	g_Data.getGuiData()->displayClientMessageF("%s[%sAutoConfig%s] Killaura is bound to C", WHITE, LIGHT_PURPLE, WHITE);
	g_Data.getGuiData()->displayClientMessageF("%s[%sAutoConfig%s] Zoom is bound to R", WHITE, LIGHT_PURPLE, WHITE);
	g_Data.getGuiData()->displayClientMessageF("=======================================");
	// Success
	g_Data.getGuiData()->displayClientMessageF("%s[%sAutoConfig%s]%s Successfully Made Config!", WHITE, LIGHT_PURPLE, WHITE, LIGHT_PURPLE);

	// Tell Dumbass To Save Config
	g_Data.getGuiData()->displayClientMessageF("%s[%sAutoConfig%s]%s Type %s.config save%s to save your config!", WHITE, GREEN, WHITE, GREEN, WHITE, GREEN);
}
