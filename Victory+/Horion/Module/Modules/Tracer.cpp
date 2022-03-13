#include "Tracer.h"

#include "../../../SDK/CCamera.h"
#include "../../DrawUtils.h"
#include "../ModuleManager.h"

Tracer::Tracer() : IModule('R', Category::VISUAL, "Draws lines to entities(MADE BY OLD GREGGO!!)") {
	registerEnumSetting("Tracer Type", &type, 0);
	type = SettingEnum(this)
			   .addEntry(EnumEntry("Normal Tracers", 0))
			   .addEntry(EnumEntry("Top Tracers", 1))
			   .addEntry(EnumEntry("Bottom tracers", 2));
	//this->registerBoolSetting("Mob Tracers", &this->isMob, this->isMob);
	//this->registerBoolSetting("Player Tracers", &this->isPlayer, this->isPlayer);
	//this->registerBoolSetting("RGB", &this->RGB, this->RGB);
}

Tracer::~Tracer() {
}

const char* Tracer::getModuleName() {
	return "Tracer";
}

static std::vector<C_Entity*> targetList;

void findEntity122(C_Entity* currentEntity122, bool isRegularEntity) {
	static auto killauraMod = moduleMgr->getModule<Tracer>();

	if (currentEntity122 == nullptr)
		return;

	if (currentEntity122 == g_Data.getLocalPlayer())  // Skip Local player
		return;

	if (!g_Data.getLocalPlayer()->canAttack(currentEntity122, false))
		return;

	if (!g_Data.getLocalPlayer()->isAlive())
		return;

	if (!currentEntity122->isAlive())
		return;
	if (killauraMod->isMob) {
	if (currentEntity122->getNameTag()->getTextLength() <= 1 && currentEntity122->getEntityTypeId() == 63)
		return;
	if (currentEntity122->width <= 0.01f || currentEntity122->height <= 0.01f)  // Don't hit this pesky antibot on 2b2e.org
		return;
	if (currentEntity122->getEntityTypeId() == 64)  // item
		return;
	} else {
		if (!Target::isValidTarget(currentEntity122))
			return;
	}

	float dist = (*currentEntity122->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < 5000.f) {
		targetList.push_back(currentEntity122);
	}
}

void Tracer::onPreRender(C_MinecraftUIRenderContext* ctx) {
	if (g_Data.getClientInstance()->isInGame()) {
		g_Data.forEachEntity([](C_Entity* currentEntity122, bool valid) {
	    DrawUtils::drawTracer(currentEntity122);
		});
	}
}