#include "Tracer.h"
#include "../../DrawUtils.h"

#include "../../../SDK/CCamera.h"
#include "../ModuleManager.h"

Tracer::Tracer() : IModule('R', Category::VISUAL, "Draws lines to entities(MADE BY OLD GREGGO!!)") {
	registerEnumSetting("Tracer Type", &type, 0);
	type = SettingEnum(this)
			   .addEntry(EnumEntry("Normal Tracers", 0))
			   .addEntry(EnumEntry("Top Tracers", 1))
			   .addEntry(EnumEntry("Bottom tracers", 2));
	this->registerBoolSetting("Mob Tracers", &this->isMob, this->isMob);
	this->registerBoolSetting("Player Tracers", &this->isPlayer, this->isPlayer);
	this->registerBoolSetting("RGB", &this->RGB, this->RGB);
}

Tracer::~Tracer() {
}

const char* Tracer::getModuleName() {
	return "Tracer";
}

void Tracer::onPreRender(C_MinecraftUIRenderContext* ctx) {
	if (g_Data.getClientInstance()->isInGame()) {
		static auto TracerMod = moduleMgr->getModule<Tracer>();
		if (TracerMod->isMob) {
			g_Data.forEachEntity([](C_Entity* ent, bool valid) {
				DrawUtils::drawTracer(ent);
			});
		}
		if (TracerMod->isPlayer) {
			g_Data.forEachEntity([](C_Entity* ent, bool valid) {
				if (Target::isValidTarget(ent))
					DrawUtils::drawTracer(ent);
			});
		}
	}
}