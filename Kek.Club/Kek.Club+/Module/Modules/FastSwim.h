#pragma once
#include "Module.h"

class FastSwim : public IModule {
public:
	float waterHorizontal; 
	float waterVertical;
	float lavaHorizontal; 
	float lavaVertical;
	FastSwim();
	~FastSwim();

	virtual const char* getModuleName() override;
	virtual void onMove(C_MoveInputHandler* input) override;
};