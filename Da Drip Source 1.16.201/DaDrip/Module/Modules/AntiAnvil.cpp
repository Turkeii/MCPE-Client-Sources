#include "AntiAnvil.h"

void AntiAnvil::onTick(C_GameMode* gm) {
	/*
	std::vector<vec3_ti> checklist;

	AABB aabb = gm->player->aabb.expandedXZ(-0.01f);
	if (oldY > -1000.f && noclipTick > 0)
		aabb.upper.y = aabb.lower.y + oldY;

	vec3_ti lower(aabb.lower.floor());
	vec3_ti upper(aabb.upper.floor());
	upper.y = lower.y;

	for (int x = lower.x; x <= upper.x; x++) {
		for (int z = lower.z; z <= upper.z; z++) {
			checklist.push_back(vec3_ti(x, 0, z));
		}
	}

	// Check 1: Is there a falling anvil above us?
	{
		std::vector<C_Entity*> fallingSandEnts;

		g_Data.forEachEntity([&](C_Entity* ent, bool) {
			if (ent->getEntityTypeId() != 66)
				return;

			vec3_ti block = ent->getPos()->floor();

			bool valid = false;
			for (auto& i : checklist) {
				if (i.x == block.x && i.z == block.z)
					valid = true;
			}

			if (!valid)
				return;

			if (block.y < (int)floorf(aabb.lower.y))
				return;

			if (block.y - (int)floorf(aabb.lower.y) > 4)  // It probably won't hit us before we can noclip
				return;

			fallingSandEnts.push_back(ent);
		});

		if (!fallingSandEnts.empty()) {
			if (noclipTick < 0) {
				oldY = aabb.upper.y - aabb.lower.y;
			}
			noclipTick = 6;
		}
	}

	// Check 2: Is there an anvil inside of us?
	bool isThereBlock = false;
	for (auto& i : checklist) {
		for (int y = (int)floorf(aabb.lower.y); y < (int)ceilf(aabb.upper.y); y++) {
			vec3_ti block(i.x, y, i.z);

			C_Material* mat = gm->player->region->getBlock(block)->blockLegacy->material;

			if (mat->isSolid && mat->isAlwaysDestroyable) {
				isThereBlock = true;
			}
		}
	}

	if (isThereBlock) {
		if (noclipTick < 0) {
			oldY = aabb.upper.y - aabb.lower.y;
		}
		noclipTick = 6;
	}

	if (noclipTick > 0) {
		gm->player->aabb.upper.y = -1.f;
		gm->player->velocity.y = 0.f;
		noclipTick--;
	} else {
		noclipTick = -1;
		if (oldY > -1000.f) {
			gm->player->aabb.upper.y = gm->player->aabb.lower.y + oldY;
			oldY = -1000.f;
		}
	}
	*/
}

void AntiAnvil::onDisable() {
	/*
	if (noclipTick > 0) {
		if (g_Data.getLocalPlayer() != nullptr && oldY > -1000.f) {
			g_Data.getLocalPlayer()->aabb.upper.y = g_Data.getLocalPlayer()->aabb.lower.y + oldY;
		}
		noclipTick = -1;
		oldY = -1000.f;
	}
	*/
}
