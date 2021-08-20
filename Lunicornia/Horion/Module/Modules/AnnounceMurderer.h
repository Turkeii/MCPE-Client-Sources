#pragma once
#include "Module.h"
#include "../../DrawUtils.h"

class AnnounceMurderer : public IModule
{
public:
	AnnounceMurderer();
	~AnnounceMurderer() {};

	void onTick(C_GameMode*) override;

	const char* getModuleName() override;

	bool doesPublicAnnounce;
};

