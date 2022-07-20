#include "Excavator.h"

Excavator::Excavator() : IModule(0x0, Category::WORLD, "Excavates blocks around you") {
	this->registerBoolSetting("Show Range", &this->radius, this->radius);
	this->registerIntSetting("Red", &this->customR, this->customR, 0, 255);
	this->registerIntSetting("Green", &this->customG, this->customG, 0, 255);
	this->registerIntSetting("Blue", &this->customB, this->customB, 0, 255);
	this->registerBoolSetting("Dont Mine Ores", &this->ores, this->ores);
	registerIntSetting("Range", &this->range, this->range, 1, 6);
	registerIntSetting("Height +", &this->up, this->up, 1, 6);
	registerIntSetting("Height -", &this->down, this->down, 1, 6);

}

Excavator::~Excavator() {
}

const char* Excavator::getModuleName() {
	return ("Excavator");
}

void Excavator::onTick(C_GameMode* gm) {
	if (!ores) {
		vec3_t* pos = gm->player->getPos();
		for (int x = (int)pos->x - range; x < pos->x + range; x++) {
			for (int z = (int)pos->z - range; z < pos->z + range; z++) {
				for (int y = (int)pos->y - down; y < pos->y + up; y++) {
					vec3_ti blockPos = vec3_ti(x, y, z);
						gm->destroyBlock(&blockPos, 1);
				}
			}
		}
	} else {
		vec3_t* pos = gm->player->getPos();
		for (int x = (int)pos->x - range; x < pos->x + range; x++) {
			for (int z = (int)pos->z - range; z < pos->z + range; z++) {
				for (int y = (int)pos->y - down; y < pos->y + up; y++) {
					vec3_ti blockPos = vec3_ti(x, y, z);
					bool destroy = true;
					int id = gm->player->region->getBlock(blockPos)->toLegacy()->blockId;
					
					if (id == 7 || id == 56 || id == 129 || id == 14 || id == 73 || id == 74 || id == 21 || id == 15 || id == 16 || id == 526 || id == 536 || id == 153 || id == 543 && this->ores) destroy = false;

					if (destroy) {
							gm->destroyBlock(&blockPos, 1);
					}
				}
			}
		}
	}
}

void Excavator::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	if (radius) {
		vec3_t* pos = g_Data.getLocalPlayer()->getPos();
		for (int x = (int)pos->x - range; x < pos->x + range; x++) {
			for (int z = (int)pos->z - range; z < pos->z + range; z++) {
				for (int y = (int)pos->y - down; y < pos->y + up; y++) {
					vec3_t blockPos = vec3_t(x, y, z);

					C_Block* block = g_Data.getLocalPlayer()->region->getBlock(blockPos);
					C_BlockLegacy* blockLegacy = (block->blockLegacy);
					bool render = true;

						if (render) {
						static auto EcavatorMod = moduleMgr->getModule<Excavator>();
						DrawUtils::setColor(((float)EcavatorMod->customR / (float)255), ((float)EcavatorMod->customG / (float)255), ((float)EcavatorMod->customB / (float)255), (float)fmax(0.1f, (float)fmin(1.f, 15)));
							DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), 0.4f);
						}
					}
				}
			}
		}
	}