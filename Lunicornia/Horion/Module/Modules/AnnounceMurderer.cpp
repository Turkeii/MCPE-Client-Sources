#include "AnnounceMurderer.h"

bool d;

void AnnounceMurderer::onTick(C_GameMode*)
{
	d = this->doesPublicAnnounce;
	g_Data.forEachEntity([](Entity e, bool)
	{
		DrawUtils::drawText(vec2_t(5.f, 20.f), new std::string(e->getNameTag()->getText()), new MC_Color(1.f, 0.1f, 0.1f, 1.f));

		if (Player p = dynamic_cast<Player>(e))
		{
			C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
			C_Inventory* a = supplies->inventory;
			for (int i = 0; i < 36; i++) 
			{
				Item* test = a->getItemStack(i)->item;
				if (test != NULL)
					if ((*test)->itemId == IRON_SWORD)
						if (d)
							g_Data.getGuiData()->displayClientMessage(new std::string("Public Announce Not Implimented!"));
						else
							DrawUtils::drawText(vec2_t(5.f, 20.f), new std::string(p->getNameTag()->getText()), new MC_Color(1.f, 0.1f, 0.1f, 1.f));
			}
		}
	});
}

const char* AnnounceMurderer::getModuleName()
{
	return ("AnnounceMurderer");
}

AnnounceMurderer::AnnounceMurderer()
	: IModule(0x0, Category::EXPLOITS, "Announces the murderer on MM games.")
{
	this->registerBoolSetting("Public Announce", &this->doesPublicAnnounce, false);
}