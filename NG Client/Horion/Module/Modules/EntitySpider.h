#pragma once
#include "Module.h"
class EntitySpider : public IModule {
public:
	float speed = 0.6f;
	bool dontOvershoot = true;

	EntitySpider();
	~EntitySpider();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onMove(C_MoveInputHandler* input) override;
};
