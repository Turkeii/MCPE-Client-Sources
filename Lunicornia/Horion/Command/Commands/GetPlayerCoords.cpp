#include "GetPlayerCoords.h"

GetPlayerCoords::GetPlayerCoords()
	: IMCCommand("gpc", "Gets coords of a player", "<NAME>")
{

}

GetPlayerCoords::~GetPlayerCoords()
{

}

bool GetPlayerCoords::execute(std::vector<std::string>* args)
{
	assertTrue(g_Data.getClientInstance()->getLocalPlayer() != nullptr);
	assertTrue(args->size() == 1);

	static auto tArgs = args;
	static auto _this = this;

	g_Data.forEachEntity([](C_Entity* e, bool)
		{
			if (std::string(e->getNameTag()->getText()) == (*tArgs)[0])
			{
				static auto p = e->getPos();
				_this->clientMessageF("%s, %s, %s", p->x, p->y, p->z);
			}
		});

	return true;
}
