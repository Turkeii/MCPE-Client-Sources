#pragma once
#include "../Module.h"



extern class FreeLook* freelookmod;

class FreeLook : public Module {
public:
	FreeLook();

	bool toggle = false;
	bool noPerspectiveChange = false;

	int8_t* cameraPerpective = 0;

	virtual void onEnable() override;
	virtual void onDisable() override;


};


//this is such a trash solution :(

class PlayerCameraUpdateHeadRotationHook1 : public Hook {
public:
	virtual void init() override;
};
class PlayerCameraUpdateHeadRotationHook2 : public Hook {
public:
	virtual void init() override;
};
