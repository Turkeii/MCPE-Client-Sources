#include "TargetHud.h"

TargetHud::TargetHud() : IModule(0, Category::VISUAL, "Shows info on who you are attacking") {
}

TargetHud::~TargetHud() {
}

const char* TargetHud::getModuleName() {
	return ("TargetHud");
}
static std::vector<C_Entity*> targethudlist;

void finddatranny(C_Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity == g_Data.getLocalPlayer())
		return;

	if (!g_Data.getLocalPlayer()->canAttack(currentEntity, false))
		return;

	if (!g_Data.getLocalPlayer()->isAlive())
		return;

	if (!currentEntity->isAlive())
		return;

	if (currentEntity->getEntityTypeId() != 319)  // Players
		return;

	if (!Target::isValidTarget(currentEntity))
		return;

	if (currentEntity->getEntityTypeId() == 1677999)  // Villager
		return;

	if (currentEntity->getEntityTypeId() == 51)  // NPC
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < 10) {
		targethudlist.push_back(currentEntity);
	}
}
void TargetHud::onPostRender(C_MinecraftUIRenderContext* ctx) {
	if (!targethudlist.empty() &&  g_Data.isInGame()) {
		vec4_t tempPos = vec4_t(70.f, 70.f, 50.f, 40.f);           
		vec2_t textPos = vec2_t(tempPos.y, tempPos.x);    
		vec4_t pos = vec4_t(70.f, 70.f, 100.f + textPos.x, 90.f); 

		std::string name = targethudlist[0]->getNameTag()->getText();
		std::string distance = "Distance: " + std::to_string((*targethudlist[0]->getPos()).dist(*g_Data.getLocalPlayer()->getPos()));

		DrawUtils::drawRectangle(pos, MC_Color(0, 255, 0), 1);
		DrawUtils::fillRectangle(pos, MC_Color(0, 0, 0), 1.f);
		DrawUtils::drawText(textPos, &name, MC_Color(255, 255, 255), 1.f);
		textPos.y += 10.f;
		DrawUtils::drawText(textPos, &distance, MC_Color(255, 255, 255), 1.f);
	}
}
//doesnt work fuckkkkkkkkkkkkkkkkk 