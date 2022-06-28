#include "Anchor.h"

Anchor::Anchor() : IModule(0x0, Category::MOVEMENT, "Stops Movement Over Holes") {
	registerBoolSetting("Obsidian", &this->oby, this->oby);
	registerBoolSetting("Bedrock Hole", &this->bedrock, this->bedrock);
}

Anchor::~Anchor() {
}

const char* Anchor::getModuleName() {
	return ("Anchor");
}
void Anchor::onTick(C_GameMode* gm) {
	vec3_ti bestPos;
	if (!(g_Data.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
		if (g_Data.isInGame()) {
			// Odelay++;
			// if (Odelay > delay * 20) {
			vec3_t* pos = g_Data.getLocalPlayer()->getPos();
			for (int x = (int)pos->x - range; x < pos->x + range; x++) {
				for (int z = (int)pos->z - range; z < pos->z + range; z++) {
					for (int y = (int)pos->y - range; y < pos->y + range; y++) {
						vec3_t blockPos = vec3_t(x, y - 1, z);
						vec3_t blockPos2 = vec3_t(x + 1, y - 1, z);
						vec3_t blockPos3 = vec3_t(x, y - 1, z + 1);
						vec3_t blockPos4 = vec3_t(x, y - 2, z);
						vec3_t blockPos5 = vec3_t(x - 1, y - 1, z);
						vec3_t blockPos6 = vec3_t(x, y - 1, z - 1);

						C_Block* block = g_Data.getLocalPlayer()->region->getBlock(blockPos);
						C_Block* block2 = g_Data.getLocalPlayer()->region->getBlock(blockPos2);
						C_Block* block3 = g_Data.getLocalPlayer()->region->getBlock(blockPos3);
						C_Block* block4 = g_Data.getLocalPlayer()->region->getBlock(blockPos4);
						C_Block* block5 = g_Data.getLocalPlayer()->region->getBlock(blockPos5);
						C_Block* block6 = g_Data.getLocalPlayer()->region->getBlock(blockPos6);

						if (block != nullptr && block2 != nullptr && block3 != nullptr && block4 != nullptr) {
							int blockId = block->toLegacy()->blockId;
							int blockId2 = block2->toLegacy()->blockId;
							int blockId3 = block3->toLegacy()->blockId;
							int blockId4 = block4->toLegacy()->blockId;
							int blockId5 = block5->toLegacy()->blockId;
							int blockId6 = block6->toLegacy()->blockId;

							if (oby) {
								if (gm->player->onGround && !gm->player->isInWater()) {
									if ((blockId2 == 49 && blockId3 == 49 && blockId4 == 49 && blockId5 == 49 && blockId6 == 49 && blockId == 0)) {
										gm->player->velocity.y = -1.f;
									}
									if (bedrock) {
										if (gm->player->onGround && !gm->player->isInWater()) {
											if ((blockId2 == 7 && blockId3 == 7 && blockId4 == 7 && blockId5 == 7 && blockId6 == 7 && blockId == 0))
												gm->player->velocity.y = -1.f;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
void Anchor::onMove(C_MoveInputHandler* input) {
	C_LocalPlayer* player = g_Data.getLocalPlayer();
	vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
	bool pressed = moveVec2d.magnitude() > 0.01f;
	if (!pressed) {
		player->velocity.x = 0;
		player->velocity.z = 0;
	}
};