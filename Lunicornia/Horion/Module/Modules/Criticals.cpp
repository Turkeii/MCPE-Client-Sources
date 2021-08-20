#include "Criticals.h"

Criticals::Criticals() : IModule(0x0, Category::COMBAT, "Each hit is a critical hit")
{
}


Criticals::~Criticals()
{
}

const char* Criticals::getModuleName()
{
	return ("Criticals");
}

void Criticals::onSendPacket(C_Packet* packet)
{
	/*bool cond = false;
	if (auto p = g_Data.getLocalPlayer())
		cond = !p->onGround;
	if (packet->isInstanceOf<C_MovePlayerPacket>() && cond)
	{
		C_MovePlayerPacket* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
		movePacket->onGround = false;
	}*/
	
}