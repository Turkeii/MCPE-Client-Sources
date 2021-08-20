#pragma once
#include "../Module.h"


class SyncRainbow : public Command {
public:

	SyncRainbow() : Command("syncrainbow", "Will sync the rainbow color of every color") {}

	virtual void execute(const char* args) override {

		for (uint16_t i = 0; i < ClickguiColor::colors.size(); i++) 
			if (ClickguiColor::colors[i] != nullptr && ClickguiColor::colors[i]->isRGB == true) {
				ClickguiColor::colors[i]->color.r = 1.f;
				ClickguiColor::colors[i]->color.g = 0.f;
				ClickguiColor::colors[i]->color.b = 0.f;
			}
		game::sendClientChat("§§l§§dR§§bA§§aI§§6N§§cB§§2O§§9W §§rSynced!");
	}

};