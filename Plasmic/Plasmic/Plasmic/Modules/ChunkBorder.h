#pragma once
#include "../Module.h"


class ChunkBorder : public Module {
public:

	ChunkBorder() : Module("Chunk Border", 0, mltext("Shows a line on the blocks which are at the chunk borders.\nOnly works in worlds or when you are in creative.", "Montre une ligne dans le sol la ou sont les bordures\nFonctione uniquement si vous etes dans un monde ou en creatif.")) {


	}

	virtual void onTick(Gamemode* gm) override {
		assertLocalPlayer;

		if (game::minecraftGame->networkHandler->raknetInstance->isonaServer() == true)
			if (game::localPlayer->gamemode != 1) {
				Disable();
				ClickGui::sendNotificationf(mltext("You can only die use %s in a world or when you are in creative.", "Vous pouvez utiliser %s seulement dans les mondes ou quand vous etes en creatif."), name);
			}
	}

};